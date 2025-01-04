#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubronegra.h"

#define black 1;
#define red 2;

unidade *criar_no_l_unid()
{
    unidade *no; //Cria nó
    no = (unidade*)malloc(sizeof(unidade)); //Aloca o nó

    no->unidade = 0; //Atribui 0 a unidade
    no->prox = NULL; // Atribui nulo ao próximo

    return no;
}

arv_ingles *cria_no_arv_BB()
{
    arv_ingles *no; //Cria o nó
    no = (arv_ingles*)malloc(sizeof(arv_ingles)); //Aloca o nó

    no->dir = NULL; //Atribui nulo a direita
    no->esq = NULL; //Atribui nulo a esquerda
    no->info.l_unidade = NULL; //Atribui nulo a lista

    return no; //Retorna o nó alocado
}

arv_ptbr *criar_no_arvRN()
{
    arv_ptbr *no;
    no = (arv_ptbr*)malloc(sizeof(arv_ptbr));

    no->dir = NULL;
    no->esq = NULL;
    no->cor = 2;

    return no;
}

int cor(arv_ptbr *no)
{
    int cor = 1;
    if(no != NULL)
        cor = no->cor;
    return cor;
}

void trocarCor(arv_ptbr *no)
{
    if(no != NULL)
    {
        
    }
}
void inserir_arvRN(arv_ptbr **R, arv_ptbr *no)
{
    if(*R == NULL)
        *R = no;
    else{
        if(strcmp(no->info.ptbr, (*R)->info.ptbr) < 0)
            inserir_arvRN(&((*R)->esq), no);
        else inserir_arvRN(&((*R)->dir), no);

    if(cor((*R)->esq) == 1 && cor((*R)->dir) == 2)
        rotacionaEsq(R);
    if(cor((*R)->esq) == 2 && cor((*R)->esq->esq) == 2)
        rotacionaDir(R);
    if(cor((*R)->esq) == 2 && cor((*R)->dir) == 2)
        trocarCor(R);
    }
}
arv_ptbr *move2EsqRed(arv_ptbr *r)
{
    trocarCor(r);
    if(cor(r->dir->esq) == 2)
    {
        r->dir = rotacionaDir(r->dir);
        r = rotacionaEsq(r);
        trocaCor(r);
    }
    return r;
}

arv_ptbr *move2DirRed(arv_ptbr *r)
{
    trocaCor(r);
    if(cor(r->esq->esq) == 2)
    {
        r = rotacionaDir(r);
        trocaCor(r);
    }
    return r; 
}
arv_ptbr *balancear(arv_ptbr *r)
{
    if(cor(r->esq) == 1 && cor(r->dir) == 2)
        r = rotacionaEsq(r);
    if(cor(r->esq) == 2 && cor(r->esq->esq) == 2)
        r = rotacionaDir(r);
    if(cor(r->esq) == 2 && cor(r->dir) == 2)
        trocaCor(r);
    return r;
}
arv_ptbr *removeMenor(arv_ptbr *no)
{
    if(no->esq == NULL)
        free(no);
    if(cor(no->esq) == 1 && cor(no->esq->esq) == 1)
        no = move2EsqRed(no);
    
    no->esq = removeMenor(no->esq);
    return balancear(no);
}

arv_ptbr *procuraMenor(arv_ptbr *atual)
{
    arv_ptbr *no1, *no2;
    no1 = atual;
    no2 = atual->esq;
    while(no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

arv_ptbr *remove_no(arv_ptbr *no, char valor)
{
    if(strcmp(valor, no->info.ptbr) == 0)
    {
        if(cor(no->esq) == 1 && cor(no->esq->esq) == 1)
        no = move2EsqRed(no);

    no->esq = remove_no(no->esq, valor);
    }
    else
    {
        if(cor(no->esq) == 2)
            no = rotacionaDir(no);
        if(strcmp(valor, no->info.ptbr) == 0 && (no->dir == NULL))
            free(no);
        if(cor(no->dir) == 1 && cor(no->dir->esq) == 1)
            no = move2DirRed(no);
        if(strcmp(valor, no->info.ptbr) == 0)
        {
            arv_ptbr *menor;
            menor = procuraMenor(no->dir);
            no->info = menor->info;
            no->dir = removeMenor(no->dir);
        }else
            no->dir = remove_no(no->dir, valor);
    }
    return balancear(no);
}

int *remove_arvRN(arv_ptbr *no, char valor)
{
    int verificao = 0;
    if(no != NULL)
    {
        arv_ptbr *raiz;
        *raiz = *no;
        raiz = remove_no(no, valor);
        if(raiz != NULL)
            raiz->cor = 1;
        verificao = 1;
    }
    return verificao;
}