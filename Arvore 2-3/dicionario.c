#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"

//-----Criar arvores

arv_ingles *criar_arvBB()
{
    return NULL;
}
arv_ptbr *criar_arvB3()
{
    return NULL;
}
//----------------------------------------------------------------------------------------------------

//-----Alocar nó da Árvore

arv_ingles *cria_no_arvBB()
{
    arv_ingles * no;
    no = (arv_ingles *)malloc(sizeof(arv_ingles));

    no->dir = NULL;
    no->esq = NULL;
    no->info.l_unidade = NULL;

    return no;
}
arv_ptbr *criar_no_arvB3(info_ptbr info, arv_ptbr *filhoE, arv_ptbr *filhoC)
{
    arv_ptbr *no; //Cria o nó
    no = (arv_ptbr *)malloc(sizeof(arv_ptbr)); //Aloca o nó

    no->info1 = info; //Atribui a struct
    no->esq = filhoE; //Atribui o filho da esquerda
    no->cen = filhoC; //Atribui o filho da direita
    no->nInfos = 1; //Atribui 1 ao número de infos

    return (no); //Retorna o nó alocado
}
//----------------------------------------------------------------------------------------------------

//----Auxiliares da inserir na árvore b3

arv_ptbr *quebra_no(arv_ptbr **no, info_ptbr info, info_ptbr *promove, arv_ptbr *filho)
{
    arv_ptbr *maior; //Cria o nó maior

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

//----Verifica se é folha

int eh_folha_BB(arv_ingles *ingles)
{
    int verifica = 0;
    if(ingles->esq == NULL && ingles->dir == NULL)
        verifica = 1;
    
    return verifica;
}
int eh_folha_B3(arv_ptbr *portugues)
{
    int verifica = 0; //Cria e inicializa o verifica com 0

    if(portugues->esq == NULL) //Se a esquerda for nula
        verifica = 1; //Atribui 1 a variável verifica, ou seja, é nulo

    return verifica; //Retorna a verificação
}
//----------------------------------------------------------------------------------------------------

arv_ingles *so_um_filho_BB(arv_ingles *ingles)
{
    arv_ingles *aux;
    
    if(ingles->esq != NULL && ingles->dir == NULL)
        aux = ingles->esq;
    
    else if(ingles->esq == NULL && ingles->dir != NULL)
        aux = ingles->dir;

    return aux;
}

arv_ingles *menor_filho_BB(arv_ingles *ingles)
{
    while(ingles != NULL && ingles->esq != NULL)
        ingles = ingles->esq;

    return ingles;
}

int ninfos_B3(arv_ptbr *portugues)
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

arv_ptbr *inserir_arvB3(arv_ptbr **portugues, info_ptbr info, info_ptbr *promove, arv_ptbr **pai)
{
    info_ptbr promove1; //Cria o promove
    arv_ptbr *maior; //Cria o nó maior
    maior = NULL; //Atribui nulo ao nó maior

    if(*portugues == NULL) //SE a árvore estiver vazia
        *portugues = criar_no_arvB3(info, NULL, NULL); //Chama a função criar_no_arvB3
    
    else //SE NÃO:
    {
        if(eh_folha_B3(*portugues) == 1) //Verifica se é folha
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
            if(strcmp(info.ptbr, (*portugues)->info1.ptbr) == 0)
                inserir_arvBB(info.ingles, NULL);
            if(strcmp(info.ptbr, (*portugues)->info1.ptbr) < 0) //Verifica se a nova info é menor q a info1
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
//----------------------------------------------------------------------------------------------------


//-----Ler do arquivo

void ler_arquivo(FILE *dicionario, arv_ptbr **portugues)
{
    dicionario = fopen("dicionario.txt", "r");
    if (dicionario != NULL)
    {
        fseek(dicionario, 0, SEEK_SET);
        char linha[100]; // Aumente o tamanho se as linhas forem maiores
        char unidade_atual[100] = "";

        while (fgets(linha, sizeof(linha), dicionario))
        {
            linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha

            if (linha[0] == '%') // Identifica uma unidade
            {
                strcpy(unidade_atual, linha + 1); // Copia a unidade atual (sem o '%')
            }
            else if (strchr(linha, ':')) // Identifica uma linha com tradução
            {
                char palavra_ingles[100];
                char palavras_portugues[100];

                sscanf(linha, "%[^:]: %[^\n]", palavra_ingles, palavras_portugues);

                char *palavra_port = strtok(palavras_portugues, ",");
                while (palavra_port)
                {
                    while (*palavra_port == ' ') palavra_port++; // Remove espaços no início

                    // Preenche a estrutura info_ptbr
                    info_ptbr nova_info;
                    strcpy(nova_info.ptbr, palavra_port); // Português
                    strcpy(nova_info.ingles->info.ingles, palavra_ingles); // Inglês

                    info_ptbr promove; // Para gerenciar possíveis promoções
                    arv_ptbr *pai = NULL;

                    // Insere na árvore
                    inserir_arvB3(portugues, nova_info, &promove, &pai);

                    palavra_port = strtok(NULL, ","); // Próxima palavra
                }
            }
        }
        fclose(dicionario);
    }
    else
        printf("Não foi possível abrir o arquivo.\n");
}
//----------------------------------------------------------------------------------------------------

int remover_arvBB(arv_ingles **ingles, arv_ingles *no)
{
    int removeu = 1, verificacao;
    arv_ingles *aux;
    arv_ingles *end_filho, *end_menor_filho;

    if((*ingles) != NULL)
    {
        if(strcmp((*ingles)->info.ingles, no->info.ingles) == 0)
        {
            verificacao = e_folha_BB(*ingles);
            
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
                    removeu = remover_arvBB(&(*ingles)->dir, no);
                } 
        }
        else if(strcmp(no->info.ingles, (*ingles)->info.ingles) < 0)
                    removeu = remover_arvBB(&((*ingles)->esq), no);        
            else 
                removeu = remover_arvBB(&((*ingles)->dir), no);
                
    }
    else removeu = 0;
    
    return removeu;
}
// arv_ptbr *remover_arvB3(arv_ptbr **portugues, info_ptbr info, info_ptbr *promove, arv_ptbr **pai)
// {

// }
//----------------------------------------------------------------------------------------------------()