**DOMANDA:** Lanciare prima il server e poi il client. Cosa si osserva? Invertire la sequenza di lancio. Cosa si osserva?

**Risposta:**







Ecco cosa si osserva nei due diversi casi, essendo la comunicazione basata su `UDP`, che è un protocollo connectionless (senza connessione):

**Lanciando prima il server e poi il client:** La comunicazione avviene con successo. Il server viene avviato e si mette in attesa (`UDPReceive`). Quando viene avviato il client, questo invia il suo messaggio al server e si mette in attesa della risposta. Il server riceve il pacchetto, stampa il contenuto a schermo e invia la risposta. Il client riceve la risposta dal server, la stampa e termina la sua esecuzione. Il server (grazie al ciclo while(true)) torna in attesa del prossimo client.

**Invertendo la sequenza di lancio (prima il client e poi il server):** Si verifica un blocco (entrambi rimangono in attesa all'infinito). Quando il client viene avviato per primo, invia subito il pacchetto `UDP` verso la porta 35000 e si mette in attesa (`UDPReceive`) della risposta. Poiché il server non è ancora attivo, non c'è nessuna applicazione in ascolto su quella porta. Essendo `UDP` senza connessione e senza garanzia di consegna, l'invio va a buon fine dal punto di vista del client, ma il pacchetto viene scartato dal sistema operativo di destinazione (e perso). Quando successivamente viene avviato il server, questo si mette in attesa di nuovi messaggi. A questo punto entrambi i programmi si trovano bloccati indefinitamente nelle rispettive `UDPReceive`: il client aspetta una risposta a un messaggio andato perso, mentre il server aspetta un nuovo messaggio che il client non invierà mai più.