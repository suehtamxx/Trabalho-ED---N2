#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubronegra.h"
#include "rubronegra.c"

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
void imprimir_arvore_RN(arv_ptbr *portugues) 
{
    if (portugues != NULL)
    {
        imprimir_arvore_RN(portugues->esq);

        printf("Portugues: %s\n", portugues->info.ptbr);
        imprimir_arvore_ingles(portugues->info.ingles);

        imprimir_arvore_RN(portugues->dir);
    }
}

void aux_remover_ingles_unidade(arv_ingles **ingles, char *palavra, int unid)
{
    if (*ingles != NULL)
    {
        aux_remover_ingles_unidade(&(*ingles)->esq, palavra, unid);

        if (strcmp((*ingles)->info.ingles, palavra) == 0)
        {
            printf("Encontrada palavra '%s' no no. Verificando unidades...\n", palavra);

            unidade **atual;
            atual = &((*ingles)->info.l_unidade);

            while (*atual != NULL)
            {
                printf("Verificando unidade: %d\n", (*atual)->unidade);
                if ((*atual)->unidade == unid)
                {
                    unidade *remover = *atual;
                    printf("Removendo unidade: %d\n", (*atual)->unidade);
                    *atual = (*atual)->prox;
                    free(remover); 
                }
                else
                    atual = &((*atual)->prox);                
            }
        }
        
        if ((*ingles)->info.l_unidade == NULL)
        {
            int resultado;
            resultado = remover_arv_BB(ingles, *ingles);
            if (resultado == 1) printf("No com palavra '%s' removido da arvore binaria.\n", (*ingles)->info.ingles);
        }

        aux_remover_ingles_unidade(&(*ingles)->dir, palavra, unid);
    }
}
void remover_ingles_unidade(arv_ptbr **portugues, arv_ptbr *no, char *palavra, int unid)
{
    printf("\nRemovendo palavra: %s\n", palavra);

    if (*portugues != NULL)
    {
        remover_ingles_unidade(&(*portugues)->esq, no, palavra, unid);

        aux_remover_ingles_unidade(&no->info.ingles, palavra, unid);
        if (no->info.ingles == NULL)
        {
            printf("No '%s' nao tem mais palavras. Removendo da arvore rubro-negra...\n", no->info.ptbr);
            int resultado;
            resultado = remove_arvRN(portugues, no->info.ptbr);
            if (resultado == 1) printf("Palavra '%s' removida da arvore rubro-negra.\n", no->info.ptbr);
            else printf("Falha ao remover palavra '%s' da arvore rubro-negra.\n", no->info.ptbr);
        }
        remover_ingles_unidade(&(*portugues)->dir, no, palavra, unid);
    }
}

int main() 
{
    arv_ptbr *dicionario_portugues;
    dicionario_portugues = NULL;

    ler_arquivo(&dicionario_portugues);
    
    printf("\n_______________________\n");
    remover_ingles_unidade(&dicionario_portugues, dicionario_portugues, "Bus", 1);

    imprimir_arvore_RN(dicionario_portugues);

    return 0;
}