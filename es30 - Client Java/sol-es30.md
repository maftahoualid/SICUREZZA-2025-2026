**DOMANDA**
Esercizio 2
● Prendere in considerazione il file ClientREST.java
– Dopo aver installato l’ambiente base di Java (già presente in Lab Delta) si
può compilare con javac ClientREST.java
– Ed eseguire con java ClientREST
● Il fatto che il server sia fatto in C e il client in Java è un problema o
un’opportunità? Perché?

**Risposta:**









**Soluzione Esercizio 30:** Webservice `REST` Client in Java

Operazioni Preliminari
Ho creato la cartella `es30 - Client Java`, copiato i file necessari e avviato il server `serverHTTP-`REST`` (scritto in C).
Successivamente, ho compilato il client in Java (``ClientREST.java``) e l'ho eseguito per effettuare la chiamata `REST`.

Risposte alle domande:

1. Il fatto che il server sia fatto in C e il client in Java è un problema o un’opportunità? Perché?

È senza dubbio una grandissima **opportunità** e rappresenta uno dei punti di forza fondamentali delle architetture `REST` e dei Web Service in generale: **l'interoperabilità e il disaccoppiamento**.

Ecco perché:
- **Indipendenza dal Linguaggio e Piattaforma:** Utilizzando protocolli di rete standard (come `HTTP` su `TCP`/`IP`) e formati di scambio dati agnostici (come stringhe di testo o JSON), i due sistemi non hanno bisogno di condividere lo stesso ecosistema. "Parlano" entrambi la lingua universale di `HTTP`, decodificandola con le rispettive librerie standard.
- **Scelta dello strumento migliore (Best Tool for the Job):** Permette agli sviluppatori di usare il linguaggio più adatto per ogni strato applicativo. Ad esempio, il server in C garantisce performance elevate, controllo a basso livello e basso overhead, mentre il client in Java offre portabilità estrema (Write Once, Run Anywhere) e librerie avanzate per eventuali interfacce grafiche (GUI) o integrazioni enterprise.
- **Decoupling nello Sviluppo:** Team diversi possono sviluppare il backend e il frontend in completa autonomia lavorando con le proprie tecnologie preferite. Finché viene rispettato il "contratto" (l'API `REST`, ovvero l'endpoint, i parametri e la struttura della risposta), l'uso di linguaggi diversi sotto il cofano è totalmente trasparente all'altra parte.

Al contrario, se si usassero paradigmi RPC strettamente legati a uno specifico linguaggio (come Java RMI per Java), si sarebbe vincolati a impiegare la medesima tecnologia sia per il client che per il server, impedendo questo grado di flessibilità.

Comandi utili:
\# Compila e avvia il server in C
`gcc` `serverHTTP-`REST`.c` `network.c` -o serverHTTP-`REST`
./serverHTTP-`REST`

\# In un altro terminale, compila ed esegui il client in Java
javac `ClientREST.java`
java ClientREST calcola-somma 4 5
