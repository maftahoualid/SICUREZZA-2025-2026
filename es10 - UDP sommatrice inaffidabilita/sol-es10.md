**DOMANDA:**
Sommatrice UDP e perdita di pacchetti
9) Usare la sommatrice su due macchine distinte provando, sulla macchina del
client, a staccare il cavo di rete prima di un
invio di un dato, ad es.
– Digitare “2345” + INVIO
– Digitare “5187” + INVIO
– Staccare il cavo
– Digitare “2” + INVIO
– Riattaccare il cavo e aspettare 30 sec che il sistema operativo si riassesti
– Digitare “1” + INVIO
– “0”
● Che somma leggo? E’ corretta?
● Se il server gira su una macchina Linux (anche una macchina virtuale) e
comunica con il client attraverso una rete WiFi
oppure in loopback è possibile simulare la perdita di pacchetti bloccando e,
dopo poco tempo, sbloccando la ricezione di
pacchetti con i seguenti comandi:
– PER BLOCCARE: sudo iptables -A INPUT -p udp --dport <porta_del_server> -j DROP
– PER SBLOCCARE: sudo iptables -D INPUT -p udp --dport <porta_del_server> -j
DROP
– Si consiglia di prepararsi questi comandi in una shell per poterli dare
velocemente

**Risposta:**















Questo esercizio dimostra in modo pratico una delle caratteristiche fondamentali del protocollo `UDP`: la sua inaffidabilità (best-effort delivery) e l'assenza di connessione.

Rispondendo alle domande:

- **Che somma leggo?** Leggerai la somma 7533 (derivata da 2345 + 5187 + 1).

- **È corretta?** Dal punto di vista dell'utente non è corretta, in quanto manca il 2 (la somma attesa sarebbe dovuta essere 7535). Dal punto di vista del protocollo `UDP`, invece, è un comportamento del tutto normale.

Ecco cosa succede nel dettaglio e il perché di questo risultato:

I primi due pacchetti (2345 e 5187) vengono inviati e raggiungono il server, che inizia ad accumulare la somma.
Quando scolleghi il cavo (o attivi la regola di iptables per far scartare (DROP) i pacchetti) e digiti 2, la funzione `UDPSend` nel codice del client non restituisce alcun errore. Per il client l'invio ha avuto successo, perché `UDP` non prevede alcun meccanismo di conferma di ricezione (ACK). Il pacchetto contenente il "2" viene semplicemente scartato dalla rete e perso per sempre (packet loss).
Quando riattacchi il cavo e invii 1 e 0, la rete è di nuovo operativa. Questi pacchetti raggiungono il server che li somma ai precedenti.
Quando arriva lo 0, il server risponde inviando il totale accumulato (7533) al client.
Questo esercizio mette in luce che, qualora si utilizzi `UDP` per applicazioni che necessitano di garanzie di consegna, è necessario implementare i controlli di ricezione, numerazione dei pacchetti e ritrasmissione direttamente a livello applicativo, poiché `UDP` a livello di trasporto non offre nulla di tutto ciò.