#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <gtk/gtk.h>

typedef struct{
	char nome[20];
	int codigo;
	int estoque;
	float preco;
}Produto;


/*----------I-Interface-------------*/
void cria_dialog(GtkWidget *window,gchar *string);

void Saldo (GtkWidget *widget);

/* Menus */
void MenuP (GtkWidget *widget);
void MenuO (GtkWidget *widget);

/* FileChoosers */
void Abrir(GtkWidget *widget);
void Salvar(GtkWidget *widget);

/*Telas das operações */
void Icompra (GtkWidget *widget);
void Ivenda (GtkWidget *widget);
void Iconsulta (GtkWidget *widget);


/*----------F-Interface-------------*/


/*------------I-Apoio-----------------*/
/* Captura saldo */
void get_saldo(GtkWidget *widget, GtkWidget *entry);

/* Pega as quantidades inseridas nos entrys nas telas de Compra e venda respectivamente */
void get_qtd(GtkWidget *widget, GtkWidget *entry);
void get_qtd_v(GtkWidget *widget, GtkWidget *entry);

/* Pega os códigos inseridos nos entrys nas telas de Compra e venda respectivamente */
void get_cod(GtkWidget *widget, GtkWidget *entry);
void get_cod_v(GtkWidget *widget, GtkWidget *entry);

// Destroi o pai de widget 
void destroy(GtkWidget *widget,gpointer *p);

/* Pega a opção do ComboBox das telas de Compra e venda respectivamente */
void get_opcao(GtkWidget *widget, GtkComboBoxText *combo);
void get_opcao_v(GtkWidget *widget, GtkComboBoxText *combo);

/* Consultas por código e por nome */
void consulta_cod(GtkWidget *widget, GtkWidget *entry);
void consulta_nome(GtkWidget *widget, GtkComboBoxText *combo);

/* Mostrar os produtos no ComboBox */
void povoar_combo(GtkComboBoxText *combo);

/* Verifica se é a última janela aberta */
void d_verifica(GtkWidget *widget);

void i_flag(GtkWidget *widget);
void i_flag2(GtkWidget *widget);

void ler_banco(GtkWidget *widget);
/*------------F-Apoio-----------------*/


/*--------I-Utilitarios-------------*/
int compra(float *saldo, Produto *produto,int quant);
int venda(float *saldo, Produto *produto,int quant);
int grava_arquivo(float *saldo,Produto *produto,int tamanho,char *nome);
int abre_arquivo(float *saldo,Produto *produto,char *nome);

/*--------F-Utilitarios-------------*/
#endif
