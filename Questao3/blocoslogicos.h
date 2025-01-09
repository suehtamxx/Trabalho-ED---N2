#ifndef BLOCOSLOGICOS_H
#define BLOCOSLOGICOS_H

typedef struct blocos
{
    int blocoi, blocof;
    int *eblocoi, *eblocof;
    int status;
}info_blocos;

typedef struct arvore_blocos
{
    struct arvore_blocos *esq, *cen, *dir;
    info_blocos info1, info2;
    int nInfos;
}arv_blocos;

arv_blocos *criar_no(info_blocos *info, arv_blocos *filhoE, arv_blocos *filhoC);
void cadastrar(arv_blocos **no, int qtd);
void inserir_blocos(info_blocos info, arv_blocos **no);

//----Auxiliares da inserir na árvore b3

// Cria um novo nó com a maior info, atualiza o promove e o número de infos
arv_blocos *quebra_no(arv_blocos **no, info_blocos info, info_blocos *promove, arv_blocos *filho);
// Adiciona a info no nó já com 1 info e atualiza o número de infos
arv_blocos *adiciona_chave(arv_blocos *no, info_blocos info, arv_blocos *filho);

int eh_folha_B3(arv_blocos *blocos);

arv_blocos *inserir_arv_B3(arv_blocos **blocos, info_blocos info, info_blocos *promove, arv_blocos **pai);
void imprimir_arvore_B3(arv_blocos *blocos);
void liberar_arv_B3(arv_blocos *no);
//----------------------------------------------------------------------------------------------------


#endif