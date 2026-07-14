**DOMANDA:**
4) Sostituire “127.0.0.1” prima con “localhost” e poi con “pippo” e osservare
cosa succede

**Risposta:**







Ecco cosa succede se nel file `clientUDP.c` modifichiamo l'indirizzo di destinazione (attualmente "127.0.0.1") all'interno della chiamata a `UDPSend`:

**Sostituendo con "localhost":** Non si osserva alcun cambiamento nel comportamento del programma. Il client e il server continueranno a comunicare correttamente. Questo accade perché la funzione di rete utilizzata sotto il cofano dalla libreria (gethostbyname()) interroga il sistema di risoluzione dei nomi (DNS locale o file /etc/hosts). Il nome "localhost" viene risolto automaticamente nell'indirizzo `IP` di loopback 127.0.0.1. Di conseguenza, i pacchetti arrivano a destinazione allo stesso identico modo.

**Sostituendo con "pippo":** Il client terminerà l'esecuzione con un errore (probabilmente in modo silenzioso o stampando un codice di errore, a seconda di come è gestita la libreria) prima di inviare il messaggio. Questo avviene perché la funzione gethostbyname("pippo") tenterà di risolvere l'hostname "pippo" in un indirizzo `IP`, ma fallirà (poiché "pippo" non è un nome noto nella rete locale, a meno di non averlo configurato manualmente nel file /etc/hosts). Andando a ispezionare la libreria `network.c`, si può notare che quando la risoluzione fallisce, la funzione `UDPSend` esegue una exit(ERRHOST) terminando brutalmente il processo. Il server, di conseguenza, rimarrà in perenne attesa del messaggio.