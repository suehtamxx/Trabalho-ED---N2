#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blocoslogicos.h"
#include "blocoslogicos.c"

#define Ocupado 0;
#define Livre 1;

void imprimir_arvore_B3(arv_blocos *blocos) 
{
    if (blocos != NULL)
    {

        if(blocos->esq != NULL)
            imprimir_arvore_B3(blocos->esq);

        printf("Inicial: %d | Final: %d - %d(INFO 1)\n", blocos->info1.blocoi, blocos->info1.blocof, blocos->info1.status);

        imprimir_arvore_B3(blocos->cen);

        if (blocos->nInfos == 2)
        {
            printf("Inicial: %d | Final: %d - %d(INFO 2)\n", blocos->info2.blocoi, blocos->info2.blocof, blocos->info2.status);
            imprimir_arvore_B3(blocos->dir); 
        }
    }
}
int main()
{
    arv_blocos *blocos;
    blocos = NULL;
    int verificacao = 0, qtd = 0, op = 0;
    
    do{
        printf("Informe a quantidade de blocos a serem alocados(maior que 0):\n");
        scanf(" %d", &qtd);
        if(qtd <= 0)printf("Valor inválido. Informe um valor maior que 0\n");
    }while(qtd <= 0);

    
    cadastrar(&blocos, qtd);
    imprimir_arvore_B3(blocos);
    
    do{


        printf("\n----------MENU----------\n");
        printf("1 - Alocar No \n");
        printf("2 - Desalocar No \n");
        printf("0 - Sair \n");
        printf("Digite a opcao:\n");
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
            printf("Informe a quantidade de nós para alocar:\n");
            scanf(" %d", &qtd);
            ocupa_espaco(&blocos, &blocos, &qtd, &verificacao, 1);
            imprimir_arvore_B3(blocos);
            break;
        case 2:
            printf("Informe a quantiade de nos para desalocar:\n");
            scanf(" %d", &qtd);
            ocupa_espaco(&blocos, &blocos, &qtd, &verificacao, 0);
            imprimir_arvore_B3(blocos);
            break;
        default:
            printf("Tchau...\n");
            break;
        }
    }while(op != 0);

    imprimir_arvore_B3(blocos);
    
    liberar_arv_B3(blocos);
}

//void inserir_no(no, info, qtd);
