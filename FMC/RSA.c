#include <stdio.h>
#include <math.h>

long int totiente(long int n){
	long int i; 
	long int raiz=sqrt(n)+1
	long int p1,p2; 	//Divisores

	if(n%2==0) p1=2;	//Se é par
	else{
		for(i=3;i<raiz;i+=2){//Teste até a raiz já que 1 deles é menor que ela
			if(n%i==0){
				p1=i;
				break;
			}
		}
	}
	p2=n/p1;
	return (p1-1)*(p2-1);
}

long int inverso(long int phi,long int e){
    long int v[10000],aux,a1,a2,a3,num=phi;
    int i,flag;	//Flag diz se é negativo
    
    for(i=0;e>0;i++){//Quocientes no array
        v[i]=phi/e;
        aux=phi;
        phi=e;
        e=aux%e;
    }
    //Número de linhas preenchidas para saber o sinal de a2
    if(i%2==0) flag=1;
    else flag=0;

    i-=3;//Pulando o quociente não utilizado e o quociente da primeira linha do dispositivo
    a1=1; a2=v[i+1];

    for(;i>=0;i--){             //      |1
        a3=v[i];                //v[i+1]|(a2)=a1
        aux=a2;                 //    a3|(a3*a2+a1)=a2
        a2=a3*a2+a1;            // a3=()|...
        a1=aux;
    }
    if(flag) return (a2*-1)+num;	//Se negativo
    return a2;
}
long int descrip(long int c,long int d,long int n){
	long int aux;
	for(aux=c;d>1;d--){
		c*=aux;
		c=c%n;
	}
	return c;
}

int main(void){
    int num,i;
    long int n,e,c;
    scanf("%d",&num);
    for(i=1;i<=num;i++){
		scanf("%ld %ld %ld",&n,&e,&c);
		if(n<15||e<1||e>=n||c<1||c>=n){
			printf("Um dos números digitados está fora da faixa permitida!");
			i--;
		}
		long int mens=descrip(c,inverso(totiente(n),e),n);
		printf("Caso %d: %c",i,(int)mens);
	}
    return 0;
}
