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

unidade *criar_no_l_unid();
arv_ingles *criar_no_arvBB();
arv_ptbr *criar_no_arvRN();

int cor(arv_ptbr *no);
void trocaCor(arv_ptbr *no);

int inserir_arv_BB(arv_ingles **ingles, arv_ingles *no);
void inserir_arvRN(arv_ptbr **R, arv_ptbr *no);
void move2EsqRed(arv_ptbr **r);
void move2DirRed(arv_ptbr **r);
arv_ptbr *balancear(arv_ptbr *r);
arv_ptbr *removeMenor(arv_ptbr *no);
arv_ptbr *procuraMenor(arv_ptbr *no);


arv_ptbr *remove_no(arv_ptbr *no, char *valor);
int remove_arvRN(arv_ptbr **no, char *valor);

int remover_arv_BB(arv_ingles **ingles, arv_ingles *no);
int eh_folha_BB(arv_ingles *ingles);
arv_ingles *menor_filho_BB(arv_ingles *ingles);
arv_ingles *so_um_filho_BB(arv_ingles *ingles);

void funcaoauxI(arv_ptbr *no, int uni);
void funcaoI(arv_ingles *no, int uni, char *palavra);
void funcaoII(arv_ingles *no, char *palavra);
void funcaoauxII(arv_ptbr *no, char *palavra);
void funcaoIII(arv_ptbr **no, char *palavra, int uni);
int funcaoauxIII(arv_ingles *no, char *palavra);
void liberar_arv_BB(arv_ingles *no);
void liberar_arvRN(arv_ptbr *no);
void liberar_lista_unidades(unidade *l_unidade);
#endif