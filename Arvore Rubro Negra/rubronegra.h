#ifndef RUBRONEGRA_H
#define RUBRONEGRA_H

#define black = 1;
#define red = 2;

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
    info_ingles info;
    struct arvore_ingles *esq, *dir;
}arv_ingles;

typedef struct informacao_ptbr
{
    char ptbr[100];
    arv_ingles *ingles;
}info_ptbr;

typedef struct arvore_portugues
{
    struct arvore_portugues *esq, *dir;
    info_ptbr info;
    int cor;
}arv_ptbr;

// Aloca e cria um novo nó para a lista de unidades
unidade *criar_no_l_unid();
// Aloca e cria um novo nó para a árvore binária de busca
arv_ingles *criar_no_arvBB();
// Aloca e cria um novo nó para a árvore rubro-negra
arv_ptbr *criar_no_arv_RN();

// Insere um novo nó na árvore binária de busca
int inserir_arv_BB(arv_ingles **ingles, arv_ingles *no);
// Insere um novo nó na árvore rubro-negra
void inserir_arv_RN(arv_ptbr **R, arv_ptbr *no);

// Retorna a cor de um nó da árvore rubro-negra (0 para preto, 1 para vermelho)
int cor(arv_ptbr *no);
// Troca a cor de um nó da árvore rubro-negra
void trocaCor(arv_ptbr *no);
// Remove um nó da árvore rubro-negra pelo valor especificado
int remove_arv_RN(arv_ptbr **no, char *valor);
// Move dois nós consecutivos à esquerda e ajusta as cores na árvore rubro-negra
void move2EsqRed(arv_ptbr **r);
// Move dois nós consecutivos à direita e ajusta as cores na árvore rubro-negra
void move2DirRed(arv_ptbr **r);
// Balanceia a árvore rubro-negra após inserções ou remoções
arv_ptbr *balancear(arv_ptbr *r);

// Remove o menor nó da subárvore e retorna o nó ajustado
arv_ptbr *removeMenor(arv_ptbr *no);
// Procura e retorna o menor nó da subárvore
arv_ptbr *procuraMenor(arv_ptbr *no);
// Remove um nó da árvore rubro-negra pelo valor especificado
arv_ptbr *remove_no(arv_ptbr *no, char *valor);

// Remove um nó da árvore binária de busca
int remover_arv_BB(arv_ingles **ingles, arv_ingles *no);

// Verifica se o nó é uma folha na árvore binária de busca
int eh_folha_BB(arv_ingles *ingles);
// Retorna o menor filho da subárvore na árvore binária de busca
arv_ingles *menor_filho_BB(arv_ingles *ingles);
// Retorna o único filho do nó na árvore binária de busca (se houver)
arv_ingles *so_um_filho_BB(arv_ingles *ingles);

// Lê os dados de um arquivo e insere na árvore rubro-negra
void ler_arquivo(arv_ptbr **portugues);

// Imprime os dados de uma unidade específica na árvore rubro-negra
void imprimir_unidade_RN(arv_ptbr *no, int uni);
// Imprime os dados de uma unidade específica na árvore binária de busca
void imprimir_unidade_BB(arv_ingles *no, int uni, char *palavra);

// Imprime os dados de uma palavra em português na árvore binária de busca
void imprimir_ptbr_BB(arv_ingles *no, char *palavra);
// Imprime os dados de uma palavra em português na árvore rubro-negra
void imprimir_ptbr_RN(arv_ptbr *no, char *palavra);

// Remove uma palavra em inglês associada a uma unidade da árvore binária de busca
void remover_ingles_BB(arv_ingles **no, char *palavra, int uni);
// Remove uma palavra em inglês associada a uma unidade da árvore rubro-negra
void remover_ingles_RN(arv_ptbr **no, arv_ptbr **portugues, char *palavra, int uni);

// Remove uma palavra em português associada a uma unidade da árvore binária de busca
void remover_portugues_BB(arv_ingles **no, int uni);
// Remove uma palavra em português associada a uma unidade da árvore rubro-negra
void remover_portgues_RN(arv_ptbr **no, arv_ptbr **portugues, char *palavra, int uni);

// Libera a memória de uma árvore binária de busca
void liberar_arv_BB(arv_ingles *no);
// Libera a memória de uma árvore rubro-negra
void liberar_arv_RN(arv_ptbr *no);
// Libera a memória da lista de unidades
void liberar_lista_unidades(unidade *l_unidade);

#endif