**DOMANDA**
applicazione di trasferimento file
● Il client chiede al server un file specificandone il nome
● Il server lo trasmette un byte alla volta
● Il client lo salva in locale con lo stesso nome
● Quale protocollo usiamo?
● [Da fare solo con i PC del Lab Delta] Lanciare client e server su due
macchine diverse, trasferire un file di grosse dimensioni in modo da
avere il tempo di staccare e riattaccare il cavo di rete per un breve tempo
durante il trasferimento.
Cosa succede al file trasferito?

**Risposta:**



















Applicazione di Trasferimento File `TCP` (es16)
Ho completato la scrittura e compilazione della versione `TCP` per il trasferimento file (byte per byte), modificando i sorgenti contenuti nella cartella es16.

Modifiche ai Sorgenti
Client (`clientTCP.c`)
Il client richiede in input all'utente il nome del file da scaricare. Invia il nome al server usando TCPSend (includendo il carattere terminatore). Apre un file in locale in modalità scrittura binaria ("wb"). Entra in un ciclo while in cui chiama ripetutamente TCPReceive(&byte, 1) per scaricare il file.

NOTE

La ricezione termina automaticamente e correttamente (EOF) nel momento in cui TCPReceive restituisce 0, evento che si verifica quando il server chiude la connessione alla fine del trasferimento.

Server (`serverTCP.c`)
Il server accetta la connessione e, per prima cosa, riceve il nome del file (leggendo fino al carattere \0). Apre il file richiesto in lettura binaria ("rb"). Inizia un ciclo leggendo un byte alla volta dal disco (tramite fread) e spedendolo nel tubo `TCP` usando TCPSend. Terminata la lettura dal disco, chiude il file locale e, soprattutto, chiude la connessione (closeConnection). In questo modo invia implicitamente al client il segnale di "Fine File".

Tutto il codice è stato compilato con successo nei rispettivi file clientTCP e serverTCP. Gli eseguibili sono pronti per essere testati per il trasferimento file!