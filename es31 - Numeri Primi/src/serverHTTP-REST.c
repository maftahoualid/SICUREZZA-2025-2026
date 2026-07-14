#include "network.h"

float calcolaSomma(float val1, float val2)  {
   return (val1 + val2);
}

int main(){
    socketif_t sockfd;
    FILE* connfd;
    int res, i;
    long length=0;
    char request[MTU], url[MTU], method[10], c;
    
    sockfd = createTCPServer(8000);
    if (sockfd < 0){
        printf("[SERVER] Errore: %i\n", sockfd);
        return -1;
    }
    
    while(true) {
        connfd = acceptConnectionFD(sockfd);
        
        fgets(request, sizeof(request), connfd);
        strcpy(method,strtok(request, " "));
        strcpy(url,strtok(NULL, " "));
        while(request[0]!='\r') {
            fgets(request, sizeof(request), connfd);
            if(strstr(request, "Content-Length:")!=NULL)  {
                length = atol(request+15);
            }
        }
        
        if(strcmp(method, "POST")==0)  {
            for(i=0; i<length; i++)  {
                c = fgetc(connfd);
            }
        }
        
        if(strstr(url, "calcola-somma")!=NULL)  {
            printf("Chiamata a funzione sommatrice\n");
            
            char *function, *op1, *op2;
            float somma, val1, val2;
   
            // skeleton: decodifica (de-serializzazione) dei parametri
            function = strtok(url, "?&");
            op1 = strtok(NULL, "?&");
            op2 = strtok(NULL, "?&");
            strtok(op1,"=");
            val1 = atof(strtok(NULL,"="));
            strtok(op2,"=");
            val2 = atof(strtok(NULL,"="));
            
            // chiamata alla business logic
            somma = calcolaSomma(val1, val2);
            
            // skeleton: codifica (serializzazione) del risultato
            fprintf(connfd,"HTTP/1.1 200 OK\r\n\r\n{\r\n    \"somma\":%f\r\n}\r\n", somma);
        }
        else if(strstr(url, "calcola-primi")!=NULL) {
            printf("Chiamata a funzione calcolo numeri primi\n");
            
            char *function, *op1, *op2;
            int min, max, i, j, flag, first = 1;
            
            // decodifica
            function = strtok(url, "?&");
            op1 = strtok(NULL, "?&");
            op2 = strtok(NULL, "?&");
            strtok(op1,"=");
            min = atoi(strtok(NULL,"="));
            strtok(op2,"=");
            max = atoi(strtok(NULL,"="));
            
            // intestazione HTTP e inizio JSON
            fprintf(connfd, "HTTP/1.1 200 OK\r\n\r\n{\r\n    \"primi\": [\r\n");
            
            // business logic
            for (i = min; i <= max; i++) {
                if (i == 1 || i == 0)
                    continue;
                flag = 1;
                for (j = 2; j <= i / 2; ++j) {
                    if (i % j == 0) {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    if (!first) {
                        fprintf(connfd, ",\n");
                    }
                    fprintf(connfd, "        %d", i);
                    first = 0;
                }
            }
            
            // fine JSON
            fprintf(connfd, "\n    ]\r\n}\r\n");
        }
        else {
            fprintf(connfd,"HTTP/1.1 200 OK\r\n\r\n{\r\n    Funzione non riconosciuta!\r\n}\r\n");
        }
        
        fclose(connfd);
                
        printf("\n\n[SERVER] sessione HTTP completata\n\n");
    }
    
    closeConnection(sockfd);
    return 0;
}



