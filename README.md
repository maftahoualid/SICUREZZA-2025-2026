## Esercizi Programmazione e Sicurezza delle Reti 25/26

[PDF delle Soluzioni agli esercizi](./doc/soluzioni.pdf)

---

# Guida Completa all'Installazione

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
sudo apt install -y build-essential
```

## 4. Ambiente Java (REST e Web Services)
```bash
sudo apt install -y default-jdk
sudo apt install -y default-jre
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

## 9. Ambiente LaTeX 
```bash
sudo apt install -y texlive-base
```

---

### "All-in-One"
Per installare **tutto** tranne LaTeX e Docker in un unico comando:
```bash
sudo apt update && sudo apt install -y net-tools curl wget git gedit build-essential default-jdk nodejs npm mosquitto mosquitto-clients wireshark python3 python3-pip
```
