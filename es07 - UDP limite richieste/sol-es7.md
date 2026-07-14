**DOMANDA:**
7) Modificare il server in maniera che soddisfi 5 richieste prima di terminare
● E se volessi che non terminasse mai?

**Risposta:**










Ecco le risposte alle tue domande:

**Modificare il server per soddisfare 5 richieste prima di terminare:** Nel file `serverUDP.c`, ho sostituito il ciclo di ascolto infinito while(true) con un ciclo definito che itera esattamente 5 volte. Il codice del blocco di ascolto è diventato il seguente:

// Al posto di while(true)
for(int i = 0; i < 5; i++) {
    `printf`("[SERVER] Sono in attesa di richieste da qualche client\n");
    `UDPReceive`(`socket`, request, `MTU`, hostAddress, &port);
    // ... stampe ...
    `UDPSend`(`socket`, response, strlen(response), hostAddress, port);
}
// Dopo aver servito i 5 client, il programma esce dal loop e il main() termina.

**E se volessi che non terminasse mai?** Per avere un server che resta in ascolto perenne senza terminare mai (comportamento tipico dei server veri e propri, detti anche daemoni), si utilizza un ciclo infinito. Nel linguaggio C, questo si ottiene utilizzando costrutti condizionali perennemente verificati, come:
while(true) (utilizzato nella versione originale, richiede la libreria <`stdbool.h`>)
while(1) (costrutto tipico in C per indicare che la condizione non sarà mai 0)
for(;;) (ciclo for privo di condizioni di terminazione)
In questo modo il programma attenderà all'infinito un nuovo pacchetto sulla porta senza fermarsi mai, a meno che non venga interrotto forzatamente (es. chiudendo il terminale o premendo Ctrl+C).