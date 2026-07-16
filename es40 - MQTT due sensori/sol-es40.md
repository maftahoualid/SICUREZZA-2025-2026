**DOMANDA:**
●  Partendo dall’esercizio mostrato nelle istruzioni creare un’applicazione
pub/sub con 2 sensori di
temperatura relativi a 2 stanze diverse. Quante finestre di terminale devo
aprire?


**Risposta:**






Soluzione esercizi `MQTT`

**Domanda:** Partendo dall'esercizio mostrato nelle istruzioni creare un'applicazione pub/sub con 2 sensori di temperatura relativi a 2 stanze diverse. Quante finestre di terminale devo aprire?

Risposta:
Devi aprire un totale di 3 finestre di terminale:
- 1 finestra per il Subscriber (che si metterà in ascolto dei dati provenienti da entrambe le stanze).
- 1 finestra per il Publisher del Sensore 1 (Stanza 1).
- 1 finestra per il Publisher del Sensore 2 (Stanza 2).

**(Nota:** non serve una finestra per il broker poiché stiamo usando quello remoto in cloud su HiveMQ).

Ecco i comandi da inserire nelle 3 finestre:

-**-- Finestra 1:** SUBSCRIBER ---
Per metterti in ascolto su entrambe le stanze, puoi usare il carattere jolly "#" (che include tutti i sotto-topic di "temperatura"), e l'opzione "-v" (verbose) per stampare a schermo anche il nome del topic oltre al valore.

mosquitto_sub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "temperatura/#" -v


-**-- Finestra 2:** PUBLISHER (Sensore Stanza 1) ---
Pubblica un valore di temperatura (es. 22) sul topic specifico della stanza 1.

mosquitto_pub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "temperatura/stanza1" -m "22"


-**-- Finestra 3:** PUBLISHER (Sensore Stanza 2) ---
Pubblica un valore di temperatura (es. 24) sul topic specifico della stanza 2.

mosquitto_pub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "temperatura/stanza2" -m "24"

**Domanda:** Partendo dall'esercizio precedente, come fare per avere un unico subscriber per entrambe le temperature? Come si fa a distinguere da quale stanza proviene la temperatura?

Risposta:
1. Come avere un unico subscriber per entrambe le temperature:
Per ricevere i messaggi da più topic simultaneamente utilizzando un solo subscriber, si utilizzano i "wildcard" (caratteri jolly) nei topic. 
Se i publisher pubblicano sui topic "temperatura/stanza1" e "temperatura/stanza2", il subscriber può iscriversi al topic "temperatura/#" (wildcard multi-livello) oppure "temperatura/+" (wildcard a singolo livello). In questo modo, intercetterà tutti i messaggi pubblicati in qualsiasi sotto-categoria di "temperatura". (Come mostrato già nel comando del subscriber nella Parte 1).

2. Come distinguere da quale stanza proviene la temperatura:
Di default, mosquitto_sub stampa a schermo solamente il "payload" del messaggio (il valore numerico, ad es. "22" o "24"), rendendo impossibile capire da quale stanza provenga. 
Per ovviare a questo problema, bisogna lanciare il comando mosquitto_sub aggiungendo l'opzione "-v" (che sta per "verbose"). In modalità verbose, il client stampa sia il topic completo sia il messaggio.

Output di esempio che vedrai sul terminale:
temperatura/stanza1 22
temperatura/stanza2 24
