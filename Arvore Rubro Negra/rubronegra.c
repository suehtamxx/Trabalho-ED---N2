#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubronegra.h"

#define int 1 = black;
#define int 2 = red;

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
