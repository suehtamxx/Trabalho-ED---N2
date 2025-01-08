#ifndef BLOCOSLOGICOS_H
#define BLOCOSLOGICOS_H

typedef struct blocos
{
    int blocoi, blocof;
    int *eblocoi, *eblocof;
    char status;

}info_blocos;

typedef struct arvore_blocos
{
    struct arvore_blocos *esq, *cen, *dir;
    info_blocos info1, info2;
    int nInfos;
}arv_blocos;


#endif