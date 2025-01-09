#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blocoslogicos.h"
#include "blocoslogicos.c"

#define Ocupado 0;
#define Livre 1;
arv_blocos *blocos;
int qtd = 0;
int *numeroF = 0;
void imprimir_arvore_B3(arv_blocos *blocos) 
{
    if (blocos != NULL)
    {
        imprimir_arvore_B3(blocos->esq);

        printf("Inicial: %d | Final: %d - %d\n", blocos->info1.blocoi, blocos->info1.blocof, blocos->info1.status);

        if (blocos->nInfos == 2)
        {
            printf("Inicial: %d | Final: %d - %d\n", blocos->info2.blocoi, blocos->info2.blocof, blocos->info2.status);
            imprimir_arvore_B3(blocos->dir); 
        }
        imprimir_arvore_B3(blocos->cen);
    }
}
int main()
{
    do{
        printf("Informe a quantidade de blocos a serem alocados(maior que 0):\n");
        scanf(" %d", &qtd);
        if(qtd <= 0)printf("Valor inválido. Informe um valor maior que 0\n");
    }while(qtd <= 0);

    cadastrar(&blocos, qtd);

    imprimir_arvore_B3(blocos);
    
    liberar_arv_B3(blocos);
}

//void inserir_no(no, info, qtd);
