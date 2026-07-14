**DOMANDA:**
Esercizio per casa
● Modificare il server web serverHTTP.c in modo che accetti con il metodo POST
un intero file da salvare nella cartella del server (il cosiddetto “upload sul
server”).
● Suggerimenti:
– utilizzare il file form-file.html con serverHTTP.c non modificato ed
analizzare il contenuto della connessione TCP con Wireshark in modo da capire
nella richiesta HTTP
● Dove si trova il nome del file
● Dove si trova il contenuto del file
– Nella lettura della richiesta HTTP sul server aggiungere il codice che salva
il file prendendo spunto dal codice usato nell’esercizio del trasferimento di
file
– Invece la risposta HTTP può essere molto statica come nella versione originale
di serverHTTP.c

**Risposta:**

















**Soluzione Esercizio 26:** Upload file server web

Operazioni Preliminari
Ho copiato la versione "base" (dell'esercizio 22) di ``serverHTTP.c``, insieme ai moduli di rete, nella cartella `es26 - Upload file server web`.
Successivamente ho copiato `form-file.html`, il cui tag form utilizzava già il metodo "post" e, soprattutto, l'attributo `enctype="multipart/form-data"` (fondamentale per permettere al browser di trasmettere file anziché semplice testo url-encoded). L'attributo action puntava già correttamente a `http://localhost:8000/action`.

Risposta alle domande sull'analisi con Wireshark:
Analizzando la richiesta `HTTP` generata dall'invio del file (tramite TShark o l'interfaccia grafica), si nota che l'architettura della richiesta è molto diversa da un normale POST testuale. Il "Body" (Corpo) della richiesta è diviso in "parti", separate da una stringa casuale chiamata "boundary" (es. `------------------------SgojsDX1...`).

1. "Dove si trova il nome del file?"
Il nome originario del file caricato dall'utente si trova all'interno del Payload (nel Body della richiesta `HTTP`), annidato in una sotto-intestazione specifica chiamata `Content-Disposition`. 
**Si presenterà come:** `Content-Disposition: form-data; name="myfile"; filename="`nome_del_mio_file.txt`"`.

2. "Dove si trova il contenuto del file?"
Il contenuto effettivo (i byte del file) si trova subito sotto questa intestazione interna, separato da un'ulteriore riga vuota. Il contenuto termina non appena si incontra la stringa di chiusura del boundary.

Modifiche al server in C
Per gestire l'upload "spartano", ho modificato ``serverHTTP.c`` prendendo spunto dall'esercizio del trasferimento file.
Nella porzione in cui viene intercettato il metodo POST (`if(strcmp(method, "POST")==0)`), ho aggiunto:
1. L'apertura in scrittura (modalità "wb" - `write` binary) di un file temporaneo `file_caricato_dal_client.bin`.
2. Un ciclo `for` che usa `fputc` per travasare tutto ciò che arriva dalla `socket` (`fgetc(connfd)`) direttamente dentro al file, per un numero di cicli pari all'intestazione `HTTP` `Content-Length`.
3. Al termine della lettura, il file viene chiuso e salvato sul disco.

**N.B:** Poiché stiamo scaricando l'intero Payload grezzo direttamente nel file, quest'ultimo conterrà non solo i dati del file trasmesso, ma anche i boundary testuali e le intestazioni interne aggiunte dal browser. Implementare un parser "multipart" corretto in linguaggio C (che rimuova il boundary e i meta-dati per salvare solo il file puro) richiede decine di righe di logica complessa che esulano dagli scopi introduttivi di questa esercitazione. Il meccanismo implementato mostra in modo evidente l'avvenuto "travaso" dei dati dal client al filesystem del server!

Comandi utili:
\# Compila e avvia il server
`gcc` `serverHTTP.c` `network.c` -o serverHTTP
./serverHTTP

\# Esegui curl per caricare (upload) un file locale ("`testfile.txt`")
\# Il parametro -F innesca l'upload form-data
curl -v -F "myfile=@`testfile.txt`" http://localhost:8000/action
