#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
   // La stringa simula un tipico URL di una richiesta HTTP GET con "Query String"
   char str[80] = "/sommatrice?op1=1&op2=2";
   char *function, *op1, *op2;
   float val1, val2;
   
   /* SPIEGAZIONE STRTOK:
    * La funzione strtok(stringa_da_dividere, "delimitatori") serve a spezzettare una stringa in "token".
    * - Il PRIMO parametro è la stringa da analizzare (da usare solo alla primissima chiamata, per le successive si usa NULL).
    * - Il SECONDO parametro è una stringa contenente uno o più caratteri usati come "forbici" (delimitatori).
    * IMPORTANTISSIMO: strtok MODIFICA la stringa originale, sostituendo i delimitatori trovati con il carattere terminatore '\0', 
    * in modo da creare tante mini-stringhe indipendenti in memoria.
    */

   // 1a CHIAMATA: Passiamo 'str'. 
   // Il delimitatore "?&" significa: "taglia non appena trovi O un '?' OPPURE una '&'".
   // Strtok scorre "/sommatrice?op1=1&op2=2", si ferma al '?' e lo rimpiazza con '\0'. 
   // Risultato: 'function' punta alla parola "/sommatrice".
   function = strtok(str, "?&");
   
   // 2a CHIAMATA: Passando NULL diciamo a strtok di "ricordarsi" la stringa di prima e riprendere da dove si era fermata.
   // Ora analizza la parte restante: "op1=1&op2=2". Trova la '&', la taglia (ci mette '\0').
   // Risultato: 'op1' punta al pezzo "op1=1".
   op1 = strtok(NULL, "?&");
   
   // 3a CHIAMATA: Riprende dopo la '&'. 
   // Non essendoci più delimitatori, prende tutto il resto fino a fine stringa.
   // Risultato: 'op2' punta a "op2=2".
   op2 = strtok(NULL, "?&");
   
   /* --------------------------------------------------------------------------------------------------
    * ORA ESTRAIAMO I VALORI NUMERICI:
    * Fino a questo momento, op1 puntava all'intera stringa "op1=1" e op2 puntava a "op2=2".
    * Ora eseguiamo di nuovo strtok passandogli come base di partenza proprio "op1" e "op2", 
    * per sminuzzarli ulteriormente cambiando il delimitatore col simbolo "=".
    */
   
   // Analizza la stringa puntata da op1 (che ora è "op1=1") e tagliala al simbolo '='. 
   // Questa mossa è fondamentale: strtok troverà l'uguale e lo sostituirà con '\0'.
   // Di conseguenza, da questo esatto istante, la variabile 'op1' punterà semplicemente a "op1"! 
   // (Il risultato restituito qui dalla funzione è ignorato, perché la magia avviene "in-place" sulla stringa).
   strtok(op1, "=");
   
   // Chiamando con NULL, riprendiamo dalla parte dopo l'uguale, ovvero il numero in formato stringa ("1").
   // La funzione atof() serve a convertire questa stringa in un vero numero con la virgola (float val1 = 1.000000).
   val1 = atof(strtok(NULL, "="));
   
   // Ripetiamo la stessa operazione per la stringa puntata da op2 ("op2=2"):
   // Trovando l'uguale, strtok lo rimpiazza con '\0'. Da qui in poi, la variabile 'op2' varrà solo "op2".
   strtok(op2, "=");
   // Estraiamo la seconda parte (il numero "2") e convertiamola in float.
   val2 = atof(strtok(NULL, "="));
   
   // Stampiamo i risultati finali per verificare il corretto disassemblaggio dell'URL.
   // Come previsto, op1 e op2 valgono solo "op1" e "op2", perché abbiamo sovrascritto l'uguale con il fine-stringa!
   printf("Endpoint: %s | Parametro 1 crudo: %s | Parametro 2 crudo: %s | Valore 1: %f | Valore 2: %f\n", function, op1, op2, val1, val2);
   
   return(0);
}
