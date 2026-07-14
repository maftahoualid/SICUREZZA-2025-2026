#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    socketif_t socket;
    connection_t connection;
    char filename[256];
    char byte;
    FILE *file;
    
    socket = createTCPServer(35000);
    if (socket < 0){
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
    }
    else
    {
        printf("[SERVER] Sono in attesa di richieste di connessione da qualche client\n");    
        connection = acceptConnection(socket);
        printf("[SERVER] Connessione instaurata\n");
        
        // Riceve il nome del file (leggendo fino al terminatore di stringa o al limite del buffer)
        int i = 0;
        while (TCPReceive(connection, &byte, 1) > 0) {
            filename[i++] = byte;
            if (byte == '\0' || i == 255) break;
        }
        filename[i] = '\0'; // Sicurezza
        
        printf("[SERVER] Il client ha richiesto il file: %s\n", filename);
        
        // Apre il file in lettura binaria
        file = fopen(filename, "rb");
        if (file == NULL) {
            printf("[SERVER] Errore: File non trovato o inaccessibile.\n");
        } else {
            printf("[SERVER] Inizio trasmissione del file...\n");
            
            // Legge e trasmette un byte alla volta
            while (fread(&byte, 1, 1, file) == 1) {
                TCPSend(connection, &byte, 1);
            }
            
            fclose(file);
            printf("[SERVER] Trasmissione completata.\n");
        }
        
        // La chiusura della connessione segnala al client che la trasmissione è finita (EOF)
        closeConnection(connection);
    }
    return 0;
}
