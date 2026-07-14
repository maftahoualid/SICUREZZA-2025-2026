**DOMANDA:**
8) Modificarlo per costruire una semplice sommatrice
– Il client acquisisce ripetutamente da tastiera un numero intero e lo
manda al server finché l’utente digita zero
– Il server accumula in una variabile “somma” i valori mandati dal client
finché il client manda zero
– Quando il client manda zero il server risponde al client con la somma
ottenuta

**Risposta:**














Ho completato la trasformazione del codice in una "sommatrice `UDP`" operando sui sorgenti presenti nella cartella es9 e li ho ricompilati.

Ecco i dettagli delle modifiche implementate per soddisfare le specifiche:

**Modifiche al Client (`clientUDP_inc.c`):** Ho racchiuso l'acquisizione da tastiera e l'invio del pacchetto all'interno di un ciclo do-while che ha come condizione di permanenza request != 0. In questo modo il client continua a richiedere numeri all'utente e a spedirli al server. Non appena l'utente digita 0, quest'ultimo valore viene inviato, il ciclo si interrompe e il client si mette in attesa (`UDPReceive`) del risultato finale.

**Modifiche al Server (`serverUDP_inc.c`):** Ho dichiarato una nuova variabile intera int somma = 0; per fungere da accumulatore. Anche in questo caso ho introdotto un ciclo do-while con la stessa condizione (request != 0). Ad ogni iterazione il server riceve un valore, lo stampa e lo somma all'accumulatore (somma += request;). Non appena riceve il numero 0 (che non altera la somma), il server esce dal ciclo e sfrutta una `UDPSend` per rispedire il valore finale calcolato (somma) al client.