#include "biblioteca.h"
#include <string.h>
extern float saldo;
extern Produto produtos[300];
int prod,qtd,cod;

void get_qtd_v(GtkWidget *widget, GtkWidget *entry){
	sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%i",&qtd);
}

void get_qtd(GtkWidget *widget, GtkWidget *entry){
	sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%i",&qtd);
}
void get_cod_v(GtkWidget *widget, GtkWidget *entry){
	char string[200],aux[50];
	int i;
	sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%i",&cod);
	for(i=0;i<300;i++){
		if(cod==(produtos+i)->codigo) break;
	}
	/* Ver essa parte */ /* Descobrir pai */
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	GtkWidget *parent = NULL;
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	/**/
	int a=venda(&saldo, (produtos+i),qtd);
	
	if (a ==-1){
		sprintf(string,"%d",qtd);
		strcat(string," unidades do produto ");
		strcat(string,(produtos+i)->nome);
		strcat(string," foram vendidas!");
		sprintf(aux,"%f",saldo);
		strcat(string,"\nSeu novo saldo é: ");
		strcat(string,aux);
		cria_dialog(parent,string);
	}else{
		sprintf(string,"%d",a);
		strcat(string," unidades do produto ");
		strcat(string,(produtos+i)->nome);
		strcat(string," podem ser vendidas!");
		cria_dialog(parent,string);
	}
}

void get_opcao_v(GtkWidget *widget, GtkComboBoxText *combo){
	int i=300;
	gchar string[200],aux[100];
	strcpy(aux,gtk_combo_box_text_get_active_text(combo));

	for(i=0;i<300;i++){
		if(strcmp(aux,(produtos+i)->nome)==0) break;
	}
	/* Ver essa parte */ /* Descobrir pai */
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	GtkWidget *parent = NULL;
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	/**/
	int a=venda(&saldo, (produtos+i),qtd);
	if (a ==-1){
		sprintf(string,"%d",qtd);
		strcat(string," unidades do produto ");
		strcat(string,aux);
		strcat(string," foram vendidas!");
		sprintf(aux,"%f",saldo);
		strcat(string,"\nSeu novo saldo é: ");
		strcat(string,aux);
		cria_dialog(parent,string);
	}else{
		sprintf(string,"%d",a);
		strcat(string," unidades do produto ");
		strcat(string,aux);
		strcat(string," podem ser vendidas!");
		cria_dialog(parent,string);
	}
	
}
void get_cod(GtkWidget *widget, GtkWidget *entry){
	char string[200],aux[50];
	int i;
	sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%i",&cod);
	for(i=0;i<300;i++){
		if(cod==(produtos+i)->codigo) break;
	}
	/* Ver essa parte */ /* Descobrir pai */
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	GtkWidget *parent = NULL;
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	/**/
	int a=compra(&saldo, (produtos+i),qtd);
	
	if (a ==-1){
		sprintf(string,"%d",qtd);
		strcat(string," unidades do produto ");
		strcat(string,(produtos+i)->nome);
		strcat(string," foram compradas!");
		sprintf(aux,"%f",saldo);
		strcat(string,"\nSeu novo saldo é: ");
		strcat(string,aux);
		cria_dialog(parent,string);
	}else{
		sprintf(string,"%d",a);
		strcat(string," unidades do produto ");
		strcat(string,(produtos+i)->nome);
		strcat(string," podem ser compradas!");
		cria_dialog(parent,string);
	}
}

void get_opcao(GtkWidget *widget, GtkComboBoxText *combo){
	int i=300;
	gchar string[200],aux[100];
	strcpy(aux,gtk_combo_box_text_get_active_text(combo));

	for(i=0;i<300;i++){
		if(strcmp(aux,(produtos+i)->nome)==0) break;
	}
	/* Ver essa parte */ /* Descobrir pai */
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	GtkWidget *parent = NULL;
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	/**/
	int a=compra(&saldo, (produtos+i),qtd);
	if (a ==-1){
		sprintf(string,"%d",qtd);
		strcat(string," unidades do produto ");
		strcat(string,aux);
		strcat(string," foram compradas!");
		sprintf(aux,"%f",saldo);
		strcat(string,"\nSeu novo saldo é: ");
		strcat(string,aux);
		cria_dialog(parent,string);
	}else{
		sprintf(string,"%d",a);
		strcat(string," unidades do produto ");
		strcat(string,aux);
		strcat(string," podem ser compradas!");
		cria_dialog(parent,string);
	}
	
}

void get_saldo(GtkWidget *widget, GtkWidget *entry){
	sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%f",&saldo);
	MenuO(widget,NULL);
}	
void povoar_combo(GtkComboBoxText *combo){
	gchar text[100];
	int i;
	for(i=0;i<300;i++){
		strcpy(text,(produtos+i)->nome);
		gtk_combo_box_text_prepend(combo,NULL,text);
	}
}
void destroy(GtkWidget *widget,gpointer *p){
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	GtkWidget *parent = NULL;
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	gtk_widget_destroy(parent);
}
