#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue_
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

QUEUE *create_queue()
{
    QUEUE *fila = (QUEUE *)malloc(sizeof(QUEUE));
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

boolean queue_push(QUEUE *f, int item)
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

int queue_pop(QUEUE *f)
{
    if (f != NULL && !queue_empty(f))
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

int queue_begin(QUEUE *f)
{
    if (f != NULL && !queue_empty(f))
    {
        return f->inicio->item;
    }
    return -1;
}

int fila_fim(QUEUE *f)
{
    if (f != NULL && !queue_empty(f))
    {
        return f->fim->item;
    }
    return -1;
}

int fila_tamanho(QUEUE *f)
{
    if (f != NULL)
        return f->tam;
    else
        return 0;
}

boolean queue_empty(QUEUE *f)
{
    if (f == NULL)
        return ERRO;
    if (f->tam == 0)
        return TRUE;
    else
        return FALSE;
}

//imprime os itens da fila do inicio ao fim
void fila_imprime(QUEUE *f)
{
    if (f == NULL || queue_empty(f))
        return;
    no *n = f->inicio;
    while (n != NULL)
    {
        printf(" %d ", n->item);
        n = n->prox;
    }
    printf("\n");
}

void fila_apagar(QUEUE **f)
{
    while (!queue_empty(*f))
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