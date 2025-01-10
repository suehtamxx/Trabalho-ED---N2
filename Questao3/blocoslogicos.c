#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blocoslogicos.h"
#include <stddef.h>
#include <sys/types.h>

arv_blocos *criar_no(info_blocos *info, arv_blocos *filhoE, arv_blocos *filhoC)
{
    arv_blocos *no;
    no = (arv_blocos *)malloc(sizeof(arv_blocos));
    if(no != NULL)
    {
        no->info1 = *info;
        no->esq = filhoE;
        no->cen = filhoC;
        no->nInfos = 1;
    
    }
    return no;
}

arv_blocos *quebra_no(arv_blocos **no, info_blocos info, info_blocos *promove, arv_blocos *filho)
{
    arv_blocos *maior; //Cria o nó maior
    maior = NULL;

    if(info.blocoi > (*no)->info2.blocoi) //Se a nova info for maior que a info2 
    {
        *promove = (*no)->info2; //Promove a info2 (sempre sobe a info do meio)
        maior = criar_no(&info, (*no)->dir, filho); //Cria um nó só com a nova info (maior info)
    }

    else if(info.blocoi > (*no)->info1.blocof) //Se a nova info for maior que a info1
    {
        *promove = info; //Promove a nova info (sempre sobe a info do meio)
        maior = criar_no(&((*no)->info2), filho, (*no)->dir); //Cria um nó só com a info2 (maior info)
    }

    else //Se a nova info for menor que info1
    {
        *promove = (*no)->info1; //Promove a info1 (sempre sobe a info do meio)
        maior = criar_no(&((*no)->info2), (*no)->cen, (*no)->dir); //Cria um nó com a info2 (maior info)
        (*no)->info1 = info; //Atribui a novo info ao info1
        (*no)->cen = filho; //Atribui nulo ao centro 
    }

    (*no)->nInfos = 1; //Atualiza o número de infos

    return (maior); //Retorna o nó com a maior info
}
arv_blocos *adiciona_chave(arv_blocos *no, info_blocos info, arv_blocos *filho)
{
    if(info.blocoi > no->info1.blocoi) //Se a nova info for maior que a do info1
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
int eh_folha_B3(arv_blocos *blocos)
{
    int verifica = 0; //Cria e inicializa o verifica com 0, ou seja, pressupõe que é nulo

    if(blocos->esq == NULL) //Se a esquerda for nula
        verifica = 1; //Atribui 1 a variável verifica, ou seja, é nulo

    return verifica; //Retorna a verificação
}

arv_blocos *inserir_arv_B3(arv_blocos **blocos, info_blocos info, info_blocos *promove, arv_blocos **pai)
{
    info_blocos promove1; //Cria o promove
    arv_blocos *maior; //Cria o nó maior
    maior = NULL; //Atribui nulo ao nó maior

    if(*blocos == NULL) //SE a árvore estiver vazia
        *blocos = criar_no(&info, NULL, NULL); //Chama a função criar_no
    
    else //SE NÃO:
    {
        if(eh_folha_B3(*blocos) == 1) //Verifica se é folha
        {
            if((*blocos)->nInfos == 1) //Verifica se tem espaço
                *blocos = adiciona_chave(*blocos, info, NULL); //Se é folha e tem espaço, chama a função adiciona_chave
            
            else
            {
                maior = quebra_no(blocos, info, promove, NULL); //Se é folha e não tem espaço, chama a função quebra_no
                
                if(*pai == NULL) //Se o pai for nulo (quebrou o nó raiz)
                {
                    *blocos = criar_no(promove, *blocos, maior); //Chama a função criar_no
                    maior = NULL; //Atribui nulo ao maior
                }
            }
        }

        else //Se não é folha:
        {
            if(info.blocoi < (*blocos)->info1.blocoi) //Verifica se a nova info é menor q a info1
                maior = inserir_arv_B3(&((*blocos)->esq), info, promove, blocos); //Vai para a sub-árvore esquerda
            
            else //Se não for menor que a info1
            {
                if((*blocos)->nInfos == 1 || info.blocoi < (*blocos)->info2.blocoi) //Verifica se tem 1 info ou se a nova info é menor que info2
                    maior = inserir_arv_B3(&((*blocos)->cen), info, promove, blocos); //Vai para a sub-ávore do centro (recursão)
                
                else if(info.blocoi > (*blocos)->info2.blocoi) //Se não for menor que info2
                    maior = inserir_arv_B3(&((*blocos)->dir), info, promove, blocos); //Vai para a sub-árvore direita (recursão)
                    
                if(maior != NULL) //Volta da recursão
                {
                    if((*blocos)->nInfos == 1) //Se tiver espaço
                    {
                        *blocos = adiciona_chave(*blocos, *promove, maior); //Chama a função adiciona_chave
                        maior = NULL; //Atribui nulo ao maior
                    } 
                    else //Se não tiver espaço
                    {
                        maior = quebra_no(blocos, *promove, &promove1, maior); //Chama a função quebra_no
                        *promove = promove1; //Atribui o promove1 ao promove (por causa de recursão)
                        if(*pai == NULL) //Se o pai for nulo (quebrou o nó raiz)
                        {
                            *blocos = criar_no(&promove1, *blocos, maior); //Cria um novo nó com a info do promove
                            maior = NULL; //Atribui nulo ao maior
                        }
                    }
                }
            }
        }
    }
    return (maior); //Retorna maior
}

void cadastrar(arv_blocos **no, int qtd)
{
    info_blocos info;
    info_blocos promove;
    arv_blocos *pai;

    info.blocoi = info.blocof = 0;
    do
    {
        printf("O primeiro bloco é livre(1) ou ocupado(0):\n");
        scanf(" %d", &info.status);

    }while(info.status != 0 && info.status != 1);
    
    do{
        printf("Qual o valor do bloco inicial:\n");
        scanf(" %d", &info.blocoi);

    }while(info.blocoi < 0);
    
    do{

        printf("Qual o valor final do bloco:\n");
        scanf(" %d", &info.blocof);

    }while(info.blocof < info.blocoi);

    info.eblocoi = &info.blocoi;
    info.eblocof = &info.blocof;


    inserir_arv_B3(no, info, &promove, &pai);

    while(info.blocof < qtd - 1)
    {
        pai = NULL;
        int aux = 0;
        aux = info.blocof + 1;
        info.blocoi = aux;

        printf("Valor disponivel de %d ate %d\n", info.blocof + 1, qtd);
        do
        {
            printf("Qual o valor final do bloco:\n");
            scanf(" %d", &info.blocof);
            
            if(info.blocof <= (aux))printf("Valor inválido\n");

        }while(info.blocof <= (aux));

        if(info.status == 1)
            info.status = 0;
        else info.status = 1;

        inserir_arv_B3(no, info, &promove, &pai);
    }  
}   

void concatena(arv_blocos **raiz, arv_blocos **no)
{
    int flag = 0, aux;

    if(*raiz != NULL && *no != NULL)
    {
       if ((*raiz)->nInfos == 1)
       {						
            if ((*no)->esq == *raiz)
            {
                (*no)->info1.blocoi = (*raiz)->info1.blocoi;
                remover_arv_B3(no, raiz, (*raiz)->info1.blocoi, &flag); 										 
            }
            //caso em que a raiz esta entre um no ocupado e um livre, concatena raiz com a info2 do pai e remove a raiz
            else if ((*no)->dir == *raiz)
            {

                (*no)->info2.blocof = (*raiz)->info1.blocof;
                remover_arv_B3(no, raiz, (*raiz)->info1.blocoi, &flag); 
            }
            //caso em que a raiz esta entre duas infos ocupadas, concatena raiz com a info1 e a info2 do pai e remove a raiz  e a info2 do pai
            else
            {                            
                if ((*no)->nInfos == 2)
                {    
                    (*no)->info1.blocof = (*no)->info2.blocof;                    
                    aux = (*no)->info2.blocoi;

                    remover_arv_B3(no, raiz, (*raiz)->info1.blocoi, &flag);	
                    remover_arv_B3(no, raiz, aux, &flag);	
                }
            }	
        }
        //quando a raiz possui 2 infos, entao a info que queremos ocupar esta entre duas infos ocupadas, concatenamos com a info do pai e removemos a raiz
        else
        {   
            if((*no)->cen == *raiz) (*no)->info1.blocof = (*raiz)->info2.blocof;            
            else (*no)->info2.blocof = (*raiz)->info2.blocof;

            remover_arv_B3(no, raiz, (*raiz)->info2.blocoi, &flag);
            remover_arv_B3(no, raiz, (*raiz)->info1.blocoi, &flag);
        }         
    }
}
arv_blocos *busca_MenorNo(arv_blocos **no){

	arv_blocos *aux;													  

	if ((*no)->esq != NULL)
		aux = busca_MenorNo(&(*no)->esq);
	else
		aux = *no;

	return aux;
}

//Recebe um no e percorre a partir desse no e retorna o no com a Maior info
arv_blocos *busca_MaiorNo(arv_blocos **no){

	arv_blocos *aux;													  

	if ((*no)->cen != NULL)
		aux = busca_MenorNo(&(*no)->cen);
	else
		aux = *no;

	return aux;
}

void libera_no(arv_blocos **no)
{
	arv_blocos *aux;

	aux = *no;
	*no = NULL;
	free(aux);
}
int remove_esq_folha(arv_blocos **portugues, arv_blocos **pai)
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
			(**pai).cen = adiciona_chave((**pai).cen, (**pai).dir->info1, NULL);
			libera_no(&(**pai).dir);
	       	(**pai).nInfos = 1;
		}
	}
	//caso em que o pai e seus filhos so tem uma info, entao ao remover_arv_B3 o valor a arvore fica desbalanceada	
    else
    {
		*pai = adiciona_chave(*pai, (**pai).cen->info1, NULL);

		(**pai).nInfos = 2;

		libera_no(&(**pai).esq);
		libera_no(&(**pai).cen);
		flag = 1;
	}
	//retorna 0 se ao remover_arv_B3 a arvore nao foi desbalanceada, retorna 1 se foi desbalanceada
	return flag; 
}
int remove_centro_folha(arv_blocos **blocos, arv_blocos **pai)
{

	int flag = 0;
	
	if((**pai).esq->nInfos == 2)
    {
		(**blocos).info1 = (**pai).info1;
		(**pai).info1 = (**pai).esq->info2;
		(**pai).esq->nInfos = 1;
	}
    
    else if((**pai).nInfos == 2 )
    {
		(**blocos).info1 = (**pai).info2;
								
		if ((**pai).dir->nInfos == 2)
        {
			(**pai).info2 = (**pai).dir->info1;
			(**pai).dir->info1 = (**pai).dir->info2;
			(**pai).dir->nInfos = 1;
		}
        
        else
        {
			(*pai)->cen = adiciona_chave((*pai)->cen, (**pai).dir->info1, NULL);
			libera_no(&(**pai).dir);
	       	(**pai).nInfos = 1;
		}
	}
	//caso em que o pai e seus filhos so tem uma info, entao a ao remover_arv_B3 o valor a arvore fica desbalanceada
    else
    {
		*pai = adiciona_chave(*pai, (**pai).esq->info1, NULL);

		(**pai).nInfos = 2;

		libera_no(&(**pai).esq);
		libera_no(&(**pai).dir);
		flag = 1;
	}
	//retorna 0 se ao remover_arv_B3 a arvore nao foi desbalanceada, retorna 1 se foi desbalanceada
	return flag; 
}
void remove_dir_folha(arv_blocos **blocos, arv_blocos **pai)
{
	(**blocos).info1 = (**pai).info2;
	
	if((**pai).cen->nInfos == 2)
    {
		(**pai).info2 = (**pai).cen->info2;
		(**pai).cen->nInfos = 1;
	}
    
    else if((**pai).esq->nInfos == 2)
    {
		info_blocos aux;
        aux = (**pai).cen->info1;
		
		(**pai).cen->info1 = (**pai).info1;
		(**pai).info1 = (**pai).esq->info2;
		(**pai).info2= aux;
		(**pai).esq->nInfos = 1;
	}
    
    else
    {
		(*pai)->cen = adiciona_chave((*pai)->cen, (**pai).info2, NULL);
		(**pai).nInfos = 1;
		libera_no(&(**pai).dir);
	}
}
int remove_folha(arv_blocos **no, arv_blocos **blocos, int inicial)
{
	int balanceamento = 0;

	if ((*blocos)->nInfos == 2)
    {
					
		if ((*blocos)->info1.blocoi == inicial)
			(*blocos)->info1 = (*blocos)->info2;

		(*blocos)->nInfos = 1;
				
	}
    
    else if (*no == NULL)
		libera_no(blocos);	
				
	else
    {
		if (*blocos == (**no).esq)
			balanceamento = remove_esq_folha(blocos,no);

		else if (*blocos == (**no).cen)
			balanceamento = remove_centro_folha(blocos,no);

		else if (*blocos == (**no).dir)
			remove_dir_folha(blocos,no);
	}

	return balanceamento;
}
int remove_no_filho_folhas(arv_blocos **blocos, int inicial)
{
	int balanceamento = 0;

	if((*blocos)->info1.blocoi == inicial) //remove quando a info é a info1 do no
    { 	
		if((**blocos).cen->nInfos == 2)
        {
			(**blocos).info1 = (**blocos).cen->info1;
			(**blocos).cen->info1 = (**blocos).cen->info2;
		   	(**blocos).cen->nInfos = 1;

		}
        
        else if((*blocos)->info1.blocoi == inicial)
        {
			(**blocos).info1 = (**blocos).esq->info2;
   			(**blocos).esq->nInfos = 1;
		}
        
        else if((**blocos).nInfos ==2)
        {
			(**blocos).info1 = (**blocos).cen->info1;
			(**blocos).cen->info1 = (**blocos).info2;
				
			if((**blocos).dir->nInfos == 2 )
            {
				(**blocos).info2 = (**blocos).dir->info1;
				(**blocos).dir->info1 =(**blocos).dir->info2;
				(**blocos).dir->nInfos = 1;
			}
            
            else
            {
				(*blocos)->cen = adiciona_chave((*blocos)->cen, (**blocos).dir->info1, NULL);
				(**blocos).nInfos = 1;
				libera_no(&(**blocos).dir);
			}
		}
		//caso em que o pai e seus filhos so tem uma info, entao ao remover_arv_B3 o valor a arvore fica desbalanceada
        else
        { 	 
		  	arv_blocos *aux;

			(*blocos)->esq = adiciona_chave((*blocos)->esq, (**blocos).cen->info1, NULL);
			aux = (**blocos).esq;
			libera_no(&(**blocos).cen);
			libera_no(blocos);
			*blocos = aux;
			balanceamento = 1;
		}
	}
	//remove quando a info é a info2 do no
    else
    {

		if((**blocos).dir->nInfos == 2)
        {
			(**blocos).info2 = (**blocos).dir->info1;
			(**blocos).dir->info1=  (**blocos).dir->info2;
			(**blocos).dir->nInfos = 1;
		}

		else if((**blocos).cen->nInfos == 2)
        {

			(**blocos).info2 = (**blocos).cen->info2;
		   	(**blocos).cen->nInfos = 1;
		}
		
        else if((**blocos).esq->nInfos == 2)
        {
			(**blocos).info2 = (**blocos).cen->info1;
		   	(**blocos).cen->info1 = (**blocos).info1;
		   	(**blocos).info1 = (**blocos).esq->info2;
		   	(**blocos).esq->nInfos = 1;
		}

		else
        {
			(*blocos)->cen = adiciona_chave((*blocos)->cen, (**blocos).dir->info1, NULL);
			(**blocos).nInfos = 1;
			libera_no(&(**blocos).dir);
		}
	}
	//retorna 0 se ao remover_arv_B3 a arvore nao foi desbalanceada, retorna 1 se foi desbalanceada
	return balanceamento; 					 
}
int balanceia_arv_B3(arv_blocos **blocos, int desbalanceamento)
{ 
	info_blocos promove;
	arv_blocos *no_maior;
	arv_blocos *aux;

	if (desbalanceamento == -1) //quando o desbalanceamento está para a esquerda da raiz
    { 
		aux = (*blocos)->cen->esq;
		(*blocos)->cen->esq = (*blocos)->esq;
		
		if((*blocos)->cen->nInfos == 1)
        {
			(*blocos)->cen = adiciona_chave((*blocos)->cen, (*blocos)->info1, aux);
			(*blocos)->esq = NULL;
			
			if((*blocos)->nInfos == 1)
            {
				aux = *blocos;
				*blocos = (*blocos)->cen;
				libera_no(&aux);
			}
            
            else
            {
				(*blocos)->info1 = (*blocos)->info2;
				(*blocos)->esq = (*blocos)->cen;
				(*blocos)->cen = (*blocos)->dir;
				(*blocos)->dir = NULL;
				(*blocos)->nInfos = 1;
			}
		}
        
        else
        {
			no_maior = quebra_no(&(*blocos)->cen,(*blocos)->info1, &promove, aux);
			(*blocos)->info1 = promove;
			(*blocos)->esq = (*blocos)->cen;
			(*blocos)->cen = no_maior;
		}
	}
    
    else if (desbalanceamento == 0) //quando o desbalanceamento está para o centro da blocos
    {
		if((*blocos)->esq->nInfos == 1)
        {
			(*blocos)->esq = adiciona_chave((*blocos)->esq, (*blocos)->info1, (*blocos)->cen);
			(*blocos)->cen = NULL;
			
			if((*blocos)->nInfos == 1)
            {				
				aux = *blocos;
				*blocos = (*blocos)->esq;
				libera_no(&aux);
			}
            
            else
            {
				(*blocos)->info1 = (*blocos)->info2;
				(*blocos)->cen = (*blocos)->dir;
				(*blocos)->dir = NULL;
				(*blocos)->nInfos = 1;
			}
		}
        
        else
        {
			no_maior = quebra_no(&(*blocos)->esq, (*blocos)->info1, &promove, (*blocos)->cen);
			(*blocos)->info1 = promove;
			(*blocos)->cen = no_maior;
		}
		
	}
    
    else //quando o desbalanceamento está para direita da blocos
    {
		if((*blocos)->cen->nInfos == 1)
        {
			(*blocos)->cen = adiciona_chave((*blocos)->cen, (*blocos)->info2, (*blocos)->dir);
			(*blocos)->nInfos = 1;
			(*blocos)->dir = NULL;
		}
        
        else
        {
			no_maior = quebra_no(&(*blocos)->cen, (*blocos)->info2, &promove, (*blocos)->dir);
			(*blocos)->info2 = promove;
			(*blocos)->dir = no_maior;
		}
	}

	return 0;
}
int remove_menor_no(arv_blocos **pai_aux, arv_blocos **no, info_blocos *promove)
{
	int balanceamento = 0;

	if ((*no)->esq != NULL)
        balanceamento = remove_menor_no(no, &(*no)->esq, promove);
	
    else
    {
		*promove = (*no)->info1;
		balanceamento = remove_folha(pai_aux,no,(*no)->info1.blocoi);
	}

	return balanceamento;
}
int remover_arv_B3(arv_blocos **pai, arv_blocos **blocos, int inicial, int *flag)
{ 

	int balanceamento = 0;

	if(*blocos != NULL)
    {
		if ((*blocos)->info1.blocoi == inicial || ((*blocos)->nInfos == 2 && (*blocos)->info2.blocoi == inicial))
        {
			*flag = 1;

			if (eh_folha_B3(*blocos) == 1)
				balanceamento = remove_folha(pai, blocos, inicial);
			
			else if((eh_folha_B3((*blocos)->esq) == 1 && eh_folha_B3((*blocos)->cen) == 1 && eh_folha_B3((*blocos)->dir) == 1) || (eh_folha_B3((*blocos)->esq) == 1 && eh_folha_B3((*blocos)->cen) == 1 && (*blocos)->nInfos == 1))
                balanceamento = remove_no_filho_folhas(blocos, inicial);
			
			else
            {
				arv_blocos *pai_aux; 
                pai_aux = NULL;
				info_blocos promove;
				
				if ((*blocos)->info1.blocoi == inicial)
                {
					balanceamento = remove_menor_no(&pai_aux, &(*blocos)->cen, &promove);
					(*blocos)->info1 = promove;

					if (balanceamento == 1) //arvore foi desbalanceada para o centro
					    balanceamento = balanceia_arv_B3(blocos,0);
				}
                
                else
                {
					balanceamento = remove_menor_no(&pai_aux, &(*blocos)->dir, &promove);
					(*blocos)->info2 = promove;

					if (balanceamento == 1)//arvore foi desbalanceada para a direita
						balanceamento = balanceia_arv_B3(blocos,1);
				}
			}		
		}
        
        else if((*blocos)->info1.blocoi == inicial)
	        balanceamento = remover_arv_B3(blocos, &(*blocos)->esq, inicial, flag);
	        
		else if((*blocos)->nInfos == 2 && (*blocos)->info1.blocoi == inicial)
	        balanceamento = remover_arv_B3(blocos, &(*blocos)->dir, inicial, flag);
	    
	    else
	        balanceamento = remover_arv_B3(blocos, &(*blocos)->cen, inicial, flag);

	    if (balanceamento == 1 && *blocos != NULL && *pai != NULL)
        {
	    	if (*blocos == (**pai).esq)
				balanceamento = balanceia_arv_B3(pai, -1);

	    	else if (*blocos == (**pai).cen)
				balanceamento = balanceia_arv_B3(pai, 0);

			else if (*blocos == (**pai).dir)
				balanceamento = balanceia_arv_B3(pai, 1);
	    }
	}

	return balanceamento;
}

void ocupa_espaco(arv_blocos **no ,arv_blocos **raiz, int *qtd, int *flag)
{
    int i_bloco = 0;
    if((*raiz) != NULL)
    {
        if(eh_folha_B3((*raiz)) == 0)
        {
            if((*raiz)->info1.status == 1 && ((*raiz)->info1.blocof - ((*raiz)->info1.blocoi + 1) > *qtd))
            {
                if((*raiz)->esq != NULL)
                {
                    if((*raiz)->esq->nInfos == 2)
                    {
                        (*raiz)->esq->info2.blocof = ((*raiz)->info1.blocof - *qtd);
                        (*raiz)->info1.blocoi = (*raiz)->esq->info2.blocof + 1;
                    }else
                    {
                        (*raiz)->esq->info1.blocof = ((*raiz)->info1.blocof - *qtd);
                        (*raiz)->info1.blocoi = (*raiz)->esq->info1.blocof + 1;
                    }
                }
            }else if((*raiz)->nInfos == 2 && (*raiz)->info2.status == 1 && ((*raiz)->info2.blocof - ((*raiz)->info2.blocoi + 1) > *qtd))
            {
                if((*raiz)->cen != NULL)
                {
                    if((*raiz)->cen->nInfos == 2)
                    {
                        (*raiz)->cen->info2.blocof = ((*raiz)->info2.blocof - *qtd);
                        (*raiz)->info2.blocoi = (*raiz)->cen->info2.blocof + 1;
                    }else
                    {
                        (*raiz)->cen->info1.blocof = ((*raiz)->info2.blocof - *qtd);
                        (*raiz)->info2.blocoi = (*raiz)->cen->info1.blocof + 1;
                    }
                }
            }else if((*raiz)->info1.status == 1 && ((*raiz)->info1.blocof - ((*raiz)->info1.blocoi + 1) == *qtd))
            {
                if((*raiz)->esq != NULL)
                {
                    if((*raiz)->esq->nInfos == 2)
                    {
                        i_bloco = (*raiz)->esq->info2.blocoi;
                        (*raiz)->info1.blocof = (*raiz)->cen->info1.blocof;

                        remover_arv_B3(no, raiz, (*raiz)->cen->info1.blocoi, flag);
                        remover_arv_B3(no, raiz, (*raiz)->esq->info2.blocoi, flag);

                        (*raiz)->info1.blocoi = i_bloco;
                    }else
                    {
                        i_bloco = (*raiz)->esq->info1.blocoi;
                        (*raiz)->info1.blocof = (*raiz)->cen->info1.blocof;

                        remover_arv_B3(no, raiz, (*raiz)->cen->info1.blocoi, flag);
                        remover_arv_B3(no, raiz, (*raiz)->esq->info1.blocoi, flag);
                        (*raiz)->info1.blocoi = i_bloco;
                    }
                }
            }else if((*raiz)->nInfos == 2 && (*raiz)->info2.status == 1 && ((*raiz)->info2.blocof - ((*raiz)->info2.blocoi + 1) == *qtd))
            {
                if((*raiz)->cen != NULL)
                {
                    if((*raiz)->cen->nInfos == 2)
                    {
                        i_bloco = (*raiz)->cen->info2.blocoi;
                        if((*raiz)->dir != NULL)
                        {
                            (*raiz)->info2.blocof = (*raiz)->dir->info1.blocof;
                            remover_arv_B3(no, raiz, (*raiz)->dir->info1.blocoi, flag); 
                        }

                        remover_arv_B3(no, raiz, (*raiz)->cen->info2.blocoi, flag);
                        (*raiz)->info2.blocoi = i_bloco;
                    }else
                    {
                        i_bloco = (*raiz)->cen->info1.blocoi;
                        if((*raiz)->dir != NULL)
                        {
                            (*raiz)->info2.blocof = (*raiz)->dir->info1.blocof;
                            remover_arv_B3(no, raiz, (*raiz)->dir->info1.blocoi, flag);
                        }

                        remover_arv_B3(no, raiz, (*raiz)->cen->info1.blocoi, flag);
                        (*raiz)->info2.blocoi = i_bloco;
                    }
                }
            }
        }
        if((*raiz)->esq != NULL)
            ocupa_espaco(no, &(*raiz)->esq, qtd, flag);
        if((*raiz)->cen != NULL)
            ocupa_espaco(no, &(*raiz)->cen, qtd, flag);
        if((*raiz)->dir != NULL && (*raiz)->nInfos == 2)
            ocupa_espaco(no, &(*raiz)->dir, qtd, flag);
    }
}

arv_blocos *buscar_no(arv_blocos *no, int status, int qtd)
{
    arv_blocos *bloco;
    int encontrou = 0;
    if(no != NULL)
    {
        if(no->info1.status == status && (no->info1.blocof - no->info1.blocoi) >= qtd)
        {
            encontrou = 1;
            bloco = no; 
        }
        else if(no->nInfos == 2 && no->info2.status == status && (no->info2.blocof - no->info2.blocoi) >= qtd)
        {
            encontrou = 1;
            bloco = no;
        }
        else if(encontrou == 0)
        {
            bloco = buscar_no(no->esq, status, qtd);
            bloco = buscar_no(no->cen, status, qtd);
            if(no->nInfos == 2)
                bloco = buscar_no(no->dir, status, qtd);
        }
    }
    return bloco;
}



void liberar_arv_B3(arv_blocos *no) 
{
    if (no != NULL) 
    {
        liberar_arv_B3(no->esq);
        liberar_arv_B3(no->cen);
        if(no->nInfos == 2)
            liberar_arv_B3(no->dir);
            
        free(no);
    }
}