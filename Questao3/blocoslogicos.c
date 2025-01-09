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
                
                else //Se não for menor que info2
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
    getchar();
    do
    {
        printf("O primeiro bloco é livre(1) ou ocupado(0):\n");
        scanf(" %d", &info.status);

    }while(info.status != 0 && info.status != 1);
    getchar();
    
    do{
        printf("Qual o valor do bloco inicial:\n");
        scanf(" %d", &info.blocoi);

    }while(info.blocoi != 0);
    
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

        printf("Valor disponivel de %d ate %d\n", info.blocof + 1, qtd);
        do
        {

            printf("Qual o valor final do bloco:\n");
            scanf(" %d", &info.blocof);
            
            if(info.blocof <= (aux))printf("Valor inválido\n");

        }while(info.blocof <= (aux));

        inserir_arv_B3(no, info, &promove, &pai);

        info.blocoi = info.blocof + 1;

        if(info.status == 1)
            info.status = 0;
        else info.status = 1;
    }
        
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