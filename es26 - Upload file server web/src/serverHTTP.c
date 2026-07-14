#include "network.h"

int main(){
    char *HTMLResponse = "HTTP/1.1 200 OK\r\n\r\n<html><head><title>An Example Page</title></head><body>Hello World, this is a very simple HTML document.</body></html>\r\n";
    socketif_t sockfd;
    FILE* connfd;
    int res, i;
    long length=0;
    char request[MTU], method[10], c;
    
    sockfd = createTCPServer(8000);
    if (sockfd < 0){
        printf("[SERVER] Errore: %i\n", sockfd);
        return -1;
    }
    
    while(true) {
        // accetta connessione
        connfd = acceptConnectionFD(sockfd);
        
        // leggi richiesta
        fgets(request, sizeof(request), connfd);
        printf("%s", request);
        // leggi metodo
        strcpy(method,strtok(request," "));
        printf("Method: %s\n", method);
        // leggi intestazioni finche non trovi la riga vuota
        while(request[0]!='\r') {
            // leggi riga
            fgets(request, sizeof(request), connfd);
            printf("%s", request);
            // controlla se c'è l'intestazione Content-Length
            if(strstr(request, "Content-Length:")!=NULL)  {
                // se c'è, valorizza la lunghezza del corpo della richiesta
                length = atol(request+15);
                //printf("length %ld\n", length);
            }
        }

        // se il metodo è POST, leggi il corpo della richiesta
        if(strcmp(method, "POST")==0)  {
            // Apriamo un file in scrittura (salviamo l'intero payload)
            FILE *out = fopen("file_caricato_dal_client.bin", "wb");
            if (out == NULL) {
                printf("[ERRORE] Impossibile creare il file di destinazione.\n");
            }
            
            // leggi il corpo della richiesta e salvalo
            for(i=0; i<length; i++)  {
                // leggi un carattere alla volta
                c = fgetc(connfd);
                if (out != NULL) {
                    fputc(c, out);
                }
            }
            
            if (out != NULL) {
                fclose(out);
                printf("\n[SERVER] Payload POST salvato in 'file_caricato_dal_client.bin' (%ld bytes).\n", length);
            }
        }
        
        // invia risposta
        fputs(HTMLResponse, connfd);
        // chiudi connessione
        fclose(connfd);
                
        printf("\n\n[SERVER] sessione HTTP completata\n\n");
    }
    
    closeConnection(sockfd);
    return 0;
}

