**DOMANDA:**
Temi d’esame
(per ognuno ragionare sulla scelta del
protocollo di livello trasporto)
● Implementare una semplice versione di terminale remoto. Il client si connette
ad un server di cui
si conosce IP e porta e chiede all’utente di scrivere un comando come in un
normale terminale a
caratteri (detto anche shell o console) di Linux.
Il comando viene eseguito dal server e il relativo
output viene stampato a video dal client.

**Risposta:**











**Piano di Implementazione:** Terminale Remoto (es20)

1. Scelta del Protocollo di Trasporto
La traccia richiede che il client si connetta a un server, invii un comando (es. comando di shell) e riceva l'output risultante dall'esecuzione di quel comando dal server.

**Scelta raccomandata:** `TCP`

Motivazione:
In questo scenario è fondamentale che i dati non vadano persi né vengano ricevuti in ordine errato. Un comando potrebbe risultare corrotto (ad es. un "ls -l" potrebbe arrivare incompleto), ma l'aspetto critico è la ricezione dell'output. L'output di un comando di shell può essere di dimensioni arbitrarie e superare ampiamente il limite di singolo pacchetto (`MTU`) supportato tipicamente da `UDP`. Il protocollo `TCP` garantisce una trasmissione orientata al flusso (stream) e gestisce nativamente la segmentazione e la ritrasmissione dei pacchetti qualora essi si perdano nella rete.
Il server leggerà l'output tramite una pipe (ad es. usando popen in C) e lo invierà sul `socket` `TCP` in vari blocchi. Il client continuerà semplicemente a leggere dal `socket` finché non riceverà un segnale di termine (la chiusura della connessione o fine dei dati). Con `UDP`, al contrario, sarebbe necessario implementare a livello applicativo la frammentazione dell'output e gestire esplicitamente ACK/NACK per garantire che il client riceva tutto l'output ordinato correttamente.

2. Implementazione
- Il client `TCP` legge il comando inserito dall'utente (es. tramite fgets), lo invia al server tramite TCPSend, e poi entra in un ciclo in cui legge (TCPReceive) l'output inviato dal server e lo stampa a video, fermandosi quando la trasmissione è completata (chiusura del `socket` o invio terminato).
- Il server `TCP` accetta connessioni. Quando riceve un comando, usa la chiamata di sistema "popen(comando, "r")" per eseguirlo come comando di shell e aprire una pipe per leggerne l'output. Legge l'output a blocchi usando fread e li invia man mano al client tramite TCPSend. Finito l'output, chiude il file associato a popen (pclose) e chiude il `socket`, il che indicherà al client che il risultato del comando è stato interamente trasmesso.
