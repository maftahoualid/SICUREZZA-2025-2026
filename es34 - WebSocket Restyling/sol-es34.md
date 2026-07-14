**DOMANDA:**

Esercizio 1
Modificare a piacimento il contenuto del file public/index.html e valutarne
l’impatto grafico

**Risposta:**






**Soluzione Esercizio 1:** Modifica grafica e impatto visivo

Operazioni Preliminari:
1. Ho copiato tutto il codice sorgente originale in `es34 - WebSocket Esercizio 1`.
2. Ho stravolto il file `public/index.html` e riscritto da zero il foglio di stile `public/styles.css`.
3. Ho avviato il server Node.js in background. Per visualizzare il risultato, basta collegarsi a `http://localhost:4000`.

Analisi dell'impatto grafico (Il restyling):

**L'interfaccia originale era molto "grezza":** un contenitore bianco su sfondo bianco, pulsanti squadrati e tipografia di sistema, caratteristiche tipiche di un prototipo base. 

Per modernizzare l'interfaccia e offrire un impatto visivo ("WOW factor") all'altezza delle applicazioni web contemporanee, ho implementato le seguenti migliorie strutturali e stilistiche in CSS puro:

1. **Il Tema (Dark Gradient):**
   Ho sostituito lo sfondo bianco con un gradiente diagonale scuro (da blu notte profondo a indaco). Questo fa risaltare il riquadro centrale della chat e riduce l'affaticamento visivo (Dark Mode nativa).

2. **Glassmorphism (Effetto Vetro Smerigliato):**
   Invece di un semplice colore a tinta unita per il container della chat, ho utilizzato uno sfondo semi-trasparente (`rgba(255, 255, 255, 0.05)`) combinato con la direttiva `backdrop-filter: blur(12px)`. Questo simula l'effetto di un pannello di vetro sospeso sopra lo sfondo, conferendo una profondità tridimensionale tipica delle UI di iOS o di Windows 11.

3. **Tipografia Moderna:**
   Ho rimosso il font di default (Nunito/System) e importato *Poppins* da Google Fonts. Le sue geometrie rotonde e i pesi marcati (`font-weight: 600`) donano alla WebApp un tono molto più amichevole, netto e leggibile.

4. **Animazioni e Dettagli (Micro-Interactions):**
   - Ho trasformato il bottone "Send" da un blocco rettangolare a un pulsante circolare flottante inserendo un'icona SVG vettoriale minimalista (un aeroplanino di carta).
   - Ho aggiunto degli effetti di *hover* (il bottone si ingrandisce al passaggio del mouse e si rimpicciolisce al click, animato fluidamente tramite `transition: all 0.3s ease`).
   - I nuovi messaggi che appaiono in chat, invece di spuntare di scatto, hanno ora un'animazione `fadeIn` CSS (`@keyframes`) che li fa "scivolare" dolcemente dal basso verso l'alto rendendo l'esperienza visiva fluida e gratificante.

Il risultato è una chat che, pur mantenendo l'identica infrastruttura e tecnologia WebSocket dell'esercizio precedente (Node.js e Socket.io), appare all'utente finale come un'applicazione premium, dimostrando quanto l'impatto grafico (Frontend) possa alterare drasticamente la percezione di qualità del software, a parità di backend.
