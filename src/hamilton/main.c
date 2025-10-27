#include "hamilton.h"
     
/**
* Das hier wird alles für die ATL Uibase gebraucht.
* Sonst meckert der Compiler
* Eigentlich ist die Uibase für kompliziertere GUIs gemacht
*/ 
// define the local domain
const char *LOCALE_DOMAIN = "hamilton";
// define the filter file
const char *DEFAULT_FILTER = "";
// define the local dir
const char *LOCALEDIR_PATH = "local/";   
   // define about infos
const char *app_icon = "org.example.Typeset";
const char *app_name = "Hamilton";
const char *developer_name = "NachtsternBuild";
const char *version = "0.1.dev";
const char *release_notes_version = "0.1";
const char *release_notes = "\
<p>\
  This release adds this features:\
</p>\
<ul>\
  <li>Add basic tools.</li>\
  <li>Add entries and dialogs.</li>\
  <li>Bug fixes and performance improvements.</li>\
</ul>\
  ";
const char *comments = "This is a very unusable comment in the about";
const char *website = "https://example.org";
const char *issue_url = "https://example.org";
const char *support_url = "https://example.org";
const char *copyright = "© NachtsternBuild";
const char *developers[] = {
	"NachtsternBuild",
	NULL
};
const char *artists[] = {
	"GNOME Design Team",
	"NachtsternBuild",
	NULL
};
const char *documentation_url = "https://example.org";
const char *font_usage = "This application uses font data from <a href='https://example.org'>somewhere</a>.";
const char *special_thanks[] = {
	"Tux",
	NULL
};
   
   
/**
* Hauptfunktion
*
* Beim Aufruf startet das Programm immer hier
* Es folgt eine Prüfung mit welchem Argument der Code aufgerufen wurde. 
* So kann man wählen was man machen will und nicht einfach alles hintereinander.
*/
int main(int argc, char *argv[]) 
{	    
    /**
    * Prüfen was für Argumente per Kommandozeile mit übergeben wurden
    * Werden jetzt gebraucht um herauszufinden welche was gemacht werden soll
    */
    int arg_idx = 1;

    // Prüfen ob überhaupt welche übergeben wurden
    if (argc <= arg_idx) 
    {
     	printf("Brauchst du Hilfe?\n");
    	printf("mitl\n");
    	printf("sched\n");
    	printf("Reicht, oder? Wenn nicht habe ich Zweifel an deiner Intelligenz.\n");   
        return 0;
    }
    
    
    const char *cmd = argv[arg_idx++];
    
    /**
    * Herausfinden was gemacht werden soll
    */
    if (strcmp(cmd, "mitl") == 0)
    {
    	// Aufruf für Man-in-the-loop
    	mitl();
    }
        
    else if (strcmp(cmd, "sched") == 0)
    {
    	// Aufruf für Beispiel Scheduling
    	teste_scheduling();
    }
        
    // Nur damit falls jemand zu blöd ist weitere Argumente zu übergeben
    else 
    {
    	printf("Brauchst du Hilfe?\n");
    	printf("mitl\n");
    	printf("sched\n");
    	printf("Reicht, oder? Wenn nicht habe ich Zweifel an deiner Intelligenz.\n");
    }
    
    
    return 0;
}


