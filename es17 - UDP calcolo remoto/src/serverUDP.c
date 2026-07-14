#include "network.h"
#include <stdio.h>
#include <stdlib.h>

// Definiamo la stessa struttura
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
    float risultato;
    
    // Server in ascolto sulla porta 35000
    socket = createUDPInterface(35000);
    if (socket < 0) {
        printf("[SERVER] Errore creazione socket UDP\n");
        return 1;
    }
    
    printf("[SERVER] Servizio di calcolo remoto avviato.\n");
    
    while(1) {
        printf("[SERVER] In attesa di calcoli da svolgere...\n");
        
        UDPReceive(socket, &richiesta, sizeof(RichiestaCalcolo), hostAddress, &port);
        
        printf("[SERVER] Ricevuta richiesta da %s:%d -> %d %c %d\n", 
               hostAddress, port, richiesta.operando1, richiesta.operatore, richiesta.operando2);
               
        // Calcolo
        switch(richiesta.operatore) {
            case '+': risultato = (float)(richiesta.operando1 + richiesta.operando2); break;
            case '-': risultato = (float)(richiesta.operando1 - richiesta.operando2); break;
            case '*': risultato = (float)(richiesta.operando1 * richiesta.operando2); break;
            case '/': 
                if (richiesta.operando2 != 0) {
                    risultato = (float)richiesta.operando1 / (float)richiesta.operando2; 
                } else {
                    printf("[SERVER] Attenzione: divisione per zero!\n");
                    risultato = 0.0f; // Semplificazione per evitare crash
                }
                break;
            default:
                printf("[SERVER] Operatore non riconosciuto.\n");
                risultato = 0.0f;
        }
        
        printf("[SERVER] Risultato elaborato: %.2f. Invio al client...\n", risultato);
        UDPSend(socket, &risultato, sizeof(float), hostAddress, port);
    }
    
    return 0;
}
