## ⚡ Quick Start: Installazione

Copia e incolla questo blocco nel terminale per scaricare e compilare il progetto immediatamente:

```bash
git clone <INSERISCI_QUI_URL_DELLA_TUA_REPO> philosophers
cd philosophers
make

Comandi per l'Uso
La sintassi del programma è la seguente:

Bash
./philo [num_filosofi] [time_to_die] [time_to_eat] [time_to_sleep] [opzionale: num_pasti]
num_filosofi: Numero di filosofi e di forchette.

time_to_die: Millisecondi max senza mangiare prima di morire.

time_to_eat: Millisecondi necessari per mangiare.

time_to_sleep: Millisecondi passati a dormire.

num_pasti: (Opzionale) Se tutti mangiano almeno 'N' volte, il programma termina.

🧪 Scenari di Test & Cosa Aspettarsi
Ecco i test fondamentali da eseguire per la correzione.

1️⃣ Test: Il caso della Morte
Un solo filosofo. Prende una forchetta, ma non ne ha una seconda.

Bash
./philo 1 800 200 200
Cosa aspettarsi:

Il filosofo stampa has taken a fork.

Passano 800ms.

Il filosofo muore (died).

Il programma termina e restituisce il prompt.

2️⃣ Test: Sopravvivenza Infinita
Scenario standard. I tempi sono bilanciati.

Bash
./philo 5 800 200 200
Cosa aspettarsi:

Nessuno deve morire.

La simulazione continua all'infinito finché non premi CTRL+C.

I messaggi scorrono fluidi senza blocchi.

3️⃣ Test: Stop Controllato (Sazietà)
Stesso scenario, ma il programma deve fermarsi da solo dopo 7 pasti.

Bash
./philo 5 800 200 200 7
Cosa aspettarsi:

Nessuno muore.

Appena l'ultimo filosofo finisce il suo 7° pasto, il programma si ferma immediatamente.

4️⃣ Test: Stress Test (200 Filosofi)
Carico pesante per la CPU.

Bash
./philo 200 800 200 200
Cosa aspettarsi:

Il programma non deve crashare (Segfault).

Nessuno deve morire (nonostante il numero elevato di thread).

📚 I Concetti in Breve
Prima di scendere nei dettagli, ecco le basi teoriche del progetto:

Thread: Ogni filosofo è un thread, ovvero un'unità di esecuzione che lavora in parallelo agli altri.

Mutex (Mutual Exclusion): Le forchette sono risorse condivise. Un mutex è come una chiave: se un filosofo prende la forchetta (lock), nessun altro può toccarla finché non viene rilasciata (unlock).

Data Race: Errore che avviene quando due thread scrivono sulla stessa variabile contemporaneamente. Qui prevenuto proteggendo tutto con mutex.

⚙️ Logic Flow: Come lavora questo programma
Questa sezione spiega l'architettura interna e le soluzioni adottate per risolvere i problemi classici di concorrenza.

1. Inizializzazione e Risorse
Il main prepara la tavola:

Crea un array di pthread_mutex_t per le forchette.

Inizializza le strutture dati per ogni filosofo.

Lancia i thread.

2. La Routine del Filosofo (Il Cuore) 🫀
Ogni filosofo esegue un loop infinito (philo_routine) composto da tre fasi:

A. Thinking (Pensare) 🧠
Appena sveglio, il filosofo pensa.

Fairness Patch: Se il numero di filosofi è dispari, qui viene introdotta una micro-pausa (usleep).

Perché? Senza questa pausa, i filosofi più veloci ruberebbero costantemente le forchette ai vicini, facendoli morire di fame (Starvation).

B. Eating (Mangiare) 🍝
Il filosofo tenta di prendere le forchette.

Soluzione Deadlock: Per evitare lo stallo (tutti prendono la sinistra e aspettano la destra all'infinito), è stato implementato un ordine gerarchico.

Regola: Si prende SEMPRE prima la forchetta con l'ID più basso, poi quella con l'ID più alto.

Una volta mangiato, aggiorna il timestamp last_meal (protetto da mutex).

C. Sleeping (Dormire) 😴
Rilascia le forchette e dorme per il tempo stabilito.

3. Il Monitor (L'Occhio che tutto vede) 👁️
Un thread separato gira in background controllando costantemente:

Morte: Se (Tempo Corrente - Ultimo Pasto) > Time To Die -> Stampa "died" e ferma tutto.

Pasti: Se tutti i filosofi hanno raggiunto il numero di pasti target -> Ferma tutto.