**DOMANDA**
Esercizio
● Considerare la cartella Webservice/
● Aprire il file serverHTTP-REST.c e analizzarne il contenuto
● Compilarlo come al solito ed eseguirlo
● Aprire il file clientREST-GET.c e analizzarne il contenuto
● Compilarlo come al solito ed eseguirlo
– Che parametri devo passare in linea di comando?
– Cosa si può vedere analizzando lo scambio di dati tramite Wireshark?
– Qual è la signature della funzione calcolaSomma() sul server e sul client?
Perché ha senso che siano uguali?

**Risposta:**





**Soluzione Esercizio 29:** Webservice `REST` (RPC via `HTTP`)

Operazioni Preliminari
Ho copiato i file ``serverHTTP-`REST`.c``, ``clientREST-GET.c`` e la libreria di rete all'interno della cartella dell'esercizio 29, compilandoli regolarmente con GCC.

Risposte alle domande:

1. Che parametri devo passare in linea di comando?
Guardando il codice del `main()` nel client, notiamo che l'eseguibile si aspetta che gli vengano passati 3 argomenti dopo il suo nome (`argc < 4`).
**I parametri da passare sono, in ordine:** il nome della funzione da chiamare e i due operandi.
**Esempio di utilizzo corretto:** `./clientREST-GET calcola-somma 10.5 4.5`

2. Cosa si può vedere analizzando lo scambio di dati tramite Wireshark?
Si osserva perfettamente il funzionamento di un'API `REST`:
- Il client effettua una richiesta `HTTP` GET formattando l'URL con i parametri "serializzati": `GET /calcola-somma?param1=10.500000&param2=4.500000 `HTTP`/1.1`
- Il server risponde con un classico pacchetto `HTTP` `200 OK`, ma invece di inviare codice HTML, nel Payload (Body) restituisce i dati strutturati formattati in **JSON**:
```json
{
    **"somma":** 15.000000
}
```
Questo dimostra come i Webservice `REST` usino il protocollo web per lo scambio di dati "raw" tra macchine e non per le interfacce umane.

**3. Qual è la signature della funzione calcolaSomma() sul server e sul client?** Perché ha senso che siano uguali?
**La signature (firma della funzione) è identica in entrambi i file:** `float calcolaSomma(float val1, float val2)`.
Questo ha un grandissimo senso architetturale ed è alla base del concetto di **RPC (Remote Procedure Call)**:
- ****Sul Server**:** la funzione contiene la vera *Business Logic*, ovvero svolge effettivamente il calcolo matematico `val1 + val2` e restituisce il risultato.
- ****Sul Client**:** la funzione funge da **Stub** (un intermediario/simulacro). Il suo scopo è "nascondere" al programmatore principale tutta la complessità della rete. Lo sviluppatore che scrive il `main()` del client può limitarsi a invocare `calcolaSomma(10, 5)` credendo di eseguire una normale funzione C locale. In realtà, lo Stub intercetta la chiamata, *serializza* i parametri nell'URL, effettua la richiesta di rete `HTTP`, riceve la risposta, *deserializza* il JSON per estrarne il numero puro, e lo restituisce al `main()`.

Comandi utili:
\# Compila server e client
`gcc` `serverHTTP-`REST`.c` `network.c` -o serverHTTP-`REST`
`gcc` `clientREST-GET.c` `network.c` -o clientREST-GET

\# Avvia il server su un terminale
./serverHTTP-`REST`

\# Esegui il client su un altro terminale
./clientREST-GET calcola-somma 10.5 4.5
