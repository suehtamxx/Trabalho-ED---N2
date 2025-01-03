#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"
#include "dicionario.c"

// Função auxiliar para imprimir as informações de uma árvore em inglês
void imprimir_arvore_ingles(arv_ingles *ingles)
{
    if (ingles == NULL)
        return;

    printf("\tIngles: %s\n", ingles->info.ingles);

    unidade *unid;
    unid = ingles->info.l_unidade;
    while (unid != NULL)
    {
        printf("\t\tUnidade: %d\n", unid->unidade);
        unid = unid->prox;
    }
}

// Função recursiva para imprimir a árvore B3
void imprimir_arvore_B3(arv_ptbr *portugues, int nivel)
{
    if (portugues == NULL)
        return;

    imprimir_arvore_B3(portugues->esq, nivel + 1);
    
    // Indentação para representar o nível da árvore
    for (int i = 0; i < nivel; i++)
        printf("  ");

    // Imprime a informação do primeiro campo
    printf("Portugues 1: %s\n", portugues->info1.ptbr);
    imprimir_arvore_ingles(portugues->info1.ingles);

    // Se houver segunda informação, imprime-a
    if (portugues->nInfos == 2)
    {
        for (int i = 0; i < nivel; i++)
            printf("  ");
        printf("Portugues 2: %s\n", portugues->info2.ptbr);
        imprimir_arvore_ingles(portugues->info2.ingles);
    }

    // Chamada recursiva para os filhos esquerdo, central e direito
    imprimir_arvore_B3(portugues->cen, nivel + 1);
    imprimir_arvore_B3(portugues->dir, nivel + 1);
}

// Função para imprimir a árvore a partir da raiz
void imprimir_arvore_completa(arv_ptbr *portugues)
{
    imprimir_arvore_B3(portugues, 0);
}

int main()
{
    arv_ptbr *dicionario_portugues;
    dicionario_portugues = NULL;
    
    // Chama a função para ler o arquivo e construir a árvore
    ler_arquivo(&dicionario_portugues);

    // Imprime a árvore para verificar se a leitura está correta
    imprimir_arvore_completa(dicionario_portugues);

    liberar_arv_B3(dicionario_portugues);

    return 0;
}
