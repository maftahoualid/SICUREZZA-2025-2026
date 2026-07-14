**DOMANDA:**
Esercizio
● Scrivere e provare una pagina HTML che ricarica periodicamente il sito
dell’ANSA

**Risposta:**






**Soluzione Esercizio 21:** Ricaricamento periodico sito ANSA (Polling)

Per ricaricare periodicamente il sito, si è utilizzata la funzione JavaScript `setInterval()` nel file `javascript-load.html`. Questo script aggiorna l'attributo `src` dell'iframe a intervalli regolari (es. ogni 10 secondi). Inoltre, aggiungendo un parametro "timestamp" all'URL, si evita che il browser mostri la pagina dalla cache locale, forzando un vero reload dal server dell'ANSA.

Approccio sincrono al refresh (Polling)
Questo metodo prende il nome di "polling". Il client effettua richieste periodiche al server in base a un timer fisso, comportandosi in modo "sincrono" rispetto alla scadenza di questo timer.

Limiti e problematiche del Polling:
**1. Spreco di risorse (Refresh inutili):** Se il server dell'ANSA non ha pubblicato nuove notizie negli ultimi 10 secondi, la richiesta è inutile. Si spreca larghezza di banda sul lato client e capacità di elaborazione/rete sul lato server, che invierà dati identici ai precedenti.
**2. Ritardo negli aggiornamenti (Mancato refresh temporaneo):** Se una notizia urgente (breaking news) viene pubblicata subito dopo che l'iframe è stato ricaricato, l'utente dovrà attendere l'intero ciclo del timer (altri 10 secondi) prima di poterla leggere.

**L'Alternativa:** Approccio Asincrono (Event-Driven)
L'alternativa è la programmazione orientata agli eventi. Utilizzando tecnologie come le Web Socket (o i Server-Sent Events, SSE), il client stabilisce una connessione persistente e bidirezionale col server. 
In questo modo, il client non ha bisogno di chiedere continuamente "Ci sono novità?". Sarà invece il server, nel momento esatto in cui viene pubblicata una nuova notizia, a "spingere" (push) in modo asincrono l'aggiornamento verso il client connesso.
**Questo risolve entrambi i problemi:** azzera il consumo di banda per richieste a vuoto e permette un aggiornamento dei contenuti rigorosamente in tempo reale.
