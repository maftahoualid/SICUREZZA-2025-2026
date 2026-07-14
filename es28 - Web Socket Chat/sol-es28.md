**DOMANDA:**
Esercizio su Web Socket
● Realizzazione di una chat eseguita dentro un browser web
– Fare riferimento al materiale apposito condiviso con gli studenti

**Risposta:**






**Soluzione Esercizio 28:** Web Socket Chat

Operazioni Preliminari
Ho copiato l'intera cartella `WebSocket_Chat` fornita nel materiale didattico all'interno della directory `es28 - Web Socket Chat`. Questo progetto non è scritto in C, bensì sfrutta Node.js e la libreria `Socket.IO` per fornire funzionalità Real-Time.

Analisi dell'Architettura
L'applicazione è composta da due parti fondamentali che comunicano tra loro:
1. Backend (Server in Node.js):
   - Il file `server.js` utilizza il framework `express` per avviare un server in ascolto sulla porta 4000.
   - La prima cosa che fa il server è servire i file statici (l'interfaccia utente) presenti nella cartella `public`.
   - Successivamente, aggancia a questo server il modulo ``socket`.io`. Da questo momento il server è in grado di accettare richieste di "Protocol Upgrade": quando un client lo richiede, la connessione `HTTP` standard viene promossa a connessione WebSocket (un tunnel `TCP` persistente e bidirezionale).
   - Quando il server riceve un evento chiamato `message` da un qualsiasi client, usa l'istruzione `io.sockets.emit('UploadChat', data)` per prendere quel messaggio e "spargere la voce" (Broadcast) ritrasmettendolo istantaneamente a TUTTI i client collegati.

2. Frontend (Client in Javascript):
   - All'interno di `public/chat.js`, il client apre una connessione WebSocket verso il server: `io.connect('http://localhost:4000')`.
   - Quando l'utente preme il tasto per inviare, il browser "emette" l'evento `message` verso il server.
   - Contestualmente, il browser si mette "in ascolto" di eventuali eventi `UploadChat` provenienti dal server. Appena ne riceve uno, il javascript manipola il DOM (aggiungendo codice HTML) per mostrare a schermo il nuovo messaggio ricevuto, aggiornando la chat in tempo reale senza dover ricaricare la pagina!

Comandi per testare la Chat:
\# Posizionati nella cartella
cd "es28 - Web Socket Chat"

\# Installa le dipendenze (se non sono già presenti nella cartella node_modules)
npm install

\# Avvia il server
node server.js

\# Ora apri il tuo browser preferito e apri DUE schede diverse puntandole a:
http://localhost:4000

\# Prova a scrivere un messaggio in una scheda e vedrai che comparirà magicamente in tempo reale anche sull'altra!
