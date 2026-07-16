**DOMANDA**
Si vuole costruire con MQTT un servizio di messaggistica
universitaria
– Il rettore può leggere tutti i messaggi
– La segreteria può leggere i messaggi dai docenti e dagli studenti
– I docenti possono leggere i messaggi dai docenti e dagli studenti
– Gli studenti possono leggere solo i messaggi degli altri studenti


**Risposta:**






Soluzione esercizio `MQTT` - es43

**Obiettivo:** Costruire un servizio di messaggistica universitaria con `MQTT` rispettando specifici permessi di lettura per i vari ruoli.

Per risolvere questo problema, la soluzione ottimale consiste nel definire una gerarchia di topic basata sul mittente (chi genera il messaggio). 
Possiamo definire la seguente struttura di topic radice:
messaggi/<ruolo_mittente>

I possibili topic in cui i vari utenti andranno a pubblicare saranno quindi:
- messaggi/rettore
- messaggi/segreteria
- messaggi/docenti
- messaggi/studenti

In base alle regole imposte dall'esercizio, ecco come si dovranno configurare le iscrizioni (subscribers) per ciascun ruolo:

1. IL RETTORE
**Regola:** Può leggere tutti i messaggi.
**Soluzione:** Il rettore si iscriverà utilizzando il carattere jolly "#" per intercettare qualsiasi messaggio sotto la radice "messaggi/".
**Topic di sottoscrizione:** messaggi/#

2. LA SEGRETERIA
**Regola:** Può leggere i messaggi dai docenti e dagli studenti.
**Soluzione:** La segreteria dovrà iscriversi a due topic separati (si può fare lanciando il client con due flag -t).
**Topic di sottoscrizione:** messaggi/docenti e messaggi/studenti

3. I DOCENTI
**Regola:** Possono leggere i messaggi dai docenti e dagli studenti.
**Soluzione:** Esattamente come la segreteria, i docenti si iscriveranno a questi due topic.
**Topic di sottoscrizione:** messaggi/docenti e messaggi/studenti

4. GLI STUDENTI
**Regola:** Possono leggere solo i messaggi degli altri studenti.
**Soluzione:** Gli studenti si iscriveranno in ascolto unicamente sul topic dedicato a loro.
**Topic di sottoscrizione:** messaggi/studenti

---
COMANDI PRATICI DA ESEGUIRE SUL TERMINALE
(I comandi utilizzano il broker remoto HiveMQ indicato negli esercizi precedenti)

>>> COMANDI PER LEGGERE (SUBSCRIBER) <<<

Rettore (ascolta tutto):
mosquitto_sub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "messaggi/#" -v

Segreteria e Docenti (ascoltano docenti e studenti):
mosquitto_sub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "messaggi/docenti" -t "messaggi/studenti" -v

Studenti (ascoltano solo studenti):
mosquitto_sub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "messaggi/studenti" -v

>>> COMANDI PER SCRIVERE (PUBLISHER) <<<

Pubblicare come Rettore:
mosquitto_pub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "messaggi/rettore" -m "Avviso dal Rettore"

Pubblicare come Segreteria:
mosquitto_pub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "messaggi/segreteria" -m "Avviso dalla Segreteria"

Pubblicare come Docenti:
mosquitto_pub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "messaggi/docenti" -m "Lezione annullata"

Pubblicare come Studenti:
mosquitto_pub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P `MQTT`-esercitazione2026 -t "messaggi/studenti" -m "Cerco appunti"
