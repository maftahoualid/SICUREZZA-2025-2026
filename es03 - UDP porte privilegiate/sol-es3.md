**DOMANDA:**
3) Mettere il server in ascolto sulla porta 100 e osservare cosa succede
● Bisogna modificare anche il client? Dove?
● Per chi usa il proprio PC con Linux o una virtual machine Linux, lanciare il
server con il comando “sudo ./serverUDP” e
osservare cosa cambia

**Risposta:**








Ecco le risposte alle tue domande:

- **Bisogna modificare anche il client?** Dove? Sì, è indispensabile modificare anche il client. Affinché il client riesca a contattare il server, deve inviare il messaggio alla porta corretta. Nel file `clientUDP.c` è necessario modificare il numero di porta di destinazione passato come ultimo argomento alla funzione `UDPSend` (portandolo da 10000 a 100). Nel codice aggiornato, questo si traduce nell'impostare la macro `SERVERPORT` a 100 anche per il client.

- Per chi usa il proprio PC con Linux... lanciare il server con "`sudo` ./serverUDP" e osservare cosa cambia Sui sistemi Linux (e Unix in generale), le porte di rete numerate da 0 a 1023 sono definite "privileged ports" (o well-known ports). Se tenti di eseguire ./serverUDP in ascolto sulla porta 100 come utente normale, il sistema operativo impedirà l'operazione. La funzione di sistema per riservare la porta (bind()) fallirà restituendo un errore di "Permission denied". Di conseguenza, il server non si avvierà. Utilizzando invece `sudo` ./serverUDP, il programma viene eseguito con i privilegi massimi (utente root), che possiede l'autorizzazione per vincolare i processi alle porte privilegiate (< 1024). In questo caso, il server si avvierà con successo e si metterà normalmente in ascolto sulla porta 100.