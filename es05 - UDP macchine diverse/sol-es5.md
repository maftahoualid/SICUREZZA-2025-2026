**DOMANDA:**
5) [Da fare solo se in Lab Delta] Accordarsi per lavorare su coppie di macchine
in modo che
server e client siano su macchine diverse. Come bisogna modificare i sorgenti?

**Risposta:**














Per far comunicare server e client posizionati su due macchine fisiche (o virtuali) diverse, l'unica modifica necessaria riguarda il client (`clientUDP.c`).

Ecco i dettagli:

**Modifica al Client (`clientUDP.c`):** Attualmente, la funzione `UDPSend` invia il pacchetto all'indirizzo "127.0.0.1", che rappresenta la macchina locale (loopback interface). Per raggiungere il server su una macchina differente, devi sostituire "127.0.0.1" con il reale indirizzo `IP` della macchina su cui sta girando il server (ad esempio "192.168.1.50", oppure il corrispondente hostname se la rete lo risolve).

// Prima:
`UDPSend`(`socket`, request, strlen(request), "127.0.0.1", 35000);
// Dopo (inserendo l'`IP` del PC del tuo collega/dell'altra macchina):
`UDPSend`(`socket`, request, strlen(request), "192.168.1.50", 35000);

**Nessuna modifica al Server (`serverUDP.c`):** Il sorgente del server non ha bisogno di essere toccato. Questo perché, se ispezioniamo la libreria `network.c`, la funzione `createUDPInterface` è progettata per configurare il `socket` (bind()) utilizzando la costante INADDR_ANY. Questo indica al sistema operativo di mettere il server in ascolto su tutte le interfacce di rete disponibili della macchina (sia quella locale 127.0.0.1 sia l'interfaccia esposta sulla rete LAN associata al suo `IP`). Pertanto, il server è già pronto a ricevere pacchetti provenienti dall'esterno.