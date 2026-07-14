**DOMANDA:**
Esercizio
● Modificare il file serverHTTP.c in modo che, invece di restituire sempre la
solita pagina web di prova, restituisca una delle pagine html usate dal lucido 9
in poi scelta attraverso l’uso del browser.
● Suggerimenti:
– Provare a fare la nuova richiesta col browser usando il serverHTTP.c in modo
da vedere la richiesta HTTP per capire dove si trova la stringa con il nome del
file nella richiesta che fa il browser (aiutarsi anche con Wireshark)
● Cosa devo scrivere nella barra del browser?
– Capire come recuperare la stringa con il nome del file dalla richiesta HTTP
(si veda esempio-parser.c)
– Per costruire la risposta riciclare parte del codice usato nell’esercizio del
trasferimento di file
● Prova finale: cosa succede se chiedo al server di restituire i file form-
get.html e form-post.html ?

**Risposta:**








**Soluzione Esercizio 25:** Web server e file dinamici (URL)

Operazioni Preliminari e Modifica del Codice
Per questo esercizio ho creato la cartella e ho modificato in modo sostanziale il file "`serverHTTP.c`":
1. Utilizzando la funzione `strtok` (come suggerito nel file `esempio-parser.c`), ho estratto la seconda parola della prima riga della richiesta `HTTP`, ovvero l'URI (es: "/prova.html").
2. Ho manipolato questa stringa per rimuovere lo slash "/" iniziale e ho inserito una logica che ripulisce la stringa da eventuali "Query String" (es. rimuovendo tutto ciò che c'è da un eventuale punto interrogativo "?" in poi).
3. Utilizzando la funzione `fopen`, il server tenta di aprire il file. Se il file esiste, invia prima di tutto gli Header di successo (``HTTP`/1.1 200 OK`) e poi, tramite un ciclo `fgetc`, legge e trasmette al client l'intero contenuto del file. Se il file non esiste, il server restituisce una pagina d'errore dinamica (``HTTP`/1.1 404 Not Found`).

**Risposta alla Domanda 1:** "Cosa devo scrivere nella barra del browser?"
Per poter richiedere una pagina specifica presente nella cartella Esempi-web (che abbiamo copiato all'interno dell'esercizio), è necessario digitare l'indirizzo base del server aggiungendo lo slash e il nome esatto del file.
**Ad esempio:** `http://localhost:8000/prova.html` oppure `http://localhost:8000/javascript.html`.

**Risposta alla Domanda 2:** "Cosa succede se chiedo al server di restituire i file form-get.html e form-post.html?"
Scrivendo l'indirizzo `http://localhost:8000/form-get.html`:
1. Il browser effettua una richiesta `HTTP` GET al nostro server C.
2. Il server C individua il file sul disco, ne legge il contenuto testuale (che è formato da tag `<form>`, `<input>`, ecc.) e lo rispedisce intatto al browser.
3. Il browser, ricevendo il file, lo **renderizza graficamente**, mostrando all'utente la classica maschera per inserire nome e cognome.
4. Se l'utente compila la form e preme il pulsante "Submit" (e l'azione della form è `action="/action"` come in originale), il browser avvierà autonomamente una **seconda** richiesta `HTTP` (`GET /action?fname=...`) verso il nostro server C. Poiché il file "action" non esiste, in questo caso il nostro server risponderà con un Errore 404 Not Found!

**Questo ci permette di capire a fondo come comunicano Front-end e Back-end:** il server prima serve l'interfaccia utente (HTML) su richiesta del client, e successivamente il client usa quell'interfaccia per inviare comandi (dati e parametri) allo stesso server.

Comandi Utili per testare l'Esercizio:
\# Compila ed esegui il server
`gcc` `serverHTTP.c` `network.c` -o serverHTTP
./serverHTTP

\# Richiedi la pagina prova.html da riga di comando per testarlo (oppure apri l'URL sul browser):
curl -v http://localhost:8000/prova.html
curl -v http://localhost:8000/`file_inesistente.txt`
