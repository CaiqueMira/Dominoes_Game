#include "pilha.h"
#include "listade.h"
#include <time.h>
#include <locale.h>

void jogo(tp_listade *maos, tp_listade *mesa, tp_pilha *cava, int jogadores){
	int condicao=0, turno, posicao;
	tp_item m;
	tp_itemp e;	
	remove_listade(maos, &e, &m, 1, 2);
	turno = m;
	turno++;
	printf("Turno - %d\n", turno);
	if(e.num1 == e.num2) 
		m = 0;	
	else 
		m = 3;	
	insere_listade_no_fim(mesa, e, m);	
	while(condicao == 0){
		if(turno > jogadores){
			turno = 1;
		}		
		imprime_listade(mesa, NULL, 1, turno); //imprime a mesa no centro da tela (precisa definir as posições das pedras na tela na função imprime_listade
		printf("\n");
		imprime_pilha(*cava);
		imprime_listade(maos, mesa, 2, turno);
		checa_pedras(maos, mesa, cava, turno);			
		printf("\n\n");
		imprime_pilha(*cava);		
		scanf("%d", &posicao);
		getchar();
		//scanf("%d", &posicao);
		//remove_listade(maos, &e, &m, 0, posicao-1);
		/*if(turno == jogadores){
			turno = 1;
		}
		if(maos->ini == NULL ||) //acrescentar quando um jogador colocou todas as peças na mesa		
		printf("\n");		
		getchar();			
	}*/	
}
}

void distribui_maos(tp_listade *maos, tp_pilha *cava, int jogadores){
	int cont=0;
	tp_itemp e;
	tp_item m=1;	
	while(jogadores > 0){		
		pop(cava, &e);					
		insere_listade_ordenado(maos, e, m);				
		cont++;
		if(cont == 7){
			jogadores--;
			m++;
			cont=0;
		}		
	}				
}

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
	setlocale(LC_ALL,"Portuguese");	
	int cont=0, jogadores;
	tp_pilha cava;
	tp_listade *maos, *mesa;
	inicializa_pilha(&cava);
	maos = inicializa_listade();
	mesa = inicializa_listade();	
	pedra vet[28];		
	cria_pedras(vet);	
	empilha_cava(vet, &cava);
	printf("Insira o número de jogadores: ");
	scanf("%d", &jogadores);
	system("cls");	
	distribui_maos(maos, &cava, jogadores);
	imprime_listade(maos, NULL, 1, 0);	
	printf("\n\n\n");
	jogo(maos, mesa, &cava, jogadores);	
	imprime_listade(maos, NULL, 1, 0);
	imprime_pilha(cava);	
	return 0;
}
