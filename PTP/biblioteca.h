#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <gtk/gtk.h>

typedef struct{
	GSList *windows;
        /* etc... whatever application vars you need */
} MyApp;

typedef struct{
	char nome[20];
	int codigo;
	int estoque;
	float preco;
}Produto;


/*----------I-Interface-------------*/
void cria_dialog(GtkWidget *window,gchar *string);

void AbrirW (GtkWidget *widget, MyApp *app);
void MenuP (GtkWidget *widget, MyApp *app);
void Abrir(GtkWidget *widget);
void Salvar(GtkWidget *widget);
void MenuO (GtkWidget *widget, MyApp *app);
void Icompra (GtkWidget *widget, MyApp *app);
void Ivenda (GtkWidget *widget, MyApp *app);
void Iconsulta (GtkWidget *widget, MyApp *app);


/*----------F-Interface-------------*/


/*------------I-Apoio-----------------*/
// Pega o texto e armazena em x
void get_saldo(GtkWidget *widget, GtkWidget *entry);

void get_qtd(GtkWidget *widget, GtkWidget *entry);
void get_qtd_v(GtkWidget *widget, GtkWidget *entry);
void get_cod(GtkWidget *widget, GtkWidget *entry);
void get_cod_v(GtkWidget *widget, GtkWidget *entry);

// Destroi o pai de widget 
void destroy(GtkWidget *widget,gpointer *p);

void get_opcao(GtkWidget *widget, GtkComboBoxText *combo);
void get_opcao_v(GtkWidget *widget, GtkComboBoxText *combo);

void povoar_combo(GtkComboBoxText *combo);

/*------------F-Apoio-----------------*/


/*-------I-Parte Funcional-------------*/
int compra(float *saldo, Produto *produto,int quant);
int venda(float *saldo, Produto *produto,int quant);
int consulta_estoque(Produto *produto);
int grava_arquivo(Produto *produto,int tamanho,char *nome);

/*-------F-Parte Funcional-------------*/
#endif
