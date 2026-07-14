#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int main(void) {
    connection_t connection;
    char command[BUF_SIZE];
    char output[BUF_SIZE];
    int len;

    printf("--- TERMINALE REMOTO CLIENT ---\n");
    printf("Connessione in corso al server...\n");
    
    connection = createTCPConnection("localhost", 40000);
    if (connection < 0) {
        printf("Errore: connessione al server fallita\n");
        return 1;
    }

    printf("Inserisci il comando da eseguire: ");
    if (fgets(command, BUF_SIZE, stdin) == NULL) {
        closeConnection(connection);
        return 0;
    }

    // Rimuove il newline finale se presente
    command[strcspn(command, "\n")] = '\0';

    // Invia il comando al server (incluso il terminatore \0)
    TCPSend(connection, command, strlen(command) + 1);

    printf("\n--- Output del comando ---\n");
    
    // Riceve l'output dal server a blocchi finché ci sono dati
    // TCPReceive restituirà un numero <= 0 quando il server chiuderà la connessione
    while ((len = TCPReceive(connection, output, BUF_SIZE - 1)) > 0) {
        output[len] = '\0'; // Terminatore per stampare correttamente
        printf("%s", output);
    }
    
    printf("\n--- Fine Output ---\n");

    closeConnection(connection);
    return 0;
}
