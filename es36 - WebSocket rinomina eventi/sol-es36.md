**DOMANDA**
Esercizio 3
Modificare il sorgente del codice in modo da cambiare nome ai seguenti eventi
message → messaggio
UploadChat → aggiornamento



**Risposta:**




Esercizio 36 - Rinomina Eventi WebSocket

Modifiche effettuate al codice sorgente:

1. Lato Server (server.js):
   - Modificato l'evento in ascolto da 'message' a 'messaggio':
     webSocket.on('messaggio', function(data) { ... });
   - Modificato l'evento emesso in broadcast da 'UploadChat' a 'aggiornamento':
     io.sockets.emit('aggiornamento', data);

2. Lato Client (public/chat.js):
   - Modificato il nome dell'evento inviato al click del pulsante da 'message' a 'messaggio':
     webSocket.emit('messaggio', { ... });
   - Modificato il nome dell'evento in ascolto per ricevere i messaggi da 'UploadChat' a 'aggiornamento':
     webSocket.on('aggiornamento', function(data) { ... });
