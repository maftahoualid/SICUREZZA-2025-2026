**DOMANDA 1:** Cosa succede se, durante la configurazione del protocollo RIP per uno dei router, non inserisco una delle reti attestaste sul router stesso?

**DOMANDA 2:** Provate ad eseguire il comando tracert (traceroute) e verificate il percorso che viene fatto dai pacchetti.

**DOMANDA 3:** Cosa succede se uno dei collegamenti WAN va offline?

**Risposte:**

1. Se un router non ha dichiarata una specifica rete connessa al suo interno (usando il comando `network` sotto `router rip`), succedono due cose: 1) il router non invierà i propri aggiornamenti RIP (routing table) tramite quell'interfaccia; 2) il router non annuncerà agli altri router l'esistenza di quella specifica rete. Pertanto, quella rete risulterà irraggiungibile dall'esterno (gli altri dipartimenti non sapranno come arrivarci), sebbene i dispositivi al suo interno potranno continuare a comunicare tra loro localmente.

2. Il comando `tracert` (da un PC Windows nel simulatore) o `traceroute` (da terminale IOS/Linux) mostra i salti (hop) eseguiti a livello 3 (i gateway/router attraversati). Eseguendolo da un PC del Dipartimento 1 a un PC del Dipartimento 2, si vedrà prima l'IP del gateway locale (es. `192.168.0.1` o `192.168.1.1` su R1), successivamente l'IP dell'interfaccia seriale del router R2 (`10.0.0.2`), e infine l'IP di destinazione del PC finale.

3. Il protocollo RIP è un protocollo di routing dinamico. Se un collegamento seriale WAN va offline (ad esempio la seriale tra R1 e R2 cade), dopo un certo tempo di timeout, i router si aggiornano a vicenda segnalando che la tratta non è più disponibile. Se la rete è costruita ad anello (R1 connesso a R2, R2 a R3, R3 a R1), il router R1 scoprirà (tramite RIP da R3) che esiste un percorso alternativo per raggiungere R2: il traffico verrà re-instradato dinamicamente (routing convergence) passando attraverso R3. Ovviamente il percorso sarà più lungo (un hop in più), ma la comunicazione non si interromperà definitivamente.
