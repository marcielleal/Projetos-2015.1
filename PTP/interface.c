#include "biblioteca.h"

extern float saldo;
extern Produto produtos[300];
extern int numero,flag,flag2;

void cria_dialog(GtkWidget *window,char *string){
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"%s",string);
  
	gtk_window_set_title(GTK_WINDOW(dialog), "Atenção");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

void Saldo (GtkWidget *widget){
	/* Criando construtor */
	GtkBuilder *builder;
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "test.glade",NULL);
	
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"AbrirW"));
	GtkWidget *buttonC = GTK_WIDGET(gtk_builder_get_object(builder,"button8"));
	GtkWidget *buttonS = GTK_WIDGET(gtk_builder_get_object(builder,"button6"));
	GtkWidget *entry= GTK_WIDGET(gtk_builder_get_object(builder,"entry1"));
	
	/* Conectando Sinais */
	
	g_signal_connect (G_OBJECT (buttonC), "clicked", G_CALLBACK (i_flag2), NULL);
	g_signal_connect (G_OBJECT (buttonC), "clicked", G_CALLBACK (ler_banco), NULL);
	g_signal_connect (G_OBJECT (buttonC), "clicked", G_CALLBACK (get_saldo), entry);
	g_signal_connect (G_OBJECT (buttonS), "clicked", G_CALLBACK (destroy), NULL);

	gtk_widget_show_all (window);
}
void Abrir(GtkWidget *widget){
	GtkWidget *dad = NULL;
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	gdk_window_get_user_data(gtk_window, (gpointer *)&dad);
	GtkWindow *parent=GTK_WINDOW(dad);
	
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
		if(abre_arquivo(&saldo,produtos,filename)) cria_dialog(dad,"Ocorreu um erro na abertura do arquivo");
		else flag2=1;
		g_free(filename);
	}
	gtk_widget_destroy (dialog);
}
void Salvar(GtkWidget *widget){
	GtkWidget *dad = NULL;
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	gdk_window_get_user_data(gtk_window, (gpointer *)&dad);
	GtkWindow *parent=GTK_WINDOW(dad);
	
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
		if(grava_arquivo(&saldo,produtos,numero,filename)) cria_dialog(dad,"Ocorreu um erro na abertura do arquivo");
		g_free(filename);
	}
	gtk_widget_destroy (dialog);
}

void MenuP (GtkWidget *widget){
	/* Criando construtor */
	GtkBuilder *builder;
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "test.glade",NULL);
	GtkWidget *window,*buttonC,*buttonS,*buttonA,*buttonI,*buttonM;
	
	window = GTK_WIDGET(gtk_builder_get_object(builder,"MenuP"));
	buttonC = GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
	buttonS = GTK_WIDGET(gtk_builder_get_object(builder,"button7"));
	buttonA = GTK_WIDGET(gtk_builder_get_object(builder,"button5"));
	buttonI = GTK_WIDGET(gtk_builder_get_object(builder,"Sair1"));
	buttonM = GTK_WIDGET(gtk_builder_get_object(builder,"button18"));
		
	g_signal_connect (G_OBJECT (buttonM), "clicked", G_CALLBACK (MenuO),NULL);
	g_signal_connect (G_OBJECT (buttonC), "clicked", G_CALLBACK (Saldo), NULL);
	g_signal_connect (G_OBJECT (buttonS), "clicked", G_CALLBACK (Salvar), NULL);
	g_signal_connect (G_OBJECT (buttonA), "clicked", G_CALLBACK (Abrir), NULL);
	g_signal_connect (G_OBJECT (buttonI), "clicked", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (d_verifica), NULL);

	gtk_widget_show_all (window);
}

void MenuO (GtkWidget *widget){
	GtkWidget *parent = NULL;
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	if(flag2==0) cria_dialog(parent,"Carregue o estado da loja ou abra o caixa!");
	else{
		i_flag(NULL);
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
		g_signal_connect (G_OBJECT (buttonC), "clicked", G_CALLBACK (Icompra), NULL);
		g_signal_connect (G_OBJECT (buttonE), "clicked", G_CALLBACK (Iconsulta), NULL);
		g_signal_connect (G_OBJECT (buttonV), "clicked", G_CALLBACK (Ivenda), NULL);
		g_signal_connect (G_OBJECT (buttonO), "clicked", G_CALLBACK (destroy), NULL);
		g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (i_flag), NULL);
		g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (MenuP), NULL);
		
		if(widget!=NULL){
			destroy(widget,NULL);
		}	
		gtk_widget_show_all (window);
	}
}

void Icompra (GtkWidget *widget){
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
	g_signal_connect (G_OBJECT(buttonV), "clicked", G_CALLBACK(destroy), NULL);
	g_signal_connect (G_OBJECT(buttonC), "clicked", G_CALLBACK(get_qtd), entryq1);
	g_signal_connect (G_OBJECT(buttonC), "clicked", G_CALLBACK(get_cod), entryC);
	g_signal_connect (G_OBJECT(buttonN), "clicked", G_CALLBACK(get_qtd), entryq2);
	g_signal_connect (G_OBJECT(buttonN), "clicked", G_CALLBACK(get_opcao), combo);
	
	gtk_widget_show_all (window);
}
void Ivenda (GtkWidget *widget){
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
	g_signal_connect (G_OBJECT(buttonV), "clicked", G_CALLBACK(destroy), NULL);
	g_signal_connect (G_OBJECT(buttonC), "clicked", G_CALLBACK(get_qtd_v), entryq1);
	g_signal_connect (G_OBJECT(buttonC), "clicked", G_CALLBACK(get_cod_v), entryC);
	g_signal_connect (G_OBJECT(buttonN), "clicked", G_CALLBACK(get_qtd_v), entryq2);
	g_signal_connect (G_OBJECT(buttonN), "clicked", G_CALLBACK(get_opcao_v), combo);
	
	gtk_widget_show_all (window);
}
void Iconsulta (GtkWidget *widget){
	GtkBuilder *builder;
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "test.glade",NULL);
	
	GtkWidget *window = GTK_WIDGET (gtk_builder_get_object(builder,"Consultar"));
	
	GtkWidget *buttonC = GTK_WIDGET(gtk_builder_get_object(builder,"button15"));
	GtkWidget *buttonN = GTK_WIDGET(gtk_builder_get_object(builder,"button16"));
	GtkWidget *buttonV = GTK_WIDGET(gtk_builder_get_object(builder,"button17"));
	
	GtkWidget *entryC = GTK_WIDGET(gtk_builder_get_object(builder,"entry4"));
	
	GtkComboBoxText *combo = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder,"comboboxtext1"));
	povoar_combo(combo);
	
	/* Conectando Sinais */
	g_signal_connect (G_OBJECT(buttonV), "clicked", G_CALLBACK(destroy), NULL);
	g_signal_connect (G_OBJECT(buttonC), "clicked", G_CALLBACK(consulta_cod), entryC);
	g_signal_connect (G_OBJECT(buttonN), "clicked", G_CALLBACK(consulta_nome), combo);
	
	gtk_widget_show_all (window);
}
