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
// Aloca e adiciona a info no nó com nenhuma info e atruibui 1 ao número de infos
arv_ptbr *criar_no_arv_B3(info_ptbr info, arv_ptbr *filhoE, arv_ptbr *filhoC);

//----------------------------------------------------------------------------------------------------

//----Auxiliares da inserir na árvore b3

// Cria um novo nó com a maior info, atualiza o promove e o número de infos
arv_ptbr *quebra_no(arv_ptbr **no, info_ptbr info, info_ptbr *promove, arv_ptbr *filho);
// Adiciona a info no nó já com 1 info e atualiza o número de infos
arv_ptbr *adiciona_chave(arv_ptbr *no, info_ptbr info, arv_ptbr *filho);

//----------------------------------------------------------------------------------------------------

//----Auxiliares da inserir na Árvore BB

arv_ingles *so_um_filho_BB(arv_ingles *ingles);
arv_ingles *menor_filho_BB(arv_ingles *ingles);

//----------------------------------------------------------------------------------------------------

//----Verifica se é folha

// Verifica se o nó é uma folha da ávore binária
int eh_folha_BB(arv_ingles *ingles);
// Verifica se o nó é uma folha da árvore b3
int eh_folha_B3(arv_ptbr *portugues);

//----------------------------------------------------------------------------------------------------

//----Inserir nó nas Árvores

// Insere uma nova informação na árvore binária
int inserir_arv_BB(arv_ingles **ingles, arv_ingles *no);
// Insere uma nova informação na árvore b3
arv_ptbr *inserir_arv_B3(arv_ptbr **portugues, info_ptbr info, info_ptbr *promove, arv_ptbr **pai);

//----------------------------------------------------------------------------------------------------

//----Ler do arquivo

void ler_arquivo(arv_ptbr **portugues);

//----------------------------------------------------------------------------------------------------

//----Imprimir de acordo com a unidade

void imprimir_unid_BB(arv_ingles *ingles, int unidade);
void imprimir_unid_B3(arv_ptbr *portugues, int unidade);

//----------------------------------------------------------------------------------------------------

//----Auxiliares da remover na árvore b3

// Libera o nó da árvore b3
void libera_no(arv_ptbr **No);
// Recebe um nó folha e o seu pai e remove quando nó é esquerda do pai
int remove_esq_folha(arv_ptbr **portugues, arv_ptbr **pai);
// Recebe um nó folha e o seu pai, remove quando o nó é o centro do pai
int remove_centro_folha(arv_ptbr **portugues, arv_ptbr **pai);
// Recebe um nó folha e o seu pai, remove quando o nó é a direita do pai
void remove_dir_folha(arv_ptbr **portugues, arv_ptbr **pai);
// Remove o nó quando é folha, recebe o nó que vai ter seu valor removido e o nó pai, depois remove o nó
int remove_folha(arv_ptbr **Pai, arv_ptbr **portugues, char *palavra);
// Recebe o nó e a palavra em português, remove o valor do nó quando os filhos do nó são folhas
int remove_no_filho_folhas(arv_ptbr **portugues, char *palavra);
// Recebe um nó e um valor para balanceia_arv_B3, ver em que lado da português esta desbalanceado então balanceia o nó
int balanceia_arv_B3(arv_ptbr **portugues, int desbalanceamento);
// FUNÇÃO QUE RECEBE UM NO E PERCORRE A PARTIR DELE BUSCANDO A MENOR INFORMAÇÃO PARA REMOVER E RETORNAR NA VARIAVEL promove
int remove_menor_no(arv_ptbr **pai_aux, arv_ptbr **No, info_ptbr *promove);

//----------------------------------------------------------------------------------------------------

//----Remover nó nas Árvores

int remover_arv_BB(arv_ingles **ingles, arv_ingles *no);
int remover_arv_B3(arv_ptbr **pai, arv_ptbr **portugues, char *palavra, int *flag);

//----------------------------------------------------------------------------------------------------

//----Liberar memória da árvore completa

// Liberar a lista de unidades
void liberar_lista_unid(unidade *l_unidade);
// Liberar a árvore de BB
void liberar_arv_BB(arv_ingles *ingles);
// Liberar a árvore B3
void liberar_arv_B3(arv_ptbr *portugues);

//----------------------------------------------------------------------------------------------------

#endif