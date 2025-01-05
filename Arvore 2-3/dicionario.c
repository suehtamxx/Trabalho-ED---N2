#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"
#include <stddef.h>
#include <sys/types.h>

//-----Alocar nó da Árvore e da Lista

unidade *criar_no_l_unid()
{
    unidade *no; //Cria nó
    no = (unidade*)malloc(sizeof(unidade)); //Aloca o nó

    no->unidade = 0; //Atribui 0 a unidade
    no->prox = NULL; // Atribui nulo ao próximo

    return no;
}
arv_ingles *cria_no_arv_BB()
{
    arv_ingles *no; //Cria o nó
    no = (arv_ingles *)malloc(sizeof(arv_ingles)); //Aloca o nó
    if(no != NULL)
    {
        no->info.l_unidade = NULL; //Atribui nulo a lista
        no->dir = NULL; //Atribui nulo a direita
        no->esq = NULL; //Atribui nulo a esquerda
    }

    return no; //Retorna o nó alocado
}
arv_ptbr *criar_no_arv_B3(info_ptbr info, arv_ptbr *filhoE, arv_ptbr *filhoC)
{
    arv_ptbr *no; //Cria o nó
    no = (arv_ptbr *)malloc(sizeof(arv_ptbr)); //Aloca o nó
    if(no != NULL){
        no->info1 = info; //Atribui a struct
        no->esq = filhoE; //Atribui o filho da esquerda
        no->cen = filhoC; //Atribui o filho da direita
        no->nInfos = 1; //Atribui 1 ao número de infos
    }

    return (no); //Retorna o nó alocado
}
//----------------------------------------------------------------------------------------------------

//----Auxiliares da inserir na Árvore B3

arv_ptbr *quebra_no(arv_ptbr **no, info_ptbr info, info_ptbr *promove, arv_ptbr *filho)
{
    arv_ptbr *maior; //Cria o nó maior
    maior = NULL;

    if(strcmp(info.ptbr, (*no)->info2.ptbr) > 0) //Se a nova info for maior que a info2 
    {
        *promove = (*no)->info2; //Promove a info2 (sempre promove a info do meio)
        maior = criar_no_arv_B3(info, (*no)->dir, filho); //Cria um nó só com a nova info (maior info)
    }

    else if(strcmp(info.ptbr, (*no)->info1.ptbr) > 0) //Se a nova info for maior que a info1
    {
        *promove = info; //Promove a nova info (sempre promove a info do meio)
        maior = criar_no_arv_B3((*no)->info2, filho, (*no)->dir); //Cria um nó só com a info2 (maior info)
    }

    else //Se a nova info for menor que info1
    {
        *promove = (*no)->info1; //Promove a info1 (sempre promove a info do meio)
        maior = criar_no_arv_B3((*no)->info2, (*no)->cen, (*no)->dir); //Cria um nó com a info2 (maior info)
        (*no)->info1 = info; //Atribui a novo info ao info1
        (*no)->cen = filho; //Atribui nulo ao centro 
    }

    (*no)->nInfos = 1; //Atualiza o número de infos

    return (maior); //Retorna o nó com a maior info
}
arv_ptbr *adiciona_chave(arv_ptbr *no, info_ptbr info, arv_ptbr *filho)
{
    //Se a nova info for maior que a do info1
    if(strcmp(info.ptbr, no->info1.ptbr) > 0)
    {
        no->info2 = info; //Atribui a nova info ao info2
        no->dir = filho; //Atribui o filho passado por parâmetro na direita (NULL)
    } 
    
    //Se a nova infor for menor, troca as posições do info
    else 
    {
        no->info2 = no->info1; //O info2 recebe o info1
        no->dir = no->cen;
        no->info1 = info; //O info1 recebe a nova info
        no->cen = filho;
    }
    
    no->nInfos = 2; //Atualiza o número de infos (o nó fica cheio)
    
    return (no); //Retorna o nó com as infos inseridas
}
//----------------------------------------------------------------------------------------------------

//----Auxiliares da inserir na Árvore BB

arv_ingles *so_um_filho_BB(arv_ingles *ingles)
{
    arv_ingles *aux; //Cria um nó aux
    
    if(ingles->esq != NULL && ingles->dir == NULL) //Se a esquerda for diferente de nulo e a direita for nulo
        aux = ingles->esq; //O nó aux recebe o filho da esquerda
    
    else if(ingles->esq == NULL && ingles->dir != NULL) //Se a esquerda for nula e a direita for diferente de nulo
        aux = ingles->dir; //O nó aux recebe o filho da direita

    return aux; //Retorna o filho
}
arv_ingles *menor_filho_BB(arv_ingles *ingles)
{
    while(ingles != NULL && ingles->esq != NULL)
        ingles = ingles->esq;

    return ingles;
}
//----------------------------------------------------------------------------------------------------

//----Verifica se é folha

int eh_folha_BB(arv_ingles *ingles)
{
    int verifica = 0; //Cria e inicializa o verifica com 0, ou seja, pressupõe que é nulo
    if(ingles->esq == NULL && ingles->dir == NULL) //Se a esquerda e a direita forem nula
        verifica = 1; //Atribui nulo a variável, ou seja, não é nulo
    
    return verifica; //Retorna a verificação
}
int eh_folha_B3(arv_ptbr *portugues)
{
    int verifica = 0; //Cria e inicializa o verifica com 0, ou seja, pressupõe que é nulo

    if(portugues->esq == NULL) //Se a esquerda for nula
        verifica = 1; //Atribui 1 a variável verifica, ou seja, é nulo

    return verifica; //Retorna a verificação
}
//----------------------------------------------------------------------------------------------------

//-----AINDA NÃO SEI

int nInfos_B3(arv_ptbr *portugues)
{
    int verifica = 0;
    if(portugues->nInfos == 2)
        verifica = 1;
    
    return verifica;
}
void troca_posicao(arv_ptbr *portugues)
{
    portugues->info1 = portugues->info2;
    portugues->nInfos = 1;
}
//----------------------------------------------------------------------------------------------------

//----Inserir no Arvore

int inserir_arv_BB(arv_ingles **ingles, arv_ingles *no)
{
    int inseriu = 1;

    if(*ingles == NULL)
        *ingles = no;

    else if (strcmp(no->info.ingles, (*ingles)->info.ingles) == 0)
    {
        unidade *nova_unidade = no->info.l_unidade;

        // Adiciona a nova unidade no início da lista
        nova_unidade->prox = (*ingles)->info.l_unidade;
        (*ingles)->info.l_unidade = nova_unidade;
    }

    else if(strcmp(no->info.ingles, (*ingles)->info.ingles) > 0)
        inseriu = inserir_arv_BB(&((*ingles)->dir), no);

    else if(strcmp(no->info.ingles, (*ingles)->info.ingles) < 0)
        inseriu = inserir_arv_BB(&((*ingles)->esq), no);

        else inseriu = 0;

    return inseriu;
}
arv_ptbr *inserir_arv_B3(arv_ptbr **portugues, info_ptbr info, info_ptbr *promove, arv_ptbr **pai)
{
    info_ptbr promove1; //Cria o promove
    arv_ptbr *maior; //Cria o nó maior
    maior = NULL; //Atribui nulo ao nó maior
    int encontrou = 0; //Verifica se a palavra em português existe

    if(*portugues == NULL) //SE a árvore estiver vazia
        *portugues = criar_no_arv_B3(info, NULL, NULL); //Chama a função criar_no_arv_B3
    
    else //SE NÃO:
    {
        if(strcmp(info.ptbr, (*portugues)->info1.ptbr) == 0) //Verifica se a nova info já existe na info1
        {   
            if(inserir_arv_BB(&((*portugues)->info1.ingles), info.ingles) == 0) printf("Nao foi possivel inserir na arvBB\n"); //Junta as árvores inglês
            encontrou = 1;
        }

        else if((*portugues)->nInfos == 2 && strcmp(info.ptbr, (*portugues)->info2.ptbr) == 0) //Se houver mais de 1 info, verifica se a nova info já existe na info2
        {
            if(inserir_arv_BB(&((*portugues)->info2.ingles), info.ingles) == 0) printf("Nao foi possivel inserir na arvBB\n");
            encontrou = 1;
        }
        
        if(!encontrou)
        {
            if(eh_folha_B3(*portugues) == 1) //Verifica se é folha
            {
                if((*portugues)->nInfos == 1) //Verifica se tem espaço
                    *portugues = adiciona_chave(*portugues, info, NULL); //Se é folha e tem espaço, chama a função adiciona_chave
                
                else
                {
                    maior = quebra_no(portugues, info, promove, NULL); //Se é folha e não tem espaço, chama a função quebra_no
                    
                    if(*pai == NULL) //Se o pai for nulo (quebrou o nó portugues)
                    {
                        *portugues = criar_no_arv_B3(*promove, *portugues, maior); //Chama a função criar_no_arv_B3
                        maior = NULL; //Atribui nulo ao maior
                    }
                }
            }

            else //Se não é folha:
            {
                if(strcmp(info.ptbr, (*portugues)->info1.ptbr) < 0) //Verifica se a nova info é menor q a info1
                    maior = inserir_arv_B3(&((*portugues)->esq), info, promove, portugues); //Vai para a sub-árvore esquerda
                
                else //Se não for menor que a info1
                {
                    if(((*portugues)->nInfos == 1) || (strcmp(info.ptbr, (*portugues)->info2.ptbr) < 0)) //Verifica se tem 1 info ou se a nova info é menor que info2
                        maior = inserir_arv_B3(&((*portugues)->cen), info, promove, portugues); //Vai para a sub-ávore do centro (recursão)
                    
                    else //Se não for menor que info2
                        maior = inserir_arv_B3(&((*portugues)->dir), info, promove, portugues); //Vai para a sub-árvore direita (recursão)
                        
                    if(maior != NULL) //Volta da recursão
                    {
                        if((*portugues)->nInfos == 1) //Se tiver espaço
                        {
                            *portugues = adiciona_chave(*portugues, *promove, maior); //Chama a função adiciona_chave
                            maior = NULL; //Atribui nulo ao maior
                        } 
                        else //Se não tiver espaço
                        {
                            maior = quebra_no(portugues, *promove, &promove1, maior); //Chama a função quebra_no
                            *promove = promove1; //Atribui o promove1 ao promove (por causa de recursão)
                            if(*pai == NULL) //Se o pai for nulo (quebrou o nó portugues)
                            {
                                *portugues = criar_no_arv_B3(promove1, *portugues, maior); //Cria um novo nó com a info do promove
                                maior = NULL; //Atribui nulo ao maior
                            }
                        }
                    }
                }
            }
        }
    }
    return (maior); //Retorna maior
}
//----------------------------------------------------------------------------------------------------

//-----Ler do arquivo

void ler_arquivo(arv_ptbr **portugues)
{
    FILE *dicionario;
    dicionario = fopen("dicionario.txt", "r"); //Abre o arquivo para leitura

        char *linha = NULL; // Ponteiro para a linha
        size_t tam = 0; // Tamanho da linha
        ssize_t num_c; // Número de caracteres lidos
        int unidade_atual = 0;
    if (dicionario != NULL)
    {
        printf("Arquivo aberto com sucesso.\n");
        //fseek(dicionario, 0, SEEK_SET);


        // Lê cada linha do arquivo
        while ((num_c = getline(&linha, &tam, dicionario)) != -1)
        {
            printf("\nLinha lida (%d caracteres): %s\n", num_c, linha);

            linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha

            if (linha[0] == '%') // Identifica uma unidade
            {
                unidade_atual = atoi(&linha[9]);
                printf("Unidade atual: %d\n", unidade_atual);
            }

            else if (strchr(linha, ':')) // Identifica uma linha com tradução
            {
                char palavra_ingles[100];
                char palavras_portugues[200];

                // Extrai as partes em inglês e português
                if (sscanf(linha, "%[^:]: %[^\n]", palavra_ingles, palavras_portugues) == 2) {
                    // Verifica e remove o ponto e vírgula ao final, se existir
                    size_t len = strlen(palavras_portugues);
                    if (len > 0 && palavras_portugues[len - 1] == ';') {
                        palavras_portugues[len - 1] = '\0'; // Remove o ponto e vírgula
                    }

                    printf("Lido: Ingles = %s, Portugues = %s\n", palavra_ingles, palavras_portugues);


                        // Processa cada tradução
                        char *palavra_port = strtok(palavras_portugues, ",");
                        while (palavra_port)
                        {
                            arv_ingles *novo_no;
                            novo_no = cria_no_arv_BB();
                            if (novo_no != NULL)
                            {
                                strcpy(novo_no->info.ingles, palavra_ingles);
                                novo_no->info.l_unidade = criar_no_l_unid();
                                novo_no->info.l_unidade->unidade = unidade_atual;

                                while (*palavra_port == ' ') palavra_port++; // Remove espaços no início

                                info_ptbr nova_info;
                                strcpy(nova_info.ptbr, palavra_port); // Português
                                nova_info.ingles = novo_no;

                                info_ptbr promove;
                                arv_ptbr *pai;
                                pai = NULL;

                                printf("Inserindo na arvore: %s -> %s\n", palavra_port, palavra_ingles);
                                inserir_arv_B3(portugues, nova_info, &promove, &pai);

                                palavra_port = strtok(NULL, ",");

                            } 
                            else printf("Erro de alocacao\n");
                        //liberar_arv_BB(novo_no);
                        }
                    } 
                    else printf("Erro ao processar linha: %s\n", linha);
                } 
            }
        }
    else printf("Nao foi possivel abrir o arquivo.\n");
    
    free(linha); // Libera a memória alocada por getline
    fclose(dicionario);
}
//----------------------------------------------------------------------------------------------------

int remover_arv_BB(arv_ingles **ingles, arv_ingles *no)
{
    int removeu = 1, verificacao;
    arv_ingles *aux;
    arv_ingles *end_filho, *end_menor_filho;

    if((*ingles) != NULL)
    {
        if(strcmp((*ingles)->info.ingles, no->info.ingles) == 0)
        {
            verificacao = eh_folha_BB(*ingles);
            
            if(verificacao == 1)
            {
                aux = *ingles;
                *ingles = NULL;
                free(aux);
            }
            else if ((end_filho = so_um_filho_BB(*ingles)) != NULL)
            {
                aux = *ingles;
                *ingles = end_filho;
                free(aux);
            }
                else
                {
                    end_menor_filho = menor_filho_BB((*ingles)->dir);
                    aux = *ingles;
                    (*ingles)->info = end_menor_filho->info;
                    removeu = remover_arv_BB(&(*ingles)->dir, no);
                } 
        }
        else if(strcmp(no->info.ingles, (*ingles)->info.ingles) < 0)
                    removeu = remover_arv_BB(&((*ingles)->esq), no);        
            else 
                removeu = remover_arv_BB(&((*ingles)->dir), no);
                
    }
    else removeu = 0;
    
    return removeu;
}

//Recebe um No Folha e o seu Pai e remove quando No é esquerda do Pai
int remove_esq_folha(arv_ptbr **portugues,arv_ptbr **pai)
{										
	int flag = 0;

	(**portugues).info1 = (**pai).info1;	
		
	if((**pai).cen->nInfos == 2)
    {
		(**pai).info1 = (**pai).cen->info1;
		(**pai).cen->info1 = (**pai).cen->info2;
		(**pai).cen->nInfos = 1;

	}
    
    else if((**pai).nInfos == 2)
    {
		(**pai).info1 = (**pai).cen->info1;
		(**pai).cen->info1 = (**pai).info2;
		
		if ((**pai).dir->nInfos == 2)
        {
			(**pai).info2 = (**pai).dir->info1;
			(**pai).dir->info1 = (**pai).dir->info2;
			(**pai).dir->nInfos = 1;
		}

        else
        {
			adicionaNo(&(**pai).cen, (**pai).dir->info1, NULL);
			libera_No(&(**pai).dir);
	       	(**pai).nInfos = 1;
		}
	}
	//caso em que o pai e seus filhos so tem uma info, entao ao remover o valor a arvore fica desbalanceada	
    else
    {
		adicionaNo(pai, (**pai).cen->info1, NULL);

		(**pai).nInfos = 2;

		libera_No(&(**pai).esq);
		libera_No(&(**pai).cen);
		flag = 1;
	}
	//retorna 0 se ao remover a arvore nao foi desbalanceada, retorna 1 se foi desbalanceada
	return flag; 
}

//Recebe um No Folha e o seu pai, remove quando o No é o centro do pai
int remove_centro_folha(arv_ptbr **portugues,arv_ptbr **pai){

	int flag = 0;
	
	if((**pai).esq->nInfos == 2)
    {
		(**portugues).info1 = (**pai).info1;
		(**pai).info1 = (**pai).esq->info2;
		(**pai).esq->nInfos = 1;
	}
    
    else if((**pai).nInfos == 2 )
    {
		(**portugues).info1 = (**pai).info2;
								
		if ((**pai).dir->nInfos == 2)
        {
			(**pai).info2 = (**pai).dir->info1;
			(**pai).dir->info1 = (**pai).dir->info2;
			(**pai).dir->nInfos = 1;
		}
        
        else
        {
			adicionaNo(&(**pai).cen, (**pai).dir->info1, NULL);
			libera_No(&(**pai).dir);
	       	(**pai).nInfos = 1;
		}
	}
	//caso em que o pai e seus filhos so tem uma info, entao a ao remover o valor a arvore fica desbalanceada
    else
    {
		adicionaNo(pai, (**pai).esq->info1, NULL);

		(**pai).nInfos = 2;

		libera_No(&(**pai).esq);
		libera_No(&(**pai).dir);
		flag = 1;
	}
	//retorna 0 se ao remover a arvore nao foi desbalanceada, retorna 1 se foi desbalanceada
	return flag; 
}

//Recebe um No folha e o seu pai, remove quando o No é a direita do Pai
void remove_dir_folha(arv_ptbr **portugues, arv_ptbr **pai)
{
	(**portugues).info1 = (**pai).info2;
	
	if((**pai).cen->nInfos == 2)
    {
		(**pai).info2 = (**pai).cen->info2;
		(**pai).cen->nInfos = 1;
	}
    
    else if((**pai).esq->nInfos == 2)
    {
		info_ptbr aux;
        aux = (**pai).cen->info1;
		
		(**pai).cen->info1 = (**pai).info1;
		(**pai).info1 = (**pai).esq->info2;
		(**pai).info2= aux;
		(**pai).esq->nInfos = 1;
	}
    
    else
    {
		adicionaNo(&(**pai).cen,(**pai).info2,NULL);
		(**pai).nInfos = 1;
		libera_No(&(**pai).dir);
	}
}

//Remove o No quando é folha, recebe o No que vai ter seu valor removido e o No Pai, depois remove o No
int remove_folha(arv_ptbr **Pai,arv_ptbr **portugues, char palavra)
{
	int balanceamento = 0;

	if ((*portugues)->nInfos == 2)
    {
					
		if ((strcmp((*portugues)->info1.ptbr, palavra) == 0))
			(*portugues)->info1 = (*portugues)->info2;

		(*portugues)->nInfos = 1;
				
	}
    
    else if (*Pai == NULL)
		libera_No(portugues);	
				
	else
    {
		if (*portugues == (**Pai).esq)
			balanceamento = remove_esq_folha(portugues,Pai);

		else if (*portugues == (**Pai).cen)
			balanceamento = remove_centro_folha(portugues,Pai);

		else if (*portugues == (**Pai).dir)
			remove_dir_folha(portugues,Pai);
	}

	return balanceamento;
}

//Recebe o No e a Info, remove o valor do No quando os filhos do No são folhas
int remove_NoFilhos_folhas(arv_ptbr **portugues, char info)
{
	int balanceamento = 0;

	if((strcmp((*portugues)->info1.ptbr, info) == 0)) //remove quando a info é a info1 do No
    { 		
		if((**portugues).cen->nInfos == 2)
        {
			(**portugues).info1 = (**portugues).cen->info1;
			(**portugues).cen->info1 = (**portugues).cen->info2;
		   	(**portugues).cen->nInfos = 1;

		}
        
        else if((strcmp((*portugues)->info1.ptbr, info) == 0))
        {
			(**portugues).info1 = (**portugues).esq->info2;
   			(**portugues).esq->nInfos = 1;
		}
        
        else if((**portugues).nInfos ==2)
        {
			(**portugues).info1 = (**portugues).cen->info1;
			(**portugues).cen->info1 = (**portugues).info2;
				
			if((**portugues).dir->nInfos == 2 )
            {
				(**portugues).info2 = (**portugues).dir->info1;
				(**portugues).dir->info1 =(**portugues).dir->info2;
				(**portugues).dir->nInfos = 1;
			}
            
            else
            {
				adicionaNo(&(**portugues).cen, (**portugues).dir->info1, NULL);
				(**portugues).nInfos = 1;
				libera_No(&(**portugues).dir);
			}
		}
		//caso em que o pai e seus filhos so tem uma info, entao ao remover o valor a arvore fica desbalanceada
        else
        { 	 
		  	arv_ptbr *aux;

			adicionaNo(&(**portugues).esq, (**portugues).cen->info1, NULL);
			aux = (**portugues).esq;
			libera_No(&(**portugues).cen);
			libera_No(portugues);
			*portugues = aux;
			balanceamento = 1;
		}
	}
	//remove quando a info é a info2 do No
    else
    {

		if((**portugues).dir->nInfos == 2)
        {
			(**portugues).info2 = (**portugues).dir->info1;
			(**portugues).dir->info1=  (**portugues).dir->info2;
			(**portugues).dir->nInfos = 1;
		}

		else if((**portugues).cen->nInfos == 2)
        {

			(**portugues).info2 = (**portugues).cen->info2;
		   	(**portugues).cen->nInfos = 1;
		}
		
        else if((**portugues).esq->nInfos == 2)
        {
			(**portugues).info2 = (**portugues).cen->info1;
		   	(**portugues).cen->info1 = (**portugues).info1;
		   	(**portugues).info1 = (**portugues).esq->info2;
		   	(**portugues).esq->nInfos = 1;
		}

		else
        {
			adicionaNo(&(**portugues).cen, (**portugues).dir->info1, NULL);
			(**portugues).nInfos = 1;
			libera_No(&(**portugues).dir);
		}
	}
	//retorna 0 se ao remover a arvore nao foi desbalanceada, retorna 1 se foi desbalanceada
	return balanceamento; 					 
}

//Recebe um No e um valor para balanceiaArvore, ver em que lado da portugues esta desbalanceado entao balanceia o No
int balanceiaArvore(arv_ptbr **portugues, int desbalanceamento)
{ 
	info_ptbr promove;
	arv_ptbr *no_maior;
	arv_ptbr *aux;

	if (desbalanceamento == -1) //quando o desbalanceamento está para a esquerda da raiz
    { 
		aux = (*portugues)->cen->esq;
		(*portugues)->cen->esq = (*portugues)->esq;
		
		if((*portugues)->cen->nInfos == 1)
        {
			adicionaNo(&(*portugues)->cen,(*portugues)->info1, aux);
			(*portugues)->esq = NULL;
			
			if((*portugues)->nInfos == 1)
            {
				aux = *portugues;
				*portugues = (*portugues)->cen;
				libera_No(&aux);
			}
            
            else
            {
				(*portugues)->info1 = (*portugues)->info2;
				(*portugues)->esq = (*portugues)->cen;
				(*portugues)->cen = (*portugues)->dir;
				(*portugues)->dir = NULL;
				(*portugues)->nInfos = 1;
			}
		}
        
        else
        {
			quebraNo(&(*portugues)->cen,(*portugues)->info1, &promove, &no_maior, aux);
			(*portugues)->info1 = promove;
			(*portugues)->esq = (*portugues)->cen;
			(*portugues)->cen = no_maior;
		}
	}
    
    else if (desbalanceamento == 0) //quando o desbalanceamento está para o centro da portugues
    {
		if((*portugues)->esq->nInfos == 1)
        {
			adicionaNo(&(*portugues)->esq, (*portugues)->info1, (*portugues)->cen);
			(*portugues)->cen = NULL;
			
			if((*portugues)->nInfos == 1)
            {				
				aux = *portugues;
				*portugues = (*portugues)->esq;
				libera_No(&aux);
			}
            
            else
            {

				(*portugues)->info1 = (*portugues)->info2;
				(*portugues)->cen = (*portugues)->dir;
				(*portugues)->dir = NULL;
				(*portugues)->nInfos = 1;
			}
		}
        
        else
        {
			quebraNo(&(*portugues)->esq, (*portugues)->info1, &promove, &no_maior, (*portugues)->cen);
			(*portugues)->info1 = promove;
			(*portugues)->cen = no_maior;
		}
		
	}
    
    else //quando o desbalanceamento está para direita da portugues
    {
		if((*portugues)->cen->nInfos == 1)
        {
			adicionaNo(&(*portugues)->cen, (*portugues)->info2, (*portugues)->dir);
			(*portugues)->nInfos = 1;
			(*portugues)->dir = NULL;
		}
        
        else
        {
			quebraNo(&(*portugues)->cen, (*portugues)->info2, &promove, &no_maior, (*portugues)->dir);
			(*portugues)->info2 = promove;
			(*portugues)->dir = no_maior;
		}
	}

	return 0;
}

//FUNÇÃO QUE RECEBE UM NO E PERCORRE A PARTIR DELE BUSCANDO A MENOR INFORMAÇÃO PARA REMOVER E RETORNAR NA VARIAVEL promove
int remove_MenorNo(arv_ptbr **pai_aux, arv_ptbr **No, info_ptbr *promove){
	int balanceamento = 0;

	if ((*No)->esq != NULL)
        balanceamento = remove_MenorNo(No, &(*No)->esq, promove);
	
    else
    {
		*promove = (*No)->info1;
		balanceamento = remove_folha(pai_aux,No,(*No)->info1.ptbr);
	}

	return balanceamento;
}

/*  remover recebe a portugues o pai que incia com NULL a info que desejamos remover e flag
    a remoção pode ser feita atravez de 3 casos
   
    1- se o No é folha
   
    2- se os filhos do No são folhas

    3- se os filhos do No não são folhas, nesse caso é buscado o menor info da direita
    da info que queremos remover e fazemos com que a info que queremos remover receba 
    a menor info da sua direita;

    apos a remoção da info a arvore pode ter ficado desbalanceado, entao se o valor
    da variavel balanceamento for 1, quer dizer que teremos que balancear o No,
	então é chamada a funçao balanceiaArvore para isso
*/

int remover(arv_ptbr **pai, arv_ptbr **portugues , char info, int *flag){ 

	int balanceamento = 0;

	if(*portugues != NULL)
    {
		if ((strcmp((*portugues)->info1.ptbr, info) == 0) || ((*portugues)->nInfos == 2 && (strcmp((*portugues)->info2.ptbr, info) == 0)))
        {
			*flag = 1;

			if (eh_folha_B3(*portugues) == 1)
				balanceamento = remove_folha(pai, portugues, info);
			
			else if((eh_folha_B3((*portugues)->esq) == 1 && eh_folha_B3((*portugues)->cen) == 1 && ehfolha((*portugues)->dir) == 1) || (ehfolha((*portugues)->esq) == 1 && ehfolha((*portugues)->cen) == 1 && (*portugues)->nInfos == 1))
                balanceamento = remove_NoFilhos_folhas(portugues, info);
			
			else
            {
				arv_ptbr *pai_aux; 
                pai_aux = NULL;
				info_ptbr promove;
				
				if ((strcmp((*portugues)->info1.ptbr, info) == 0))
                {
					balanceamento = remove_MenorNo(&pai_aux, &(*portugues)->cen, &promove);
					(*portugues)->info1 = promove;

					if (balanceamento == 1) //arvore foi desbalanceada para o centro
					    balanceamento = balanceiaArvore(portugues,0);
				}
                
                else
                {
					balanceamento = remove_MenorNo(&pai_aux, &(*portugues)->dir, &promove);
					(*portugues)->info2 = promove;

					if (balanceamento == 1)//arvore foi desbalanceada para a direita
						balanceamento = balanceiaArvore(portugues,1);
				}
			}		
		}
        
        else if((strcmp((*portugues)->info1.ptbr, info) < 0))
	        balanceamento = remover(portugues, &(*portugues)->esq, info, flag);
	        
		else if((*portugues)->nInfos == 2 && (strcmp((*portugues)->info1.ptbr, info) > 0))
	        balanceamento = remover(portugues, &(*portugues)->dir, info, flag);
	    
	    else
	        balanceamento = remover(portugues, &(*portugues)->cen, info, flag);

	    if (balanceamento == 1 && *portugues != NULL && *pai != NULL)
        {
	    	if (*portugues == (**pai).esq)
				balanceamento = balanceiaArvore(pai,-1);

	    	else if (*portugues == (**pai).cen)
				balanceamento = balanceiaArvore(pai,0);

			else if (*portugues == (**pai).dir)
				balanceamento = balanceiaArvore(pai,1);
	    }
	}

	return balanceamento;
}
//----------------------------------------------------------------------------------------------------


//----Liberar memória

void liberar_lista_unidades(unidade *l_unidade) {
    unidade *atual = l_unidade;
    while (atual != NULL) {
        unidade *prox = atual->prox;
        free(atual);
        atual = prox;
    }
}

// Função para liberar a árvore de inglês
void liberar_arv_BB(arv_ingles *no) {
    if (no != NULL) {
        // Libera as subárvores recursivamente
            liberar_arv_BB(no->esq);
            liberar_arv_BB(no->dir);

        // Libera a lista de unidades associada ao nó
        liberar_lista_unidades(no->info.l_unidade);

        // Libera o nó atual
        free(no);
    }
}
void liberar_arv_B3(arv_ptbr *no) {
    if (no != NULL) {
        // Libera as subárvores recursivamente
            liberar_arv_B3(no->esq);
            liberar_arv_B3(no->cen);
            if(no->nInfos == 2)
                liberar_arv_B3(no->dir);
            
        free(no);
    }
}