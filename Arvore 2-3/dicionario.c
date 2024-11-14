#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"

//----Criar arvores
arv_ingles *criar_arvBB()
{
    return NULL;
}
arv_B3 *criar_arvB3()
{
    return NULL;
}
//-----
//----Alocar arvore
arv_ingles *alocar_arvBB()
{

}
arv_B3 *criar_no_arvB3(info_ptbr info, arv_B3 *filhoE, arv_B3 *filhoC)
{
    arv_B3 *no;
    no = (arv_B3 *)malloc(sizeof(arv_B3));
    no->info1 = info;
    no->esq = filhoE;
    no->cen = filhoC;
    no->nInfos = 1;

return (no);
}
//-----
//----Quebra No
arv_B3 *quebra_no(arv_B3 **no, info_ptbr info, info_ptbr *promove, arv_B3 *filho)
{
    arv_B3 *maior;
    if(strcmp(info.ptbr, (*no)->info2.ptbr) > 0)
    {
        *promove = (*no)->info2;
        maior = criar_no_arvB3(info, (*no)->dir, filho);
    }
    else if(strcmp(info.ptbr, (*no)->info1.ptbr) > 0)
    {
        *promove = info;
        maior = criar_no_arvB3((*no)->info2, filho, (*no)->dir);
    }
    else 
    {
        *promove = (*no)->info1;
        maior = criar_no_arvB3((*no)->info2, (*no)->cen, (*no)->dir);
        (*no)->info1 = info;
        (*no)->cen = filho;
    }
    (*no)->nInfos = 1;
return (maior);
}
//-----
//----Adiciona Chave
arv_B3 *adiciona_chave(arv_B3 *no, info_ptbr info, arv_B3 *filho)
{
    if(strcmp(info.ptbr, no->info1.ptbr) > 0)
    {
        no->info2 = info;
        no->dir = filho;
    } else 
    {
        no->info2 = no->info1;
        no->dir = no->cen;
        no->info1 = info;
        no->cen = filho;
    }
    no->nInfos = 2;
return (no);
}
//----