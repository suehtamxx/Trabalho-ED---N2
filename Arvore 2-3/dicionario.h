#ifndef DICIONARIO_H
#define DICIONARIO_H
typedef struct informacao_ingles
{
    char ingles[100];
    int unidade;
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

typedef struct arvore_B3
{
    struct arvore_B3 *esq, *cen, *dir;
    info_ptbr info1, info2;
    int nInfos;
}arv_B3;

//----Criar arvores
arv_ingles *criar_arvBB();
arv_B3 *criar_arvB3();
//-----

//----Alocar arvore
arv_ingles *alocar_arvBB();
arv_B3 *alocar_arvB3(char info, );
//-----

//----Inserir no Arvore
int inserir_arvBB(arv_ingles **ingles, arv_ingles *no);
int inserir_arvB3(arv_B3 **portugues, arv_B3 *no, char info, char *promove, arv_B3 **Pai);
//-----




#endif