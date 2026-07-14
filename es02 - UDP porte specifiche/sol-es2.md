**DOMANDA:** 
2) Modificare i sorgenti per mettere il server che riceve sulla porta 10000 e il
client che trasmette
dalla propria porta 30000 (ogni modifica dei sorgenti richiede una loro
ricompilazione)

**Risposta:**









Modificato `serverUDP.c` per metterlo in ascolto sulla porta 10000 (#define `SERVERPORT` 10000).
Modificato `clientUDP.c` per fare in modo che la sua `socket` venga creata sulla porta 30000 (`createUDPInterface`(30000)).
Modificato `clientUDP.c` affinché la `UDPSend` invii il pacchetto alla porta di destinazione 10000.