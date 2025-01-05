#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"
#include "dicionario.c"


int main()
{
    arv_ptbr *dicionario_portugues;
    dicionario_portugues = NULL;
    
    // Chama a função para ler o arquivo e construir a árvore
    ler_arquivo(&dicionario_portugues);

    // Imprime a árvore para verificar se a leitura está correta
    //imprimir_arvore_completa(dicionario_portugues);

    liberar_arv_B3(dicionario_portugues);

    return 0;
}
