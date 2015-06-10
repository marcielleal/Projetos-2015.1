/* Funções que não tem ligação direta com a interface gráfica */
#include <stdlib.h>
#include "biblioteca.h"

extern float saldo;
extern numero;

/* Retorna -1 caso tenha conseguido comprar ou um inteiro positivo caso não tenha.
 * Este indica a quantidade possível de produtos que podem ser comprados com o saldo
 */
int compra(float *saldo, Produto *produto,int quant){
	float valor= (*produto).preco*quant;
	if((*saldo>=valor)){
		(*saldo)-=valor;
		(*produto).estoque+=quant;
		return -1;
	}else{
		for(;quant>0;quant--,valor-=(*produto).preco){
			if((*saldo>=valor)) return quant;
		}
	}return 0;
}

/* Retorna -1 caso tenha vendido com sucesso ou um inteiro caso não tenha.
 * Este indica o estoque atual do produto
 */
int venda(float *saldo,Produto *produto,int quant){
	if((*produto).estoque>=quant){
		(*produto).estoque-=quant;
		*saldo+=(quant*((*produto).preco));
		return -1;
	}return produto->estoque;
}

int grava_arquivo(float *saldo,Produto *produto,int tamanho,char *nome){
	FILE *p;
	char s [30];
	int i;
	if((p = fopen(nome,"w")) ==NULL){
		printf("\nNao consigo abrir o arquivo ! ");
		return 1;
	}
	/* Adicionando o saldo na primeira linha */
	sprintf(s,"%f",*saldo);
	strcat(s,"\n");
	fputs(s,p);
	
	/* Adicionando nome, codigo, estoque e preco */
	for(i=0;i<numero;i++){//Poderia gravar direto
		char string[200],aux[50];

		strcpy(string,(produto+i)->nome);

		sprintf(aux,"%d",(produto+i)->codigo);
		strcat(string,aux);
		strcat(string,"\n");

		sprintf(aux,"%d",(produto+i)->estoque);
		strcat(string,aux);
		strcat(string,"\n");

		sprintf(aux,"%f",(produto+i)->preco);
		strcat(string,aux);
		strcat(string,"\n");

		fputs(string,p);

		if(ferror(p)){
			perror("Erro na gravacao");
			fclose(p);
			return 1;
		}
	}fclose(p);
	return 0;
}

int abre_arquivo(float *saldo,Produto *produto,char *nome){
	FILE *p;
	int i;
	char s[30];
	if((p = fopen(nome,"r")) ==NULL){
		printf("\nNao consigo abrir o arquivo ! ");
		return 1;
	}
	
	fgets(s,30,p);
	sscanf(s,"%f",saldo);
	
	for(i=0;i<numero&&!(feof(p));i++){
		char string[200];

		fgets(string,200,p);
		string[strlen(string)-1]='\0';	//Retira o \n
		strcpy((produto+i)->nome,string);

		fgets(string,200,p);
		sscanf(string,"%i",&((produto+i)->codigo));
		
		fgets(string,200,p);
		sscanf(string,"%i",&((produto+i)->estoque));

		fgets(string,200,p);
		sscanf(string,"%f",&((produto+i)->preco));

	}fclose(p);
	return 0;
}
