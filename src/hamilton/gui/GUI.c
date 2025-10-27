#include "atlbase.h"
#include "hamilton.h"

/**
* Funktion um asynchrone Programmierung mit einem UI zu zeigen
*
* Hier wird vollständig auf die ATL Uibase zurück gegriffen
* Bedeutet hier werden die UI-Tools, GTK4 und Libadwaita genutzt (Linux/Gnome spezifisch)
*
* Nur verstehen wenn man sich intensiver mit GTK beschäftigen will
*/

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

static void on_entry_submitted(const gchar *text, gpointer user_data)
{
    g_print("User entered: %s\n", text);
}

static void open_name_dialog(GtkWidget *widget, gpointer stack)
{
    show_entry_dialog(widget,
                            "Eingabe Nutzername",
                            "Bitte geben Sie unten Ihren Namen ein.:",
                            "Bestätigen",
                            "Abbrechen",
                            "Name:",
                            "Margaret Hamilton",
                            on_entry_submitted,
                            NULL);
}

static void multi_progress_dialog(GtkWidget *widget, gpointer stack)
{
	// prepare commands and descriptions
    GSList *commands = NULL;

    CommandEntry *entry1 = g_new0(CommandEntry, 1);
    entry1->cmd = g_strdup("sleep 2"); 
    entry1->description = g_strdup("Initialize the system..."); 
    commands = g_slist_append(commands, entry1);
    
    CommandEntry *entry2 = g_new0(CommandEntry, 1);
    entry2->cmd = g_strdup("ls -l");
    entry2->description = g_strdup("Fetching filesystem informations...");
    commands = g_slist_append(commands, entry2);
    
    CommandEntry *entry3 = g_new0(CommandEntry, 1);
    entry3->cmd = g_strdup("sleep 2");
    entry3->description = g_strdup("Preparing filesystem...");
    commands = g_slist_append(commands, entry3);
	
	CommandEntry *entry4 = g_new0(CommandEntry, 1);
    entry4->cmd = g_strdup("sleep 3");
    entry4->description = g_strdup("Patching filesystem...");
    commands = g_slist_append(commands, entry4);
	
	CommandEntry *entry5 = g_new0(CommandEntry, 1);
    entry5->cmd = g_strdup("curl -O https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.17.5.tar.xz");
    entry5->description = g_strdup("Downloading update files...");
    commands = g_slist_append(commands, entry5);
	
    CommandEntry *entry6 = g_new0(CommandEntry, 1);
    entry6->cmd = g_strdup("sleep 5");
    entry6->description = g_strdup("Installing images...");
    commands = g_slist_append(commands, entry6);
    
    CommandEntry *entry7 = g_new0(CommandEntry, 1);
    entry7->cmd = g_strdup("sleep 1");
    entry7->description = g_strdup("Running postinstall...");
    commands = g_slist_append(commands, entry7);

    CommandEntry *entry8 = g_new0(CommandEntry, 1);
    entry8->cmd = g_strdup("sleep 3");
    entry8->description = g_strdup("Finalize the configuration...");
    commands = g_slist_append(commands, entry8);
	
	CommandEntry *entry9 = g_new0(CommandEntry, 1);
    entry9->cmd = g_strdup("echo 'Fertig aktualisiert'");
    entry9->description = g_strdup("Finalize the configuration...");
    commands = g_slist_append(commands, entry9);
	
    // show the dialog and run the commands
    show_progress_dialog_multi(widget, "System-Update", "Das braucht so seine Zeit...", commands);
}

// main window
static void activate_hamilton(GtkApplication* app, gpointer user_data) 
{   
    // use the advanced custom css provider
    use_adw_provider();
        
    // create the main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), _("Test UI Base"));
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);  

    // create a box container for the main content
    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), content_box);
    gtk_widget_set_halign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(content_box, TRUE);
    gtk_widget_set_vexpand(content_box, TRUE);
    
    // create the stack for navigation
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 300);
    gtk_widget_set_hexpand(stack, TRUE);
    gtk_widget_set_vexpand(stack, TRUE);
    
    // add the stack to the box
    gtk_box_append(GTK_BOX(content_box), stack);
    
    // create the home page grid
    GtkWidget *home_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    
    GtkWidget *btn1 = create_button_icon_position("pan-start-symbolic", _("Man-in-the-loop"), G_CALLBACK(open_name_dialog), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("pan-start-symbolic", _("Asynchroner Spaß"), G_CALLBACK(multi_progress_dialog), stack, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(home_page), btn1);
    gtk_box_append(GTK_BOX(home_page), btn2);
    
    // add grid to stack
    gtk_stack_add_named(GTK_STACK(stack), home_page, "home_page");
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "home_page");
    
	// present the window
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) 
{	   	
	g_autoptr(AdwApplication) app = NULL;
	
   	app = adw_application_new("com.presentation.hamilton", G_APPLICATION_DEFAULT_FLAGS);
  	g_signal_connect(app, "activate", G_CALLBACK (activate_hamilton), NULL);

   	return g_application_run(G_APPLICATION (app), argc, argv);
}
