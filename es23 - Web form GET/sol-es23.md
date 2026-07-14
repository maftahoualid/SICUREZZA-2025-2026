**DOMANDA:**
form-get.html
<!DOCTYPE html><html>
<body>
<h2>The method Attribute</h2>
<p>This form will be submitted using the GET method:</p>
<form action="/action" target="_blank" method="get">
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
form-get.html
● Cosa si vede?
● Provare ad analizzare il contenuto della connessione TCP con Wireshark.
● Cosa si vede?

**Risposta:**











**Soluzione Esercizio 23:** Web form GET

Operazioni Preliminari
1. È stato copiato il server in linguaggio C e il codice HTML per il modulo web forniti dal professore.
2. Affinché l'invio del modulo comunichi effettivamente con il server in ascolto in locale, è necessario che il file HTML "form-get.html" punti al server giusto. Se il file viene aperto dal browser come file locale, il campo action="/action" andrebbe modificato in action="http://127.0.0.1:8000/action" (oppure http://localhost:8000/action).

**Risposta alla Domanda 1:** "Cosa si vede (sul browser)?"
Cliccando sul pulsante "Submit", il browser raccoglie i dati inseriti nei campi di input (fname e lname) e li appende direttamente all'URL di destinazione indicato nell'attributo "action", separandoli con il carattere "?" e unendo le varie coppie chiave-valore con la "&".
Nella barra degli indirizzi della nuova scheda che si apre vedremo quindi una stringa simile a questa:
http://127.0.0.1:8000/action?fname=John&lname=Doe

A schermo si vedrà la pagina statica HTML di cortesia ("Hello World...") restituita dal nostro `serverHTTP`.

**Risposta alla Domanda 2:** "Cosa si vede (analizzando il `TCP` con Wireshark)?"
Catturando il traffico sull'interfaccia di loopback, ad esempio tramite il comando:
`sudo` tshark -i lo -f "tcp port 8000" -Y "http" -V
oppure seguendo lo stream `TCP` nella GUI di Wireshark, si osserverà la richiesta `HTTP` in chiaro, che mostrerà quanto segue:

GET /action?fname=John&lname=Doe `HTTP`/1.1
**Host:** 127.0.0.1:8000
**User-Agent:** ...

- Si nota chiaramente che la particolarità del metodo GET per l'invio dei form consiste nel passare i parametri direttamente nell'URL (Request URI).
- Di conseguenza, NON è presente un corpo del messaggio (Body o payload aggiuntivo nella richiesta `HTTP`).
- Questo metodo espone i dati inseriti direttamente nel log delle richieste del server e nei log dei sistemi intermedi o cronologie del browser, rendendolo completamente inadatto al trasferimento di dati sensibili (come le password).

Comandi Utili per Riprodurre l'Esercizio:
\# Eseguire il server
./serverHTTP

\# Per testare l'invio via terminale e simulare il submit del form:
curl -v "http://127.0.0.1:8000/action?fname=John&lname=Doe"

\# Analizzare l'esatta richiesta arrivata usando TShark:
`sudo` tshark -i lo -f "tcp port 8000" -z follow,tcp,ascii,0
