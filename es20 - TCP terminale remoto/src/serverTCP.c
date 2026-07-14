#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int main(void) {
    socketif_t server_socket;
    connection_t connection;
    char command[BUF_SIZE];
    char output[BUF_SIZE];
    FILE *fp;

    server_socket = createTCPServer(40000);
    if (server_socket < 0) {
        printf("[SERVER] Errore di creazione del socket del server\n");
        return 1;
    }

    printf("[SERVER] Servizio Terminale Remoto avviato sulla porta 40000.\n");
    printf("[SERVER] In attesa di comandi...\n");

    while(1) {
        connection = acceptConnection(server_socket);
        if (connection < 0) continue;
        
        printf("\n[SERVER] Nuovo client connesso.\n");

        // Ricezione del comando (leggiamo un carattere alla volta fino al terminatore)
        char byte;
        int i = 0;
        while (TCPReceive(connection, &byte, 1) > 0) {
            command[i++] = byte;
            if (byte == '\0' || i == BUF_SIZE - 1) break;
        }
        command[i] = '\0';

        printf("[SERVER] Comando ricevuto: %s\n", command);

        // Esegue il comando e ne cattura l'output
        // "r" permette di leggere lo stdout del comando eseguito
        fp = popen(command, "r");
        if (fp == NULL) {
            strcpy(output, "Errore: impossibile eseguire il comando.\n");
            TCPSend(connection, output, strlen(output));
        } else {
            // Legge l'output e lo invia al client a blocchi
            int bytesRead;
            while ((bytesRead = fread(output, 1, BUF_SIZE, fp)) > 0) {
                TCPSend(connection, output, bytesRead);
            }
            pclose(fp);
        }

        // Chiude la connessione con questo client (il client rileverà 0 byte letti o chiusura e terminerà)
        closeConnection(connection);
        printf("[SERVER] Esecuzione terminata, output inviato. Connessione chiusa.\n");
    }

    return 0;
}
