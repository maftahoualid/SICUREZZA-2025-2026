**DOMANDA**
Esercizio 2
Modificare il sorgente del codice in modo da far ascoltare il server sulla porta
80 invece che 4000. Quali altri
accorgimenti sono necessari per farlo funzionare: lato server? Lato client?

**Risposta:**








Esercizio 35 - WebSocket porta 80

Lato Server
In sistemi Unix-like (come Linux e macOS), le porte al di sotto della 1024 sono considerate porte "privilegiate" o "well-known". Per far sì che un programma possa mettersi in ascolto sulla porta 80, sono necessari permessi di amministratore. Di conseguenza, il comando per avviare il server non sarà più solamente "node server.js", ma dovrà essere eseguito con i privilegi di root, ad esempio:
`sudo` node server.js
(In alternativa, si possono concedere all'eseguibile di node le capabilities per fare bind su porte privilegiate usando: setcap cap_net_bind_service=+ep /path/to/node).

Lato Client
Dal punto di vista dell'utente finale, per connettersi alla chat non sarà più necessario specificare il numero di porta nell'URL del browser (la porta 80 è quella predefinita per il protocollo `HTTP`). L'indirizzo da visitare sarà semplicemente "http://localhost/" (oppure l'indirizzo `IP` del server).
Per quanto riguarda il codice JavaScript del client (public/chat.js), la chiamata per instaurare la connessione WebSocket è attualmente:
var webSocket = io.connect();
Poiché questa chiamata non specifica esplicitamente un host e una porta, la libreria `socket`.io utilizzerà automaticamente lo stesso host e la stessa porta da cui è stata scaricata la pagina HTML (ovvero la porta 80). Pertanto, non è necessario apportare alcuna modifica al codice lato client per farlo funzionare. Se invece il codice avesse utilizzato un URL hard-coded come "io.connect('http://localhost:4000')", sarebbe stato necessario modificarlo o rimuovere l'URL.
