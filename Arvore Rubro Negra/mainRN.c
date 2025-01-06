#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubronegra.h"
#include "rubronegra.c"

// Prototipos das funções necessárias
void imprimir_arvore_BST_ingles(arv_ingles *ingles) {
    if (ingles == NULL)
        return;

    // Imprime informações do nó atual
    printf("\tInglês: %s\n", ingles->info.ingles);

    // Imprime as unidades associadas
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
void imprimir_arvore_rubro_negra(arv_ptbr *raiz, int nivel) {
    if (raiz == NULL)
        return;

    // Indentação de acordo com o nível da árvore
    for (int i = 0; i < nivel; i++)
        printf("    ");
    printf("[%s] (%s)\n", raiz->info.ptbr, raiz->cor == 1 ? "PRETO" : "VERMELHO");

    imprimir_arvore_BST_ingles(raiz->info.ingles);

    imprimir_arvore_rubro_negra(raiz->esq, nivel + 1);
    imprimir_arvore_rubro_negra(raiz->dir, nivel + 1);
}

int main() {
    arv_ptbr *dicionario_portugues = NULL;
    arv_ingles *arvore_binaria = NULL;

    // Lê o arquivo e constrói as árvores
    ler_arquivo(&dicionario_portugues);

    char *palavra;
    palavra = (char *)malloc(sizeof(char));
    int unidade = 0;
     // Imprime a árvore Rubro-Negra (português) e Binária (inglês)
    //printf("Árvore Rubro-Negra de Português:\n");
    //imprimir_arvore_rubro_negra(dicionario_portugues, 0);

    //printf("informe um elemento para ser removido: ");
    //scanf(" %s", valor);

    //verificacao = remove_arvRN(&dicionario_portugues, valor);
    //if(verificacao == 1)printf("elemento removido");
    //else printf("elemento nao foi removido");

    printf("Informe a palavra em ingles: \n");
    scanf("%[^\n]", palavra);
    printf("informe a unidade: \n");
    scanf("%d", &unidade);

    funcaoauxIII(&dicionario_portugues, &dicionario_portugues, palavra, unidade);

    imprimir_arvore_rubro_negra(dicionario_portugues, 0);


    // Liberação de memória seria realizada aqui, caso necessário
    liberar_arvRN(dicionario_portugues);
    liberar_arv_BB(arvore_binaria);

    return 0;
}