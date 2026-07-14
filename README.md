## Esercizi Programmazione e Sicurezza delle Reti 25/26

[PDF delle Soluzioni agli esercizi](./doc/soluzioni.pdf)

---

## Come Avviare e Testare gli Esercizi

Il repository contiene diverse tipologie di esercizi (C, Java, Node.js, MQTT). Di seguito trovi le istruzioni generiche per compilarli e avviarli. Tutti i comandi presuppongono che tu stia lavorando da un terminale e ti trovi all'interno della cartella dello specifico esercizio (es. `cd "es09 - UDP sommatrice"`).

### Esercizi in C (Socket TCP/UDP e affini)
Ogni esercizio basato sul C utilizza un `Makefile` per gestire la compilazione, mantenendo pulita la cartella dei sorgenti (`src`), degli oggetti (`obj`) e degli eseguibili (`bin`).
1. **Compilazione:**
   ```bash
   make
   ```
   *Questo comando compilerà tutti i sorgenti e posizionerà gli eseguibili nella cartella `bin/`.*
2. **Esecuzione Server e Client:** apri due terminali separati.
   Nel primo avvia il server (ad es. sulla porta 8080):
   ```bash
   ./bin/serverUDP_inc 8080
   ```
   Nel secondo avvia il client puntando all'indirizzo locale:
   ```bash
   ./bin/clientUDP_inc 127.0.0.1 8080
   ```
3. **Pulizia dei file generati:**
   ```bash
   make clean
   ```

### Esercizi in Java (REST e Web Services)
Anche per i progetti Java è spesso presente un `Makefile` che compila automaticamente le classi Java nella directory `bin/` (insieme ad eventuali client C allegati).
1. **Compilazione:**
   ```bash
   make
   ```
2. **Esecuzione di un'applicazione Java:**
   Una volta creati i file `.class`, spostati nella cartella `bin/` e avvia il main specificando il nome della classe:
   ```bash
   cd bin
   java RESTAPIThread
   ```
   *(Sostituisci `RESTAPIThread` con il nome della classe principale da eseguire)*

### Esercizi in Node.js (WebSocket Chat)
Le applicazioni web e WebSocket si basano sull'ecosistema Node e includono un file `package.json` che descrive le dipendenze e gli script di base.
1. **Installazione delle dipendenze (da fare solo la prima volta):**
   ```bash
   npm install
   ```
2. **Avvio del Server:**
   ```bash
   npm start
   ```
   *(In alternativa: `node server.js` oppure `nodemon server.js`)*
3. **Test:** Apri il browser all'indirizzo `http://localhost:4000` (o quello indicato nei log) e apri più schede contemporaneamente per testare la chat.

### Esercizi IoT / MQTT (Mosquitto)
Questi esercizi simulano la comunicazione Pub/Sub tra sensori e cloud tramite un broker MQTT.
1. **Sottoscrizione in ascolto (Subscriber):**
   In un terminale, mettiti in ascolto su un topic (es. `temperatura`):
   ```bash
   mosquitto_sub -t "temperatura"
   ```
   *(Aggiungi opzioni come `-h`, `-p`, `-u` e `-P` se richiesto per connetterti a un cloud come HiveMQ, come dettagliato nei file `MQTT.txt` interni)*
2. **Pubblicazione messaggi (Publisher):**
   In un altro terminale, invia un messaggio allo stesso topic:
   ```bash
   mosquitto_pub -m "24" -t "temperatura"
   ```

---

# Guida Completa all'Installazione - Ambiente Sicurezza

Questa sezione elenca i comandi per preparare una macchina **Ubuntu (fresh install)** ad eseguire tutti gli esercizi presenti nel repository (Socket C, Web Services Java, WebSocket Node.js, MQTT, Docker, e Analisi di rete).

## 1. Aggiornamento Iniziale del Sistema
```bash
sudo apt update
sudo apt upgrade -y
```

## 2. Strumenti di Base e Rete
```bash
sudo apt install -y net-tools curl wget git gedit software-properties-common unzip
```

## 3. Ambiente C (Socket TCP/UDP)
```bash
# build-essential installa i pacchetti fondamentali come gcc, make e librerie standard (incluso pthread)
sudo apt install -y build-essential
```

## 4. Ambiente Java (REST e Web Services)
```bash
sudo apt install -y default-jdk
```

## 5. Ambiente Node.js (WebSocket Chat)
```bash
sudo apt install -y nodejs npm
```

## 6. Ambiente IoT e MQTT
```bash
# Installazione del broker Mosquitto e dei client CLI
sudo apt install -y mosquitto mosquitto-clients

# Avvio e abilitazione del broker per farlo partire all'avvio del sistema
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
```

## 7. Analisi del Traffico di Rete (Wireshark)
```bash
sudo apt install -y wireshark tshark tcpdump
```
> **Nota durante l'installazione di Wireshark:** Scegli **Sì** per permettere ai non-"superuser" di catturare pacchetti. Poi, aggiungi il tuo utente al gruppo `wireshark`:
> ```bash
> sudo usermod -aG wireshark $USER
> # Sarà necessario un log-out/log-in per applicare le modifiche.
> ```

## 8. Docker & Ambiente Python
Per l'esercizio *3) DOCKER* e l'applicazione Python/Flask.
```bash
# Installazione Docker
sudo apt install -y docker.io docker-compose
sudo usermod -aG docker $USER

# Installazione Ambiente Python Locale
sudo apt install -y python3 python3-pip python3-venv
pip3 install flask
```

## 9. Ambiente LaTeX (Opzionale per compilare i PDF)
```bash
sudo apt install -y texlive-full
```

---

### Riepilogo installazione rapida "All-in-One"
Per installare **tutto** tranne LaTeX e Docker in un unico comando:
```bash
sudo apt update && sudo apt install -y net-tools curl wget git gedit build-essential default-jdk nodejs npm mosquitto mosquitto-clients wireshark python3 python3-pip
```
