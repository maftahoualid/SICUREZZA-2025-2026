**DOMANDA:**
7) Compilare ed eseguire il secondo esempio

**Risposta:**














Avviando poi in background il server ./serverUDP_inc e successivamente lanciando il client ./clientUDP_inc, il comportamento osservato in esecuzione è il seguente:

Il server si mette in ascolto sulla porta 35000.
Il client chiede in input un numero intero (es. ho inserito 42).
Il client invia l'intero al server.
Il server lo riceve, calcola request + 1 (ottenendo 43) e lo rispedisce al client.
**Il client riceve la risposta dal server e stampa a video:** [CLIENT] Contenuto: 43. Entrambi i programmi, arrivati alla fine, terminano la loro esecuzione.