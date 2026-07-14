**DOMANDA:**
Temi d’esame
(per ognuno ragionare sulla scelta del
protocollo di livello trasporto)
● Implementare un servizio di calcolo remoto: il client spedisce al server in un
unico messaggio
due numeri interi e il tipo di operatore (somma, sottrazione, moltiplicazione,
divisione) e il server,
dopo aver svolto il calcolo, restituisce il risultato al client che così termina
la sua esecuzione.

**Risposta:**









**Piano di Implementazione:** Servizio di Calcolo Remoto (es17)
1. Scelta del Protocollo di Trasporto
La traccia chiede di ragionare sulla scelta tra `UDP` e `TCP` per un servizio in cui il client invia un unico messaggio con i dati, riceve la risposta e termina.

**Scelta ideale:** `UDP`

**Motivazione:** Il modello di comunicazione richiesto è strettamente di tipo "Richiesta-Risposta" singola. Il payload (due interi e un carattere per l'operatore) è minuscolo e rientra comodamente in un unico datagramma `UDP`.
**Efficienza:** Usare `TCP` richiederebbe un notevole overhead per stabilire la connessione (3-way handshake) e abbatterla, scambiando una decina di pacchetti di controllo solo per inviare due messaggi utili. Con `UDP`, i pacchetti in gioco sono solo due (uno di andata, uno di ritorno).
**Risoluzione di inaffidabilità:** Trattandosi di una singola query, se il pacchetto va perso il client potrebbe semplicemente riprovare (con un timeout applicativo), in maniera del tutto analoga a come funziona il protocollo DNS.
Pertanto, l'implementazione proposta utilizzerà `UDP`.

2. Struttura dei Dati
Definiremo una struct per il messaggio di richiesta:

typedef struct {
    int operando1;
    int operando2;
    char operatore; // '+', '-', '*', '/'
} RichiestaCalcolo;

3. Implementazione del Client (`clientUDP.c`)
Crea un'interfaccia `UDP` (es. porta 20000).
Chiede in input all'utente i due numeri e l'operatore.
Popola la struct RichiestaCalcolo.
Spedisce la struct al server (`UDPSend`).
Attende il risultato in ricezione (`UDPReceive`).
Stampa il risultato e termina.
4. Implementazione del Server (`serverUDP.c`)
Crea un'interfaccia `UDP` in ascolto (es. porta 35000).
Entra in un ciclo infinito di ricezione `UDPReceive` in attesa di richieste.
Quando riceve una RichiestaCalcolo, valuta l'operatore (switch statement).
Calcola il risultato (float o intero, gestiremo le divisioni o daremo un intero).
Risponde al client inviando il risultato.