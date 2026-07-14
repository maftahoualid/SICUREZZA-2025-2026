**DOMANDA:**
6) Lanciare due volte il server usando due terminali. Cosa si osserva?
Funzionano entrambi?

**Risposta:**







Lanciando due volte il server su due terminali diversi per l'esercizio 6, si osserva il seguente comportamento:

**Si avviano entrambi senza mostrare errori:** Entrambi i processi stamperanno il messaggio "Sono in attesa di richieste..." e non apparirà il tipico errore di porta già occupata (Address already in use). Questo è possibile perché, se andiamo a ispezionare il sorgente della libreria `network.c`, la funzione `createUDPInterface` applica l'opzione SO_REUSEADDR al `socket` prima di chiamare la funzione di sistema bind(). Questa opzione comunica al sistema operativo di consentire a più `socket` di mettersi in ascolto sulla medesima porta.

**Funzionano entrambi? Solo parzialmente (solo uno riceverà i dati):** Sebbene entrambi siano apparentemente in funzione, quando il client invia un pacchetto `UDP` a quella porta, il sistema operativo lo consegnerà solo a uno dei due server (generalmente all'ultimo che è stato avviato in ordine temporale, o ripartendo le richieste, a seconda della gestione specifica di rete del kernel Linux). Poiché i messaggi inviati dal client sono indirizzati specificamente alla porta (pacchetti unicast e non multicast o broadcast), il pacchetto non verrà duplicato. L'esito pratico è che un server gestirà la richiesta e l'altro rimarrà in perenne attesa senza ricevere nulla.