#include "network.h"

int main(void) {
    int request;
    int somma = 0;
    socketif_t socket;
    char hostAddress[MAXADDRESSLEN];
    int port;
    
    socket = createUDPInterface(35000);
    
    printf("[SERVER] Sono in attesa di richieste da qualche client\n");
    
    do {
        UDPReceive(socket, &request, sizeof(request), hostAddress, &port);
        printf("[SERVER] Ho ricevuto un messaggio da host/porta %s/%d\n", hostAddress, port);
        printf("[SERVER] Contenuto: %d\n", request);
        somma += request;
    } while (request != 0);
    
    UDPSend(socket, &somma, sizeof(somma), hostAddress, port);
}

