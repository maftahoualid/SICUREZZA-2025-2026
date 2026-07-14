**DOMANDA**
13) Provare a rifare il caso dell’Esercizio 10 ma con questa nuova versione
della sommatrice.
Cosa si può osservare? Che soluzione si può trovare? C’è influenza reciproca tra
i due client?

**Risposta:**














Rifacendo il caso dell'Esercizio 10 con la nuova versione `TCP` della sommatrice, ci troveremo di fronte a uno scenario completamente diverso rispetto a `UDP`.

Ecco cosa succede rispondendo alle tue domande:

- **Cosa si può osservare?** Osserverai che il server gestirà soltanto il Client A, ignorando del tutto il Client B fino alla fine. Quando avvii il server, questo si blocca sulla acceptConnection() in attesa del primo client. Avviando il Client A, la connessione viene instaurata e il server entra nel ciclo per calcolare la somma di A. Se nel frattempo avvii il Client B, a livello di rete il sistema operativo del server accetterà "dietro le quinte" la connessione `TCP` (grazie alla coda di `listen`()), permettendo al Client B di avviarsi e farti inserire i numeri. Tuttavia, il programma del server è bloccato all'interno del ciclo do-while a leggere esclusivamente dal canale (`socket`) del Client A. I numeri inviati dal Client B si accumuleranno semplicemente nel buffer del sistema operativo in attesa di essere letti. Quando il Client A invierà lo "0", il server gli risponderà con la somma corretta (es. 7535), chiuderà la connessione e, per come è scritto attualmente il codice, il programma del server terminerà. Di conseguenza, il Client B non riceverà mai alcuna risposta, la sua connessione verrà interrotta bruscamente dal sistema operativo (generando un errore se prova a inviare o ricevere altro) e i suoi dati andranno persi senza essere stati elaborati.

- **C'è influenza reciproca tra i due client?** Rispetto ai dati, assolutamente no. A differenza di `UDP`, dove i numeri dei due client finivano mischiati nello stesso "calderone", `TCP` crea un "tubo" dedicato per ogni connessione. I dati non si sovrappongono in alcun modo e le somme non si inquinano a vicenda. L'unica (pesante) influenza reciproca è di tipo temporale/bloccante: il Client A "monopolizza" il server impedendo che il Client B venga servito (e nel nostro caso, causandone poi l'esclusione definitiva).

- **Che soluzione si può trovare?** Per risolvere il problema ci sono due step:

**Per servirli in modo sequenziale (uno dopo l'altro):** È necessario racchiudere la acceptConnection e la logica della somma all'interno di un ciclo while(true) nel server. In questo modo, dopo aver servito il Client A (alla ricezione dello "0"), il server tornerà in attesa e farà la `accept`() della connessione del Client B che era rimasta "parcheggiata" in coda.
**Per servirli in modo concorrente (contemporaneamente):** Serve un'architettura multi-thread (o multi-processo). Il server accetta la connessione nel thread principale e poi passa il `socket` appena creato a un nuovo thread "figlio" (es. usando la createConcurrentNetworkFunction fornita dalla libreria `network.c`). Il thread figlio si occuperà di fare la somma per quel client, mentre il padre tornerà immediatamente in attesa di nuove connessioni (acceptConnection) per altri client.