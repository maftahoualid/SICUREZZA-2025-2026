**DOMANDA:**
form-post.html
<!DOCTYPE html><html>
<body>
<h2>The method Attribute</h2>
<p>This form will be submitted using the GET method:</p>
<form action="/action" target="_blank" method="post">
<label for="fname">First name:</label><br>
<input type="text" id="fname" name="fname" value="John"><br>
<label for="lname">Last name:</label><br>
<input type="text" id="lname" name="lname" value="Doe"><br><br>
<input type="submit" value="Submit">
</form>
<p>After you submit, notice that the form values is visible in the address bar
of the new browser tab.</p>
</body>
</html>
---
Esercizio
● Eseguire il server web serverHTTP.c e con il browser preferito aprire il file
form-post.html
● Cosa si vede?
● Provare ad analizzare il contenuto della connessione TCP con Wireshark.
● Cosa si vede?

**Risposta:**








**Soluzione Esercizio 24:** Web form POST

Operazioni Preliminari
1. Sono stati nuovamente copiati i file base del server (`serverHTTP.c`) e creata la cartella per l'esercizio.
2. È stato creato il file "form-post.html" modificando l'URL di destinazione all'interno dell'attributo action, impostandolo a "http://127.0.0.1:8000/action" affinché punti al web server locale da noi lanciato. (Nota: Il testo pre-impostato all'interno del file HTML del professore conteneva un refuso, dicendo erroneamente che i valori sarebbero stati visibili nella barra degli indirizzi, ma essendo un POST questo non è vero!).

**Risposta alla Domanda 1:** "Cosa si vede (sul browser)?"
Dopo aver cliccato il pulsante "Submit", il browser naviga verso la pagina di destinazione (restituendo il consueto messaggio "Hello World").
La differenza fondamentale rispetto all'esercizio precedente è nella BARRA DEGLI INDIRIZZI: questa volta l'URL si presenterà "pulito", mostrando esclusivamente `http://127.0.0.1:8000/action`. 
Nessun dato (nome e cognome) viene appeso all'URL, i parametri sono completamente invisibili.

**Risposta alla Domanda 2:** "Cosa si vede (analizzando il `TCP` con Wireshark)?"
Catturando la connessione su Wireshark (o analizzando l'output che viene stampato sul terminale dal nostro server C), notiamo la struttura della richiesta `HTTP` POST:

POST /action `HTTP`/1.1
**Host:** localhost:8000
**User-Agent:** ...
**Content-Length:** 20
**Content-Type:** application/x-www-form-urlencoded

fname=John&lname=Doe

A differenza del GET, qui possiamo vedere:
1. Il metodo `HTTP` è cambiato in `POST`.
2. I parametri (`fname=John&lname=Doe`) non sono più nella prima riga dell'URI, ma si trovano isolati all'interno del "Corpo" (Body/Payload) della richiesta, separati dalle intestazioni tramite una riga vuota.
3. Proprio a causa della presenza del Body, il client (il browser) ha dovuto specificare al server la dimensione in byte di quest'ultimo usando l'intestazione `Content-Length: 20` (che è il numero esatto di caratteri di "fname=John&lname=Doe") e il tipo di codifica `Content-Type: application/x-www-form-urlencoded`.

Guardando il codice ``serverHTTP.c``, si nota proprio la presenza di una logica "if(strcmp(method, "POST")==0)" che intercetta i POST e utilizza il valore catturato da "Content-Length" per capire quanti caratteri ("byte") leggere per poter estrapolare dal corpo della richiesta l'intero modulo compilato dall'utente.

Comandi Utili per Riprodurre l'Esercizio:
\# Compilare ed eseguire il server
`gcc` `serverHTTP.c` `network.c` -o serverHTTP
./serverHTTP

\# Per testare l'invio via terminale e simulare l'HTML form con metodo POST:
curl -v -d "fname=John&lname=Doe" "http://localhost:8000/action"

\# Wireshark (Filtrare per traffico `HTTP` sulla porta 8000 e guardare la stringa `TCP`):
`sudo` tshark -i lo -f "tcp port 8000" -z follow,tcp,ascii,0
