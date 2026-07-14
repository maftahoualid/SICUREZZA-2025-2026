#include "network.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    connection_t connection;
    int operando1, operando2;
    char operatore;
    float risposta;
 	
    printf("[CLIENT] --- CALCOLATRICE REMOTA TCP (3 Messaggi) ---\n");
    printf("[CLIENT] Creo una connessione col server...\n");
    connection = createTCPConnection("localhost", 35000);
    if (connection < 0) {
        printf("[CLIENT] Errore nella connessione al server\n");
        return 1;
    }
    
    printf("Inserisci il primo operando: ");
    scanf("%d", &operando1);
    
    printf("Inserisci l'operatore (+, -, *, /): ");
    scanf(" %c", &operatore);
    
    printf("Inserisci il secondo operando: ");
    scanf("%d", &operando2);
    
    printf("[CLIENT] Spedisco i dati in 3 messaggi distinti...\n");
    TCPSend(connection, &operando1, sizeof(int));
    TCPSend(connection, &operatore, sizeof(char));
    TCPSend(connection, &operando2, sizeof(int));
    
    printf("[CLIENT] In attesa del risultato...\n");
    TCPReceive(connection, &risposta, sizeof(float));
    printf("[CLIENT] Ho ricevuto il risultato dal server: %.2f\n", risposta);
    
    closeConnection(connection);
    return 0;
}
