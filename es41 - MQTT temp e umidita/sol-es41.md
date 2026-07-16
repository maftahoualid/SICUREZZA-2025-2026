**DOMANDA:**
● Prova a pubblicare un valore di umidità relativa (topic “UR”); il subscriber
interessato alle
temperature lo riceve? Come si fa a creare un subscriber interessato
all’umidità? Costruire
un’applicazione pub/sub con 4 finestre per produrre e visualizzare sia valori di
temperatura sia
valori di umidità.


**Risposta:**





Soluzione esercizio `MQTT` - es41

**Domanda 1:** Prova a pubblicare un valore di umidità relativa (topic "UR"); il subscriber interessato alle temperature lo riceve?
**Risposta 1:** No, il subscriber non lo riceve. Il protocollo `MQTT` si basa su un filtraggio rigoroso tramite i topic. Un subscriber iscritto al topic "temperatura" (o "temperatura/#") ignorerà completamente tutti i messaggi pubblicati su topic differenti, come "UR".

**Domanda 2:** Come si fa a creare un subscriber interessato all'umidità?
**Risposta 2:** Bisogna lanciare un nuovo client mosquitto_sub specificando come argomento per il parametro -t il topic dell'umidità, ovvero "UR".

**Domanda 3:** Costruire un'applicazione pub/sub con 4 finestre per produrre e visualizzare sia valori di temperatura sia valori di umidità.
**Risposta 3:** Per avere un sistema completo servono 4 terminali separati. Di seguito i comandi da inserire in ciascuna finestra (utilizzando sempre il broker cloud di HiveMQ):

-**-- Finestra 1:** SUBSCRIBER TEMPERATURA ---
mosquitto_sub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "temperatura/#" -v

-**-- Finestra 2:** SUBSCRIBER UMIDITA' ---
mosquitto_sub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "UR/#" -v

-**-- Finestra 3:** PUBLISHER TEMPERATURA ---
mosquitto_pub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "temperatura/stanza1" -m "22"

-**-- Finestra 4:** PUBLISHER UMIDITA' ---
mosquitto_pub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "UR/stanza1" -m "60"
