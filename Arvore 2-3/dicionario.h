#ifndef DICIONARIO_H
#define DICIONARIO_H

typedef struct lista_unidade
{
    int unidade;
    struct lista_unidade *prox;
}unidade;

typedef struct informacao_ingles
{
    char ingles[100];
    unidade *l_unidade;
}info_ingles;

typedef struct arvore_ingles
{
    struct arvore_ingles *esq, *dir;
    info_ingles info;
}arv_ingles;

typedef struct informacao_ptbr
{
    char ptbr[100];
    arv_ingles *ingles;
}info_ptbr;

typedef struct arvore_portugues
{
    struct arvore_portugues *esq, *cen, *dir;
    info_ptbr info1, info2;
    int nInfos;
}arv_ptbr;

//----Alocar nó da Árvore e da Lista

unidade *criar_no_l_unid();
arv_ingles *cria_no_arv_BB();
/*
Função criar_no_arvB3

-> Aloca e adiciona a info no nó com nenhuma info e atruibui 1 ao número de infos

-> Parâmetros:
    info (struct): a info para inserir;
    filhoC (ponteiro p/ árvore): filho do centro nulo; 
    filhoE (ponteiro p/ árvore): filho nulo para a esquerda.

-> Retorna os nó com a info inserida
*/
arv_ptbr *criar_no_arv_B3(info_ptbr info, arv_ptbr *filhoE, arv_ptbr *filhoC);

//----------------------------------------------------------------------------------------------------

//----Auxiliares da inserir na árvore b3

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
arv_ptbr *quebra_no(arv_ptbr **no, info_ptbr info, info_ptbr *promove, arv_ptbr *filho);
/*
Função adiciona_chave

-> Adiciona a info no nó já com 1 info e atualiza o número de infos

-> Parâmetros;
    no (ponteiro p/ árvore): nó onde a info será inserida; 
    info (struct): a info para inserir;
    filho (ponteiro p/ árvore): filho nulo.

-> Retorna os nó com a info inserida
*/
arv_ptbr *adiciona_chave(arv_ptbr *no, info_ptbr info, arv_ptbr *filho);

//----------------------------------------------------------------------------------------------------

//----Verifica se é folha

/*
Função e_folha

-> Verifica se o nó é uma folha da ávore binária

-> Parâmetro;
    portugues(pornteiro p/ árvore): nó a ser verificado.

-> Retorna 1 para folha e 0 para não folha
*/
int eh_folha_BB(arv_ingles *ingles);
/*
Função e_folha

-> Verifica se o nó é uma folha da árvore b3

-> Parâmetro;
    portugues(ponteiro p/ árvore): nó a ser verificado.

-> Retorna 1 para folha e 0 para não folha
*/
int eh_folha_B3(arv_ptbr *portugues);

//----------------------------------------------------------------------------------------------------

arv_ingles *so_um_filho_BB(arv_ingles *ingles);
arv_ingles *menor_filho_BB(arv_ingles *ingles);
int ninfos_B3(arv_ptbr *portugues);
void troca_posicao(arv_ptbr *portugues);

//----Inserir no Arvore

int inserir_arv_BB(arv_ingles **ingles, arv_ingles *no);
void juntar_arv_BB(arv_ingles **ingles, arv_ingles *no);
/*
Função inserir_arvB3

-> Insere uma nova indormação na árvore

-> Parâmetros:
    portugues (ponteiro para ponteiro p/ árvore): raíz da árvore;
    info (struct): a info para inserir;
    promove (ponteiro p/ árvore): info que será inserida no nó pai; 
    pai (ponteiro para ponteiro p/ árvore): pai da variável portugues.

-> Retorna a árvore com a nova info inserida
*/
arv_ptbr *inserir_arv_B3(arv_ptbr **portugues, info_ptbr info, info_ptbr *promove, arv_ptbr **pai);

//----------------------------------------------------------------------------------------------------

//----Ler do arquivo

void ler_arquivo(arv_ptbr **portugues);

//----------------------------------------------------------------------------------------------------

//----Remover no Arvore

int remover_arv_BB(arv_ingles **ingles, arv_ingles *no);
arv_ptbr *remover_arv_B3(arv_ptbr **portugues, info_ptbr info, info_ptbr *promove, arv_ptbr **pai);

//----------------------------------------------------------------------------------------------------

//----Liberar nó

void liberar_arv_BB(arv_ingles *ingles);
void liberar_arv_B3(arv_ptbr *portugues);

#endif