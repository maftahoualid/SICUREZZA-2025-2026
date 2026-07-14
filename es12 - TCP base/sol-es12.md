**DOMANDA:**
Esercizi su TCP
11) Lanciare due volte il server usando due terminali. Cosa si osserva?
Funzionano entrambi?

**Risposta:**


















Essendo ora passati agli esercizi su `TCP`, il comportamento del programma è differente rispetto al precedente caso `UDP`.

Lanciando due volte il server `TCP` (presente nella cartella es12) su due terminali, si osserva quanto segue:

**Il primo server funziona regolarmente:** si avvia, esegue il bind() e si mette in ascolto delle connessioni (`listen`()), stampando il messaggio di attesa a video.
Il secondo server NON funziona e termina immediatamente.
**Perché succede questo?** A differenza di quanto visto con `UDP`, nel protocollo `TCP` l'opzione del `socket` SO_REUSEADDR ha un significato più stringente: serve esclusivamente a consentire il riutilizzo di una porta che si trova in stato di "TIME_WAIT" (cioè una porta utilizzata da una connessione chiusa di recente dal sistema operativo). Tuttavia, SO_REUSEADDR non consente a due programmi di mettersi contemporaneamente in stato di ascolto attivo (`listen`) sulla medesima porta e `IP`. Di conseguenza, il tentativo di eseguire la bind() da parte del secondo server andrà incontro a un errore (del tipo Address already in use) e, come previsto dalla gestione degli errori all'interno della funzione createTCPServer nel file `network.c`, causerà la chiusura immediata (terminazione silente tramite exit()) del secondo programma.