#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

typedef struct{
	int codigo;
	char nome[20];
	float preco;
	int estoque;
}Produto;

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

/* Retorna o estoque do produto */
int consulta_estoque(Produto *produto){
	return produto->estoque;
}

#endif
