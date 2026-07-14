#include "network.h"

int main(void) {
    int request, response;
    socketif_t socket;
    connection_t connection;
    
    socket = createTCPServer(35000);
    if (socket < 0){
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
    }
    else
    {
        printf("[SERVER] Sono in attesa di richieste di connessione da qualche client\n");    
        connection = acceptConnection(socket);
        int somma = 0;
        printf("[SERVER] Connessione instaurata\n");
        do {
            TCPReceive(connection, &request, sizeof(request));
            printf("[SERVER] Ho ricevuto la seguente richiesta dal client: %d\n", request);
            somma += request;
        } while (request != 0);
        printf("[SERVER] Invio la somma al client\n");
        TCPSend(connection, &somma, sizeof(somma));
        closeConnection(connection);
    }
}

