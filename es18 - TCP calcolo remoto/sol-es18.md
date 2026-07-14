**DOMANDA:**
Temi d’esame
(per ognuno ragionare sulla scelta del
protocollo di livello trasporto)
● Implementare un servizio di calcolo remoto: il client spedisce al server in 3
distinti messaggi due
numeri interi e il tipo di operatore (somma, sottrazione, moltiplicazione,
divisione) e il server,
dopo aver svolto il calcolo, restituisce il risultato al client che così termina
la sua esecuzione.

**Risposta:**







**Piano di Implementazione:** Servizio di Calcolo Remoto (es18)
1. Scelta del Protocollo di Trasporto
La traccia chiede di ragionare sulla scelta tra `UDP` e `TCP` per un servizio in cui il client invia i dati del calcolo suddivisi in 3 messaggi distinti (operando 1, operatore, operando 2).

**Scelta obbligata (o fortemente raccomandata):** `TCP`

**Motivazione (Ordine di consegna):** Poiché i dati viaggiano su 3 messaggi separati, l'ordine in cui arrivano al server è fondamentale. `UDP` non garantisce la consegna in ordine: il server potrebbe ricevere prima l'operatore e poi il primo numero, confondendo la logica di ricezione. `TCP`, essendo orientato allo stream, garantisce la consegna ordinata.
**Motivazione (Affidabilità e Sessione):** Se un pacchetto `UDP` andasse perso, il server rimarrebbe bloccato in attesa di un "pezzo" del calcolo mancante (o peggio, leggerebbe il pezzo della richiesta di un altro client). `TCP` garantisce che, finché la connessione è aperta, i 3 messaggi arriveranno a destinazione completi. Inoltre, la connessione `TCP` fornisce un "tubo dedicato" (sessione) per il client: il server non rischia di mischiare il primo operando del Client A con il secondo operando del Client B.
Pertanto, l'implementazione proposta utilizzerà `TCP`.

2. Implementazione del Client (`clientTCP.c`)
Instaura una connessione `TCP` con il server (porta 35000).
Chiede in input all'utente il primo operando, l'operatore e il secondo operando.
Effettua tre distinte chiamate TCPSend:
Invia operando1 (int)
Invia operatore (char)
Invia operando2 (int)
Effettua una TCPReceive per attendere il risultato (float).
Stampa il risultato e chiude la connessione.
3. Implementazione del Server (`serverTCP.c`)
Crea un server `TCP` in ascolto sulla porta 35000.
In un ciclo infinito while(1), accetta una nuova connessione (acceptConnection).
Effettua tre distinte chiamate TCPReceive sequenziali dal `socket` del client:
Riceve operando1 (int)
Riceve operatore (char)
Riceve operando2 (int)
Calcola il risultato con uno switch (gestendo la divisione per zero).
Usa TCPSend per inviare il risultato al client.
Chiude il `socket` del client (closeConnection) e torna in ascolto per il prossimo client.