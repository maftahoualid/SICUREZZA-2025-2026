# Makefile Globale per compilare tutti gli esercizi

SUBDIRS = 'es01 - UDP base e ordine avvio' \
          'es02 - UDP porte specifiche' \
          'es03 - UDP porte privilegiate' \
          'es04 - UDP localhost e hostname' \
          'es05 - UDP macchine diverse' \
          'es06 - UDP riutilizzo porta' \
          'es07 - UDP limite richieste' \
          'es08 - UDP invio numeri' \
          'es09 - UDP sommatrice' \
          'es10 - UDP sommatrice inaffidabilita' \
          'es11 - UDP sommatrice multiclient' \
          'es12 - TCP base' \
          'es13 - TCP sommatrice' \
          'es14 - TCP sommatrice bloccante' \
          'es15 - TCP sommatrice affidabilita' \
          'es16 - TCP trasferimento file' \
          'es17 - UDP calcolo remoto' \
          'es18 - TCP calcolo remoto' \
          'es19 - TCP servizio telepass' \
          'es20 - TCP terminale remoto' \
          'es22 - Web server' \
          'es23 - Web form GET' \
          'es24 - Web form POST' \
          'es25 - Web server URL' \
          'es26 - Upload file server web' \
          'es27 - Web server CGI' \
          'es29 - Webservice' \
          'es30 - Client Java' \
          'es31 - Numeri Primi' \
          'es32 - Thread REST'

all:
	@printf "\033[1;36m=== Inizio compilazione globale ===\033[0m\n"
	@for dir in $(SUBDIRS); do \
		$(MAKE) --no-print-directory -C "$$dir"; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) --no-print-directory -C "$$dir" clean; \
	done
