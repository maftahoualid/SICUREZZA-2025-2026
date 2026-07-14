**DOMANDA:**
12) Scrivere la sommatrice usando TCP, compilare ed eseguire

**Risposta:**














Ho completato la scrittura della sommatrice basata su `TCP` operando sui file nella cartella es13 e li ho ricompilati.

Ecco nel dettaglio cosa ho modificato:

**Modifiche al Client (`clientTCP.c`):** Subito dopo aver instaurato la connessione logica (con createTCPConnection), ho inserito un ciclo do-while che continua a chiedere e acquisire un numero intero dall'utente (scanf), inviandolo immediatamente al server tramite TCPSend sul canale stabilito. Il ciclo termina quando l'utente digita lo 0. Dopodiché, il client si mette in attesa con TCPReceive e stampa a video la somma finale prima di chiudere la connessione.

**Modifiche al Server (`serverTCP.c`):** Subito dopo aver accettato la connessione (acceptConnection), ho introdotto la variabile int somma = 0;. Da quel momento il server entra in un ciclo do-while in cui usa TCPReceive per leggere i valori in arrivo dal "tubo" logico del client e li accumula nella variabile somma. Non appena arriva il valore 0, il server esce dal ciclo e utilizza la TCPSend per rispedire la somma totale al client. Al termine chiude la connessione.