#ifndef LISTADE_H
#define LISTADE_H

#include <stdio.h>
#include <stdlib.h>

typedef int tp_item;

//dados estruturado que representa o descritor
typedef struct tp_no_aux{
	tp_item info;
	struct tp_no_aux *ant;
	struct tp_no_aux *prox;
}tp_no;

//dado estruturado que representa o nó da lista
typedef struct{
	tp_no *ini;
	tp_no *fim;
	//int tamanho;
}tp_listade;

tp_listade *inicializa_listade(){
	tp_listade *lista=(tp_listade *) malloc(sizeof(tp_listade));
	lista->ini = NULL;
	lista->fim = NULL;
	//lista->tamanho=0;
	return lista;
}

//Aloca um nó da lista
tp_no *aloca() {
	tp_no* pt;
	pt=(tp_no*) malloc(sizeof(tp_no));
	return pt;
}

int listade_vazia(tp_listade *lista){
	if(lista->ini == NULL) return 1;
	return 0;
}

int insere_listade_no_fim(tp_listade *lista, tp_item e){
	tp_no *novo;
	novo=aloca();
	if(!novo) return 0;
	novo->info = e;
	if(lista->ini == NULL){
		novo->prox = NULL;
		novo->ant = NULL;
		lista->ini = lista->fim = novo;
	}
	else{
		novo->prox = NULL;
		novo->ant = lista->fim;
		lista->fim->prox = novo;
		lista->fim = novo;
	}
	//lista->tamanho++;
	return 1;
}

int remove_listade(tp_listade *lista, tp_item e){
	tp_no *atu;
	atu = lista->ini;
	while((atu != NULL)&&(atu->info != e)){
		atu = atu->prox;}
	if(atu == NULL) return 0;
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
	//lista->tamanho--;
	return 1;
}

void imprime_listade(tp_listade *lista, int ordem){
	tp_no *atu;
	switch(ordem){
		case 1: atu = lista->ini;
			while(atu != NULL){
				printf("%d\n", atu->info);
				atu = atu->prox;
			}
			break;
		case 2: atu = lista->fim;
			while(atu != NULL){
				printf("%d\n", atu->info);
				atu = atu->ant;
			}
			break;
		default : printf("codigo invalido");
	}
	printf("\n");
}

tp_no *busca_listade(tp_listade *lista, tp_item e){
	tp_no *atu;
	atu = lista->ini;
	while((atu != NULL) && (atu->info != e)){
		atu = atu->prox;		
	}
	return atu;
}

tp_listade *destroi_listade(tp_listade *lista){
	tp_no *atu;
	atu = lista->ini;
	while(atu != NULL){
		lista->ini = atu->prox;
		free(atu);
		atu=lista->ini;
	}
	free(lista);
	return NULL;
}

#endif
