#include <stdio.h>
#include "biblioteca.h"

int main(void){
	Produto p={12,"nome",12.5,12};
	float i=12;
	printf("%d",compra(&i,&p,12));
	return 0;
}
