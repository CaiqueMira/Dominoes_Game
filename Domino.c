#include "pilha.h"
#include "listade.h"
#include <time.h>
#include <locale.h>

// Fun��o respons�vel por printar as bordas superiores e inferiores dos bot�es do menu
void printa_botao(){
	int i;
	for(i=0;i<17;i++){printf("-");
	}	
}

// Fun��o respons�vel por printar as bordas da tela, recebendo como par�metro as posi��es x e y de onde a borda come�ar� e o tamanho desejado
void printa_borda(int x, int y, int tam){
	while(y < tam){
		posicao(x, y);
		printf("#");				
			if(x == 88){
				x = 0;
				y++;
			}
			else{		
				x++;
				if(x >= 1 && y > 0 && y != tam-1){
					x = 88;
				}
			}
	}	
}

// Fun��o respons�vel por printar e atualizar todas as informa��es das telas
void printa_tela(int tela, char nome1[1], char nome2[1], char nome3[1], char nome4[1], int tam, int turno, tp_listade *maos, tp_listade *mesa){
	int x=0, y=0, num = 10, i;	
	system("cls");			
	switch(tela){
		// Caso tela = 0, ser� printada a tela inicial
		case 0:				
			printa_borda(x, y, 22);
			posicao(44-7, 3);
			printf("JOGO DE DOMIN�");			
			printa_pedra(4, 4, 6, 6, 0);
			printa_pedra(80, 4, 2, 3, 0);
			printa_pedra(4, 15, 5, 4, 0);
			printa_pedra(80, 15, 3, 2, 0);
			x = 36;
			y = 9;
			posicao(x, y);
			printa_botao();
			y++;
			posicao(x, y);
			printf("|     Jogar     |");
			y++;
			posicao(x, y);
			printf("|  Pressione 1  |");
			y++;
			posicao(x, y);
			printa_botao();
			x = 44;
			y += 5;
			posicao(x, y);						
			break;
		
		// Caso tela = 1, ser� printada uma tela vazia somente com as bordas
		case 1:			
			printa_borda(x, y, 22);			
			break;		
		
		// Caso tela = 2, ser� printada a tela que possui as bordas, informa��es do cava, a mesa e a m�o do jogador				
		case 2:		
			printa_borda(x, y, 23);
			y = 23;
			
			// Imprime as informa��es do cava	
			while(y < 27){
				x = 73;				
				posicao(x, y);
				printf("|");				
				if(y == 23 || y == 24 || y == 25 || y == 26){
					while(x <= 88){
						if(y == 23 || y == 26){
							printf("-");
							x++;
							posicao(x, y);																									
						}
						if(y == 24){
							printf("Cava restante:");
							x = 89;
						}
						if(y == 25){
							posicao(81, y);
							printf("%d", tam);
							x = 89;
						}				
					}
				}
				y++;			
			}
			
			// Imprime a mesa no centro da tela			
			imprime_listade(mesa, NULL, 1, turno); 
			
			// Imprime a m�o do jogador atual com as posi��es das pedras para que o jogador possa selecionar
			imprime_listade(maos, mesa, 2, turno);
			
			// Imprime o turno atual de quem est� jogando			
			switch(turno){
				case 1:
					posicao(44-(9+strlen(nome1))/2, 24);
					printf("Turno de %s", nome1);
					break;
				case 2:
					posicao(44-(9+strlen(nome2))/2, 24);
					printf("Turno de %s", nome2);
					break;
				case 3:
					posicao(44-(9+strlen(nome3))/2, 24);
					printf("Turno de %s", nome3);
					break;
				case 4:
					posicao(44-(9+strlen(nome4))/2, 24);
					printf("Turno de %s", nome4);
					break;
				default: printf("Jogador inv�lido");					
			}			
			break;
		
		// Caso tela = 3, ser� printada a tela final com as bordas, indicando quem foi o vencedor e os bot�es de sele��o se deseja jogar novamente ou sair
		case 3:
			printa_borda(x, y, 22);
			
			// Mostra quem venceu
			switch(turno){
				case 1:
				posicao(44-(17+strlen(nome1))/2, 3);
					printf("%s venceu a partida!", nome1);
					break;
				case 2:
					posicao(44-(17+strlen(nome2))/2, 3);
					printf("%s venceu a partida!", nome2);
					break;
				case 3:
					posicao(44-(17+strlen(nome3))/2, 3);
					printf("%s venceu a partida!", nome3);
					break;
				case 4:
					posicao(44-(17+strlen(nome4))/2, 3);
					printf("%s venceu a partida!", nome4);
					break;
				default: printf("Jogador inv�lido");				
			}
			x=36;
			y=3;
			
			// Printa os bot�es na tela	
			for(i=1;i<=2;i++){		
				y+=3;				
				posicao(x,y);	
				printa_botao();		
				y++;
				posicao(x,y);					
				if(i==1){printf("|Jogar novamente|");}
				else{printf("|     Sair      |");}						
				y++;
				posicao(x,y);					
				if(i==1){printf("|  Pressione 1  |");}
				else{printf("|  Pressione 2  |");}						
				y++;
				posicao(x,y);
				printa_botao();			
			}
			break;						
	}	
}

// Fun��o respons�vel por contar as pedras da m�o do jogador atual, caso n�o haja mais pedras na m�o do jogador atual ela retorna 0 para indicar que a m�o do jogador est� vazia
int conta_pedras(tp_listade *maos, int turno){
	tp_no *atu;
	atu = maos->ini;
	while(atu != NULL && atu->marcador != turno){
		atu=atu->prox;		
	}
	if(atu == NULL) return 0;
	return 1;			
}

// Fun��o respons�vel por checar quem foi o vencedor caso o jogo seja fechado, sendo aquele que possui o menor valor na soma das suas pedras restantes
int vencedor(tp_listade *maos, int tam, char nome1[1], char nome2[1], char nome3[1], char nome4[1]){
	int menor, pontuacao[tam], i, posicao, igual=0;
	tp_no *atu;
	atu = maos->ini;
	// Atribui 0 para o vetor pontuacao em todas as posi��es de acordo com o n�mero de jogadores
	for(i=0; i<tam; i++){
		pontuacao[i] = 0;
		i++;
	}
	
	// Percorre toda a lista das m�os somando as pedras e armazenando em cada posi��o do vetor pontuacao para cada jogador		
	while(atu != NULL){
		if(atu->marcador == 1){		
			pontuacao[0] = pontuacao[0] + (atu->info.num1 + atu->info.num2);
		}
		else{
			if(atu->marcador == 2){
				pontuacao[1] = pontuacao[1] + (atu->info.num1 + atu->info.num2);
			}
			else{
				if(atu->marcador == 3){
					pontuacao[2] = pontuacao[2] + (atu->info.num1 + atu->info.num2);
				}
				else{
					pontuacao[3] = pontuacao[3] + (atu->info.num1 + atu->info.num2);
				}
			}
		}
		atu=atu->prox;			
	}
	menor = pontuacao[0];
	posicao = 0;
	
	// Percorre todo o vetor pontuacao buscando encontrar o menor valor
	for(i=1;i<tam;i++){
		if(pontuacao[i] < menor){
			menor = pontuacao[i];
			posicao = i;
		}			
	}
	// Printa a tela final passando como par�metro o jogador que possui o menor valor na soma de suas pedras, informando que o mesmo venceu a partida	
	printa_tela(3, nome1, nome2, nome3, nome4, NULL, posicao+1, NULL, NULL);			
}

// Fun��o respons�vel por checar se o jogador do turno atual possui alguma pedra correspondente para ser jogada 
int checa_pedras(tp_listade *maos, tp_listade *mesa, tp_pilha *cava, int turno, char nome1[1], char nome2[1], char nome3[1], char nome4[1]){
	int condicao_cava = 1, cont = 0;	
	tp_no *atu;
	tp_item m_ini, m_fim;	
	tp_itemp mesaini, mesafim, e;
	m_ini = mesa->ini->marcador;
	m_fim = mesa->fim->marcador;
	mesaini = mesa->ini->info;
	mesafim = mesa->fim->info;		
	atu = maos->ini;
	
	// Percorre a lista das m�os at� atingir a posi��o da m�o do jogador atual			
	while(atu->marcador != turno){
		atu=atu->prox;
	}
	//Percorre toda a m�o do jogador atual chamando a fun��o compara_pedras para conferir alguma pedra pode ser jogada	
	while(atu != NULL && atu->marcador == turno){
		if(compara_pedras(m_ini, m_fim, mesaini, mesafim, atu->info, 3, NULL)){
			condicao_cava = 0;			
		}
		atu=atu->prox;				
	}
	// Caso a condicao_cava = 1, significa que n�o h� nenhuma pedra dispon�vel para ser jogada na m�o do jogador atual	
	while(condicao_cava == 1){
		if(cont == 0){
			posicao(0, 40);
			switch(turno){
				case 1:
					printf("-> %s ", nome1);
					break;
				case 2:
					printf("-> %s ", nome2);
					break;
				case 3:
					printf("-> %s ", nome3);
					break;
				case 4:
					printf("-> %s ", nome4);
					break;
				default: printf("Jogador inv�lido");
			}		
			printf("n�o possui pedras para jogar");
			cont++;
		}
		Sleep(2000);
		// Caso a pilha esteja vazia, ser� retornada para a fun��o jogo que o jogador atual n�o possui as pedras e que n�o h� mais um cava restante, passando a vez para o pr�ximo jogador
		if(pilha_vazia(cava)){
			posicao(0, 41);		
			printf("-> N�o h� mais pedras dispon�veis no cava, passa a vez\n");
			Sleep(2000);
			return 0;
		}
		// Caso a pilha n�o esteja vazia, ser� removida uma pedra do cava e adicionada a m�o desse jogador por meio da fun��o insere_lsitade_ordenado				
		pop(cava, &e);
		insere_listade_ordenado(maos, e, turno);
		printa_tela(2, nome1, nome2, nome3, nome4, tamanho_pilha(cava), turno, maos, mesa);
		posicao(0, 41);
		printf("-> Cavando...\n");
		Sleep(2000);
		// A pedra removida do cava e adicionada na m�o ser� ent�o conferida por meio da fun��o compara_pedra se � poss�vel ser jogada em alguma das extremidades da mesa		
		if(compara_pedras(m_ini, m_fim, mesaini, mesafim, e, 3, NULL))
			condicao_cava = 0;						
	}
	return 1;		
}

// Fun��o onde toda a l�gica do jogo ocorrer�
int jogo(tp_listade *maos, tp_listade *mesa, tp_pilha *cava, int jogadores, char nome1[1], char nome2[1], char nome3[1], char nome4[1]){
	int condicao_parada=0, turno, localizacao, lado, jogo_fechado = 0, escolha;
	tp_itemp pedra_atu;
	tp_item m;
	tp_itemp e;
	
	// Chama a fun��o de remover um elemento da lista no caso 1, ou seja, ser� procurada a bucha de sena nas m�os dos jogadores
	// Caso n�o haja a bucha de sena na m�o dos jogadores, ser� removida a bucha que tiver o maior valor
	// Caso n�o haja buchas n�s m�os dos jogadores, ser� removida a pedra com o menor valor
	// Ser� armazenado de quem a pedra foi retirada para definir o sentido do jogo que ser� a partir desse jogador em ordem crescente			
	remove_listade(maos, &e, &m, 1, NULL, 2);
	turno = m;
	
	// Printa a primeira tela e mostra de qual jogador a primeira pedra foi retirada		
	printa_tela(1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	posicao(0, 40);	
	printf("->Pedra inicial sai da m�o de ");
	switch(turno){
		case 1:
			printf("%s", nome1);
			break;
		case 2:
			printf("%s", nome2);
			break;
		case 3:
			printf("%s", nome3);
			break;
		case 4:
			printf("%s", nome4);
			break;
		default: printf("Jogador inv�lido");
	}
	// Soma mais um no turno para passar a ver para o pr�ximo jogador seguido do qual cedeu a primeira pedra do jogo		
	turno++;
	Sleep(2000);
	
	// Se a pedra removida for uma bucha, o seu marcador ser� igual a 0. Caso n�o, seu marcador � igual a 3	
	if(e.num1 == e.num2) 
		m = 0;	
	else 
		m = 3;
	
	// Insere na mesa a primeira pedra removida da m�o dos jogadores	
	insere_listade_no_fim(mesa, e, m);
	
	// Enquanto a vari�vel condicao_parada for igual a 0, significa que a partida n�o acabou e o jogo ocorrer�		
	while(condicao_parada == 0){
		
		// Caso o turno seja maior que o n�mero de jogadores, significa que foi dada uma volta completa entre os jogadores, do jogador 1 ao jogador 4, e o turno passa a ser novamente do jogador 1		
		if(turno > jogadores){
			turno = 1;
		}
		
		// Printa a segunda tela do jogo mostrando informa��es essenciais, como: a mesa, a m�o do jogador atual para que ele possa escolher qual pedra quer jogar e a quantidade restante de pedras no cava				
		printa_tela(2, nome1, nome2, nome3, nome4, tamanho_pilha(cava), turno, maos, mesa);
		
		// Confere por meio da fun��o checa_pedra se o jogador atual possui a pedra correspondente para jogar em alguma das extremidades da mesa (esquerda ou direita)
		// Caso n�o, esse jogador ir� cavar, entretanto se n�o houver pedras restantes no cava, ser� passada a vez do jogador para o pr�ximo
		// A cada vez que uma vez � passada, a vari�vel jogo_fechado � incrementada, pois se ela for igual ao n�mero de jogadores significa que nenhum dos jogadores possui uma pedra correspondente para jogar e que o jogo est� fechado
		// Dessa forma, condicao_parada se torna 1 para indicar que a partida est� encerrada				
		if(!checa_pedras(maos, mesa, cava, turno, nome1, nome2, nome3, nome4)){
			jogo_fechado++;
			turno++;
			if(jogo_fechado == jogadores){
				condicao_parada = 1;
			}			
		}
		else{
			
			// Caso o jogador cave ou ja possua uma pedra correspondente para jogar, as informa��es seram atualizadas e ser� solicitado ao usu�rio que uma escolha uma das pedras disponiveis para jogar 
			printa_tela(2, nome1, nome2, nome3, nome4, tamanho_pilha(cava), turno, maos, mesa);
			jogo_fechado = 0;						
			posicao(0, 40);
			printf("-> Selecione qual pedra deseja jogar: ");				
			scanf("%d", &localizacao);
			
			// Enquanto a sele��o do usu�rio for menor que 0 ou maior do que a quantidade de pedras disponiveis para jogar, ser� solicitado que ele insira uma posi��o v�lida		
			while(localizacao >= tamanho_listade(maos, turno) || localizacao < 0){
				printa_tela(2, nome1, nome2, nome3, nome4, tamanho_pilha(cava), turno, maos, mesa);
				posicao(0, 40);						
				printf("-> Posi��o inserida inv�lida, insira uma posi��o v�lida: ");
				scanf("%d", &localizacao);
			}
			// A vari�vel pedra_atu � utilizada para receber o valor da pedra selecionada pelo jogador por meio da fun��o busca_listade_posicao, que retorna a struct da pedra na posicao selecionada pelo jogador
			pedra_atu = busca_listade_posicao(maos, localizacao-1, turno);
			
			// Por meio da fun��o compara_pedras, ser� conferida se � poss�vel jogar a pedra selecionada em alguma das extremidades da mesa (esquerda ou direita)
			// Caso n�o, ser� solicitado que o jogador atual selecione outra pedra
			while(!compara_pedras(mesa->ini->marcador, mesa->fim->marcador, mesa->ini->info, mesa->fim->info, pedra_atu, 3, NULL)){
				printa_tela(2, nome1, nome2, nome3, nome4, tamanho_pilha(cava), turno, maos, mesa);
				posicao(0, 40);				
				printf("-> A pedra escolhida n�o pode ser jogada, selecione outra: ");
				scanf("%d", &localizacao);
				
				// Enquanto a sele��o do usu�rio for menor que 0 ou maior do que a quantidade de pedras disponiveis para jogar, ser� solicitado novamente ao jogador atual que ele insira uma posi��o v�lida
				while(localizacao >= tamanho_listade(maos, turno) || localizacao < 0){
				printa_tela(2, nome1, nome2, nome3, nome4, tamanho_pilha(cava), turno, maos, mesa);
				posicao(0, 40);				
				printf("-> Posi��o inserida inv�lida, insira uma posi��o v�lida: ");
				scanf("%d", &localizacao);
				}
				pedra_atu = busca_listade_posicao(maos, localizacao-1, turno);		
			}			
			printa_tela(2, nome1, nome2, nome3, nome4, tamanho_pilha(cava), turno, maos, mesa);
			posicao(0, 40);
			
			// Ser� solicitado ao jogador atual que insira 0 ou 1 para jogar a pedra selecionada na esquerda ou direita
			printf("-> Selecione em qual extremidade deseja jogar a pedra (0 para esquerda, 1 para direita): ");			
			scanf("%d", &lado);
			
			// Enquanto esse n�mero for diferente de 0 e 1 ser� solicitado ao usu�rio que insira um n�mero v�lido
			while(lado != 0 && lado != 1){
				printa_tela(2, nome1, nome2, nome3, nome4, tamanho_pilha(cava), turno, maos, mesa);
				posicao(0, 40);
				printf("-> Insira um n�mero v�lido (0 para esquerda, 1 para direita): ");
				scanf("%d", &lado);
			}
			
			// Ap�s ser conferida, a pedra selecionada pelo usu�rio ser� removida de sua m�o e tentar� ser adicionada na extremidade escolhida pelo jogador
			remove_listade(maos, NULL, NULL, 0, turno, localizacao-1);
			
			// Por meio da fun��o compara_pedra, ser� conferida se a pedra selecionada pelo jogador pode realmente ser jogada na extremidade selecionada
			// Caso n�o, ser� solicitado ao usu�rio que insira o n�mero da outra extremidade 											
			while(!compara_pedras(mesa->ini->marcador, mesa->fim->marcador, mesa->ini->info, mesa->fim->info, pedra_atu, lado, &m)){
				printa_tela(2, nome1, nome2, nome3, nome4, tamanho_pilha(cava), turno, maos, mesa);				
				posicao(0, 40);
				printf("-> A pedra n�o pode ser jogada na extremidade selecionada, selecione a outra (0 para esquerda, 1 para direita): ");
				scanf("%d", &lado);
				
				// Enquanto esse n�mero for diferente de 0 e 1 ser� solicitado ao usu�rio novamente que insira um n�mero v�lido
				while(lado != 0 && lado != 1){
					printa_tela(2, nome1, nome2, nome3, nome4, tamanho_pilha(cava), turno, maos, mesa);
					posicao(0, 40);				
					printf("-> Insira um n�mero v�lido (0 para esquerda, 1 para direita): ");
					scanf("%d", &lado);
				}
			}
			
			// Caso o lado selecionado pelo usu�rio seja esquerda (0), a pedra selecionada � inserida no inicio da lista da mesa
			// Caso o lado selecionado seja a direita (1), a pedra selecionada � isnerida no fim da lista da mesa
			switch(lado){
				case 0:
					insere_listade_no_inicio(mesa, pedra_atu, m);
					break;
				case 1:
					insere_listade_no_fim(mesa, pedra_atu, m);
					break;
				default: printf("Erro, c�digo invalido\n");
			}
			
			// Ao final da jogada, ser� contada as pedras do jogador por meio da fun��o conta_pedras, caso seja igual a 0, significa que o jogador conseguir jogar todas as suas pedras e condicao_parada se torna 1 para encerrar a partida
			if(!conta_pedras(maos, turno)) condicao_parada = 1;
			
			// Caso o jogador ainda possua pedras na sua m�o, o turno ser� incrementado e ser� a vez do pr�ximo jogador
			else turno++;						
		}					
	}
	
	// Ao finalizar a partida ser� conferido se a vari�vel jogo_fechado � igual ao n�mero de jogadores, ou seja, o jogo foi encerrado devido a ter sido fechado 
	if(jogo_fechado == jogadores){	
		// Chama a fun��o vencedor, passando as m�os dos jogadores, quantidade de jogadores e seus nomes para definir quem ser� o vencedor	
		vencedor(maos, jogadores, nome1, nome2, nome3, nome4);			
	}
	// Caso jogo_fechado n�o seja igual ao n�mero de jogadores, significa que algum jogador conseguiu jogar todas as suas pedras
	else{
		// Dessa forma a tela 3 final ser� printada passando o turno atual para informar quem foi o vencedor 				
		printa_tela(3, nome1, nome2, nome3, nome4, NULL, turno, NULL, NULL);		
	}
	posicao(44, 19);
	// Na tela final ser� solicitado para os usu�rios que insiram 1 para jogar novamente ou 2 para sair e enquanto essa escolha for diferente desses n�meros nada ocorrer� at� que o usu�rio insira um n�mero v�lido	
	scanf("%d", &escolha);
	while(escolha != 1 && escolha != 2){
		printa_tela(3, nome1, nome2, nome3, nome4, NULL, turno, NULL, NULL);
		posicao(44, 19);		
		scanf("%d", &escolha);
	}
	// Caso a escolha seja um n�mero v�lido, retorna para a fun��o principal a escolha do usu�rio para definir se o jogo reiniciar� ou finalizar�
	return escolha;	
}

// Fun��o onde as pedras ser�o desimpilhadas e distribuidas 7 pedras para cada jogador
void distribui_maos(tp_listade *maos, tp_pilha *cava, int jogadores){
	int cont=0;
	tp_itemp e;
	tp_item m=1;
	
	// Enquanto a quantidade de jogadores for maior que 0 ser� desimpilhada uma pedra do cava e inserida na lista das m�os at� que contabilize um total de 7 pedras
	while(jogadores > 0){		
		pop(cava, &e);							
		insere_listade_ordenado(maos, e, m);				
		cont++;
		// Quando 7 pedras forem contabilizadas ser� alternado o jogador que ir� receber as pedras at� que jogadores = 0
		if(cont == 7){
			jogadores--;
			m++;
			cont=0;
		}		
	}				
}

// Fun��o onde todas as pedras do jogo ser�o criadas e armazenadas no vetor vet
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

// Fun��o onde todas as pedras criadas ser�o embaralhadas
void embaralha_pedras(pedra *vet){
	pedra aux;
	int i, random;
	srand(time(NULL));
	
	// � sorteado um n�mero de 0 a 27 e ent�o � realizada a troca do elemento do vetor nessa posi��o sorteada pela posi��o atual
	for(i=0;i<28;i++){		
		random = rand() % 28;
		aux = vet[i];
		vet[i] = vet[random];
		vet[random] = aux;						
	}	
}

// Fun��o onde todas as pedras restantes ser�o empilhadas no cava 
void empilha_cava(pedra *vet, tp_pilha *cava){	
	int i=27;	
	while(i >= 0){						
		push(cava, vet[i]);
		i--;					
	}
}

// Fun��o onde estar� o menu principal do jogo
int main(){
	setlocale(LC_ALL,"Portuguese");	
	int cont=0, jogadores, condicao = 1, i=1, x=0, y=0, escolha;
	char nome1[50], nome2[50], nome3[50], nome4[50], lixo[2];	
	tp_itemp e;
	tp_pilha *cava;
	tp_listade *maos, *mesa;
	
	// Chama a fun��o printa_tela passando como par�metro o 0 para imprimir a primeira tela inicial
	printa_tela(0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	scanf("%d", &escolha);
	
	// MENU principal, enquanto a escolha do usu�rio n�o for um, nada ocorrer�
	while(escolha != 1){
		printa_tela(0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		scanf("%d", &escolha);
	}
	while(condicao == 1){			
		cava = inicializa_pilha();
		maos = inicializa_listade();
		mesa = inicializa_listade();	
		pedra vet[28];		
		cria_pedras(vet);		
		empilha_cava(vet, cava);
		
		// Chama a fun��o printa_tela passando como par�metro o 1 para imprimir a segunda tela inicial		
		printa_tela(1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		posicao(3, 11);
		printf("-> Insira o n�mero de jogadores: ");		
		scanf("%d", &jogadores);
		
		// Enquanto a escolha do n�mero de jogadores for menor ou igual a 1 ou maior que 4, ser� solicitado ao usu�rio para inserir uma quantidade v�lida de 2 a 4 jogadores
		while(jogadores <= 1 || jogadores > 4){
			printa_tela(1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			posicao(3, 11);
			printf("-> N�mero de jogadores inv�lido, insira de 2 a 4 jogadores: ");
			scanf("%d", &jogadores);
		}
		distribui_maos(maos, cava, jogadores);
		gets(lixo);		
		printa_tela(1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		
		// Armazena o nome dos jogadores de acordo com a quantidade de jogadores escolhida					
		while(i <= jogadores){
			printa_tela(1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			posicao(3, 11);						
			printf("-> Insira o nome do jogador %d: ", i);
			if(i == 1) gets(nome1);
			else{
				if(i == 2) gets(nome2);
				else{
					if(i == 3) gets(nome3);
					else gets(nome4);
				}
			}
			i++;						
		}
		
		// A vari�vel condicao recebe o retorno da fun��o jogo e enquanto ela for igual a 1 o jogo n�o terminar�		
		condicao = jogo(maos, mesa, cava, jogadores, nome1, nome2, nome3, nome4);
		if(condicao == 1){
			maos = destroi_listade(maos, &e);
			mesa = destroi_listade(mesa, &e);
			destroi_pilha(cava);
			i = 1;			
		}	
	}
	system("cls");
	y=9;
	x=36;
	posicao(x,y);
	textcolor(12);
	printf("Finalizando....");
	textcolor(3);
	Sleep(1500);
	y=11;
	x=37;
	posicao(x,y);
	printf("Volte Sempre!\n\n");
	textcolor(15);
	return 0;
}
