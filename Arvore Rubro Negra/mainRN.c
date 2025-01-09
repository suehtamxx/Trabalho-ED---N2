#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubronegra.h"
#include "rubronegra.c"

void imprimir_arvore_BB(arv_ingles *ingles) 
{
    if (ingles != NULL) 
    {
        printf("\tInglês: %s\n", ingles->info.ingles);

        unidade *unid = ingles->info.l_unidade;
        while (unid != NULL) 
        {
            printf("\t\tUnidade: %d\n", unid->unidade);
            unid = unid->prox;
        }

        imprimir_arvore_BB(ingles->esq);
        imprimir_arvore_BB(ingles->dir);
    }
}

void imprimir_arvore_RN(arv_ptbr *raiz) 
{
    if (raiz != NULL) 
    {
        printf("\t[%s] (%s)\n", raiz->info.ptbr, raiz->cor == 1 ? "PRETO" : "VERMELHO");

        imprimir_arvore_BB(raiz->info.ingles);
        imprimir_arvore_RN(raiz->esq);
        imprimir_arvore_RN(raiz->dir);
    }
}

int main()
{
    int op = 0, unid = 0;
    char palavra[100];
    arv_ptbr *dicionario_portugues;
    dicionario_portugues = NULL;
    
    ler_arquivo(&dicionario_portugues);
    
    do
    {
        printf("\n==================== MENU ====================\n");
        printf("1. Imprimir todas as palavras de acordo com a unidade\n");
        printf("2. Imprimir todas as palavras em ingles de acordo com a palavra em portugues.\n");
        printf("3. Remover uma palavra em ingles de acordo com a unidade.\n");
        printf("4. Remover uma palavra em portugues de acordo com a unidade.\n");
        printf("5. Sair.\n");

        printf("\nInforme uma opcao: ");
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
            printf("\nInforme uma unidade: ");
            scanf(" %d", &unid);

            printf("\n----Resultado:\n");
            imprimir_unidade_RN(dicionario_portugues, unid);

            break;

        case 2:
            printf("\nInforme uma palavra em portugues: ");
            scanf(" %[^\n]", palavra);

            printf("\n----Resultado:\n");
            imprimir_ptbr_RN(dicionario_portugues, palavra);

            break;

        case 3:
            printf("\nInforme uma palavra em ingles que deseja remover: ");
            scanf(" %[^\n]", palavra);

            printf("\nInforme de qual unidade: ");
            scanf(" %d", &unid);

            remover_ingles_RN(&dicionario_portugues, &dicionario_portugues, palavra, unid);
            imprimir_arvore_RN(dicionario_portugues);

            break;
        case 4:
            printf("\nInforme uma palavra em portugues que deseja remover: ");
            scanf(" %[^\n]", palavra);

            printf("\nInforme de qual unidade: ");
            scanf(" %d", &unid);

            remover_portugues_RN(&dicionario_portugues, &dicionario_portugues, palavra, unid);
            imprimir_arvore_RN(dicionario_portugues);

            break;

        default:
            printf("\nSaindo...");
            break;
        }

    } while (op != 5);
    
    liberar_arv_RN(dicionario_portugues);

    return 0;
}