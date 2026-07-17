**DOMANDA 1:** Nella semplice configurazione proposta ad ogni switch erano collegati sia utenti appartenenti al gruppo studenti che utenti del gruppo docenti:
- Non era più facile dedicare uno switch per il gruppo studenti e uno per il gruppo docenti?
- Perché ci interessa che sullo stesso switch ci possano essere gruppi diversi di utenti?

**DOMANDA 2:** Cosa succede al traffico broadcast di livello 2 (ad esempio, una richiesta ARP) inviato da un utente del gruppo docenti? Quali utenti vedranno tale traffico?

**Risposta:**

Dedicarne uno per gruppo sarebbe stato fisicamente più semplice per l'isolamento (reti fisiche separate), ma non scalabile e molto costoso, specialmente se i membri dei due gruppi sono sparsi nello stesso ufficio o piano. L'uso delle VLAN permette di separare logicamente i domini di broadcast utilizzando lo stesso hardware di rete fisico, riducendo i costi e aumentando la flessibilità organizzativa (se un utente cambia scrivania o stanza, basta riassegnare la VLAN della nuova porta senza spostare cavi o aggiungere nuovi switch dedicati).

Il traffico broadcast di livello 2 (come ARP) viene confinato al dominio di broadcast in cui viene generato, ovvero all'interno della singola VLAN. Quindi, una richiesta ARP inviata da un utente della VLAN 20 (docenti) verrà inoltrata dallo switch su tutte e sole le porte associate alla VLAN 20 (e attraverso le porte Trunk verso gli altri switch, che faranno lo stesso sulle loro porte della VLAN 20). Gli utenti della VLAN 10 (studenti) non vedranno affatto questo traffico.
