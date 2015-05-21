#include <stdio.h>
#include <math.h>

unsigned int eulerRSA(unsigned int n){
	unsigned int i, r=sqrt(n)+1,p1,p2;

	if(n%2==0) p1=2;	//Se é par
	else{
		for(i=3;i<r;i+=2){	//Teste até a raiz, já que pelo menos 1 deles tem de ser menor que a raiz
			if(n%i==0){		//Poderia começar da raiz(o for)
				p1=i;
				break;
			}
		}
	}
	p2=n/p1;
	return (p1-1)*(p2-1);
}

int inv(int a,int b){//a=phi, b=e
    int v[10000],aux,a1,a2,a3,i,flag,num=a;	//Flag diz se é negativo
    for(i=0;b>0;i++){//Quocientes no array
        v[i]=a/b;
        aux=a;
        a=b;
        b=aux%b;
    }
    //Tem um i a mais aqui por isso o teste é inverso e eu diminuo 3
    //Número de linhas preenchidas para saber o sinal de a2
    if(i%2==0) flag=1;
    else flag=0;

    i-=3;
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
unsigned int descrip(unsigned int c,unsigned int d,unsigned int n){
	int aux;
	for(aux=c;d>1;d--){
		c*=aux;
		c=c%n;
	}
	return c;
}

int main(void){
    int num,n,e,c,i;
    scanf("%d",&num);
    for(i=1;i<=num;i++){
		scanf("%d %d %d",&n,&e,&c);
		if(n<15||n>pow(10,8)||e<1||e>=n||c<1||c>=n){
			printf("Um dos números digitados está fora da faixa permitida!");
			num++;
		}
		int mens=descrip(c,inv(eulerRSA(n),e),n);
		printf("Caso %d: %c",i,mens);
	}
    return 0;
}
