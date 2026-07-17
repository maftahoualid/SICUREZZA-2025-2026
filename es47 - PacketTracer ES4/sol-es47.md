**DOMANDA 1:** Si controlli il significato dei comandi che si possono impartire quando il router è in modalità dhcp-config; ad esempio, cosa significa il comando lease e che parametri vuole?

**DOMANDA 2:** Verificate quale indirizzo è stato assegnato ad una macchina dal server DHCP (ad esempio, la macchina DOC1). Chiamiamo tale indirizzo IP_a. Cosa succede se assegnate manualmente proprio tale indirizzo, ovvero IP_a, ad un'altra macchina, ad esempio DOC2?

**DOMANDA 3:** Sarebbe possibile impostare il server DHCP in modo che il range di indirizzi della sottorete 192.168.0.0 vada solo tra 192.168.0.100 e 192.168.0.110?

**DOMANDA 4:** Qual è il percorso seguito da un generico pacchetto inviato dall'utente DOC1 all'utente STD1?

**DOMANDA 5:** Nel caso venisse aggiunta una VLAN, quante sotto-interfacce avrebbe il router sul singolo collegamento fisico?

**DOMANDA 6:** Fino a quante sotto interfacce si possono creare su un'interfaccia di un router?

**DOMANDA 7:** In questo esercizio, all’interfaccia fisica del router sono associate 2 sottointerfacce e due indirizzi IP: quanti indirizzi MAC sono associati all’interfaccia?

**Risposte:**

1. Il comando `lease` specifica per quanto tempo l'indirizzo IP assegnato a un client rimarrà valido prima di dover essere rinnovato. Accetta come parametri giorni, ore e minuti (`lease [days] [hours] [minutes]`), oppure la keyword `infinite` per non farlo scadere mai. Altri comandi utili in dhcp-config sono `network` (definisce la subnet del pool), `default-router` (definisce il gateway), `dns-server` (imposta il server DNS).

2. Se si assegna manualmente un indirizzo IP già distribuito dal DHCP (es. DOC2 si prende staticamente l'IP di DOC1), si verificherà un **conflitto di indirizzi IP** nella rete. Cisco IOS tenta di mitigare questo problema con il "DHCP Conflict Logging": il DHCP server (o la macchina stessa, tramite gratuitous ARP) rileva che l'IP è già in uso. La macchina DOC2 con IP statico causerà problemi di connettività a DOC1.

3. Sì, è possibile usando il comando globale `ip dhcp excluded-address` prima di dichiarare il pool, per escludere gli indirizzi che NON vogliamo assegnare. Per assegnare solo il range .100 - .110 scriveremmo:
   `ip dhcp excluded-address 192.168.0.1 192.168.0.99`
   `ip dhcp excluded-address 192.168.0.111 192.168.0.254`

4. DOC1 si accorge che STD1 si trova in una sottorete diversa controllando la propria netmask. Quindi impacchetta il messaggio e lo invia al proprio Default Gateway (il Router). Il pacchetto passa da DOC1 allo switch, lo switch lo instrada sulla porta trunk inviandolo al Router. Il router lo riceve sulla sub-interface della VLAN Docenti, ne legge l'IP di destinazione, capisce che appartiene alla sottorete Studenti connessa direttamente sull'altra sub-interface, lo re-incapsula nella VLAN Studenti e lo rimanda giù sullo stesso link trunk. Lo switch lo riceve sulla VLAN Studenti e lo inoltra verso la porta di STD1.

5. In questo specifico schema "Router on a stick", ci sarebbe **una sotto-interfaccia logica per ogni VLAN** presente. Quindi, aggiungendo una VLAN, il router avrebbe 3 sotto-interfacce sullo stesso collegamento fisico.

6. Il numero di sotto-interfacce è limitato logicamente dal protocollo di trunking (l'ID VLAN 802.1Q è di 12 bit, quindi ci sono massimo 4094 VLAN utilizzabili). Quindi un massimo di circa 4000 sotto-interfacce (sottoposto a eventuali limitazioni di memoria o limiti imposti dall'IOS specifico della macchina).

7. È associato un **singolo indirizzo MAC**. Tutte le sotto-interfacce (es. FastEthernet0/0.1 e FastEthernet0/0.2) ereditano lo stesso MAC address ("burned-in address") dell'interfaccia fisica hardware (FastEthernet0/0) da cui derivano.
