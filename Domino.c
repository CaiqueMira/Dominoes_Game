#include "pilha.h"
#include "listade.h"
#include <time.h>
#include <locale.h>

void jogo(tp_listade *maos, tp_listade *mesa, tp_pilha *cava, int jogadores){
	int condicao_parada=0, turno, posicao, lado;
	tp_itemp pedra_atu;
	tp_item m;
	tp_itemp e;	
	
	remove_listade(maos, &e, &m, 1, NULL, 2);
	turno = m;
	turno++;
	printf("Turno - %d\n", turno);
	if(e.num1 == e.num2) 
		m = 0;	
	else 
		m = 3;	
	insere_listade_no_fim(mesa, e, m);	
	while(condicao_parada == 0){
		if(turno > jogadores){
			turno = 1;
		}		
		imprime_listade(mesa, NULL, 1, turno); //imprime a mesa no centro da tela (precisa definir as posições das pedras na tela na função imprime_listade
		printf("\n");
		imprime_pilha(cava);
		imprime_listade(maos, mesa, 2, turno);
		checa_pedras(maos, mesa, cava, turno);			
		printf("\n\n");
		imprime_pilha(cava);
		imprime_listade(maos, mesa, 2, turno);
		printf("Selecione qual pedra deseja jogar: \n");				
		scanf("%d", &posicao);		
		while(posicao >= tamanho_listade(maos, turno) || posicao < 0){			
			printf("Posição inserida inválida, insira uma posição válida: \n");
			scanf("%d", &posicao);
		}
		pedra_atu = busca_listade_posicao(maos, posicao-1, turno);
		while(!compara_pedras(mesa->ini->marcador, mesa->fim->marcador, mesa->ini->info, mesa->fim->info, pedra_atu, 3, NULL)){
			printf("%d/%d\n", pedra_atu.num1, pedra_atu.num2);
			printf("A pedra escolhida não pode ser jogada, selecione outra: ");
			scanf("%d", &posicao);
			while(posicao >= tamanho_listade(maos, turno) || posicao < 0){
			printf("%d\n", tamanho_listade(maos, turno));
			printf("Posição inserida inválida, insira uma posição válida: \n");
			scanf("%d", &posicao);
			}
			pedra_atu = busca_listade_posicao(maos, posicao-1, turno);		
		}
		remove_listade(maos, NULL, NULL, 0, turno, posicao-1);
		printf("Selecione em qual extremidade deseja jogar a pedra (0 para esquerda, 1 para direita): \n");
		printf("Para voltar insira 999: ");
		scanf("%d", &lado);
		while(lado != 0 && lado != 1){
			printf("Insira um número válido: \n");
			scanf("%d", &lado);
		}								
		while(!compara_pedras(mesa->ini->marcador, mesa->fim->marcador, mesa->ini->info, mesa->fim->info, pedra_atu, lado, &m)){
			printf("A pedra não pode ser jogada na extremidade selecionada\n");
			scanf("%d", &lado);
			while(lado != 0 && lado != 1){
			printf("Insira um número válido: \n");
			scanf("%d", &lado);
			}
		}
		switch(lado){
			case 0:
				insere_listade_no_inicio(mesa, pedra_atu, m);
				break;
			case 1:
				insere_listade_no_fim(mesa, pedra_atu, m);
				break;
			default: printf("Erro, código invalido\n");
		}
		turno++;				
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
		printf("%d/%d\n", vet[i].num1, vet[i].num2);				
		push(cava, vet[i]);
		i--;					
	}
}

int main(){
	setlocale(LC_ALL,"Portuguese");	
	int cont=0, jogadores;
	tp_pilha *cava;
	tp_listade *maos, *mesa;
	cava = inicializa_pilha();
	maos = inicializa_listade();
	mesa = inicializa_listade();	
	pedra vet[28];		
	cria_pedras(vet);		
	empilha_cava(vet, cava);
	printf("Insira o número de jogadores: ");
	scanf("%d", &jogadores);
	system("cls");	
	distribui_maos(maos, cava, jogadores);
	imprime_listade(maos, NULL, 1, 0);	
	printf("\n\n\n");
	jogo(maos, mesa, cava, jogadores);	
	imprime_listade(maos, NULL, 1, 0);
	imprime_pilha(cava);	
	return 0;
}
