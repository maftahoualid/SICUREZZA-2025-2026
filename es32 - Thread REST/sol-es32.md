**DOMANDA**
Esercizio finale
● Prendere in considerazione il file clientThreadREST.java
– Esso invoca calcolaSomma() in 3 thread concorrenti
– Però la macchina su cui gira il server chiamato è la stessa e quindi non ci
guadagno in prestazioni
– Come si potrebbe modificare il codice in modo che le 3 invocazioni finiscano
su 3 macchine diverse?
– Bisogna modificare anche il codice del server?
● Si riconsideri consideri il servizio che calcola i numeri primi
nell’intervallo [min, max] costruito nell’esercizio precedente
– Si trovi un modo efficiente, sfruttando diversi server in rete, per calcolare
il numeri primi tra 1 e 1000000
– Di quanto migliorano le prestazioni?
– Devo modificare anche il codice del server?

**Risposta:**








**Soluzione Esercizio 32:** Multithreading e Calcolo Parallelo Distribuito

Risposte alle domande:

1. Come si potrebbe modificare il codice (del client) in modo che le 3 invocazioni finiscano su 3 macchine diverse?
Basterebbe passare al costruttore `RESTAPI` (nel `main` di ``ClientThreadREST.java``) gli indirizzi `IP` delle 3 macchine reali invece di passare `127.0.0.1` fisso a tutti e tre. Esempio:
```java
RESTAPI service1 = new RESTAPI("192.168.1.10", args[0], args[1], args[2]);
RESTAPI service2 = new RESTAPI("192.168.1.11", args[0], args[1], args[2]);
RESTAPI service3 = new RESTAPI("192.168.1.12", args[0], args[1], args[2]);
```

2. Bisogna modificare anche il codice del server?
Se le macchine sono 3 host fisici o virtuali separati in rete, **NO**. Si può semplicemente copiare lo stesso eseguibile `serverHTTP-`REST`` identico (che ascolta sulla porta 8000) sulle 3 macchine e avviarlo. Avendo `IP` diversi, non ci saranno conflitti. 
*(Tuttavia, se volessimo simulare il cluster testandolo in locale sulla nostra singola macchina loopback `127.0.0.1`, dovremmo modificare una riga del server per permettergli di ascoltare su porte diverse, es. 8000, 8001, 8002, per evitare il classico errore di rete "Address already in use").*
Il server che abbiamo costruito all'esercizio 31 accetta già due parametri arbitrari `param1` e `param2` nell'URL per estrarre `min` e `max`. Basterà unicamente che il client Java formuli gli URL con i parametri opportuni frammentati. La bellezza dei Web Service `REST` è proprio questa: finché l'interfaccia/endpoint non varia, la scalabilità e le logiche di partizionamento applicativo si possono gestire senza toccare l'implementazione del servizio vero e proprio.

3. Si trovi un modo efficiente, sfruttando diversi server in rete, per calcolare i numeri primi tra 1 e 1000000.
Il calcolo dei numeri primi è un problema altamente parallelizzabile (definito in gergo *embarrassingly parallel*). Possiamo sfruttare i 3 thread del client per contattare i 3 server inviando a ciascuno un **sotto-intervallo** diverso da calcolare. Ad esempio, una ripartizione base potrebbe essere:
- ****Thread 1 (Server A)**:** invoca l'intervallo `[1, 333333]`
- ****Thread 2 (Server B)**:** invoca l'intervallo `[333334, 666666]`
- ****Thread 3 (Server C)**:** invoca l'intervallo `[666667, 1000000]`

4. Di quanto migliorano le prestazioni?
Essendo il carico diviso su 3 macchine distinte che calcolano in perfetta contemporanea, il tempo si abbasserà drasticamente, ma il guadagno reale dipenderà da come vengono scelti gli intervalli.

*L'importanza del bilanciamento del carico (Load Balancing):*
Poiché l'algoritmo C esegue un ciclo di divisioni fino a `i/2`, la sua complessità computazionale cresce in modo quadratico rispetto al valore dei numeri processati. Se usassimo la suddivisione lineare di base (333.333 elementi ciascuno), il Thread 3 (che calcola i numeri più alti) impiegherebbe molto più tempo del Thread 1, creando un "collo di bottiglia" che impedisce un miglioramento proporzionale.

**Ipotesi di partizionamento alternativo bilanciato (Ottimizzato):**
Per ottenere un bilanciamento perfetto in cui il carico (e quindi il tempo d'esecuzione) è identico per tutti e 3 i server, dobbiamo stringere gli intervalli man mano che i numeri si fanno più grandi. Sapendo che le operazioni totali per arrivare a N crescono proporzionalmente a N², per dividere il lavoro (N=1.000.000) in 3 porzioni equivalenti (ognuna contenente il 33% del numero totale di divisioni effettuate dalle CPU), si possono calcolare le soglie matematiche con la radice quadrata:
- ****Thread 1 (Server A)**:** invoca l'intervallo `[1, 577350]` *(gestisce la fetta più ampia di numeri, ma molto veloci da processare)*
- ****Thread 2 (Server B)**:** invoca l'intervallo `[577351, 816496]` *(fetta intermedia)*
- ****Thread 3 (Server C)**:** invoca l'intervallo `[816497, 1000000]` *(fetta più ristretta, compensando l'altissimo costo di processamento di numeri vicini al milione)*

Adottando questa ripartizione ponderata dal lato client, le 3 macchine finiranno di elaborare quasi nello stesso identico istante, sfruttando appieno il parallelismo e ottenendo l'ideale riduzione del tempo di elaborazione totale esattamente a 1/3 (il 33%)!

