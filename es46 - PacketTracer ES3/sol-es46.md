**DOMANDA 1:** Cosa succede al traffico broadcast di livello 2 (ad esempio, una richiesta ARP) inviato da un utente del gruppo docenti ? Quali utenti vedranno tale traffico?

**DOMANDA 2:** Cosa succede al traffico broadcast di livello 3 (ad esempio, una richiesta DHCP) inviato da un utente del gruppo docenti ? Quali utenti vedranno tale traffico?

**Risposta:**

Un broadcast di livello 2, come una richiesta ARP, viene confinato al dominio di broadcast, ovvero all'interno della stessa VLAN. Verrà inoltrato dallo switch a tutte le porte che appartengono alla VLAN dei docenti (VLAN 20) e attraverso le porte Trunk, per raggiungere gli altri switch della rete. Raggiungerà anche l'interfaccia del Router (sub-interface FastEthernet0/0.2) in quanto associata alla VLAN 20. Gli utenti della VLAN studenti (VLAN 10) non lo riceveranno.

Anche il traffico broadcast di livello 3 (come DHCPDISCOVER), essendo trasportato su pacchetti con indirizzo IP di destinazione broadcast (255.255.255.255), viene incapsulato in un frame broadcast di livello 2. Pertanto, sottostà alle stesse regole di isolamento delle VLAN: il broadcast rimarrà confinato all'interno della VLAN docenti. A differenza di uno switch, un router interrompe per definizione i domini di broadcast: il router riceverà la richiesta DHCP sull'interfaccia virtuale dedicata alla VLAN docenti, ma di default **non** la inoltrerà verso la VLAN studenti (a meno che non venga specificato un "IP helper-address" per configurare il DHCP Relay). Pertanto, tale traffico sarà visto solo dagli host e dalle interfacce router attestate sulla VLAN 20.
