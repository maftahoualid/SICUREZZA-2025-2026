**DOMANDA**
Esempio di web server esteso con gestione CGI
● Aprire il file serverHTTP-CGI.c in Esempi-web/ e analizzarne il contenuto
● Compilarlo come al solito ed eseguirlo
● Aprire il browser preferito e il file sommatrice-web.html
– Cosa si vede sul browser?
– NOTA: Provare con numeri positivi, negativi, con parte decimale...
● A cosa corrisponde il secondo parametro della funzione sommatrice() ?

**Risposta:**






**Soluzione Esercizio 27:** Web server con gestione CGI

Operazioni Preliminari
Ho copiato i file ``serverHTTP-CGI.c`` e `sommatrice-web.html` nella nuova cartella dell'esercizio e ho compilato l'eseguibile del server C, per poi avviarlo.

Risposte alle domande:
1. Cosa si vede sul browser aprendo sommatrice-web.html?
Si presenta una semplice interfaccia (creata tramite Web Form) che richiede l'inserimento di "Operando 1" e "Operando 2", accompagnata dal pulsante "Somma". Inviando il modulo, il browser invia i dati inseriti appendendoli all'URL (es: `/sommatrice?op1=5.5&op2=-2.2`).
Provando a inviare numeri positivi, negativi o con la virgola (utilizzando il punto come separatore decimale), il server restituisce correttamente il risultato matematico elaborato (es. Risultato=3.300000).
Questo avviene perché il backend scritto in C utilizza la funzione `atof()`, la quale supporta nativamente il parsing delle stringhe contenenti segni negativi e punti decimali.

2. A cosa corrisponde il secondo parametro della funzione sommatrice()?
**Analizzando la firma della funzione:** `void sommatrice(char *url, FILE *out)`
Il parametro `FILE *out` corrisponde allo stream di output del `socket` `TCP`, ovvero la connessione aperta con il client (il browser). 
Se guardiamo il `main()`, notiamo che la funzione viene richiamata passando `connfd` (il file descriptor della connessione): `sommatrice(url, connfd);`.
**Questo meccanismo è l'essenza dell'interfaccia CGI (Common Gateway Interface):** il server "delega" l'elaborazione a un programma o funzione esterna, passandole i parametri e fornendole l'accesso diretto allo standard output della rete. Qualsiasi cosa la funzione `sommatrice` stampi tramite `fprintf(out, ...)`, andrà a finire dritta al browser (ecco perché la funzione si preoccupa di stampare lei stessa l'intestazione `HTTP` `200 OK` e i tag HTML).

Comandi utili:
\# Compila ed esegui
`gcc` `serverHTTP-CGI.c` `network.c` -o serverHTTP-CGI
./serverHTTP-CGI

\# Simula l'inserimento di numeri decimali e negativi (test)
curl -v "http://localhost:8000/sommatrice?op1=5.5&op2=-2.2"
