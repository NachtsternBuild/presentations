#include "hamilton.h"

// Anzahl ans Aufgaben die es maximal sein dürfen
#define MAX_TASKS 10

/**
* Wie sieht eine Aufgabe aus.
*
* Array weil die alle lieben
* Global definiert
*/
typedef struct {
    char message[100]; // eine Nachricht mit maximaler Länge
    int priority;      // und eine Zahl (1 = höchste Prio, 7 = niedrigste Prio)
    int time_required; // für Round Robin und MLFQ
} Task;


// Array erstellen mit der maximalen Aufgaben Anzahl
Task task_list[MAX_TASKS];
int task_count = 0; 

/**
 * Vergleichsfunktion für qsort() → Nur mit dabei weil irgendwie muss 
 * Definiert, wie zwei Task-Strukturen basierend auf ihrer Priorität sortiert werden.
 *
 * Regeln:
 * - Wenn Prio A < Prio B, soll A vor B kommen (Rückgabe < 0).
 * - Wenn Prio A > Prio B, soll B vor A kommen (Rückgabe > 0).
 *
 * niedrigere Zahlen = höhere Priorität → subtrahieren.
 */
int compare_tasks(const void *a, const void *b) 
{
    // Umwandlung von void* Pointern in Task* Pointer
    const Task *taskA = (const Task *)a;
    const Task *taskB = (const Task *)b;
    
    /**
    * Subtraktion liefert das gewünschte Ergebnis:
    // Lies:
    // Wenn die Priorität von TaskA kleiner ist als die von TaskB Ergebnis negativ
	*/
    return taskA->priority - taskB->priority;
}

/**
 * Funktion zum "Übergeben" einer neuen Aufgabe (Argumente).
 * Dies simuliert das Hinzufügen der Aufrufe in einer unbekannten Reihenfolge.
 */
void submit_task(const char* message, int priority, int time_required)
{
    /**
    * Fehlertoelranz:
    * Ausgabe des Fehlers, kein beenden
    */
    if (task_count >= MAX_TASKS)
    {
        fprintf(stderr, "Das war zuviel. Ich gehe wandern.\n");
        return;
    }

    /**
    * Fehlerbehandlung/Fehlertoleranz:
    *
    * Priorität muss gültig sein
    */
    if (priority < 1 || priority > 7) 
    {
        fprintf(stderr, "Diese Priorität mag ich nicht: %d\n", priority);
        return;
    }

    /**
	* Jetzt wird es kompilziert:
	*
	* Ist aber auch erstmal egal, ob ihr es versteht
	*/
    // Speichern der Nachricht + Prioröität in einer Liste
    strncpy(task_list[task_count].message, message, sizeof(task_list[task_count].message) - 1);
    task_list[task_count].message[sizeof(task_list[task_count].message) - 1] = '\0'; // Sicherstellen das nischt null ist
    // Priorität setzen
    task_list[task_count].priority = priority;
    // Task Zeit setzen
    task_list[task_count].time_required = time_required;
    
    task_count++;
}

/**
* Statisches Scheduling (First-Come-First-Served)
*/
void execute_first_come_first_served() 
{
    if (task_count == 0) 
    {
        printf("Nix zu tun.\n");
        return;
    }

    printf("\n--- Statisches Scheduling (First-Come-First-Served) ---\n");
    
    /**
    * Aufrufen des Tasks 
	* Wer zuerst kommt, malt zuerst
    */
    for (int i = 0; i < task_count; i++) 
    {
        printf("Task %d: %s (Prio %d, Dauer %d)\n", i + 1, task_list[i].message, task_list[i].priority, task_list[i].time_required);
        sleep(1);
    }
}

/**
* Prioritätsbasiertes Scheduling
*/
void execute_tasks_by_priority() 
{
    if (task_count == 0) 
    {
        printf("Nix tun. Wie schön.\n");
        return;
    }
    
    printf("\n --- Prioritätsbasiertes Scheduling (1 bis 7) ---\n");

    /**
    * Sortierung der Aufgaben mit qsort()
    * Nicht wichtig wie das funktioniert, wir brauchen nur eine sortierte Liste
    * Einfach Benutzen!
    */
    qsort(task_list, task_count, sizeof(Task), compare_tasks);

    /**
    * Nun das Aufrufen der Task nach ihrer Priorität
	* @arg Priorität
    * @arg die Nachricht
    */
    for (int i = 0; i < task_count; i++) 
    {
        printf("[Prio %d]: %s\n", task_list[i].priority, task_list[i].message);
    }
}

/**
* Round Robin Scheduling = Zeitscheibenverfahren
* Jeder Task bekommt eine feste "Zeitscheibe" (quantum), z. B. 2 Sekunden CPU-Zeit.
* Danach wird der Task unterbrochen, der nächste Task läuft.
* Wenn der Task noch nicht fertig ist, kommt er später wieder dran.
* → Fairness für alle Tasks.
*/
void execute_round_robin(int quantum) 
{
    if (task_count == 0) 
    {
        printf("Keine Tasks vorhanden.\n");
        return;
    }

    printf("\n--- Round Robin Scheduling (Zeitscheibe = %d) ---\n", quantum);

    int remaining = task_count;   // Wie viele Tasks sind noch nicht fertig?
    int time_remaining[MAX_TASKS];      // Zeit, die jeder Task noch braucht
    
    // Anfangszustand: alle Restzeiten = ursprüngliche Dauer
    for (int i = 0; i < task_count; i++) 
    {
        time_remaining[i] = task_list[i].time_required;
    }
	
	// Solange es noch unfertige Tasks gibt
    while (remaining > 0) 
    {
        // Jeder Task kommt reihum dran
        for (int i = 0; i < task_count; i++)
        {
            // Überspringen, wenn der Task schon fertig ist
            if (time_remaining[i] <= 0) 
            {
            	continue;
            }

            printf("Task %d läuft: %s (Restzeit %d)\n", i + 1, task_list[i].message, time_remaining[i]);
			
			// Der Task darf nur maximal `quantum` Zeiteinheiten laufen
            int run_time = (time_remaining[i] < quantum) ? time_remaining[i] : quantum;
            // Simulation von der Laufzeit des Tasks
            sleep(run_time);
            // Verbleibende Zeit verringern
            time_remaining[i] -= run_time;
			
			 // Falls der Task nun fertig ist → entfernen
            if (time_remaining[i] <= 0) 
            {
                printf("Task %d fertig!\n", i + 1);
                remaining--;
            }
        }
    }
}

/**
* Multilevel Feedback Queue (MLFQ)
*
* Das ist ein adaptives Scheduling-System:
* - Es gibt mehrere Warteschlangen ("Queues") mit unterschiedlichen Zeitscheiben.
* - Ein Task startet in der höchsten (schnellsten) Queue.
* - Wenn er seine Zeitscheibe überschreitet, "fällt" er in die nächste (langsamere) Queue.
* - Dadurch bekommen interaktive, kurze Tasks mehr Reaktionszeit.
* - Lange Tasks werden nach unten gestuft und dürfen seltener laufen.
*
* Ab und an	werden alle Tasks wieder in die höchste Queue gesetzt, um zu verhindern, dass den Task die Ressourcen nicht dauerhaft vorenthalten werden.
*/
void execute_mlfq() 
{
    if (task_count == 0) 
    {
        printf("Keine Tasks vorhanden.\n");
        return;
    }

    printf("\n--- Multilevel Feedback Queue Scheduling ---\n");

    // 3 Queues mit unterschiedlichen Zeitscheiben
    #define LEVELS 3
	int quantum[LEVELS] = {1, 2, 4}; // Queue 0: 1 Sekunde, Queue 1: 2 Sek., Queue 2: 4 Sek.
    int priority_boost = 5; // Nach 5 "Zeiteinheiten" werden die Tasks auf ein höheres Queue

    // Kopieren der Restzeiten
    int time_remaining[MAX_TASKS]; // Restlaufzeit jedes Tasks
    int current_level[MAX_TASKS]; // Welche Queue der Task aktuell hat

    // Anfangszustand: jeder Task startet in der höchsten Queue (Level 0)
    for (int i = 0; i < task_count; i++) 
    {
        time_remaining[i] = task_list[i].time_required;
        current_level[i] = 0; 
    }

    int remaining = task_count; // Wie viele Tasks sind noch nicht fertig?
    int time_passed = 0; // Simulierte Zeit, um Boost zu erkennen

	// Haupt-Simulationsschleife
    while (remaining > 0) 
    {
        for (int i = 0; i < task_count; i++) 
        {
            // Task bereits fertig → fortfahren
            if (time_remaining[i] <= 0) 
            {
            	continue;
			}
			
            int lvl = current_level[i]; // Aktuelle Queue-Stufe (0 = höchste)
            
            printf("Task %d läuft auf Queue %d: %s (Rest %d)\n", i + 1, lvl, task_list[i].message, time_remaining[i]);
			
			 // Laufzeit = Minimum aus Restzeit oder Quantum der aktuellen Queue
            int run_time = (time_remaining[i] < quantum[lvl]) ? time_remaining[i] : quantum[lvl];
            
            // Simulation des Ablaufs von einem Prozess
            sleep(run_time);
            time_remaining[i] -= run_time;
            time_passed += run_time;

            if (time_remaining[i] <= 0) 
            {
                // Task ist fertig
                printf("Task %d abgeschlossen!\n", i + 1);
                remaining--;
            } 
            
            else if (lvl < LEVELS - 1) 
            {
                // Task ist nicht fertig → "tieferstufen" in die nächste langsamere Queue
                current_level[i]++; 
            }
			
			// Nach einer gewissen Zeit alles wieder auf die höchste Stufe setzen
            if (time_passed >= priority_boost) 
            {
                printf("Prioritäten-Boost! Alle Tasks wieder in höchste Queue.\n");
                for (int j = 0; j < task_count; j++)
                {
                    if (time_remaining[j] > 0) 
                    {
                        current_level[j] = 0; // Zurücksetzen auf höchste Queue
                	}
                }
                time_passed = 0; // Boost-Zähler zurücksetzen
            }
        }
    }
}

/**
* Hier die Beispiele, wie man das oben alles nutzt
*/
void teste_scheduling() 
{
    printf("Jetzt mal was zum Prioritätsscheduling: \n");
        
    // Task Aufrufen und berabeiten
    submit_task("Ich muss auf's Klo!", 1, 3); // Höchste Prio + Taskdauer
    submit_task("Täglicher Blödsinn", 5, 4);  // Niedrige Prio + Taskdauer
    submit_task("Irgendwas machen was der Nutzer von mir will.", 3, 2); // Mittlere Prio + Taskdauer
    submit_task("Das Mittagessen wartet.", 2, 5); // Hohe Prio + Taskdauer
    submit_task("BWL", 7, 1); // Niedrigste Prio + Taskdauer
    
    
    // Gleis <pid> ausführen von: 
    execute_first_come_first_served();
    execute_tasks_by_priority();
    execute_round_robin(2);
    execute_mlfq();
}
