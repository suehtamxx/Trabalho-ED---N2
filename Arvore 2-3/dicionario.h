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
    int nInfos;
    info_ptbr info1, info2;
    struct arvore_portugues *esq, *cen, *dir;
}arv_ptbr;

//----Alocar nó da Árvore e da Lista

// Aloca e cria um novo nó para a lista de unidades
unidade *criar_no_l_unid();
// Aloca e cria um novo nó para a árvore BB
arv_ingles *cria_no_arv_BB();
// Aloca e cria um novo nó para a árvore B3, atribuindo as informações iniciais e os filhos
arv_ptbr *criar_no_arv_B3(info_ptbr info, arv_ptbr *filhoE, arv_ptbr *filhoC);

//----------------------------------------------------------------------------------------------------

//----Auxiliares da inserir na árvore B3

// Quebra um nó da árvore B3, criando um novo nó com a maior informação e atualizando o promove
arv_ptbr *quebra_no(arv_ptbr **no, info_ptbr info, info_ptbr *promove, arv_ptbr *filho);
// Adiciona uma nova chave a um nó já existente na árvore B3, atualizando o número de informações
arv_ptbr *adiciona_chave(arv_ptbr *no, info_ptbr info, arv_ptbr *filho);

//----------------------------------------------------------------------------------------------------

//----Auxiliares da inserir na Árvore BB

// Retorna o único filho existente em um nó da árvore BB
arv_ingles *so_um_filho_BB(arv_ingles *ingles);
// Encontra e retorna o menor filho de um nó na árvore BB
arv_ingles *menor_filho_BB(arv_ingles *ingles);

//----------------------------------------------------------------------------------------------------

//----Verifica se é folha

// Verifica se o nó é uma folha da árvore BB
int eh_folha_BB(arv_ingles *ingles);
// Verifica se o nó é uma folha da árvore B3
int eh_folha_B3(arv_ptbr *portugues);

//----------------------------------------------------------------------------------------------------

//----Inserir nó nas Árvores

// Insere uma nova informação na árvore BB
int inserir_arv_BB(arv_ingles **ingles, arv_ingles *no);
// Insere uma nova informação na árvore B3, realizando as operações de split se necessário
arv_ptbr *inserir_arv_B3(arv_ptbr **portugues, info_ptbr info, info_ptbr *promove, arv_ptbr **pai);

//----------------------------------------------------------------------------------------------------

//----Ler do arquivo

// Lê informações de um arquivo e as insere na árvore B3
void ler_arquivo(arv_ptbr **portugues);

//----------------------------------------------------------------------------------------------------

//----Imprimir de acordo com a unidade

// Imprime todas as palavras de uma unidade específica da árvore BB
void imprimir_unid_BB(arv_ingles *ingles, int unidade, char *palavra);
// Imprime todas as palavras de uma unidade específica da árvore B3
void imprimir_unid_B3(arv_ptbr *portugues, int unidade);

//----------------------------------------------------------------------------------------------------

//----Imprimir de acordo com a palavra em português

// Imprime todas as palavras correspondentes a um termo em português na árvore BB
void imprimir_ptbr_BB(arv_ingles *ingles);
// Imprime todas as palavras correspondentes a um termo em português na árvore B3
void imprimir_ptbr_B3(arv_ptbr *portugues, char *palavra);

//----------------------------------------------------------------------------------------------------

//----Remover de acordo com a palavra em inglês e a unidade

// Remove um nó com base na palavra em inglês e unidade na árvore VV
void remover_ingles_BB(arv_ingles **no, char *palavra, int unid);
// Remove um nó com base na palavra em inglês e unidade na árvore B3
void remover_ingles_B3(arv_ptbr **no, arv_ptbr **portugues, char *palavra, int unid);

//----------------------------------------------------------------------------------------------------

//----Remover de acordo com a palavra em português e a unidade

// Remove um nó com base na palavra em português e unidade na árvore BB
void remover_portugues_BB(arv_ingles **no, int unid);
// Remove um nó com base na palavra em português e unidade na árvore B3
void remover_portugues_B3(arv_ptbr **no, arv_ptbr **portugues, char *palavra, int unid);

//----------------------------------------------------------------------------------------------------

//----Auxiliares da remover na árvore B3

// Libera a memória alocada para um nó na árvore B3
void libera_no(arv_ptbr **No);
// Remove um nó folha na esquerda, considerando o nó pai
int remove_esq_folha(arv_ptbr **portugues, arv_ptbr **pai);
// Remove um nó folha no centro, considerando o nó pai
int remove_centro_folha(arv_ptbr **portugues, arv_ptbr **pai);
// Remove um nó folha na direita, considerando o nó pai
void remove_dir_folha(arv_ptbr **portugues, arv_ptbr **pai);
// Remove um nó quando é folha, liberando o nó e ajustando o pai
int remove_folha(arv_ptbr **Pai, arv_ptbr **portugues, char *palavra);
// Remove um valor de um nó cujos filhos são folhas
int remove_no_filho_folhas(arv_ptbr **portugues, char *palavra);
// Balanceia a árvore B3 após uma remoção
int balanceia_arv_B3(arv_ptbr **portugues, int desbalanceamento);
// Remove a menor informação de um nó e retorna para ser promovida
int remove_menor_no(arv_ptbr **pai_aux, arv_ptbr **No, info_ptbr *promove);

//----------------------------------------------------------------------------------------------------

//----Remover nó nas Árvores

// Remove um nó completo da árvore BB
int remover_arv_BB(arv_ingles **ingles, arv_ingles *no);
// Remove um nó completo da árvore B3, ajustando estrutura se necessário
int remover_arv_B3(arv_ptbr **pai, arv_ptbr **portugues, char *palavra, int *flag);

//----------------------------------------------------------------------------------------------------

//----Liberar memória da árvore completa

// Libera a memória alocada para a lista de unidades
void liberar_lista_unid(unidade *l_unidade);
// Libera toda a memória alocada para a árvore BB
void liberar_arv_BB(arv_ingles *ingles);
// Libera toda a memória alocada para a árvore B3
void liberar_arv_B3(arv_ptbr *portugues);

//----------------------------------------------------------------------------------------------------
#endif