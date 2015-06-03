#include "registros.c"
#include "funcoes.c"
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

/*Funcao de cadastro de produtos. Retorna 1 se cadastrado com sucesso e 0 se não.
 * Recebe o ponteiro i que seria o primeiro elemento vazio no vetor de Produtos
*/
int cadastro(int *i,char *nome,float valor,int estoque, Produto *produto);

int compra(int *saldo,Produto *produto,int quant);

int venda(Produto *produto,int quant);

#endif
