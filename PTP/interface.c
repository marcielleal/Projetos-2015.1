#include "biblioteca.h"

extern float saldo;
extern Produto produtos[300];
void cria_dialog(GtkWidget *window,char *string){
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"%s",string);
  
	gtk_window_set_title(GTK_WINDOW(dialog), "informação");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
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
	
	/* Conectando Sinais */
	g_signal_connect (G_OBJECT (buttonC), "clicked", G_CALLBACK (get_saldo), entry);
	g_signal_connect (G_OBJECT (buttonS), "clicked", G_CALLBACK (MenuP), app);
	
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
		if(abre_arquivo(produtos,filename)) printf("ALTERA ISSO AKI MULEKE");
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
		grava_arquivo(produtos,300,filename);
	}
	gtk_widget_destroy (dialog);
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
	
	/* Conectando os sinais */
	g_signal_connect (G_OBJECT (buttonC), "clicked", G_CALLBACK (AbrirW), app);
	g_signal_connect (G_OBJECT (buttonS), "clicked", G_CALLBACK (Salvar), app);
	g_signal_connect (G_OBJECT (buttonA), "clicked", G_CALLBACK (Abrir), app);
	g_signal_connect (G_OBJECT (buttonI), "clicked", G_CALLBACK (gtk_main_quit), app);
	
	
	if(widget!=NULL){
		destroy(widget,NULL);
	}	
	gtk_widget_show_all (window);
}

void MenuO (GtkWidget *widget, MyApp *app){
	/* Criando construtor */
	GtkBuilder *builder;
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "test.glade",NULL);
	
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"MenuO"));
	GtkWidget *buttonC = GTK_WIDGET(gtk_builder_get_object(builder,"button2"));
	GtkWidget *buttonV = GTK_WIDGET(gtk_builder_get_object(builder,"button3"));
	GtkWidget *buttonE = GTK_WIDGET(gtk_builder_get_object(builder,"button4"));
	GtkWidget *buttonO = GTK_WIDGET(gtk_builder_get_object(builder,"Voltar"));
	
	/* Conectando os sinais */
	g_signal_connect (G_OBJECT (buttonC), "clicked", G_CALLBACK (Icompra), app);
	g_signal_connect (G_OBJECT (buttonV), "clicked", G_CALLBACK (Ivenda), app);
	g_signal_connect (G_OBJECT (buttonE), "clicked", G_CALLBACK (Iconsulta), app);
	g_signal_connect (G_OBJECT (buttonO), "clicked", G_CALLBACK (MenuP), app);
	
	if(widget!=NULL){
		destroy(widget,NULL);
	}	
	gtk_widget_show_all (window);
}

void Icompra (GtkWidget *widget, MyApp *app){
	/* Criando construtor */
	GtkBuilder *builder;
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "test.glade",NULL);
	
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"Comprar"));
	
	GtkWidget *buttonC = GTK_WIDGET(gtk_builder_get_object(builder,"button9"));
	GtkWidget *buttonN = GTK_WIDGET(gtk_builder_get_object(builder,"button10"));
	GtkWidget *buttonV = GTK_WIDGET(gtk_builder_get_object(builder,"button11"));
	
	GtkWidget *entryC = GTK_WIDGET(gtk_builder_get_object(builder,"entry3"));
	GtkWidget *entryq1 = GTK_WIDGET(gtk_builder_get_object(builder,"entry7"));
	GtkWidget *entryq2 = GTK_WIDGET(gtk_builder_get_object(builder,"entry8"));
	
	GtkComboBoxText *combo = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder,"comboboxtext3"));
	povoar_combo(combo);
	
	/* Conectando Sinais */
	g_signal_connect (G_OBJECT(buttonV), "clicked", G_CALLBACK(MenuO), app);
	g_signal_connect (G_OBJECT(buttonC), "clicked", G_CALLBACK(get_qtd), entryq1);
	g_signal_connect (G_OBJECT(buttonC), "clicked", G_CALLBACK(get_cod), entryC);
	g_signal_connect (G_OBJECT(buttonN), "clicked", G_CALLBACK(get_qtd), entryq2);
	g_signal_connect (G_OBJECT(buttonN), "clicked", G_CALLBACK(get_opcao), combo);
	
	if(widget!=NULL){
		destroy(widget,NULL);
	}	
	gtk_widget_show_all (window);
}
void Ivenda (GtkWidget *widget, MyApp *app){
int i;
	/* Criando construtor */
	GtkBuilder *builder;
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "test.glade",NULL);
	
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"Vender"));
	
	GtkWidget *buttonC = GTK_WIDGET(gtk_builder_get_object(builder,"button12"));
	GtkWidget *buttonN = GTK_WIDGET(gtk_builder_get_object(builder,"button13"));
	GtkWidget *buttonV = GTK_WIDGET(gtk_builder_get_object(builder,"button14"));
	
	GtkWidget *entryC = GTK_WIDGET(gtk_builder_get_object(builder,"entry2"));
	GtkWidget *entryq1 = GTK_WIDGET(gtk_builder_get_object(builder,"entry5"));
	GtkWidget *entryq2 = GTK_WIDGET(gtk_builder_get_object(builder,"entry6"));
	
	GtkComboBoxText *combo = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder,"comboboxtext2"));
	povoar_combo(combo);
	
	/* Conectando Sinais */
	g_signal_connect (G_OBJECT(buttonV), "clicked", G_CALLBACK(MenuO), app);
	g_signal_connect (G_OBJECT(buttonC), "clicked", G_CALLBACK(get_qtd_v), entryq1);
	g_signal_connect (G_OBJECT(buttonC), "clicked", G_CALLBACK(get_cod_v), entryC);
	g_signal_connect (G_OBJECT(buttonN), "clicked", G_CALLBACK(get_qtd_v), entryq2);
	g_signal_connect (G_OBJECT(buttonN), "clicked", G_CALLBACK(get_opcao_v), combo);
	
	if(widget!=NULL){
		destroy(widget,NULL);
	}	
	gtk_widget_show_all (window);
}
void Iconsulta (GtkWidget *widget, MyApp *app){
}
