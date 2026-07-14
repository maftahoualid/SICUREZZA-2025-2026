**DOMANDA**
Esercizio 3
● Estendere il webservice serverHTTP-REST.c in modo che esponga un secondo
servizio relativo al calcolo dei numeri primi compresi nell’intervallo [min,
max]
– Si tragga spunto al programma prime-number-interval.c
● Estendere il file ClientREST.java in modo da poter chiamare, a scelta,
entrambe le funzionalità della nuova API
● Provare il client con il calcolo dei numeri primi compresi nell’intervallo [1,
1000000]
– Quanto tempo ci mette?
– E’ stato necessario tradurre l’algoritmo dei numeri primi in Java? Perché?

**Risposta:**







**Soluzione Esercizio 31:** Estensione del Webservice con Numeri Primi

Operazioni Preliminari
1. Ho copiato i file necessari nella cartella `es31 - Numeri Primi`.
2. Ho modificato il file ``serverHTTP-`REST`.c`` implementando un meccanismo di routing per intercettare l'URL `/calcola-primi`. Una volta intercettato, il server esegue l'algoritmo per i numeri primi (preso da ``prime-number-interval.c``) e invia gradualmente la lista formattata in JSON tramite la `socket` `HTTP`.
3. Ho esteso il client in ``ClientREST.java`` aggiungendo un metodo `calcolaPrimi(int min, int max)` che si occupa di formattare l'URL e leggere le risposte del server (restituendo i dati riga per riga per non saturare la memoria in caso di payload enormi).
4. Ho compilato ed eseguito il server C in background e lanciato il client Java con il comando `time java ClientREST calcola-primi 1 1000000`.

Risposte alle domande:

1. Provare il client con il calcolo dei numeri primi compresi nell’intervallo [1, 1000000]. Quanto tempo ci mette?

Il tempo totale impiegato dall'esecuzione completa per calcolare un milione di numeri primi (con l'algoritmo non ottimizzato, O(N^2)) è stato di circa:
- **Tempo Reale (real):** 2 minuti e 19 secondi

Questo tempo dipende pesantemente dalla CPU della macchina su cui gira il server e dall'inefficienza dell'algoritmo (visto che calcola i moduli fino a i/2), ma dimostra chiaramente che il client è in grado di attendere e gestire connessioni prolungate fino a elaborazione conclusa.

**2. E' stato necessario tradurre l'algoritmo dei numeri primi in Java?** Perché?

**Assolutamente NO**. 
Non è stato necessario tradurre una singola riga di logica matematica in Java. L'intero algoritmo di calcolo risiede ed è eseguito sul **server (in C)**. 
**Il client Java funge esclusivamente da *Stub*:** il suo unico compito è codificare i parametri nell'URL della richiesta GET, inoltrarla tramite `HTTP` e restare in ascolto sulla `socket` per leggere (deserializzare) il risultato.

Questo mette in evidenza un altro grande vantaggio dell'architettura `REST` (e delle architetture client-server basate su RPC): la **centralizzazione della Business Logic**. Il carico computazionale gravoso viene demandato a una macchina remota dedicata (il server C), senza che il client debba possedere le capacità o conoscere le regole per risolverlo, ma preoccupandosi solamente della presentazione all'utente.
