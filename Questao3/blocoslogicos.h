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
void concatena(arv_blocos **raiz, arv_blocos **no);
arv_blocos *buscar_no(arv_blocos *no, int status, int qtd);
//----Auxiliares da inserir na árvore b3

// Cria um novo nó com a maior info, atualiza o promove e o número de infos
arv_blocos *quebra_no(arv_blocos **no, info_blocos info, info_blocos *promove, arv_blocos *filho);
// Adiciona a info no nó já com 1 info e atualiza o número de infos
arv_blocos *adiciona_chave(arv_blocos *no, info_blocos info, arv_blocos *filho);

int eh_folha_B3(arv_blocos *blocos);

arv_blocos *inserir_arv_B3(arv_blocos **blocos, info_blocos info, info_blocos *promove, arv_blocos **pai);
void imprimir_arvore_B3(arv_blocos *blocos);
arv_blocos *busca_MenorNo(arv_blocos **no);
arv_blocos *busca_MaiorNo(arv_blocos **no);
void ocupa_espaco(arv_blocos **no ,arv_blocos **raiz, int *qtd, int *verificacao, int status);
int remove_esq_folha(arv_blocos **portugues, arv_blocos **pai);
int remove_centro_folha(arv_blocos **blocos, arv_blocos **pai);
void remove_dir_folha(arv_blocos **blocos, arv_blocos **pai);
int remove_folha(arv_blocos **no, arv_blocos **blocos, int inicial);
int remove_no_filho_folhas(arv_blocos **blocos, int inicial);
int balanceia_arv_B3(arv_blocos **blocos, int desbalanceamento);
int remove_menor_no(arv_blocos **pai_aux, arv_blocos **no, info_blocos *promove);
int remover_arv_B3(arv_blocos **pai, arv_blocos **blocos, int inicial, int *flag);

void libera_no(arv_blocos **no);
void liberar_arv_B3(arv_blocos *no);
//----------------------------------------------------------------------------------------------------


#endif