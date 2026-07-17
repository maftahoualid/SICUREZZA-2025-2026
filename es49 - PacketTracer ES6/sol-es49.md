**DOMANDA 1:** Una volta introdotto il NAT come è possibile per un PC fuori dal NAT, accedere ad un PC dentro il NAT?

**DOMANDA 2:** Qual è il principale uso del NAT?

**DOMANDA 3:** Qual è la differenza tra NAT dal NAPT? ... E il “port forwarding”?

**DOMANDA 4:** Che cos'è e a cosa serve il “port triggering”?

**Risposte:**

1. Di base, un PC all'esterno del NAT non può avviare spontaneamente una connessione verso un PC all'interno della rete privata (invisibile all'esterno). Per renderlo possibile è necessario configurare regole specifiche sul router NAT, come il **Port Forwarding** (Static NAT / PAT), che mappa una porta pubblica specifica del router verso l'indirizzo IP e la porta privata del PC interno. In alternativa, si può inserire il PC interno in "DMZ" (esponendolo completamente all'esterno).

2. Il principale uso del NAT (Network Address Translation) è mitigare l'esaurimento degli indirizzi IPv4 pubblici. Permette a un'intera rete locale (con indirizzi privati non instradabili su Internet, come 192.168.x.x) di accedere a Internet utilizzando uno (o pochi) indirizzi IP pubblici forniti dall'ISP. Offre anche un blando livello di sicurezza "by design", nascondendo la struttura della rete interna dall'esterno.

3.
   - **NAT (Network Address Translation):** Traduce l'indirizzo IP locale in un indirizzo IP globale. Nel "Static NAT", la mappatura è 1 a 1 (un IP interno per un IP pubblico).
   - **NAPT (Network Address Port Translation / PAT):** Mappa più indirizzi IP privati verso un singolo indirizzo IP pubblico, discriminando le connessioni tramite le **porte** (sorgente/destinazione). È il NAT classico (Overload) usato nei router domestici.
   - **Port Forwarding:** È l'azione di reindirizzare le richieste in arrivo su una determinata porta dell'IP pubblico verso uno specifico indirizzo IP privato (e porta) all'interno della rete LAN (es. per ospitare un web server).

4. Il **Port Triggering** è una tecnica di NAT dinamico. Quando un PC interno alla LAN avvia una connessione verso l'esterno usando una certa porta ("trigger port"), il router apre automaticamente in ingresso una o più porte specifiche verso quel particolare PC. Risulta utile per applicazioni (es. vecchi giochi online o protocolli VoIP) che richiedono connessioni in ingresso su porte specifiche ma di cui non si conosce a priori a quale client locale andranno reindirizzate. Una volta che la connessione viene chiusa, le porte in ingresso vengono nuovamente bloccate per sicurezza.
