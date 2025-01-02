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
    struct arvore_portugues *esq, *dir;
    info_ptbr info;
    int cor;
}arv_ptbr;

arv_ingles *criar_arvBB();
arv_ptbr *criar_arvRN();

arv_ingles *criar_no_arvBB();
arv_ptbr *criar_no_arvRN();

void inserir_arvRN(arv_ptbr **R, arv_ptbr *no);
#endif