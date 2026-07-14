#include "network.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    socketif_t socket;
    connection_t connection;
    int operando1, operando2;
    char operatore;
    float risultato;
    
    socket = createTCPServer(35000);
    if (socket < 0) {
        printf("[SERVER] Errore di creazione del socket\n");
        return 1;
    }
    
    printf("[SERVER] Servizio di calcolo remoto TCP (3 messaggi) avviato.\n");
    
    while(1) {
        printf("[SERVER] In attesa di richieste di connessione...\n");    
        connection = acceptConnection(socket);
        printf("[SERVER] Connessione instaurata col client.\n");
        
        // Ricezione in 3 messaggi
        TCPReceive(connection, &operando1, sizeof(int));
        TCPReceive(connection, &operatore, sizeof(char));
        TCPReceive(connection, &operando2, sizeof(int));
        
        printf("[SERVER] Ricevuti: %d %c %d. Elaborazione...\n", operando1, operatore, operando2);
        
        // Calcolo
        switch(operatore) {
            case '+': risultato = (float)(operando1 + operando2); break;
            case '-': risultato = (float)(operando1 - operando2); break;
            case '*': risultato = (float)(operando1 * operando2); break;
            case '/': 
                if (operando2 != 0) {
                    risultato = (float)operando1 / (float)operando2; 
                } else {
                    printf("[SERVER] Attenzione: divisione per zero!\n");
                    risultato = 0.0f;
                }
                break;
            default:
                printf("[SERVER] Operatore non riconosciuto.\n");
                risultato = 0.0f;
        }
        
        printf("[SERVER] Risultato: %.2f. Invio in corso...\n", risultato);
        TCPSend(connection, &risultato, sizeof(float));
        
        closeConnection(connection);
        printf("[SERVER] Connessione chiusa.\n\n");
    }
    return 0;
}
