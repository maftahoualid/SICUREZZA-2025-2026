**DOMANDA:**
Temi d’esame
(per ognuno ragionare sulla scelta del
protocollo di livello trasporto)
● Implementare un servizio di telepass: quando l'auto si avvicina al casello il
terminale in esso
presente spedisce al server il numero di targa;
il server tiene traccia in una struttura dati del
numero di passaggi per ogni targa e restituisce al client tale numero.

**Risposta:**















**Piano di Implementazione:** Servizio Telepass (es19)
1. Scelta del Protocollo di Trasporto
La traccia richiede di inviare un numero di targa (stringa) al server, il quale deve incrementare un contatore per quella specifica targa e restituire il numero aggiornato di passaggi.

**Scelta raccomandata:** `TCP`

**Motivazione (Affidabilità e Modifica di Stato):** Il problema principale di questo scenario è che il server modifica uno stato interno (incrementa il numero di passaggi, che ha rilevanza per la fatturazione/tracciamento). Se usassimo `UDP` e il pacchetto di risposta (dal server al client) andasse perso, il client andrebbe in timeout e ritrasmetterebbe la richiesta. Il server, ricevendo nuovamente il datagramma `UDP`, incrementerebbe il contatore per la seconda volta per lo stesso passaggio fisico dell'auto, creando un'incongruenza grave (doppio addebito).
**Vantaggio di `TCP`:** Usando `TCP`, la libreria di rete gestisce internamente le ritrasmissioni e l'eliminazione dei pacchetti duplicati. Il server è garantito di ricevere la richiesta una e una sola volta per ogni connessione stabilita dal casello per un dato veicolo. Se c'è un problema di rete, la connessione cade, ma non si creano addebiti "fantasma" dovuti a ritrasmissioni applicative non gestite.
**Nota:** Si potrebbe usare `UDP` solo a patto di implementare a livello applicativo un identificatore univoco di transazione (ID Passaggio) per riconoscere i duplicati, ma in un contesto base `TCP` offre questa garanzia "gratis".
Pertanto, l'implementazione proposta utilizzerà `TCP`.

2. Implementazione del Client (`clientTCP.c`)
Il client (Terminale Casello) instaura una connessione `TCP` con il server.
Legge o simula l'acquisizione della targa dell'auto (es. char targa[10]).
Invia la stringa della targa al server tramite TCPSend.
Effettua una TCPReceive per attendere in risposta l'intero relativo al conteggio dei passaggi.
Stampa il risultato (es. "L'auto AB123CD è passata 4 volte") e chiude la connessione.
3. Implementazione del Server (`serverTCP.c`)
Crea un server `TCP` in ascolto.
Gestisce una semplice struttura dati (es. un array di struct contenenti targa e conteggio, per semplicità limitato a un numero massimo di targhe).
In un ciclo infinito, accetta una connessione da un casello (acceptConnection).
Riceve la targa (TCPReceive).
Cerca la targa nella struttura dati:
Se esiste, incrementa il conteggio.
Se non esiste, la aggiunge con conteggio = 1.
Risponde al client inviando il conteggio aggiornato (TCPSend).
Chiude il `socket` del client e torna in attesa del prossimo passaggio.
