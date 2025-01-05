#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubronegra.h"
#include <stddef.h>
#include <sys/types.h>

//1 = black
//2 = red

unidade *criar_no_l_unid()
{
    unidade *no; //Cria nó
    no = (unidade*)malloc(sizeof(unidade)); //Aloca o nó

    no->unidade = 0; //Atribui 0 a unidade
    no->prox = NULL; // Atribui nulo ao próximo

    return no;
}

arv_ingles *cria_no_arv_BB()
{
    arv_ingles *no; //Cria o nó
    no = (arv_ingles*)malloc(sizeof(arv_ingles)); //Aloca o nó

    no->dir = NULL; //Atribui nulo a direita
    no->esq = NULL; //Atribui nulo a esquerda
    no->info.l_unidade = NULL; //Atribui nulo a lista

    return no; //Retorna o nó alocado
}

arv_ptbr *criar_no_arvRN()
{
    arv_ptbr *no;
    no = (arv_ptbr*)malloc(sizeof(arv_ptbr));

    no->dir = NULL;
    no->esq = NULL;
    no->cor = 2;;

    return no;
}

int cor(arv_ptbr *no)
{
    int cor = 0;
    if(no == NULL)
        cor = 1;
    else cor = no->cor;
    return cor;
    
}
void trocaCor(arv_ptbr *no)
{
    if(no != NULL)
    {
        if(cor(no) == 1)
            no->cor = 2;
        else no->cor = 1;

        if(no->esq != NULL)
        {
            if(cor(no->esq) == 1)
                no->esq->cor = 2;
            else no->esq->cor = 1;
        }

        if(no->dir != NULL)
        {
            if(cor(no->dir) == 1)
                no->dir->cor = 2;
            else no->dir->cor = 1;
        }
    }
}

void rotacionaEsq(arv_ptbr **no)
{
    arv_ptbr *aux;
    aux = NULL;

    aux = (*no)->dir;
    (*no)->dir = aux->esq;
    aux->esq = (*no);
    aux->cor = (*no)->cor;
    (*no)->cor = 2;
    (*no) = aux;
}
void rotacionaDir(arv_ptbr **no)
{
    arv_ptbr *aux;
    aux = NULL;

    aux = (*no)->esq;
    (*no)->esq = aux->dir;
    aux->dir = (*no);
    aux->cor = (*no)->cor;
    (*no)->cor = 2;
    (*no) = aux;
}

int inserir_arv_BB(arv_ingles **ingles, arv_ingles *no)
{
    int inseriu = 1;

    if(*ingles == NULL)
        *ingles = no;

    else if (strcmp(no->info.ingles, (*ingles)->info.ingles) == 0)
    {
        unidade *atual;
        atual = (*ingles)->info.l_unidade;

        while (atual != NULL) 
            atual = atual->prox;

        atual = no->info.l_unidade;
    }

    else if(strcmp(no->info.ingles, (*ingles)->info.ingles) > 0)
        inseriu = inserir_arv_BB(&((*ingles)->dir), no);

    else if(strcmp(no->info.ingles, (*ingles)->info.ingles) < 0)
        inseriu = inserir_arv_BB(&((*ingles)->esq), no);

        else inseriu = 0;

    return inseriu;
}

void inserir_arvRN(arv_ptbr **R, arv_ptbr *no)
{
    if(*R == NULL)
        *R = no;

    else{
        if(strcmp(no->info.ptbr, (*R)->info.ptbr) == 0)
        {
            if(inserir_arv_BB(&((*R)->info.ingles), no->info.ingles) == 0) 
                printf("nao foi possivel inserir na arvBB!");
        }
        if(strcmp(no->info.ptbr, (*R)->info.ptbr) < 0)
            inserir_arvRN(&((*R)->esq), no);
        else if(strcmp(no->info.ptbr, (*R)->info.ptbr) > 0)
            inserir_arvRN(&((*R)->dir), no);

    if(cor((*R)->esq) == 1 && cor((*R)->dir) == 2)
        rotacionaEsq(R);
    if(cor((*R)->esq) == 2 && cor((*R)->esq->esq) == 2)
        rotacionaDir(R);
    if(cor((*R)->esq) == 2 && cor((*R)->dir) == 2)
        trocaCor(*R);
    }
}
void move2EsqRed(arv_ptbr **r)
{
    trocaCor(*r);

    if((*r)->dir != NULL){
        if(cor((*r)->dir->esq) == 2)
        {
            rotacionaDir(&((*r)->dir));
            rotacionaEsq(r);
            trocaCor(*r);
        }
    }
}

void move2DirRed(arv_ptbr **r)
{
    trocaCor(*r);
    if((*r)->esq != NULL)
    {
        if(cor((*r)->esq->esq) == 2)
        {
            rotacionaDir(r);
            trocaCor(*r);
        }
    }
}
arv_ptbr *balancear(arv_ptbr *r)
{
    if(r != NULL)
    {
        if(cor(r->esq) == 1 && cor(r->dir) == 2)
            rotacionaEsq(&r);
        if(cor(r->esq) == 2 && cor(r->esq->esq) == 2)
            rotacionaDir(&r);
        if(cor(r->esq) == 2 && cor(r->dir) == 2)
            trocaCor(r);
    }
    return r;
}
arv_ptbr *removeMenor(arv_ptbr *no)
{
    if(no->esq == NULL)
    {
        free(no);
        return NULL;
    }
    if(cor(no->esq) == 1 && cor(no->esq->esq) == 1)
        move2EsqRed(&no);
    
    no->esq = removeMenor(no->esq);

    return balancear(no);
}

arv_ptbr *procuraMenor(arv_ptbr *atual)
{
    arv_ptbr *no1, *no2;
    no1 = atual;
    no2 = atual->esq;
    while(no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

arv_ptbr *remove_no(arv_ptbr *no, char *valor)
{
    if(no != NULL)
    {
        if(strcmp(valor, no->info.ptbr) < 0)
        {
            if(no->esq != NULL && cor(no->esq) == 1 && cor(no->esq->esq) == 1)
            move2EsqRed(&no);

        no->esq = remove_no(no->esq, valor);
        }
        else
        {
            if(cor(no->esq) == 2)
                rotacionaDir(&no);
            if(strcmp(valor, no->info.ptbr) == 0 && (no->dir == NULL))
            {
                free(no);
                return NULL;
            }
            if(no->dir != NULL && cor(no->dir) == 1 && cor(no->dir->esq) == 1)
                move2DirRed(&no);
            if(strcmp(valor, no->info.ptbr) == 0)
            {
                arv_ptbr *menor;
                menor = procuraMenor(no->dir);
                no->info = menor->info;
                no->dir = removeMenor(no->dir);
            }else
                no->dir = remove_no(no->dir, valor);
        }
    }
    return balancear(no);
}

int remove_arvRN(arv_ptbr **no, char *valor)
{
    int verificacao = 0;
    *no = remove_no(*no, valor);

    if(*no != NULL)
    {
        (*no)->cor = 1;
        verificacao = 1;
        
    }
    return verificacao;
}

void ler_arquivo(arv_ptbr **portugues)
{
    FILE *dicionario = fopen("dicionario.txt", "r"); // Abre o arquivo para leitura
    if (dicionario == NULL)
    {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    printf("Arquivo aberto com sucesso.\n");

    char *linha = NULL; // Ponteiro para armazenar cada linha do arquivo
    size_t tam = 0; // Tamanho do buffer da linha
    ssize_t num_c; // Número de caracteres lidos em uma linha
    int unidade_atual = 0; // Unidade atual para as palavras

    // Lê cada linha do arquivo
    while ((num_c = getline(&linha, &tam, dicionario)) != -1)
    {
        linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha

        if (linha[0] == '%') // Identifica uma unidade
        {
            unidade_atual = atoi(&linha[9]); // Assume que a unidade está na posição 9 em diante
            printf("Unidade atual: %d\n", unidade_atual);
        }
        else if (strchr(linha, ':')) // Identifica uma linha com tradução
        {
            char palavra_ingles[100];
            char palavras_portugues[200];

            // Extrai as partes em inglês e português
            if (sscanf(linha, "%[^:]: %[^\n]", palavra_ingles, palavras_portugues) == 2)
            {
                // Remove o ponto e vírgula ao final, se existir
                size_t len = strlen(palavras_portugues);
                if (len > 0 && palavras_portugues[len - 1] == ';')
                    palavras_portugues[len - 1] = '\0';

                printf("Lido: Inglês = %s, Português = %s\n", palavra_ingles, palavras_portugues);

                // Processa cada tradução em português
                char *palavra_port = strtok(palavras_portugues, ",");
                while (palavra_port)
                {
                    // Cria o nó para a árvore binária de busca
                    arv_ingles *novo_no = cria_no_arv_BB();
                    if (novo_no != NULL)
                    {
                        // Preenche informações do nó
                        strcpy(novo_no->info.ingles, palavra_ingles);
                        novo_no->info.l_unidade = criar_no_l_unid();
                        novo_no->info.l_unidade->unidade = unidade_atual;

                        // Remove espaços iniciais na palavra em português
                        while (*palavra_port == ' ') palavra_port++;

                        // Cria a estrutura de informações para a árvore rubro-negra
                        info_ptbr nova_info;
                        strcpy(nova_info.ptbr, palavra_port); // Palavra em português
                        nova_info.ingles = novo_no;

                        // Cria o nó para a árvore rubro-negra
                        arv_ptbr *novo_no_rn = criar_no_arvRN();
                        if (novo_no_rn != NULL)
                        {
                            novo_no_rn->info = nova_info; // Copia a informação
                            printf("Inserindo na árvore: %s -> %s\n", palavra_port, palavra_ingles);
                            inserir_arvRN(portugues, novo_no_rn); // Insere o nó na árvore rubro-negra
                            (*portugues)->cor = 1;
                        }
                        else
                        {
                            printf("Erro ao alocar nó na árvore rubro-negra.\n");
                        }
                    }
                    else
                    {
                        printf("Erro ao alocar nó na árvore binária de busca.\n");
                    }

                    // Avança para a próxima tradução
                    palavra_port = strtok(NULL, ",");
                }
            }
            else
            {
                printf("Erro ao processar linha: %s\n", linha);
            }
        }
    }

    // Libera recursos
    free(linha); // Libera o buffer alocado pelo getline
    fclose(dicionario); // Fecha o arquivo
}

void liberar_lista_unidades(unidade *l_unidade) {
    unidade *atual = l_unidade;
    while (atual != NULL) {
        unidade *prox = atual->prox;
        free(atual);
        atual = prox;
    }
}

void liberar_arv_BB(arv_ingles *no) 
{
    if (no != NULL) {
        // Libera as subárvores recursivamente
            liberar_arv_BB(no->esq);
            liberar_arv_BB(no->dir);

        // Libera a lista de unidades associada ao nó
        liberar_lista_unidades(no->info.l_unidade);

        // Libera o nó atual
        free(no);
    }
}
void liberar_arvRN(arv_ptbr *no)
{
    if(no != NULL)
    {
        liberar_arvRN(no->esq);
        liberar_arvRN(no->dir);

        free(no);
    }
}