**DOMANDA:**
sommatrice UDP e influenze reciproche
10)
● Invocare il server della sommatrice con due client diversi (tutti e tre
possono
anche essere sulla stessa macchina ovviamente su finestre terminali diverse), ad
es.
● Che somma leggo da ciascun client? E’ la somma che ciascun client da solo si
aspetterebbe?
Client A:
● Digitare “2345” + INVIO
● Digitare “5187” + INVIO
● Digitare “2” + INVIO
● Digitare “1” + INVIO
● “0”
Client B:
● Digitare “2” + INVIO
● Digitare “8” + INVIO
● “0”

**Risposta:**













In questo scenario, il server si comporterà in modo anomalo dal punto di vista applicativo.

Ecco le risposte alle due domande:

- **Che somma leggo da ciascun client?** Il client che per primo invia il valore "0" leggerà una somma "mista" composta dai numeri inviati da entrambi i client fino a quel momento. Supponendo che i pacchetti arrivino in modo intervallato, il server sommerà tutti i valori insieme (ad esempio 2345 + 5187 + 2 + 1 + 2 + 8 = 7545). Il primo client a inviare lo "0" riceverà come risposta 7545 (o un valore intermedio a seconda di quanti pacchetti di B sono arrivati prima del suo "0"). Il secondo client (che manda lo "0" per ultimo) non riceverà nulla se il server termina l'esecuzione, o riceverà una somma azzerata/parziale se il server ha un ciclo esterno che lo fa ricominciare.

- **È la somma che ciascun client da solo si aspetterebbe?** Assolutamente no. Il Client A si aspetterebbe 7535 e il Client B si aspetterebbe 10. Invece, i dati si sono mischiati.

**Perché succede questo?** A differenza di `TCP` (che crea un "tubo" dedicato e isolato per ogni connessione/client), `UDP` non ha il concetto di connessione. Il server ha una sola coda di ricezione per la porta `UDP` e una singola variabile somma. Quando esegue `UDPReceive`, legge semplicemente il prossimo pacchetto in coda, senza distinguere se proviene dal Client A o dal Client B, sommandolo all'accumulatore globale. Inoltre, quando il server riceve lo "0" da uno dei due, il ciclo si interrompe e la funzione `UDPSend` risponde all'indirizzo `IP` e alla porta dell'ultimo pacchetto ricevuto (cioè quello del client che ha mandato lo "0"), inviando il "calderone" di numeri mischiati.

Questo esercizio evidenzia che `UDP`, non gestendo nativamente le sessioni, richiede allo sviluppatore di identificare esplicitamente da quale client proviene ogni messaggio e di gestire le variabili di stato (come la "somma") separatamente per ogni utente.