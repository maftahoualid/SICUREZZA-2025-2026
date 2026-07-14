#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    connection_t connection;
    char filename[256];
    char byte;
    FILE *file;
 	
    printf("[CLIENT] Creo una connessione logica col server\n");
    connection = createTCPConnection("localhost", 35000);
    if (connection < 0) {
        printf("[CLIENT] Errore nella connessione al server: %i\n", connection);
    }
    else
    {
        printf("[CLIENT] Inserisci il nome del file da richiedere:\n");
        scanf("%255s", filename);
        printf("[CLIENT] Invio richiesta per il file '%s'\n", filename);
        
        // Invia il nome del file (+1 per includere il terminatore di stringa \0)
        TCPSend(connection, filename, strlen(filename) + 1);
        
        // Apre il file locale in scrittura binaria
        file = fopen(filename, "wb");
        if (file == NULL) {
            printf("[CLIENT] Errore nell'apertura del file locale per la scrittura.\n");
            closeConnection(connection);
            return 1;
        }
        
        printf("[CLIENT] Ricezione file in corso (un byte alla volta)...\n");
        
        // Legge un byte alla volta. TCPReceive restituirà 0 quando il server chiude la connessione (EOF)
        while (TCPReceive(connection, &byte, 1) > 0) {
            fwrite(&byte, 1, 1, file);
        }
        
        printf("[CLIENT] File '%s' ricevuto e salvato con successo.\n", filename);
        
        fclose(file);
        closeConnection(connection);
    }
    return 0;
}
