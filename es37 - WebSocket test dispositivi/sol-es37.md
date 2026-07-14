**DOMANDA:**
Esercizio 4
Se si dispone di due PC in grado di dialogare sulla stessa rete IP (oppure un PC
per il server e uno smartphone per
il client sempre in grado di dialogare tra loro a livello IP) provare ad
accedere al server che è su Linux mediante
diversi tipi di browser e di sistemi operativi. Cosa si può notare?

**Risposta:**







Esercizio 37 - Test WebSocket da diversi dispositivi

Effettuando il test di accesso da vari dispositivi (come PC Windows, macOS, smartphone Android o iOS) e browser differenti (Chrome, Firefox, Safari, Edge, ecc.), si possono notare due aspetti principali:

**1. Interoperabilità e Standardizzazione:** L'applicazione funziona in modo identico e fluido su tutti i dispositivi e browser moderni senza necessità di installare software aggiuntivo o applicazioni dedicate sul client. Questo perché le WebSocket sono uno standard web nativamente supportato da tutti i principali browser e operano al di sopra del protocollo `HTTP`/`TCP`.
**2. Sincronizzazione in tempo reale (Real-time):** Qualsiasi messaggio inviato da uno dei dispositivi (ad esempio dallo smartphone) compare istantaneamente sugli schermi di tutti gli altri dispositivi collegati (ad esempio i PC), confermando che il server riesce a mantenere aperte le connessioni persistenti (full-duplex) con tutti i client simultaneamente e a fare broadcast degli eventi in tempo reale, indipendentemente dal sistema operativo o dal browser utilizzato.

**Nota operativa:** 
Perché l'accesso abbia successo, è fondamentale che i client nella rete locale conoscano l'indirizzo `IP` del server (es. 192.168.x.x) e che l'eventuale firewall sul server Linux (es. ufw o iptables) sia configurato per accettare connessioni in entrata sulla porta utilizzata dal server Node.js (es. porta 4000). Altrimenti la pagina non si caricherà.
