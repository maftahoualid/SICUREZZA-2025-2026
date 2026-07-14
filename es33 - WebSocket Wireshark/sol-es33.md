**DOMANDA**
Esercizio 0
Effettuare una cattura Wireshark relativa al funzionamento della chat. Occorre
attivare la cattura prima di aprire la
URL dalla finestra del browser e ascoltare non solo sull’interfaccia di loopback
ma anche su quella verso l’esterno
(opzione ANY).

**Risposta:**






**Soluzione Esercizio 0:** Cattura Wireshark del funzionamento della chat

Operazioni Preliminari:
Ho creato la cartella dell'esercizio (`es33 - WebSocket Esercizio 0`) e vi ho copiato dentro tutto il codice sorgente del progetto "11 WebSocket_Chat".

Analisi della cattura Wireshark:
Avviando una cattura di rete sull'interfaccia "ANY" (o di loopback `lo` se testiamo tutto in locale) e filtrando per la porta del nostro server (es. `tcp.port == 4000`), aprendo il browser e mandando un messaggio in chat si assisterà a una precisa sequenza di eventi di rete che dimostra il funzionamento e il passaggio da `HTTP` a WebSocket.

Ecco cosa si vede passo per passo nei pacchetti:

1. FASE `HTTP` (Recupero File Statici)
- Inizialmente si vedrà il classico "3-way handshake" del `TCP` (SYN, SYN-ACK, ACK) per stabilire la connessione con la porta 4000 del server Node.js.
- Il browser invia una ``HTTP` GET /` per richiedere la pagina principale.
- Il server Express risponde con un ``HTTP`/1.1 200 OK` che contiene il codice HTML della pagina.
- Subito dopo, il browser invierà altre richieste ``HTTP` GET` per scaricare i file statici referenziati nell'HTML (come `/chat.js` e `/styles.css`).

2. FASE DI UPGRADE (Il passaggio a WebSocket)
- Il client (grazie all'istruzione `io.connect()` nel file JavaScript) inizializzerà una richiesta speciale verso il server. Nello specifico, invierà una richiesta ``HTTP` GET` contenente degli header molto particolari:
  **`Connection:** Upgrade`
  **`Upgrade:** websocket`
  **`Sec-WebSocket-Key:** [chiave casuale]`
- Se il server supporta WebSocket (come nel nostro caso grazie a Socket.IO), risponderà al browser con un pacchetto speciale: ``HTTP`/1.1 101 Switching Protocols`.
- Negli header della risposta 101, il server confermerà l'avvenuto "cambio di lingua" ri-dichiarando `Upgrade: websocket` e rispondendo alla chiave di sicurezza.

3. FASE WEBSOCKET (Comunicazione Bidirezionale in Real-Time)
- Da questo momento in poi (dopo il pacchetto 101), Wireshark smetterà di classificare la conversazione come "`HTTP`". I pacchetti successivi sulla stessa connessione `TCP` saranno etichettati col protocollo "WebSocket".
- Quando l'utente preme il bottone per inviare un messaggio nella chat, Wireshark mostrerà un pacchetto "WebSocket Text Frame".
- Poiché la comunicazione non è cifrata (non stiamo usando WSS ma semplice WS), cliccando sul payload del pacchetto in Wireshark sarà possibile leggere in chiaro il messaggio inviato.
- Essendo mediato dalla libreria Socket.IO, il testo nel payload apparirà con un piccolo prefisso numerico usato dal protocollo interno della libreria, seguito dal nostro oggetto JSON. Ad esempio:
  `42["message", {"sender":"Mario", "message":"Ciao a tutti!"}]`
- Subito dopo, si vedranno pacchetti WebSocket simili in direzione opposta (Server -> Client) che rappresentano il "broadcasting" dell'evento `UploadChat` verso gli altri client connessi per aggiornare le loro interfacce.

Conclusione:
**La cattura dimostra visivamente il più grande vantaggio dei WebSocket:** al contrario del polling `HTTP`, non c'è bisogno di instaurare continuamente nuove connessioni o inviare pesanti Header `HTTP` per ogni singolo messaggio. Una volta effettuato l'handshake e l'Upgrade (101 Switching Protocols), il tunnel `TCP` resta permanentemente aperto e i messaggi viaggiano al suo interno come frame leggerissimi e a bassissima latenza.
