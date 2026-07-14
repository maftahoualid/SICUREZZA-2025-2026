#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TARGHE 1000

// Struttura per tracciare i passaggi
typedef struct {
    char targa[16];
    int passaggi;
} RecordTelepass;

RecordTelepass database[MAX_TARGHE];
int numeroTargheRegistrate = 0;

int main(void) {
    socketif_t socket;
    connection_t connection;
    char targaRicevuta[16];
    int conteggioRisposta = 0;
    
    socket = createTCPServer(35000);
    if (socket < 0) {
        printf("[SERVER] Errore di creazione del socket\n");
        return 1;
    }
    
    printf("[SERVER] Servizio Telepass Centrale avviato. In attesa dei caselli...\n");
    
    while(1) {
        connection = acceptConnection(socket);
        printf("\n[SERVER] Casello connesso.\n");
        
        // Ricezione della targa (leggiamo un carattere alla volta fino al \0 o al limite)
        char byte;
        int i = 0;
        while(TCPReceive(connection, &byte, 1) > 0) {
            targaRicevuta[i++] = byte;
            if(byte == '\0' || i == 15) break;
        }
        targaRicevuta[i] = '\0'; // Terminatore di sicurezza
        
        printf("[SERVER] Ricevuta lettura targa: %s\n", targaRicevuta);
        
        // Cerca la targa nel database
        int trovata = 0;
        for(int j = 0; j < numeroTargheRegistrate; j++) {
            if(strcmp(database[j].targa, targaRicevuta) == 0) {
                database[j].passaggi++;
                conteggioRisposta = database[j].passaggi;
                trovata = 1;
                printf("[SERVER] Targa nota. Aggiornamento passaggi a %d.\n", conteggioRisposta);
                break;
            }
        }
        
        // Se non trovata e c'è spazio, la aggiunge
        if(!trovata) {
            if(numeroTargheRegistrate < MAX_TARGHE) {
                strcpy(database[numeroTargheRegistrate].targa, targaRicevuta);
                database[numeroTargheRegistrate].passaggi = 1;
                conteggioRisposta = 1;
                numeroTargheRegistrate++;
                printf("[SERVER] Nuova targa registrata. Passaggi inizializzati a 1.\n");
            } else {
                printf("[SERVER] ERRORE: Database pieno!\n");
                conteggioRisposta = -1; // Codice d'errore
            }
        }
        
        // Invia il conteggio aggiornato al casello
        TCPSend(connection, &conteggioRisposta, sizeof(int));
        
        closeConnection(connection);
        printf("[SERVER] Dati elaborati e connessione chiusa col casello.\n");
    }
    
    return 0;
}
