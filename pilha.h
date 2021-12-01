#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>

// Struct das pedras
typedef struct{
	int num1, num2;	
}pedra;

typedef pedra tp_itemp; 

//Dados que representam um n� da pilha
typedef struct tp_no_pilha_aux{   
	tp_itemp info;   
	struct tp_no_pilha_aux *prox;   
}tp_no_pilha; 

//Dado que representa a pilha
typedef struct {   
	tp_no_pilha *topo;   
}tp_pilha;

// Fun��o respons�vel por inicializar a pilha
tp_pilha *inicializa_pilha(){
	tp_pilha *pilha=(tp_pilha*) malloc(sizeof(tp_pilha));   
	pilha->topo = NULL;   
	return pilha;
}  

// Aloca um n� da pilha
tp_no_pilha *aloca_pilha(){
	tp_no_pilha* pt;
	pt=(tp_no_pilha*) malloc(sizeof(tp_no_pilha));
	return pt;
}

//Fun��o respons�vel por indicar se a pilha est� vazia ou n�o
int pilha_vazia(tp_pilha *pilha){   
	if (pilha->topo == NULL) return 1;
	return 0;
}

//Fun��o respons�vel por inserir um elemento no topo da pilha
int push(tp_pilha *pilha, tp_itemp e){   
	tp_no_pilha *novo;   
	novo=aloca_pilha();	
	if (!novo) return 0;
	
	novo->info = e;	  
	if(pilha_vazia(pilha)==1) { 
	 novo->prox = NULL; 
	 }  
	else {
	 novo->prox = pilha->topo;	 
	 }  
	pilha->topo = novo; 
	return 1;   
}        

//Fun��o respons�vel por remover um elemento do topo da pilha e retornar a struct desse elemento
int pop(tp_pilha *pilha, tp_itemp *e){   
	tp_no_pilha *aux;
	
	if (pilha_vazia(pilha)) return 0;
	*e=pilha->topo->info;
	aux=pilha->topo;
	pilha->topo=pilha->topo->prox;
	free(aux);
	aux=NULL;
	return 1;   
}        

 
// Fun��o respons�vel por contabilizar o tamanho da pilha
int tamanho_pilha(tp_pilha *pilha){
	int cont=0;
	tp_no_pilha *aux;
	aux = pilha->topo;
	while(aux != NULL){
		cont++;
		aux = aux->prox;
	}
	return cont;
		
}       


// Fun��o respons�vel por destruir a pilha
void destroi_pilha(tp_pilha *pilha) {    
	tp_no_pilha *atu=pilha->topo, *aux;
	tp_itemp e;
	while (atu != NULL){
		aux = atu->prox;
	    pop(pilha, &e);  
		atu= aux; 
	}
	pilha->topo = NULL;
	free(pilha);
}


// Fun��o para imprimir os elementos da pilha
// Obs: N�o est� sendo utilizada no jogo, utilizada somente para fins de curiosidade da visualiza��o do cava
void imprime_pilha(tp_pilha *pilha) {
	int cont = 0;
	tp_pilha *pilha_aux;
	tp_itemp e;
	//cria e inicializa uma pilha auxiliar
	pilha_aux=inicializa_pilha();	
	while (!pilha_vazia(pilha)){
	    pop(pilha,&e);
		printf("%d-%d/%d\n", cont+1, e.num1, e.num2);
		cont++;	    	    
	    push(pilha_aux, e);           
	} 		
	while (!pilha_vazia(pilha_aux)){
	    pop(pilha_aux,&e);	    
	    push(pilha, e);           
	}
	free(pilha_aux);
}

#endif
