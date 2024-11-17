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
arv_B3 *criar_no_arvB3(info_ptbr info, arv_B3 *filhoE, arv_B3 *filhoC);
//-----

//----Quebra No
arv_B3 *quebra_no(arv_B3 **no, info_ptbr info, info_ptbr *promove, arv_B3 *filho);
//-----

//----Adiciona Chave
arv_B3 *adiciona_chave(arv_B3 *no, info_ptbr info, arv_B3 *filho);
//----

//----Inserir no Arvore
int inserir_arvBB(arv_ingles **ingles, arv_ingles *no);
arv_B3 *inserir_arvB3(arv_B3 **portugues, info_ptbr info, info_ptbr *promove, arv_B3 **pai);
//-----




#endif