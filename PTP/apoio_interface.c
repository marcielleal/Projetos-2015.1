#include "biblioteca.h"
#include <string.h>
extern float saldo;
extern Produto produtos[300];
extern int numero,flag,flag2;
int prod,qtd,cod;

void consulta_cod(GtkWidget *widget, GtkWidget *entry){
	GtkWidget *parent=NULL;
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	char string[200],aux[50];
	int i;
	sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%i",&cod);
	for(i=0;i<numero;i++){
		if(cod==(produtos+i)->codigo) break;
	}
	if(i<numero){
		strcpy(string,"Existem ");
		sprintf(aux,"%d",(produtos+i)->estoque);
		strcat(string,aux);
		strcat(string," unidades do produto ");
		strcat(string,(produtos+i)->nome);
		strcat(string," no estoque!");
	}else{
		strcpy(string,"Não existe produto correspondente a esse código!");	
	}
	cria_dialog(parent,string);
	gtk_widget_destroy(parent);
}

void consulta_nome(GtkWidget *widget, GtkComboBoxText *combo){
	GtkWidget *parent=NULL;
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	int i;
	gchar string[200],aux[100];
	strcpy(aux,gtk_combo_box_text_get_active_text(combo));

	for(i=0;i<numero;i++){
		if(strcmp(aux,(produtos+i)->nome)==0) break;
	}
	strcpy(string,"Existem ");
	sprintf(aux,"%d",(produtos+i)->estoque);
	strcat(string,aux);
	strcat(string," unidades do produto ");
	strcat(string,(produtos+i)->nome);
	strcat(string," no estoque!");
	cria_dialog(parent,string);
}


void get_qtd_v(GtkWidget *widget, GtkWidget *entry){
	sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%i",&qtd);
}

void get_qtd(GtkWidget *widget, GtkWidget *entry){
	sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%i",&qtd);
}
void get_cod_v(GtkWidget *widget, GtkWidget *entry){
	GtkWidget *parent=NULL;
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	if(qtd<=0){
		cria_dialog(parent,"A quantidade tem que ser positiva e não nula");
	}else{
		char string[200],aux[50];
		int i;
		sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%i",&cod);
		for(i=0;i<numero;i++){
			if(cod==(produtos+i)->codigo) break;
		}
		int a=venda(&saldo, (produtos+i),qtd);
		if(cod<=((produtos+(numero-1))->codigo)&&cod>=((produtos)->codigo)){
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
				strcpy(string,"Somente ");
				sprintf(aux,"%d",a);
				strcat(string,aux);
				strcat(string," unidades do produto ");
				strcat(string,(produtos+i)->nome);
				strcat(string," podem ser vendidas!");
				cria_dialog(parent,string);
			}
		}else{
			sprintf(aux,"%d",cod);
			strcpy(string,"Não existe o produto de código ");
			strcat(string,aux);
			strcat(string," no estoque!");
			cria_dialog(parent,string);
		}
	}
}

void get_opcao_v(GtkWidget *widget, GtkComboBoxText *combo){
	GtkWidget *parent=NULL;
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	if(qtd<=0){
		cria_dialog(parent,"A quantidade tem que ser positiva e não nula");
	}else{
		int i;
		gchar string[200],aux[100];
		strcpy(aux,gtk_combo_box_text_get_active_text(combo));

		for(i=0;i<numero;i++){
			if(strcmp(aux,(produtos+i)->nome)==0) break;
		}
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
			strcpy(string,"Somente ");
			sprintf(aux,"%d",a);
			strcat(string,aux);
			strcat(string," unidades do produto ");
			strcat(string,(produtos+i)->nome);
			strcat(string," podem ser vendidas!");
			cria_dialog(parent,string);
		}
	}
}
void get_cod(GtkWidget *widget, GtkWidget *entry){
	GtkWidget *parent=NULL;
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	if(qtd<=0){
		cria_dialog(parent,"A quantidade tem que ser positiva e não nula");
	}else{
		char string[200],aux[50];
		int i;
		sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%i",&cod);
		for(i=0;i<numero;i++){
			if(cod==(produtos+i)->codigo) break;
		}
		if(cod<=((produtos+(numero-1))->codigo)&&cod>=((produtos)->codigo)){
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
				strcpy(string,"Somente ");
				sprintf(aux,"%d",a);
				strcat(string,aux);
				strcat(string," unidades do produto ");
				strcat(string,(produtos+i)->nome);
				strcat(string," podem ser compradas!");
				cria_dialog(parent,string);
			}
		}else{
			sprintf(aux,"%d",cod);
			strcpy(string,"Não existe o produto de código ");
			strcat(string,aux);
			strcat(string," no estoque!");
			cria_dialog(parent,string);
		}
	}
}

void get_opcao(GtkWidget *widget, GtkComboBoxText *combo){
	GtkWidget *parent=NULL;
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	if(qtd<=0){
		cria_dialog(parent,"A quantidade tem que ser positiva e não nula");
	}else{
		int i;
		gchar string[200],aux[100];
		strcpy(aux,gtk_combo_box_text_get_active_text(combo));

		for(i=0;i<numero;i++){
			if(strcmp(aux,(produtos+i)->nome)==0) break;
		}
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
			strcpy(string,"Somente ");
			sprintf(aux,"%d",a);
			strcat(string,aux);
			strcat(string," unidades do produto ");
			strcat(string,(produtos+i)->nome);
			strcat(string," podem ser compradas!");
			cria_dialog(parent,string);
		}
	}
}

void get_saldo(GtkWidget *widget, GtkWidget *entry){
	sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%f",&saldo);
	destroy(widget,NULL);
}	
void povoar_combo(GtkComboBoxText *combo){
	int i;
	for(i=0;i<numero;i++){
		gtk_combo_box_text_prepend(combo,NULL,(produtos+i)->nome);
	}
}
void destroy(GtkWidget *widget,gpointer *p){
	GtkWidget *parent = NULL;
	GdkWindow *gtk_window = gtk_widget_get_parent_window(widget);
	gdk_window_get_user_data(gtk_window, (gpointer *)&parent);
	gtk_widget_destroy(parent);
}

void d_verifica(GtkWidget *widget){
	if(flag==0) gtk_main_quit();
}

void i_flag(GtkWidget *widget){
	if(flag) flag=0;
	else flag=1;
}

void i_flag2(GtkWidget *widget){
	flag2=1;
}

void ler_banco(GtkWidget *widget){
	float a=0;		//Não passo saldo, pois ele seria reescrito
	if(abre_arquivo(&a,produtos,"banco")) cria_dialog(NULL,"Não foi possível abrir o banco default");
}
