#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    connection_t connection;
    char targa[16];
    int conteggio;
 	
    printf("[CASELLO] --- TERMINALE TELEPASS ---\n");
    printf("[CASELLO] Creazione connessione verso il server centrale...\n");
    connection = createTCPConnection("localhost", 35000);
    if (connection < 0) {
        printf("[CASELLO] Errore di connessione al server\n");
        return 1;
    }
    
    printf("Acquisizione targa veicolo in avvicinamento: ");
    scanf("%15s", targa);
    
    printf("[CASELLO] Trasmissione targa '%s' al server...\n", targa);
    
    // Invia la targa (+1 per il terminatore di stringa \0)
    TCPSend(connection, targa, strlen(targa) + 1);
    
    // Attende la risposta con il conteggio dei passaggi
    TCPReceive(connection, &conteggio, sizeof(int));
    
    printf("[CASELLO] Risposta dal server: l'auto con targa %s ha effettuato %d passaggi totali.\n", targa, conteggio);
    
    closeConnection(connection);
    return 0;
}
