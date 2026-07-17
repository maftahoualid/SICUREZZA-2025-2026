import java.io.*; 
import java.net.*;

class ClientThreadREST
{    
    public static void main(String args[])
    {
        if(args.length < 3)    {
            System.out.println("USAGE: java ClientREST tipofunzione op1 op2");
        }   
        else  {
            String tipoFunzione = args[0];

            if (tipoFunzione.equals("calcola-somma")) {
                RESTAPIThread service = new RESTAPIThread("127.0.0.1", args[0], args[1], args[2]);
                service.start();
            } 
            else if (tipoFunzione.equals("calcola-primi")) {
                
                int min = Integer.parseInt(args[1]);
                int max = Integer.parseInt(args[2]);
                
                // Dividiamo la differenza tra max e min in 3 parti uguali
                int step = (max - min) / 3;
                
                // --- DEFINIAMO I 3 INTERVALLI MANUALMENTE ---
                
                // 1° Intervallo
                int start1 = min;
                int end1 = min + step;
                
                // 2° Intervallo
                int start2 = end1 + 1;
                int end2 = min + (step * 2);
                
                // 3° Intervallo (arriva dritto fino al 'max' finale)
                int start3 = end2 + 1;
                int end3 = max;
                
                // Lanciamo i 3 thread tutti in LOCALE ("127.0.0.1")
                RESTAPIThread t1 = new RESTAPIThread("127.0.0.1", tipoFunzione, String.valueOf(start1), String.valueOf(end1));
                RESTAPIThread t2 = new RESTAPIThread("127.0.0.1", tipoFunzione, String.valueOf(start2), String.valueOf(end2));
                RESTAPIThread t3 = new RESTAPIThread("127.0.0.1", tipoFunzione, String.valueOf(start3), String.valueOf(end3));
                
                t1.start();
                t2.start();
                t3.start();
                
            } else {
                System.out.println("Funzione non riconosciuta. Usa 'calcola-somma' o 'calcola-primi'.");
            }
        }
    }
}

class RESTAPIThread extends Thread
{
    String server, service, param1, param2;

    RESTAPIThread(String remoteServer, String srvc, String p1, String p2)  {
        server = remoteServer;
        service = srvc;
        param1 = p1;
        param2 = p2;
    }

    public void run()   {
        if(service.equals("calcola-somma"))    {
            System.out.println("Risultato: " + calcolaSomma(Float.parseFloat(param1), Float.parseFloat(param2)));
        }
        else if (service.equals("calcola-primi")) {
            System.out.println("Avviato thread locale per intervallo [" + param1 + " - " + param2 + "]");
            calcolaPrimi(Integer.parseInt(param1), Integer.parseInt(param2));
        }
        else    {
            System.out.println("Servizio non disponibile!");
        }
    }

    // --- FUNZIONE ORIGINALE SOMMA ---
    synchronized float calcolaSomma(float val1, float val2)  {
        URL u = null;
        float risultato = 0;
        int i;

        try { 
            u = new URL("http://"+server+":8000/calcola-somma?param1="+val1+"&param2="+val2);
        }
        catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
        }

        try {
            URLConnection c = u.openConnection();
            c.connect();
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            String s;
            while( (s = b.readLine()) != null ) {
                if((i = s.indexOf("somma")) != -1)
                    risultato = Float.parseFloat(s.substring(i+7));
            }
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    
        return risultato;
    }    

    // --- FUNZIONE NUMERI PRIMI ---
    synchronized void calcolaPrimi(int min, int max) {
        URL u = null;
        
        try { 
            // NOTA BENE: verifica che il tuo server accetti 'min' e 'max' e non 'param1' e 'param2'
            u = new URL("http://"+server+":8000/calcola-primi?min="+min+"&max="+max);
        }
        catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
            return;
        }

        try {
            URLConnection c = u.openConnection();
            c.connect();
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            String s;
            while( (s = b.readLine()) != null ) {
                System.out.println("[Risposta Server]: " + s);
            }
        }
        catch (IOException e) {
            System.out.println("Impossibile connettersi al server. Assicurati che il server C sia in esecuzione sulla porta 8000.");
        }
    }
}
