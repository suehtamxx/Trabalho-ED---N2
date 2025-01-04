#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"
#include "dicionario.c"

// Função auxiliar para imprimir as informações de uma árvore em inglês
void imprimir_arvore_BST_ingles(arv_ingles *ingles) {
    if (ingles == NULL)
        return;

    // Imprime informações do nó atual (raiz)
    printf("\tIngles: %s\n", ingles->info.ingles);

    // Imprime a lista de unidades associadas
    unidade *unid = ingles->info.l_unidade;
    while (unid != NULL) {
        printf("\t\tUnidade: %d\n", unid->unidade);
        unid = unid->prox;
    }

    // Subárvore esquerda
    imprimir_arvore_BST_ingles(ingles->esq);

    // Subárvore direita
    imprimir_arvore_BST_ingles(ingles->dir);
}

// Função recursiva para imprimir a árvore B3
void imprimir_arvore_23_B3(arv_ptbr *portugues, int nivel) {
    if (portugues == NULL)
        return;

    imprimir_arvore_23_B3(portugues->esq, nivel + 1);
    // Imprime a primeira informação da raiz
    for (int i = 0; i < nivel; i++)
        printf("  ");
    printf("Portugues 1: %s\n", portugues->info1.ptbr);

    // Imprime a árvore de inglês associada à primeira informação
    imprimir_arvore_BST_ingles(portugues->info1.ingles);

    // Se houver uma segunda informação, imprime-a
    if (portugues->nInfos == 2) {
        for (int i = 0; i < nivel; i++)
            printf("  ");
        printf("Portugues 2: %s\n", portugues->info2.ptbr);
        imprimir_arvore_BST_ingles(portugues->info2.ingles);
    }

    // Subárvore esquerda

    // Subárvore central
    imprimir_arvore_23_B3(portugues->cen, nivel + 1);

    // Subárvore direita
    imprimir_arvore_23_B3(portugues->dir, nivel + 1);
}

// Função para imprimir a árvore a partir da raiz

int main()
{
    arv_ptbr *dicionario_portugues;
    dicionario_portugues = NULL;
    
    // Chama a função para ler o arquivo e construir a árvore
    ler_arquivo(&dicionario_portugues);

    // Imprime a árvore para verificar se a leitura está correta
    imprimir_arvore_23_B3(dicionario_portugues, 0);

    liberar_arv_B3(dicionario_portugues);

    return 0;
}
