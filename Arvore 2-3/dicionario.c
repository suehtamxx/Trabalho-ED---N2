#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"

//-----Criar arvores
arv_ingles *criar_arvBB()
{
    return NULL;
}
arv_B3 *criar_arvB3()
{
    return NULL;
}
//-----

//-----Alocar nó da Árvore
arv_ingles *alocar_arvBB()
{

}

/*
Função criar_no_arvB3

-> Aloca e adiciona a info no nó com nenhuma info e atruibui 1 ao número de infos

-> Parâmetros:
    info (struct): a info para inserir;
    filhoC (ponteiro p/ árvore): filho do centro nulo; 
    filhoE (ponteiro p/ árvore): filho nulo para a esquerda.

-> Retorna os nó com a info inserida
*/
arv_B3 *criar_no_arvB3(info_ptbr info, arv_B3 *filhoE, arv_B3 *filhoC)
{
    arv_B3 *no; //Cria o nó
    no = (arv_B3 *)malloc(sizeof(arv_B3)); //Aloca o nó

    no->info1 = info; //Atribui a struct
    no->esq = filhoE; //Atribui o filho da esquerda
    no->cen = filhoC; //Atribui o filho da direita
    no->nInfos = 1; //Atribui 1 ao número de infos

    return (no); //Retorna o nó alocado
}
//-----

/*
Função quebra_no

-> Cria um novo nó com a maior info, atualiza o promove e o número de infos

-> Parâmetros:
    no (ponteiro para ponteiro p/ árvore): nó que será quebrado; 
    info (struct): a info para inserir no nó;
    promove (ponteiro p/ árvore): info que será inserida no nó pai;
    filho (ponteiro p/ árvore): filho nulo.

-> Retorna o nó com a maior info
*/
arv_B3 *quebra_no(arv_B3 **no, info_ptbr info, info_ptbr *promove, arv_B3 *filho)
{
    arv_B3 *maior; //Cria o nó maior

    if(strcmp(info.ptbr, (*no)->info2.ptbr) > 0) //Se a nova info for maior que a info2 
    {
        *promove = (*no)->info2; //Promove a info2 (sempre sobe a info do meio)
        maior = criar_no_arvB3(info, (*no)->dir, filho); //Cria um nó só com a nova info (maior info)
    }

    else if(strcmp(info.ptbr, (*no)->info1.ptbr) > 0) //Se a nova info for maior que a info1
    {
        *promove = info; //Promove a nova info (sempre sobe a info do meio)
        maior = criar_no_arvB3((*no)->info2, filho, (*no)->dir); //Cria um nó só com a info2 (maior info)
    }

    else //Se a nova info for menor que info1
    {
        *promove = (*no)->info1; //Promove a info1 (sempre sobe a info do meio)
        maior = criar_no_arvB3((*no)->info2, (*no)->cen, (*no)->dir); //Cria um nó com a info2 (maior info)
        (*no)->info1 = info; //Atribui a novo info ao info1
        (*no)->cen = filho; //Atribui nulo ao centro 
    }

    (*no)->nInfos = 1; //Atualiza o número de infos

    return (maior); //Retorna o nó com a maior info
}
//-----

/*
Função adiciona_chave

-> Adiciona a info no nó já com 1 info e atualiza o número de infos

-> Parâmetros;
    no (ponteiro p/ árvore): nó onde a info será inserida; 
    info (struct): a info para inserir;
    filho (ponteiro p/ árvore): filho nulo.

-> Retorna os nó com a info inserida
*/
arv_B3 *adiciona_chave(arv_B3 *no, info_ptbr info, arv_B3 *filho)
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
//-----

/*
Função e_folha

-> Verifica se o nó é uma folha

-> Parâmetro;
    portugues(pornteiro p/ árvore): nó a ser verificado.

-> Retorna 1 para folha e 0 para não folha
*/
int eh_folha(arv_B3 *portugues)
{
    int verifica = 0; //Cria e inicializa o verifica com 0

    if(portugues->esq == NULL) //Se a esquerda for nula
        verifica = 1; //Atribui 1 a variável verifica, ou seja, é nulo

    return verifica; //Retorna a verificação
}
//-----


/*
Função inserir_arvB3

-> Insere uma nova indormação na árvore

-> Parâmetros:
    portugues (poteiro para ponteiro p/ árvore): raíz da árvore;
    info (struct): a info para inserir;
    promove (ponteiro p/ árvore): info que será inserida no nó pai; 
    pai (ponteiro para ponteiro p/ árvore): pai da variável portugues.

-> Retorna a árvore com a nova info inserida
*/
arv_B3 *inserir_arvB3(arv_B3 **portugues, info_ptbr info, info_ptbr *promove, arv_B3 **pai)
{
    info_ptbr promove1; //Cria o promove
    arv_B3 *maior; //Cria o nó maior
    maior = NULL; //Atribui nulo ao nó maior

    if(*portugues == NULL) //SE a árvore estiver vazia
        *portugues = criar_no_arvB3(info, NULL, NULL); //Chama a função criar_no_arvB3
    
    else //SE NÃO:
    {
        if(eh_folha(*portugues) == 1) //Verifica se é folha
        {
            if((*portugues)->nInfos == 1) //Verifica se tem espaço
                *portugues = adiciona_chave(*portugues, info, NULL); //Se é folha e tem espaço, chama a função adiciona_chave
            
            else
            {
                maior = quebra_no(portugues, info, promove, NULL); //Se é folha e não tem espaço, chama a função quebra_no
                
                if(*pai == NULL) //Se o pai for nulo (quebrar o nó raiz)
                {
                    *portugues = criar_no_arvB3(*promove, *portugues, maior); //Chama a função criar_no_arvB3
                    maior = NULL; //Atribui nulo ao maior
                }
            }
        }

        else //Se não é folha:
        {
            if(strcmp(info.ptbr, (*portugues)->info1.ptbr) < 0) //Verifica se a nova info é maior q a info1
                maior = inserir_arvB3(&((*portugues)->esq), info, promove, portugues); //Vai para a sub-árvore esquerda
            
            else
            {
                if(((*portugues)->nInfos == 1) || (strcmp(info.ptbr, (*portugues)->info2.ptbr) < 0)); //Verifica se tem 1 info ou se a nova info é maior que info2
                else
                    maior = inserir_arvB3(&((*portugues)->dir), info, promove, portugues);
                if(maior != NULL)
                {
                    if((*portugues)->nInfos == 1)
                        *portugues = adiciona_chave(*portugues, *promove, maior);
                    else
                    {
                        maior = quebra_no(portugues, *promove, &promove1, maior);
                        if(*pai == NULL)
                        {
                            *portugues = criar_no_arvB3(promove1, *portugues, maior);
                            maior = NULL;
                        }
                    }
                }
            }
        }
    }
    return (maior);
}
//-----


//-----Ler do arquivo
void ler_arquivo(FILE *dicionario)
{
    dicionario = fopen("dicionario.txt", "r");
    if(dicionario != NULL)
    {
        fseek(dicionario, 0, SEEK_SET);
        while(fscanf(dicionario, ""));
    }
}
//-----