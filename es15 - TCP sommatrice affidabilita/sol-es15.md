**DOMANDA**
14) Usare la sommatrice TCP su due macchine distinte provando, sulla macchina
del client, a staccare il cavo di rete prima di un
invio di un dato, ad es.
– Digitare “2345” + INVIO
– Digitare “5187” + INVIO
– Staccare il cavo
– Digitare “2” + INVIO
– Riattaccare il cavo e aspettare 30 sec che il sistema operativo si riassesti
– Digitare “1” + INVIO
– “0”
Che somma leggo? E’ corretta?
● NOTA: Se il server gira su una macchina Linux (anche una macchina virtuale) e
comunica con il client attraverso una rete WiFi
oppure in loopback è possibile simulare la perdita di pacchetti bloccando e,
dopo poco tempo, sbloccando la ricezione di pacchetti
con i seguenti comandi:
– PER BLOCCARE: sudo iptables -A INPUT -p tcp --dport <porta_del_server> -j DROP
– PER SBLOCCARE: sudo iptables -D INPUT -p tcp --dport <porta_del_server> -j
DROP
– Si consiglia di prepararsi questi comandi in una shell a parte per poterli
dare velocemente

**Risposta:**











A differenza di quanto accaduto nell'analogo esercizio svolto con `UDP` (Esercizio 9), in questo caso la situazione cambia radicalmente grazie all'affidabilità garantita dal protocollo `TCP`.

Rispondendo alle tue domande:

- **Che somma leggo?** Leggerai la somma 7535 (che deriva da 2345 + 5187 + 2 + 1).

- **È corretta?** Sì, è assolutamente corretta. Nessun dato è andato perso.

Cosa è successo dietro le quinte?

I primi due invii (2345 e 5187) avvengono normalmente.
Quando scolleghi il cavo (o attivi la regola di drop su iptables) e invii il "2", la funzione TCPSend accoda il dato nel buffer di trasmissione locale e il sistema operativo prova a spedirlo. Non ricevendo il pacchetto di conferma (ACK) dal server a causa dell'assenza di rete, `TCP` non scarta il pacchetto, ma lo conserva nel buffer e avvia un timer. Scaduto il timer, `TCP` effettuerà automaticamente una serie di ritrasmissioni a intervalli di tempo crescenti.
Quando riattacchi il cavo, la connettività si ripristina. Alla successiva ritrasmissione automatica, il pacchetto contenente il "2" raggiungerà finalmente il server (con un leggero ritardo, invisibile all'applicazione se non per l'attesa).
Digitando successivamente "1" e "0", anche questi verranno consegnati, sempre garantendo l'ordine corretto di arrivo.
Il server riceverà tutti i numeri nella sequenza esatta, senza perdersi alcun pezzo, calcolerà il totale e lo restituirà al client.
A meno che il cavo non rimanga staccato per un tempo lunghissimo (tipicamente svariati minuti, portando la connessione in timeout e causando un errore irreversibile sul `socket`), `TCP` è in grado di "riparare" autonomamente questo genere di guasti temporanei di rete senza che lo sviluppatore debba scrivere una singola riga di codice aggiuntiva.