#include "hamilton.h"

/**
* Funktion für Man-in-the-loop
*/
void mitl() 
{
	char weintraube[2];
    
    printf("Gibt es heute Weintrauben zum Mittag? (j/n): \n");
     	
  	/**
  	* Man-in-the-loop
   	*
   	* Hier wird gewartet bis eine Nutzereingabe kommt
   	*
	* Fehlertoleranz 1.:
	* erstes Zeichen wird gelesen
   	*/
    scanf("%c", &weintraube);
     
    /** 
    * Auswertung der Eingabe:
    *
    * Fehlertoleranz 2.: 
    * Überprüft, ob der String mit 'j', 'J', 'y', oder 'Y' beginnt. Die werden alle entgegen genommen.
    * Falls der Benutzer z.B. "ja" oder "yes" eingibt, wird es trotzdem als "wahr" erkannt.
    */
    if (strcmp(weintraube, "j") == 0 || strcmp(weintraube, "J") == 0 || strcmp(weintraube, "y") == 0 || strcmp(weintraube, "Y") == 0 )
    {
    	printf("Du solltest lieber in die Mensa gehen. Nur Obst essen ist nicht gesund.");
    }
    /**
	* Standard, falls irgendwas anderes eingegeben wurde
	*/
    else
    {
    	printf("Du solltest auch mal Obst essen. Vitamine sind wichtig.");
    }
}

/**
* Für alle die nicht so coole Variante in Java wollen
*/
/*
import java.util.Scanner;

public class Mittagsfrage {

    public static void mitl() {
        // Erstellen eines Scanner-Objekts
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Gibt es heute Weintrauben zum Mittag? (j/n):");

        // Man-in-the-loop: Hier wird auf eine Nutzereingabe gewartet.
        // Fehlertoleranz 1.: Liest die gesamte Zeile als String
        String weintraubeEingabe = scanner.nextLine();
        
        // Scanner freigeben, durch überschreiben
        // Schließen macht sich nicht so gut
        scanner = new Scanner(System.in);

        // Auswertung der Eingabe:
        // Fehlertoleranz 2.: überprüft, ob der String mit 'j', 'J', 'y', oder 'Y' beginnt.
        // Falls der Benutzer z.B. "ja" oder "yes" eingibt, wird es trotzdem als "wahr" erkannt.
        if (weintraubeEingabe.toLowerCase().startsWith("j") || weintraubeEingabe.toLowerCase().startsWith("y")) {
            System.out.println("Du solltest lieber in die Mensa gehen. Nur Obst essen ist nicht gesund.");
        }
        
        // Standard, falls etwas anderes eingegeben wurde (n, nein, alles andere)
        else {
            System.out.println("Du solltest auch mal Obst essen. Vitamine sind wichtig.");
        }
    }

    // Funktion ausführen
    public static void main(String[] args) {
        mitl();
    }
}
*/
