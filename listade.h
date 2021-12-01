#ifndef LISTADE_H
#define LISTADE_H

#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.c>
#include "pilha.h"

typedef int tp_item;

// Dados estruturados que representam os n�s da lista
// info representa as informa��es da pedra, o marcador para as m�os indica de quem � a pedra e para a mesa qual n�mero da pedra n�o est� conectado com outra pedra, ou seja, est� livre e os ponteiros ant e prox apontam para o elemento anterior e posterior da lista respectivamente
typedef struct tp_no_aux{
	tp_itemp info;
	tp_item marcador;
	struct tp_no_aux *ant;
	struct tp_no_aux *prox;
}tp_no;

// Dado estruturado que representa o descritor da lista
// Ponteiros ini, fim e meio que apontam para o inicio, fim e meio da lista respectivamente
typedef struct{
	tp_no *ini;
	tp_no *fim;
	tp_no *meio;	
}tp_listade;

// Fun��o respos�vel por inicializar a lista
tp_listade *inicializa_listade(){
	tp_listade *lista=(tp_listade *) malloc(sizeof(tp_listade));
	lista->ini = NULL;
	lista->fim = NULL;
	lista->meio = NULL;	
	return lista;
}

// Aloca um n� da lista
tp_no *aloca_listade() {
	tp_no* pt;
	pt=(tp_no*) malloc(sizeof(tp_no));
	return pt;
}

// Fun��o respons�vel por navegar nas linhas e colunas da tela. Ela recebe como par�metro a posi��o em x e em y desejada
void posicao(int x,int y){ 	
	COORD p={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),p);
}

// Fun��o respons�vel por printar uma pedra na tela. Ela recebe como par�metro as posi��es x e y, os n�meros da pedra e a sua orientacao
// Para orientacao = 0, a pedra ser� imprimida na vertical. Para orientacao = 1, a pedra ser� imprimida na horizontal
void printa_pedra(int x, int y, int num1, int num2, int orientacao){
	switch(orientacao){
		case 0:			
			posicao(x,y);
			printf("+---+");
			y++;
			posicao(x,y);	
			printf("| %d |", num1);		
			y++;
			posicao(x,y);
			printf("+---+");
			y++;
			posicao(x,y);	
			printf("| %d |", num2);
			y++;
			posicao(x,y);
			printf("+---+");
			break;
		case 1:
			posicao(x, y);
			printf("+---+---+");
			y++;
			posicao(x, y);
			printf("| %d | %d |", num1, num2);
			y++;
			posicao(x, y);
			printf("+---+---+");
			break;
		default: printf("Orientacao invalida");			
	}		
					
}

// Fun��o respons�vel por conferir se a lista est� vazia
int listade_vazia(tp_listade *lista){
	if(lista->ini == NULL) return 1;
	return 0;
}

// Fun��o para inserir os elementos nas m�os dos jogadores de forma ordenada. Ela recebe como par�metro a lista, a struct da pedra e a vari�vel m que funciona como um marcador para indicar de qual jogador � essa pedra
int insere_listade_ordenado(tp_listade *lista, tp_itemp e, tp_item m){	
	tp_no *novo, *atu;	
	novo=aloca_listade();	
	if(!novo) return 0;		
	novo->info.num1 = e.num1;
	novo->info.num2 = e.num2;	
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

// Fun��o respons�vel por inserir um elemento no fim da lista da mesa. Ela recebe como par�metro a lista da mesa, o struct da pedra e a vari�vel m que indica qual lado da pedra n�o est� conectado com alguma pedra, ou seja, est� livre
// Para m = 1, o num1 da struct da pedra est� livre, para m = 2, o num2 da struct da pedra est� livre, para m = 0, se trata de uma bucha num1 = num2 e para m = 3, se trata da primeira pedra a sair na partida e que n�o � uma bucha, ou seja, suas duas extremidades est�o livres
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
		// Se o m(marcador) do elemento inicial da lista for igual a 3, ao ser adicionado uma nova pedra no fim dessa lista esse m passa a ser 1, ou seja, num1 est� livre
		if(lista->ini->marcador == 3){
			lista->ini->marcador = 1;
		}
		novo->prox = NULL;
		novo->ant = lista->fim;
		lista->fim->prox = novo;
		lista->fim = novo;
	}	
	return 1;
}

// Fun��o respons�vel por inserir um elemento no inicio da lista da mesa. Ela recebe como par�metro a lista da mesa, o struct da pedra e a vari�vel m que indica qual lado da pedra n�o est� conectado com alguma pedra, ou seja, est� livre
// Para m = 1, o num1 da struct da pedra est� livre, para m = 2, o num2 da struct da pedra est� livre, para m = 0, se trata de uma bucha num1 = num2 e para m = 3, se trata da primeira pedra a sair na partida e que n�o � uma bucha, ou seja, suas duas extremidades est�o livres
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
		// Se o m(marcador) do elemento inicial da lista for igual a 3, ao ser adicionado uma nova pedra no inicio dessa lista esse m passa a ser 2, ou seja, num2 est� livre
		if(lista->ini->marcador == 3){
			lista->ini->marcador = 2;
		}
		novo->prox = lista->ini;
		novo->ant = NULL;		
		lista->ini->ant = novo;		
		lista->ini = novo;		
	}
}

// Fun��o respons�vel por remover um elemento da lista. Recebe como par�metro o caso desejado, a lista, a posi��o e a depender do caso retorna o valor de (m) e da struct (e) da pedra. 
int remove_listade(tp_listade *lista, tp_itemp *e, tp_item *m, int caso, int turno, int posicao){
	if(listade_vazia(lista)) return 0;
	int condicao = 0;
	tp_itemp menor, reserva;	
	tp_no *atu, *aux;
	atu = lista->ini;	
	menor = atu->info;
	reserva.num1 = reserva.num2 = 0;
	switch(caso){
		// Caso o caso seja igual a 0, ela remove o elemento da m�o de acordo com a posi��o escolhida pelo usu�rio 
		case 0:
			while(atu->marcador != turno){
				atu=atu->prox;
			}			
			while(atu != NULL && posicao > 0){
				atu = atu->prox;
				posicao--;
			}
			break;
		// Caso o caso seja igual a 1, ela procura se h� uma bucha de sena nas m�os dos jogadores para remover, caso n�o encontre ela remove a bucha seguida de maior e caso n�o haja buchar ela remove a pedra com o menor valor no seu somat�rio
		case 1:
			// Procura a bucha de sena
			while(atu != NULL && (atu->info.num1 != 6 || atu->info.num2 != 6)){			
			if(atu->info.num1 == atu->info.num2){
				// Armazena as buchas de maior valor
				if(condicao == 0 || atu->info.num1 > reserva.num1){					
					reserva=atu->info;
					condicao = 1;
					aux = atu;					
				}											
			}
			// Armazena a pedra de menor valor caso ainda n�o tenha encontrado nenhuma bucha
			if((atu->info.num1 + atu->info.num2)<(menor.num1 + menor.num2) && condicao != 1){
				menor = atu->info;
				aux = atu;
			}		
			atu = atu->prox;					
			}
			break;		
		default : printf("codigo invalido");
	}
	
	if(caso == 1){
		// Se atu = NULL, a bucha de sena n�o foi encontrada						
		if(atu == NULL){
			// Se o caso for 1, o valor de num1 da struct reserva igual a 0 e a condicao = 0, ou seja, n�o foi encontrada nenhuma bucha, ele retorna a struct da pedra com menor valor e o valor de m (marcador) dessa pedra		
			if(reserva.num1 == 0 && condicao == 0){
				*e = menor;
				*m = aux->marcador;
			}
			// Se condicao = 1, significa que foi encontrada uma bucha, ent�o � retornado o struct dessa bucha e o valor de m (marcador) dessa pedra
			else{				
				*e = reserva;
				*m = aux->marcador;
			}				
			atu = aux;
		} 
		// Se atu != NULL, a bucha de sena foi encontrada, ent�o retorna a struct dessa pedra e o valor de m (marcador)
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

// Fun��o respons�vel por comparar as pedras das m�os dos jogadores com a extremidade da mesa para saber se � poss�vel jogar a pedra.
//Recebe como par�metro os marcadores iniciais e finais da mesa (m_ini, m_fim), o struct inicial e final da mesa (mesaini, mesafim), a struct da pedra atual da m�o do jogador (pedra), o caso e retorna o valor de m (marcador)
// Caso o caso = 3, ela ir� comparar a pedra da m�o do jogador com as duas extremidades da mesa, caso = 0 somente a extremidade esquerda ser� comparada e caso = 1 somente a extremidade direita ser� comparada  
int compara_pedras(tp_item m_ini, tp_item m_fim, tp_itemp mesaini, tp_itemp mesafim, tp_itemp pedra, int caso, tp_item *m){
	// Compara a extremidade esquerda
	if(caso == 0 || caso == 3){
		// Se o marcador inicial da lista for igual a 0 ou 1, compara os n�meros da pedra com num1 (n�mero livre) da struct do inicio da mesa para saber se s�o iguais e se � poss�vel jogar			
		if(m_ini == 0 || m_ini == 1){		
			if(pedra.num1 == mesaini.num1 || pedra.num2 == mesaini.num1){
				if(caso == 0){
					if(pedra.num1 == pedra.num2)
						*m = 0;
					else{																				
						if(pedra.num1 == mesaini.num1)
							*m = 2;
						else
							*m = 1;	
					}
				}							
				return 1;
			}
		}
		else{
			// Se o marcador inicial da lista for igual a 2, compara os n�meros da pedra com num2 (n�mero livre) da struct do inicio da mesa para saber se s�o iguais e se � poss�vel jogar
			if(m_ini == 2){
				if(pedra.num1 == mesaini.num2 || pedra.num2 == mesaini.num2){
					if(caso == 0){	
						if(pedra.num1 == pedra.num2)
							*m = 0;
						else{										
							if(pedra.num1 == mesaini.num2)
								*m = 2;
							else
								*m = 1;
						}
					}					
					return 1;
				}			
			}
			else{
				// Se o marcador do elemento da lista for igual a 3, compara os n�meros da pedra com num1 e num2 (n�meros livres) da struct do inicio da mesa para saber se s�o iguais e se � poss�vel jogar em algum dos lados
				if(pedra.num1 == mesaini.num1 || pedra.num1 == mesaini.num2 || pedra.num2 == mesaini.num1 || pedra.num2 == mesaini.num2){
					if(caso == 0){
						if(pedra.num1 == pedra.num2)
							*m = 0;
						else{ 											
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
					}					
					return 1;
				}			
			}
		}
	}
	// Compara a extremidade direita
	if(caso == 1 || caso == 3){
		// Se o marcador final da lista for igual a 0 ou 1, compara os n�meros da pedra com num1 (n�mero livre) da struct do fim da mesa para saber se s�o iguais e se � poss�vel jogar	
		if(m_fim == 0 || m_fim == 1){		
			if(pedra.num1 == mesafim.num1 || pedra.num2 == mesafim.num1){
				if(caso == 1){
					if(pedra.num1 == pedra.num2)
						*m = 0;
					else{								
						if(pedra.num1 == mesafim.num1)
							*m = 2;
						else
							*m = 1;
					}
				}							
				return 1;
			}
		}	
		else{
			// Se o marcador final da lista for igual a 2, compara os n�meros da pedra com num2 (n�mero livre) da struct do fim da mesa para saber se s�o iguais e se � poss�vel jogar
			if(m_fim == 2){
				if(pedra.num1 == mesafim.num2 || pedra.num2 == mesafim.num2){
					if(caso == 1){
						if(pedra.num1 == pedra.num2)
							*m = 0;
						else{
							if(pedra.num1 == mesafim.num2)
								*m = 2;
							else
								*m = 1;	
						}
					}					
					return 1;
				}			
			}			
		}
	}	
	return 0;	
}

// Fun��o respons�vel por retornar o tamanho da lista da mao do jogador
int tamanho_listade(tp_listade *lista, int turno){
	int cont = 1;
	tp_no *atu;
	atu=lista->ini;
	// Percorre a lista at� encontrar a m�o do jogador desejado
	while(atu->marcador != turno){		
		atu=atu->prox;
	}
	// Realiza a contagem da quantidade de pedras em m�os do jogador
	while(atu != NULL && atu->marcador == turno){
		atu=atu->prox;
		cont++;
	}
	return cont;	
}

// Fun��o respons�vel por printar as listas das m�os e da mesa em tela
// Recebe como par�metro as duas listas, a ordem (caso a ser impresso) e o turno do jogador
void imprime_listade(tp_listade *lista, tp_listade *lista2, int ordem, int turno){
	int cont=1, cond = 0, condicao_tela = 0, x, y, orientacao = 0;
	tp_itemp mesaini, mesafim;
	tp_item m_ini, m_fim;	
	tp_no *atu;	
	switch(ordem){
		// Caso ordem = 1, ela ir� imprimir a mesa no centro da tela
		// Primeiramente, imprime a extremidade esquerda da lista		
		case 1: atu = lista->meio;			
			x = 44;
			y = 11;					
			while(atu != NULL){
				// Confere se o primeiro elemento n�o � uma bucha
				if(atu->marcador == 3){
					x -= 4;
					y -= 1;
					printa_pedra(x, y, atu->info.num1, atu->info.num2, 1);
				}
				else{
					// Confere se o primeiro elemento � uma bucha				
					if(atu->marcador == 0 && atu == lista->meio){
						x -= 2;
						y -= 2;
						printa_pedra(x, y, atu->info.num1, atu->info.num2, 0);
					}
					else{
						// Confere se o elemento que est� sendo printado � uma bucha
						if(atu->marcador == 0){	
							// condicao_tela = 0, a lista ser� printada normalmente da direita para esquerda
							if(condicao_tela == 0){
								x -= 5;
								y -= 1;
								orientacao = 0;																
							}
							// condicao_tela = 2, a lista ser� printada de forma inversa da esquerda para direita
							if(condicao_tela == 2){
								x += 9;
								y -= 1;
								orientacao = 0;								
							}
							// condicao_tela = 1, o elemento ser� printado na horizontal da esquerda para direita 
							if(condicao_tela == 1){
								y -= 3;
								orientacao = 1;
								condicao_tela = 2;
							}
							
							// Caso o limite da tela for superado, as pedras ser�o adaptadas e printadas na vertical para cima													
							if(x <= 0){
								y += 1;
								x += 5;
								y -= 5;
								condicao_tela = 1;								
							}
														
							printa_pedra(x, y, atu->info.num1, atu->info.num2, orientacao);														
						}
						// Confere se o elemento que est� sendo printado n�o � uma bucha
						else{
							// condicao_tela = 0, a lista ser� printada normalmente da direita para esquerda																			
							if(condicao_tela == 0){
								x -= 9;
								// Confere se o elemento anterior ao que est� sendo printado era uma bucha 								
								if(atu->prox->marcador == 0)							
									y += 1;
								orientacao = 1;																								
							}
							// condicao_tela = 2, a lista ser� printada de forma inversa da esquerda para direita
							if(condicao_tela == 2){
								// Confere se o elemento anterior ao que est� sendo printado � uma bucha e se o local a ser printado est� fora do range de transi��o da adapta��o da tela
								if(atu->prox->marcador == 0 && x > 7){								
									y += 1;
									x += 5;
								}
								else{
									x += 9;
								}								
								orientacao = 1;								
							}
							// condicao_tela = 1, o elemento ser� printado na horizontal da esquerda para direita
							if(condicao_tela == 1){
								orientacao = 1;
								y -= 3;
								condicao_tela = 2;																
							}
							// Caso o limite da tela for superado, as pedras ser�o adaptadas e printadas na vertical para cima							
							if(x <= 0){
								if(atu->prox->marcador == 0)
									y -= 1;
								x += 9;
								y -= 5;
								orientacao = 0;
								condicao_tela = 1;
							}
							
							if(condicao_tela == 0 || condicao_tela == 1){																																				
								if(atu->marcador == 1)																														
									printa_pedra(x, y, atu->info.num1, atu->info.num2, orientacao);							
								else																						
									printa_pedra(x, y, atu->info.num2, atu->info.num1, orientacao);	
							}
							else{
								if(atu->marcador == 1)
									printa_pedra(x, y, atu->info.num2, atu->info.num1, orientacao);
								else
									printa_pedra(x, y, atu->info.num1, atu->info.num2, orientacao);								
							}
						}												
																		
					}
				}
				atu = atu->ant;						
			}
			condicao_tela = 0;			
			atu = lista->meio->prox;						
			x = 44;
			y = 11;
			// Imprime a extremidade direita da mesa
			while(atu != NULL){
				// Confere se o primeiro elemento da lista foi uma bucha								
				if(atu->ant->marcador == 0 && atu->ant == lista->meio){					
					x -= 2;
					y -= 2;					
				}
				// Confere se o primeiro elemento da lista n�o foi uma bucha
				else{					
					if(atu->ant->marcador == 3){
						x -= 4;						
						y -= 1;						
					}
				}
				// Confere se o elemento que est� sendo printado � uma bucha																									
				if(atu->marcador == 0){
					// condicao_tela = 0, a lista ser� printada normalmente da esquerda para direita
					if(condicao_tela == 0){													
						x += 9;
						y -= 1;							
						orientacao = 0;
					}
					// condicao_tela = 2, a lista ser� printada de forma inversa da direita para esquerda
					if(condicao_tela == 2){
						x -= 5;
						y -= 1;
						orientacao = 0;
					}
					//condicao_tela = 1, o elemento ser� printado na horizontal da direita para esquerda
					if(condicao_tela == 1){
						y += 5;
						x -= 4;
						condicao_tela = 2;
						orientacao = 1;								
					}					
					
					//Caso o limite da tela for superado, as pedras ser�o adaptadas e printadas na vertical para baixo
					if(x + 4 >= 88){
						x -= 1;
						y += 1;
						x -= 4;
						y += 3;
						orientacao = 0; 								
						condicao_tela = 1;								
					}							
					printa_pedra(x, y, atu->info.num1, atu->info.num2, orientacao);
				}
				// Confere se o elemento que est� sendo printado n�o � uma bucha
				else{
					// condicao_tela = 0, a lista ser� printada normalmente da esquerda para direita					
					if(condicao_tela == 0){
						// Confere se o elemento anterior ao que est� sendo printado � uma bucha					
						if(atu->ant->marcador == 0){													
							y += 1;							
							x += 5;
						}
						else
							x += 9;
						orientacao = 1;
					}
					// condicao_tela = 2, a lista ser� printada de forma inversa da direita para esquerda
					if(condicao_tela == 2){
						// Confere se o elemento anterior ao que est� sendo printado � uma bucha e se o local a ser printado est� fora do range de transi��o da adapta��o da tela
						if(atu->ant->marcador == 0 && x < 74)							
							y += 1;											
						x -= 9;						
						orientacao = 1;	
					}
					//condicao_tela = 1, o elemento ser� printado na horizontal da direita para esquerda
					if(condicao_tela == 1){
						x -= 4;								
						y += 5;
						orientacao = 1;
						condicao_tela = 2;															
					}
					//Caso o limite da tela for superado, as pedras ser�o adaptadas e printadas na vertical para baixo
					if(x + 8 >= 88){
						if(atu->ant->marcador == 0){
							y -= 1;
							y += 5;
						}
						else{
							y += 3;
						}							
						x -= 5;						
						condicao_tela = 1;
						orientacao = 0;
					}
					
					if(condicao_tela == 0 || condicao_tela == 1){ 																											
						if(atu->marcador == 1)																				
							printa_pedra(x, y, atu->info.num2, atu->info.num1, orientacao);						
						
						else																			
							printa_pedra(x, y, atu->info.num1, atu->info.num2, orientacao);								
					}
					
					else{
						if(atu->marcador == 1)																				
							printa_pedra(x, y, atu->info.num1, atu->info.num2, orientacao);						
						
						else																			
							printa_pedra(x, y, atu->info.num2, atu->info.num1, orientacao);								
					}											
				}							
				atu = atu->prox;								
			}											
			break;
		// Caso ordem = 2, ela ir� imprimir a m�o do jogador atual com as respectivas posi��es da pedra para que ele possa selecionar qual deseja jogar			
		case 2: atu = lista->ini;
			mesaini = lista2->ini->info;
			mesafim = lista2->fim->info;
			m_ini = lista2->ini->marcador;
			m_fim = lista2->fim->marcador;
			
			//Percorre a lista at� as m�os do jogador atual			
			while(atu->marcador != turno){
				atu=atu->prox;
			}			
			x = 44 - (5*tamanho_listade(lista, turno))/2;
			if(x < 0){
				x = 2;
			}
			//Percorre a m�o do jogador atual			
			while(atu != NULL && atu->marcador == turno){
				// Por meio da fun��o compara_pedras, compara se � poss�vel jogar a pedra selecionada, se sim a cor � branca, se n�o, a cor � cinza escuro					
				if(compara_pedras(m_ini, m_fim, mesaini, mesafim, atu->info, 3, NULL)){					
					textcolor(15);					
				}									
				else{
					textcolor(8);					
				}
				// Caso a quantidade de pedras n�o caiba na tela, ele pula de linha
				if(x >= 88 || cond == 1){
					y = 33;
					if(x >= 88){
						x = 2;
					}			
					cond = 1;
				}
				if(cond == 0){
					y = 27;
				}		
				posicao(x, y);				
				printf("%d", cont);		
				x = x - 2;
				y++;
				posicao(x, y);
				printa_pedra(x, y, atu->info.num1, atu->info.num2, 0);
				x = x + 8;	
				posicao(x, y);							
				atu = atu->prox;
				cont++;
			}
			textcolor(15);
			break;
		case 3: atu = lista->ini;
			posicao(0, 60);
			while(atu != NULL){				
				printf("|%d - %d/%d| ", atu->marcador, atu->info.num1, atu->info.num2);
				atu = atu->prox;
			}
			break;		
		default : printf("codigo invalido");
	}
	printf("\n");
}

// Fun��o repons�vel por buscar a pedra na m�o do jogador atual na posi��o selecionada pelo mesmo
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

// Fun��o respons�vel por destruir a lista
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
