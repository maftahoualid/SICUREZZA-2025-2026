#include "network.h"

int main(void) {
    connection_t connection;
    int request, response;
 	
    printf("[CLIENT] Creo una connessione logica col server\n");
    connection = createTCPConnection("localhost", 35000);
    if (connection < 0) {
        printf("[CLIENT] Errore nella connessione al server: %i\n", connection);
    }
    else
    {
        do {
            printf("[CLIENT] Inserisci un numero intero (0 per terminare):\n");
            scanf("%d", &request);
            TCPSend(connection, &request, sizeof(request));
        } while(request != 0);
        
        printf("[CLIENT] Invio terminato, in attesa della somma...\n");
        TCPReceive(connection, &response, sizeof(response));
        printf("[CLIENT] Ho ricevuto la seguente somma dal server: %d\n", response);
        closeConnection(connection);
    }
}


