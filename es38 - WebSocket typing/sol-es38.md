**DOMANDA:**
Esercizio 5
Modificare il sorgente del codice per fare in modo che ad ogni utente connesso
alla chat arrivi nella console il
messaggio “l‘utente sta scrivendo...” .
NOTA: Lato client, bisogna spedire al server un evento apposito (ad es.
“typing”) quando l’utente scrive sulla
tastiera (catturando l’evento di sistema “keydown”). Lato server, la chiamata
webSocket.broadcast.emit(‘typing’,
data) rilancia l’evento “typing” a tutti i client connessi tranne che a quello
dalla quale si è ricevuto il messaggio.
Lato client occorre infine gestire la ricezione del messaggio “typing” che
arriva dal server (vedere gestione del
messaggio “UploadChat”).


**Risposta:**






Esercizio 38 - Segnalazione "l'utente sta scrivendo..."

Modifiche effettuate al codice sorgente:

1. Lato Client (public/chat.js):
   - È stato aggiunto un listener ('keydown') sull'input testuale per intercettare la pressione dei tasti. Quando l'utente digita, viene emesso un evento 'typing' inviando al server il nome del mittente:
     message.addEventListener('keydown', function(){
         webSocket.emit('typing', sender.value);
     });
   - È stato aggiunto un listener per gestire l'evento 'typing' in arrivo dal server. Per evitare che il messaggio sovrascriva eventuali altri utenti che stanno digitando contemporaneamente, viene verificato se la stringa è già presente nel div "feedback" e, se non lo è, viene aggiunta (accodata) e viene scritto un log nella console:
     webSocket.on('typing', function(data){
         if (feedback.innerHTML.indexOf(data + ' sta scrivendo') === -1) {
             feedback.innerHTML += '<p><em>' + data + ' sta scrivendo...</em></p>';
             console.log(data + " sta scrivendo...");
         }
     });
   **(Nota:** L'evento 'UploadChat' preesistente pulisce già il div "feedback" azzerandone il contenuto quando un messaggio viene effettivamente inviato, rimuovendo quindi la scritta "sta scrivendo...").

2. Lato Server (server.js):
   - È stata aggiunta la gestione dell'evento 'typing'. Quando il server lo riceve, usa la funzione "broadcast" per re-inviare lo stesso evento a tutti gli altri client connessi, escludendo il client mittente:
     webSocket.on('typing', function(data){
         webSocket.broadcast.emit('typing', data);
     });
