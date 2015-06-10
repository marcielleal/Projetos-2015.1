#include <stdio.h>
#include <string.h>
void gera_estoque(char *nome,float saldo){
	FILE *p;
	int i;
	if((p = fopen(nome,"w")) ==NULL){
		printf("\nNao consigo abrir o arquivo ! ");
	}
	/* Adicionando o saldo na primeira linha */
	fputs("\n",p);
	
	for(i=0;i<200;i++){//Poderia gravar direto
		char string[200],aux[50];

		strcpy(string,"Produto");
		sprintf(aux,"%d",i);
		strcat(string,aux);
		strcat(string,"\n");
		
		sprintf(aux,"%d",(i+1));
		strcat(string,aux);
		strcat(string,"\n");

		strcat(string,"100");
		strcat(string,"\n");

		strcat(string,"50.0");
		strcat(string,"\n");

		fputs(string,p);

		if(ferror(p)){
			perror("Erro na gravacao");
			fclose(p);
		}
	}fclose(p);
}
int main(void){
	gera_estoque("banco",3000);
	return 0;
}
