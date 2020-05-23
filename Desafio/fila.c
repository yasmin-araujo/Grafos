#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila_
{
    no *inicio;
    no *fim;
    int tam;
};

struct no_
{
    int item;
    no *prox;
};

FILA *fila_criar()
{
    FILA *fila = (FILA *)malloc(sizeof(FILA));
    if (fila == NULL)
        printf("\tNão foi possível alocar fila !");

    else
    {
        fila->inicio = NULL;
        fila->fim = NULL;
        fila->tam = 0;
    }

    return fila;
}

boolean fila_entra(FILA *f, int item)
{
    if (f != NULL)
    {
        no *novo = (no *)malloc(sizeof(no));
        novo->item = item;
        novo->prox = NULL;
        if (f->tam == 0) //primeiro da fila
        {
            f->inicio = novo;
            f->fim = novo;
        }
        else
        {
            f->fim->prox = novo;
            f->fim = novo;
        }

        f->tam++;
        return TRUE;
    }
    return FALSE;
}

int fila_sai(FILA *f)
{
    if (f != NULL && !fila_vazia(f))
    {
        f->tam--;

        no *aux = (no *)malloc(sizeof(no));
        aux = f->inicio;       //aux é o que vai sair
        f->inicio = aux->prox; //inicio da fila alterado
        if (f->fim == aux)     //se for o ultimo item da lista
            f->fim = NULL;

        int item = aux->item;

        aux->prox = NULL;
        aux->item = -1;
        free(aux);
        aux = NULL;

        return item;
    }
    return -1;
}

int fila_frente(FILA *f)
{
    if (f != NULL && !fila_vazia(f))
    {
        return f->inicio->item;
    }
    return -1;
}

int fila_fim(FILA *f)
{
    if (f != NULL && !fila_vazia(f))
    {
        return f->fim->item;
    }
    return -1;
}

int fila_tamanho(FILA *f)
{
    if (f != NULL)
        return f->tam;
    else
        return 0;
}

boolean fila_vazia(FILA *f)
{
    if (f == NULL)
        return ERRO;
    if (f->tam == 0)
        return TRUE;
    else
        return FALSE;
}

//imprime os itens da fila do inicio ao fim
void fila_imprime(FILA *f)
{
    if (f == NULL || fila_vazia(f))
        return;
    no *n = f->inicio;
    while (n != NULL)
    {
        printf(" %d ", n->item);
        n = n->prox;
    }
    printf("\n");
}

void fila_apagar(FILA **f)
{
    while (!fila_vazia(*f))
    {
        if (*f != NULL)
        {
            (*f)->tam--;

            no *aux = (no *)malloc(sizeof(no));
            aux = (*f)->inicio;       //aux é o que vai sair
            (*f)->inicio = aux->prox; //inicio da fila alterado
            if ((*f)->fim == aux)     //se for o ultimo item da lista
                (*f)->fim = NULL;

            aux->prox = NULL;
            aux->item = -1;
            free(aux);
            aux = NULL;
        }
    }
    free(*f);
    f = NULL;
}