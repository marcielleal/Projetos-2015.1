/* Compile com gcc -o nome nome.c $(pkg-config --cflags --libs gtk+-3.0) -rdynamic */
/* Arquivo principal do projeto */
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "interface.c"
#include "apoio_interface.c"
#include "utilitarios.c"

float saldo=0;
Produto produtos[300]; 	//Vetor de Produtos
int numero=100;			//Número de produtos a serem lidos
int flag=0;				//Controle de janelas
int flag2=0;			//Controle do botão "Menu de Operações" da tela inicial

int main (int argc, char *argv[]){
	gtk_init (&argc, &argv);
	
	MenuP(NULL);
	
	gtk_main ();
	return 0;               
}
