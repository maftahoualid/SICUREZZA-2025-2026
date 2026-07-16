**DOMANDA:**
● Partendo dall’esercizio mostrato nelle istruzioni, cosa succede se pubblico
una temperatura prima
di aver lanciato il subscriber?
– Provare il publisher con l’opzione --retain

**Risposta:**





Soluzione esercizi `MQTT` - Pub-sub1 e Pub-sub2

Partendo dalle istruzioni mostrate per pubblicare e iscriversi a un topic:

1. Cosa succede se pubblico una temperatura prima di aver lanciato il subscriber?
Nel funzionamento standard di `MQTT` (senza l'opzione --retain), se un publisher invia un messaggio su un topic quando non ci sono subscriber attualmente connessi e in ascolto per quel topic, il messaggio viene perso. Il broker non memorizza i messaggi passati, si limita a smistarli ai client online in quel preciso istante. Lanciando il subscriber in un momento successivo, quest'ultimo rimarrà semplicemente in attesa dei nuovi messaggi futuri.

2. Provare il publisher con l'opzione --retain (e cosa comporta)
Se il comando del publisher viene lanciato aggiungendo l'opzione --retain (oppure -r), ad esempio:
mosquitto_pub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t temperatura -m "24" --retain

Il broker `MQTT` memorizzerà (tratterrà) quest'ultimo messaggio per il topic specificato.
Di conseguenza, se avvii un subscriber successivamente, non appena si iscriverà al topic riceverà immediatamente l'ultimo messaggio memorizzato (il "24"), senza dover attendere una nuova pubblicazione. (Nota: il broker trattiene sempre e solo l'ultimo messaggio per cui è stato specificato il flag retain).
