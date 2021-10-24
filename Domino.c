#include "pilha.h"
#include <time.h>

void cria_pedras(pedra *vet){
	pedra *aux = vet;
	int i=0, j=0;
	while(i < 7){
		vet->num1 = i;		
		vet->num2 = j;
		j++;
		if(j == 7){						
			i++;
			j=i;
		}
		vet++;									
	}
	embaralha_pedras(aux);		
}

void embaralha_pedras(pedra *vet){
	pedra aux;
	int i, random;
	srand(time(NULL));
	for(i=0;i<28;i++){
		random = rand() % 28;
		aux = vet[i];
		vet[i] = vet[random];
		vet[random] = aux;						
	}	
}

void empilha_cava(pedra *vet, tp_pilha *cava){	
	int i=27;	
	while(i >= 0){		
		push(cava, vet[i]);
		i--;				
	}
}

int main(){
	int cont=0;
	tp_pilha cava;
	inicializa_pilha(&cava);
	//23;
	pedra vet[28];		
	cria_pedras(vet);	
	empilha_cava(vet, &cava);
	/*while(cont<28){
		printf("%d - %d/%d\n", cont, vet[cont].num1, vet[cont].num2);
		cont++;
	}*/
	imprime_pilha(cava);	
	return 0;
}
