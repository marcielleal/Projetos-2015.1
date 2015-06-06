#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
typedef struct{
	GSList *windows;
        /* etc... whatever application vars you need */
} MyApp;

void MenuP (GtkWidget *widget, MyApp *app);
void destroy(GtkWidget *widget,gpointer *p){
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	GtkWidget *parent = NULL;
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	gtk_widget_destroy(parent);
}
//Alterar para gravação em arquivo
void get_text(GtkWidget *widget, GtkWidget *entry){
	printf("%s\n",gtk_entry_get_text(GTK_ENTRY(entry)));
	destroy(widget);	
}

void AbrirW (GtkWidget *widget, MyApp *app){
	/* Criando construtor */
	GtkBuilder *builder;
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "test.glade",NULL);
	
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"AbrirW"));
	GtkWidget *buttonC = GTK_WIDGET(gtk_builder_get_object(builder,"button8"));
	GtkWidget *buttonS = GTK_WIDGET(gtk_builder_get_object(builder,"button6"));
	GtkWidget *entry= GTK_WIDGET(gtk_builder_get_object(builder,"entry1"));
	
	/* connect callbacks to signals */
	g_signal_connect (G_OBJECT (buttonC), "clicked", G_CALLBACK (get_text), entry);
	g_signal_connect (G_OBJECT (buttonS), "clicked", G_CALLBACK (MenuP), NULL);
	
	if(widget!=NULL){
		destroy(widget,NULL);
	}	
	gtk_widget_show_all (window);
}
void Abrir(GtkWidget *widget){
	/* Quem eh a janela pai? */
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	GtkWindow *parent = NULL;
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	
	/* Criando */
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File",parent,action,("_Cancel"),GTK_RESPONSE_CANCEL,("_Open"),GTK_RESPONSE_ACCEPT,NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT){
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		filename = gtk_file_chooser_get_filename (chooser);
	}

	gtk_widget_destroy (dialog);
}
void Salvar(GtkWidget *widget){
	/* Quem eh a janela pai? */
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	GtkWindow *parent = NULL;
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Save File",parent,action,("_Cancel"),GTK_RESPONSE_CANCEL,("_Save"),GTK_RESPONSE_ACCEPT,NULL);
	chooser = GTK_FILE_CHOOSER (dialog);
	
	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT){
		gtk_file_chooser_set_current_name (chooser,("Untitled document"));
		char *filename;
		filename = gtk_file_chooser_get_filename (chooser);
		printf("%s\n",filename);
	}

	gtk_widget_destroy (dialog);
}
void on_window_destroy (GtkWidget *widget, MyApp *app){
	app->windows = g_slist_remove (app->windows, widget);
	
	if (g_slist_length (app->windows) == 0){
		/* last window was closed... exit */
		g_debug ("Exiting...");
		g_slist_free (app->windows);
		gtk_main_quit ();
	}
}

void MenuP (GtkWidget *widget, MyApp *app){
	/* Criando construtor */
	GtkBuilder *builder;
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "test.glade",NULL);
	
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"MenuP"));
	GtkWidget *buttonC = GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
	GtkWidget *buttonS = GTK_WIDGET(gtk_builder_get_object(builder,"button7"));
	GtkWidget *buttonA = GTK_WIDGET(gtk_builder_get_object(builder,"button5"));
	GtkWidget *buttonI = GTK_WIDGET(gtk_builder_get_object(builder,"Sair1"));
	
	/* connect callbacks to signals */
	g_signal_connect (G_OBJECT (buttonC), "clicked", G_CALLBACK (Abrir), app);
	g_signal_connect (G_OBJECT (buttonS), "clicked", G_CALLBACK (Salvar), app);
	g_signal_connect (G_OBJECT (buttonA), "clicked", G_CALLBACK (AbrirW), app);
	g_signal_connect (G_OBJECT (buttonI), "clicked", G_CALLBACK (gtk_main_quit), app);
	
	
	if(widget!=NULL){
		destroy(widget,NULL);
	}	
	gtk_widget_show_all (window);
}

int main (int argc, char *argv[]){
	MyApp *app;

	gtk_init (&argc, &argv);
	app = g_slice_new (MyApp);
	app->windows = NULL;
	
	/* create first window */
	MenuP(NULL, app);
	
	gtk_main ();
	g_slice_free (MyApp, app);
	
	return 0;               
}
