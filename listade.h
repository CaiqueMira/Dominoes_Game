#ifndef LISTADE_H
#define LISTADE_H

#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include "pilha.h"

typedef int tp_item;

//dados estruturados quee representam os nós da lista
typedef struct tp_no_aux{
	tp_itemp info;
	tp_item marcador;
	struct tp_no_aux *ant;
	struct tp_no_aux *prox;
}tp_no;

//dado estruturado que representa o descritor da lista
typedef struct{
	tp_no *ini;
	tp_no *fim;
	tp_no *meio;	
}tp_listade;

tp_listade *inicializa_listade(){
	tp_listade *lista=(tp_listade *) malloc(sizeof(tp_listade));
	lista->ini = NULL;
	lista->fim = NULL;
	lista->meio = NULL;	
	return lista;
}

//Aloca um nó da lista
tp_no *aloca_listade() {
	tp_no* pt;
	pt=(tp_no*) malloc(sizeof(tp_no));
	return pt;
}

int listade_vazia(tp_listade *lista){
	if(lista->ini == NULL) return 1;
	return 0;
}

//Função para inserir os elementos nas mãos dos jogadores de forma ordenada
int insere_listade_ordenado(tp_listade *lista, tp_itemp e, tp_item m){	
	tp_no *novo, *atu;	
	novo=aloca_listade();	
	if(!novo) return 0;		
	novo->info.num1 = e.num1;
	novo->info.num2 = e.num2;
	novo->info.joga = NULL;
	novo->marcador = m;	
	atu = lista->ini;
	while(atu != NULL && atu->marcador != m){
		atu = atu->prox;
	}
	while(atu != NULL && atu->marcador == m && (atu->info.num1 + atu->info.num2 < novo->info.num1 + novo->info.num2)){
		atu = atu->prox;
	}		
	if(lista->ini == NULL){		
		novo->prox = NULL;
		novo->ant = NULL;
		lista->ini = lista->fim = novo;
	}
	else{
		if(atu == NULL){		
		novo->prox = NULL;
		novo->ant = lista->fim;
		lista->fim->prox = novo;
		lista->fim = novo;}
		else{
			if(atu == lista->ini){
				novo->prox = lista->ini;
				novo->ant = NULL;
				lista->ini->ant = novo;
				lista->ini = novo;
			}
			else{
				novo->prox = atu;
				novo->ant = atu->ant;				
				atu->ant->prox = novo;
				atu->ant = novo;				
			}
		}
	}	
	return 1;
}

int insere_listade_no_fim(tp_listade *lista, tp_itemp e, tp_item m){	
	tp_no *novo;	
	novo=aloca_listade();	
	if(!novo) return 0;		
	novo->info.num1 = e.num1;
	novo->info.num2 = e.num2;
	novo->marcador = m;		
	if(lista->ini == NULL){		
		novo->prox = NULL;
		novo->ant = NULL;
		lista->ini = lista->fim = lista->meio = novo;
	}
	else{
		novo->prox = NULL;
		novo->ant = lista->fim;
		lista->fim->prox = novo;
		lista->fim = novo;
	}	
	return 1;
}

int insere_listade_no_inicio(tp_listade *lista, tp_itemp e, tp_item m){
	tp_no *novo;
	novo=aloca_listade();
	if(!novo) return 0;
	novo->info.num1 = e.num1;
	novo->info.num2 = e.num2;
	novo->marcador = m;
	if(lista->ini == NULL){
		novo->prox = NULL;
		novo->ant = NULL;
		lista->ini = lista->fim = lista->meio = novo;		
	}
	else{
		novo->prox = lista->ini;
		novo->ant = NULL;		
		lista->ini->ant = novo;		
		lista->ini = novo;		
	}
}

int remove_listade(tp_listade *lista, tp_itemp *e, tp_item *m, int caso, int turno, int posicao){
	if(listade_vazia(lista)) return 0;
	int condicao = 0;
	tp_itemp menor, reserva;	
	tp_no *atu, *aux;
	atu = lista->ini;	
	menor = atu->info;
	reserva.num1 = reserva.num2 = 0;
	switch(caso){
		case 0:
			while(atu->marcador != turno){
				atu=atu->prox;
			}			
			while(atu != NULL && posicao > 0){
			atu = atu->prox;
			posicao--;
			}
			break;
		case 1:
			while(atu != NULL && (atu->info.num1 != 6 || atu->info.num2 != 6)){			
			if(atu->info.num1 == atu->info.num2){
				if(condicao == 0 || atu->info.num1 > reserva.num1){					
					reserva=atu->info;
					condicao = 1;
					aux = atu;					
				}											
			}
			if((atu->info.num1 + atu->info.num2)<(menor.num1 + menor.num2) && condicao != 1){
				menor = atu->info;
				aux = atu;
			}		
			atu = atu->prox;					
			}
			break;
		case 2:
			break;
		default : printf("codigo invalido");
	}
	
	if(caso == 1){				
		if(atu == NULL){		
			if(reserva.num1 == 0 && condicao == 0){
				*e = menor;
				*m = aux->marcador;
			}
			else{
				*e = reserva;
				*m = aux->marcador;
			}				
			atu = aux;
		} 
		else{
		*e=atu->info;
		*m=atu->marcador;
		}
	}
	
	if(lista->ini == lista->fim){		
		lista->ini = lista->fim = NULL;}
	else{
		if(lista->ini == atu){
			lista->ini = atu->prox;
			atu->prox->ant = NULL;
		}
		else{
			if(lista->fim == atu){
				lista->fim = atu->ant;
				atu->ant->prox = NULL;
			}
			else{
				atu->prox->ant = atu->ant;
				atu->ant->prox = atu->prox;
			}
		}
	}	
	free(atu);
	atu=NULL;
	aux=NULL;	
	return 1;
}

int compara_pedras(tp_item m_ini, tp_item m_fim, tp_itemp mesaini, tp_itemp mesafim, tp_itemp pedra, int caso, tp_item *m){
	if(caso == 0 || caso == 3){				
		if(m_ini == 0 || m_ini == 1){		
			if(pedra.num1 == mesaini.num1 || pedra.num2 == mesaini.num1){
				if(caso == 0){				
					if(pedra.num1 == mesaini.num1)
						*m = 2;
					else
						*m = 1;					
				}
				pedra.joga = 1;			
				return 1;
			}
		}
		else{
			if(m_ini == 2){
				if(pedra.num1 == mesaini.num2 || pedra.num2 == mesaini.num2){
					if(caso == 0){					
						if(pedra.num1 == mesaini.num2)
							*m = 2;
						else
							*m = 1;
					}
					pedra.joga = 1;
					return 1;
				}			
			}
			else{
				if(pedra.num1 == mesaini.num1 || pedra.num1 == mesaini.num2 || pedra.num2 == mesaini.num1 || pedra.num2 == mesaini.num2){
					if(caso == 0){					
						if(pedra.num1 == mesaini.num1)
							*m = 2;
						else{
							if(pedra.num1 == mesaini.num2)
								*m = 2;
							else{
								if(pedra.num2 == mesaini.num1)
									*m = 1;
								else
									*m = 1;
							}
						}
					}
					pedra.joga = 1;
					return 1;
				}			
			}
		}
	}
	if(caso == 1 || caso == 3){	
		if(m_fim == 0 || m_fim == 1){		
			if(pedra.num1 == mesafim.num1 || pedra.num2 == mesafim.num1){
				if(caso == 1){				
					if(pedra.num1 == mesafim.num1)
						*m = 2;
					else
						*m = 1;					
				}			
				pedra.joga = 1;			
				return 1;
			}
		}	
		else{
			if(m_fim == 2){
				if(pedra.num1 == mesafim.num2 || pedra.num2 == mesafim.num2){
					if(caso == 1){				
						if(pedra.num1 == mesafim.num2)
							*m = 2;
						else
							*m = 1;					
					}
					pedra.joga = 1;
					return 1;
				}			
			}
			else{
				if(pedra.num1 == mesafim.num1 || pedra.num1 == mesafim.num2 || pedra.num2 == mesafim.num1 || pedra.num2 == mesafim.num2){
					if(caso == 1){					
						if(pedra.num1 == mesafim.num1)
							*m = 2;
						else{
							if(pedra.num1 == mesafim.num2)
								*m = 2;
							else{
								if(pedra.num2 == mesafim.num1)
									*m = 1;
								else
									*m = 1;
							}
						}
					}
					pedra.joga = 1;
					return 1;
				}			
			}
		}
	}
	pedra.joga = 0;
	return 0;	
}

void checa_pedras(tp_listade *maos, tp_listade *mesa, tp_pilha *cava, int turno){
	int condicao_cava = 1, cont = 0;	
	tp_no *atu;
	tp_item m_ini, m_fim;	
	tp_itemp mesaini, mesafim, e;
	m_ini = mesa->ini->marcador;
	m_fim = mesa->fim->marcador;
	mesaini = mesa->ini->info;
	mesafim = mesa->fim->info;		
	atu = maos->ini;		
	while(atu->marcador != turno){
		atu=atu->prox;
	}	
	while(atu != NULL && atu->marcador == turno){
		if(compara_pedras(m_ini, m_fim, mesaini, mesafim, atu->info, 3, NULL)){
			condicao_cava = 0;			
		}
		atu=atu->prox;				
	}	
	while(condicao_cava == 1){
		if(cont == 0){		
			printf("Jogador %d não possui pedras para jogar\n", turno);
			cont++;
		}		
		printf("Cavando...\n");
		Sleep(500);
		pop(cava, &e);
		insere_listade_ordenado(maos, e, turno);
		if(compara_pedras(m_ini, m_fim, mesaini, mesafim, e, 3, NULL))
			condicao_cava = 0;						
	}		
}

void imprime_listade(tp_listade *lista, tp_listade *lista2, int ordem, int turno){
	int cont=1;
	tp_itemp mesaini, mesafim;
	tp_item m_ini, m_fim;	
	tp_no *atu;	
	switch(ordem){
		case 1: atu = lista->ini;
			while(atu != NULL){
				printf("%d-%d/%d | ", atu->marcador, atu->info.num1, atu->info.num2);
				atu = atu->prox;
			}			
			break;
		case 2: atu = lista->ini;
			mesaini = lista2->ini->info;
			mesafim = lista2->fim->info;
			m_ini = lista2->ini->marcador;
			m_fim = lista2->fim->marcador;			
			while(atu->marcador != turno){
				atu=atu->prox;
			}			
			while(atu != NULL && atu->marcador == turno){
				//if(atu->info.num1 == mesaini.num1 || atu->info.num1 == mesaini.num2 || atu->info.num2 == mesafim.num1 || atu->info.num2 == mesafim.num2)	
				if(compara_pedras(m_ini, m_fim, mesaini, mesafim, atu->info, 3, NULL))			
					printf("Joga - ");		
									
				else
					printf("Não joga - ");					
				printf("%d-%d/%d-%d\n", cont, atu->info.num1, atu->info.num2, atu->info.joga);
				atu = atu->prox;
				cont++;
			}
			break;
		/*case 3: atu = lista->ini;
			while(atu->marcador != turno){
				atu=atu->prox;
			}
			while(atu != NULL){
				printf("%d-%d/%d\n", atu->marcador, atu->info.num1, atu->info.num2);
				atu = atu->ant;
			}
			break;*/
		default : printf("codigo invalido");
	}
	printf("\n");
}

/*int compara_pedras(tp_item m_ini, tp_item m_fim, tp_itemp mesaini, tp_itemp mesafim, tp_itemp pedra){	
	if(m_ini == 0 || m_ini == 1 || m_fim == 0 || m_fim == 1){		
		if((pedra.num1 == mesaini.num1 || pedra.num2 == mesaini.num1) || (pedra.num1 == mesafim.num1 || pedra.num2 == mesafim.num1)){			
			pedra.joga = 1;			
			return 1;
		}
	}		
	if(m_ini == 2 || m_fim == 2){
		if((pedra.num1 == mesaini.num2 || pedra.num2 == mesaini.num2) || (pedra.num1 == mesafim.num2 || pedra.num2 == mesafim.num2)){
			pedra.joga = 1;
			return 1;
		}			
	}
	if(m_ini == 3 || m_fim == 3){
		if((pedra.num1 == mesaini.num1 || pedra.num1 == mesaini.num2 || pedra.num2 == mesaini.num1 || pedra.num2 == mesaini.num2 ) || (pedra.num1 == mesafim.num1 || pedra.num1 == mesafim.num2 || pedra.num2 == mesafim.num1 || pedra.num2 == mesafim.num2)){
			pedra.joga = 1;
			return 1;
		}			
	}
	pedra.joga = 0;
	return 0;	
}*/

int tamanho_listade(tp_listade *lista, int turno){
	int cont = 1;
	tp_no *atu;
	atu=lista->ini;
	while(atu->marcador != turno){		
		atu=atu->prox;
	}
	while(atu != NULL && atu->marcador == turno){
		atu=atu->prox;
		cont++;
	}
	return cont;	
}

tp_itemp busca_listade_posicao(tp_listade *lista, int posicao, int turno){	
	tp_no *atu;
	atu = lista->ini;
	while(atu->marcador != turno){
		atu = atu->prox;
	}
	while(posicao > 0){
		atu = atu->prox;
		posicao--;		
	}	
	return atu->info;
}

tp_listade *destroi_listade(tp_listade *lista, tp_itemp *e){
	tp_no *atu;
	atu = lista->ini;	
	while(atu != NULL){
		*e=atu->info;
		lista->ini = atu->prox;
		free(atu);
		atu=lista->ini;
	}
	free(lista);
	return NULL;
}

#endif
