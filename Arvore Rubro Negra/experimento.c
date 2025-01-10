#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "rubronegra.h"
#include "rubronegra.c"

#define Repeticao 30

void buscar_palavras(arv_ptbr *raiz, char *palavra, char *caminho, int *encontrou)
{
    if(raiz != NULL)
    {
        if (strcmp(raiz->info.ptbr, palavra) == 0)
        {
            *encontrou = 1;
            strcat(caminho, raiz->info.ptbr);    
        }

        if (*encontrou == 0)
        {
            if (strcmp(palavra, raiz->info.ptbr) < 0)
            {
                strcat(caminho, raiz->info.ptbr);
                strcat(caminho, " -> ");
                buscar_palavras(raiz->esq, palavra, caminho, encontrou);
            }

            else if (strcmp(palavra, raiz->info.ptbr) < 0)            
            {
                strcat(caminho, raiz->info.ptbr);
                strcat(caminho, " -> ");
                buscar_palavras(raiz->dir, palavra, caminho, encontrou);
            }
        }
    }
}
void calcular_tempo(arv_ptbr *raiz, char palavras[][100])
{
    LARGE_INTEGER inicio, fim, frequencia;
    
    QueryPerformanceFrequency(&frequencia);  // Obtém a frequência do contador de alta precisão

    for (int i = 0; i < Repeticao; i++)
    {
        char caminho[1000] = "";
        int encontrou = 0;

        QueryPerformanceCounter(&inicio);  // Captura o início do contador

        buscar_palavras(raiz, palavras[i], caminho, &encontrou);

        QueryPerformanceCounter(&fim);  // Captura o fim do contador

        // Calcula o tempo em milissegundos
        double tempo = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / frequencia.QuadPart;

        printf("\n------------------------------\n");
        printf("Busca: %d\n", i);
        printf("Palavra: %s\n", palavras[i]);
        printf("Caminho percorrido: %s\n", caminho);
        printf("Encontrada: %s\n", encontrou ? "Sim" : "Nao");
        printf("Tempo gasto: %.6f milissegundos\n\n", tempo);
    }
}
void preencher_matriz_arvore(arv_ptbr *raiz, char palavras[][100], int *posicao)
{
    if (raiz != NULL)
    {
        preencher_matriz_arvore(raiz->esq, palavras, posicao);
        
        strcpy(palavras[*posicao], raiz->info.ptbr);
        (*posicao)++;         
        
        preencher_matriz_arvore(raiz->dir, palavras, posicao);
    }
}
void preencher_restante_matriz(char palavras[][100], int *posicao)
{
    strcpy(palavras[(*posicao)++], "aviao");
    strcpy(palavras[(*posicao)++], "casa");
    strcpy(palavras[(*posicao)++], "janela");
}

int main ()
{
    arv_ptbr *dicionario;
    dicionario = NULL;
    int posicao = 0;
    char palavras[30][100];

    ler_arquivo(&dicionario);

    preencher_matriz_arvore(dicionario, palavras, &posicao);
    preencher_restante_matriz(palavras, &posicao);
    preencher_matriz_arvore(dicionario, palavras, &posicao);
    preencher_matriz_arvore(dicionario, palavras, &posicao);

    // printf("Palavras:\n");
    // for (int i = 0; i < 30; i++)
    //     printf("%d - %s\n", i, palavras[i]);

    calcular_tempo(dicionario, palavras);
    
    liberar_arv_RN(dicionario);

    return 0;
}