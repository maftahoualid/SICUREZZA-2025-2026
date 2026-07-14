#include "network.h"
#include <stdio.h>
#include <stdlib.h>

// Definiamo la struttura del messaggio
typedef struct {
    int operando1;
    int operando2;
    char operatore;
} RichiestaCalcolo;

int main(void) {
    socketif_t socket;
    char hostAddress[MAXADDRESSLEN];
    int port;
    RichiestaCalcolo richiesta;
    float risposta;
    
    // Creiamo il socket UDP del client sulla porta 20000
    socket = createUDPInterface(20000);
    if (socket < 0) {
        printf("[CLIENT] Errore creazione socket UDP\n");
        return 1;
    }
    
    printf("[CLIENT] --- CALCOLATRICE REMOTA ---\n");
    printf("Inserisci il primo operando: ");
    scanf("%d", &richiesta.operando1);
    
    printf("Inserisci l'operatore (+, -, *, /): ");
    scanf(" %c", &richiesta.operatore);
    
    printf("Inserisci il secondo operando: ");
    scanf("%d", &richiesta.operando2);
    
    printf("[CLIENT] Spedisco la richiesta di calcolo al server...\n");
    UDPSend(socket, &richiesta, sizeof(RichiestaCalcolo), "127.0.0.1", 35000);
     
    // Attendiamo la risposta
    UDPReceive(socket, &risposta, sizeof(float), hostAddress, &port);
    printf("[CLIENT] Ho ricevuto il risultato dal server: %.2f\n", risposta);
    
    return 0;
}
