#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"
#include "dicionario.c"

void imprimir_arvore_ingles(arv_ingles *ingles) 
{
    if (ingles != NULL)
    {
        printf("\tIngles: %s\n", ingles->info.ingles);

        unidade *unid;
        unid = ingles->info.l_unidade;
        while (unid != NULL) 
        {
            printf("\t\tUnidade: %d\n", unid->unidade);
            unid = unid->prox;
        }
        printf("\n");

        imprimir_arvore_ingles(ingles->esq);
        imprimir_arvore_ingles(ingles->dir);
    }
}
void imprimir_arvore_B3(arv_ptbr *portugues) 
{
    if (portugues != NULL)
    {
        imprimir_arvore_B3(portugues->esq);

        printf("Portugues: %s\n", portugues->info1.ptbr);
        imprimir_arvore_ingles(portugues->info1.ingles);

        if (portugues->nInfos == 2)
        {
            printf("Portugues: %s\n", portugues->info2.ptbr);
            imprimir_arvore_ingles(portugues->info2.ingles);
            imprimir_arvore_B3(portugues->dir); //DESCOBRI O ERRO DA IMPRESSÂO AQUI            //
        }
        
        imprimir_arvore_B3(portugues->cen);
    }
}

int main()
{
    arv_ptbr *dicionario_portugues;
    dicionario_portugues = NULL;
    
    // Chama a função para ler o arquivo e construir a árvore
    ler_arquivo(&dicionario_portugues);

    // Imprime a árvore para verificar se a leitura está correta
    imprimir_arvore_B3(dicionario_portugues);

    printf("\n_______________________\n");
    //imprimir_unid_B3(dicionario_portugues, 2);
    //imprimir_ptbr_B3(dicionario_portugues, "bicicleta");

    liberar_arv_B3(dicionario_portugues);

    return 0;
}
