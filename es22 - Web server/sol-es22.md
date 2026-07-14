**DOMANDA**
Un semplice web server
● Aprire il file serverHTTP.c in Esempi-web/ e analizzarne il contenuto
● Compilarlo come nell’esercitazione sull’interfaccia socket ed eseguirlo
● Provare ad aprire un secondo terminale nella stessa cartella e a rilanciare lo
stesso server. Funziona? Perché?
● Aprire il browser preferito e impostare la URL “http://127.0.0.1:8000/” Cosa
si vede sul browser e sul terminale?
● Aprire il browser preferito e impostare la URL “http://localhost:8000/” Cosa
cambia?

**Risposta:**









**Soluzione Esercizio 22:** Un semplice web server

Operazioni Preliminari e Compilazione
Inizialmente sono stati copiati i file necessari (`serverHTTP.c`, `network.c`, `network.h`) all'interno della cartella dell'esercizio. Analizzando il sorgente di "`serverHTTP.c`", sono stati corretti alcuni commenti non validi scritti in stile Python (carattere "#") sostituendoli con quelli corretti in linguaggio C ("//"). Infine, il codice è stato compilato tramite il comando `gcc`.
Il file è un banale server `TCP` che resta in ascolto sulla porta 8000, accetta la connessione di un client, processa testualmente la richiesta leggendo riga per riga l'header `HTTP`, invia in risposta una pagina HTML di base e infine chiude la `socket`.

Rilancio del Server su un secondo terminale
Se si prova a lanciare una seconda istanza del server in un altro terminale, mentre il primo è ancora in esecuzione, il programma terminerà subito per un errore. Questo avviene a causa del fallimento della syscall "bind": non è possibile associare la medesima porta e lo stesso indirizzo a due processi in ascolto nello stesso istante.

Navigazione tramite l'indirizzo `IP` (127.0.0.1)
Richiedendo con il browser la URL "http://127.0.0.1:8000/":
- **Nel browser:** Si visualizza il contenuto statico inserito nel server (la scritta "Hello World, this is a very simple HTML document.").
- **Nel terminale:** Il programma stampa la richiesta `HTTP` pura inviata dal browser. Tra le varie intestazioni è presente la prima riga "GET / `HTTP`/1.1" e in particolare l'intestazione "Host: 127.0.0.1:8000".

Navigazione tramite Hostname (localhost)
Richiedendo con il browser la URL "http://localhost:8000/":
- **Nel browser:** Non cambia assolutamente nulla, in quanto l'hostname "localhost" viene risolto localmente nell'`IP` di loopback 127.0.0.1. Il server riceverà la connessione e invierà in risposta la stessa identica pagina HTML.
- **Nel terminale:** La richiesta catturata cambierà l'intestazione Host, che rifletterà la stringa usata dal client, diventando "Host: localhost:8000". Questo dimostra come l'hostname testuale digitato dall'utente venga inserito dal browser e trasmesso all'interno delle intestazioni `HTTP`.

Comandi Utili per il Test e l'Analisi

\# 1. Compilazione
`gcc` `serverHTTP.c` `network.c` -o serverHTTP

\# 2. Esecuzione del Web Server
./serverHTTP

\# 3. Test tramite CLI (utilizzando curl per visualizzare gli header scambiati)
curl -v http://127.0.0.1:8000/
curl -v http://localhost:8000/

\# 4. Registrazione del Traffico (cattura su interfaccia locale 'lo' sulla porta 8000)
\# Tramite riga di comando (salvataggio su file .pcap):
`sudo` tshark -i lo -f "tcp port 8000" -w web_traffic.pcap

\# 5. Analisi del Traffico Registrato
\# --- Tramite Riga di Comando (CLI) ---
\# 1. Leggere tutti i pacchetti registrati:
tshark -r web_traffic.pcap

\# 2. Filtrare per mostrare solo i messaggi a livello applicativo `HTTP`:
tshark -r web_traffic.pcap -Y "http"

\# 3. Leggere il contenuto completo delle intestazioni (Dettagli pacchetto estesi):
\#    Il flag -V (Verbose) mostrerà per ogni pacchetto tutto il contenuto esploso (come espandere i vari menu nella GUI).
tshark -r web_traffic.pcap -Y "http" -V

\# 4. Seguire l'intera conversazione scambiata (Equivalente del "Follow `TCP` Stream"):
\#    Stampa a terminale tutta la comunicazione ASCII scambiata sul primo stream (id 0).
tshark -r web_traffic.pcap -z follow,tcp,ascii,0

\# --- Tramite Interfaccia Grafica (GUI) ---
\# Lanciare Wireshark normalmente (permette poi di selezionare l'interfaccia 'lo' o aprire file):
`sudo` wireshark
\# Oppure per aprire direttamente il file registrato per l'analisi visiva:
wireshark web_traffic.pcap

\# Istruzioni d'uso per l'interfaccia di Wireshark:
\# 1. Filtrare i pacchetti:
\#    - Nella barra verde orizzontale in alto (Display Filter), scrivi "http" (senza virgolette) e premi Invio.
\#    - In questo modo la GUI nasconderà i pacchetti a livello di trasporto (SYN, ACK, ecc.) e mostrerà
\#      esclusivamente i messaggi dell'applicazione (es. le richieste GET e le risposte 200 OK).
**#      (In alternativa, per filtrare per porta, si può scrivere:** tcp.port == 8000).
#
\# 2. Leggere il contenuto dei pacchetti (Intestazioni):
\#    - Clicca con il tasto sinistro su una delle richieste `HTTP` nella lista centrale.
\#    - Nel pannello intermedio (Packet Details), cerca la riga "Hypertext Transfer Protocol" ed espandila cliccando sulla freccetta.
\#    - All'interno potrai leggere tutte le intestazioni processate in chiaro, come "Host: 127.0.0.1:8000" o "User-Agent".
#
\# 3. Leggere l'intera conversazione (Stream):
\#    - Fai clic destro su un pacchetto `HTTP` nella lista principale.
\#    - Clicca su "Follow" (Segui) e poi su "`TCP` Stream" o "`HTTP` Stream".
\#    - Si aprirà una finestra di testo dedicata che ti mostrerà per intero la comunicazione testuale: 
\#      in rosso vedrai il testo inviato dal client (le richieste), e in blu quello restituito dal server (la pagina HTML).
