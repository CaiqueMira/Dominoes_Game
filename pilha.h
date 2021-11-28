#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int num1, num2, joga;	
}pedra;

typedef pedra tp_itemp; 

typedef struct tp_no_pilha_aux{   
	tp_itemp info;   
	struct tp_no_pilha_aux *prox;   
}tp_no_pilha; 


typedef struct {   
	tp_no_pilha *topo;   
}tp_pilha;


tp_pilha *inicializa_pilha(){
	tp_pilha *pilha=(tp_pilha*) malloc(sizeof(tp_pilha));   
	pilha->topo = NULL;   
	return pilha;
}  

tp_no_pilha *aloca_pilha(){
	tp_no_pilha* pt;
	pt=(tp_no_pilha*) malloc(sizeof(tp_no_pilha));
	return pt;
}

int pilha_vazia(tp_pilha *pilha){   
	if (pilha->topo == NULL) return 1;
	return 0;
}

int push(tp_pilha *pilha, tp_itemp e){   
	tp_no_pilha *novo;   
	novo=aloca_pilha();	
	if (!novo) return 0;
	
	novo->info = e;	  
	if(pilha_vazia(pilha)==1) { //Se for o primeiro elemento da lista
	 novo->prox = NULL;   
	 //pilha->topo = novo;
	 }  
	else {
	 novo->prox = pilha->topo;   
	 //pilha->topo = novo; 
	 }  
	pilha->topo = novo; 
	return 1;   
}        

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

int top(tp_pilha *pilha, tp_itemp *e){   
	tp_no_pilha *aux;
	
	if (pilha_vazia(pilha)) return 0;
	*e=pilha->topo->info;
	return 1;   
}        



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
