#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue_
{
    node *begin;
    node *end;
    int size;
};

struct node_
{
    int item;
    node *next;
};

QUEUE *create_queue()
{
    QUEUE *queue = (QUEUE *)malloc(sizeof(QUEUE));
    if (queue == NULL)
        printf("\tNão foi possível alocar fila !");

    else
    {
        queue->begin = NULL;
        queue->end = NULL;
        queue->size = 0;
    }

    return queue;
}

boolean queue_push(QUEUE *f, int item)
{
    if (f != NULL)
    {        
        node *new = (node *)malloc(sizeof(node));
        new->item = item;
        new->next = NULL;

        if (f->size == 0) // Primeiro da fila
        {
            f->begin = new;
            f->end = new;
        }
        else
        {
            f->end->next = new;
            f->end = new;
        }

        f->size++;
        return TRUE;
    }
    return FALSE;
}

int queue_pop(QUEUE *f)
{
    if (f != NULL && !queue_empty(f))
    {
        f->size--;

        node *aux = (node *)malloc(sizeof(node));
        aux = f->begin;       // Aux recebe nó a ser retirado que vai sair
        f->begin = aux->next; // Altera inicio da fila

        // Se for o último item da lista
        if (f->end == aux)     
            f->end = NULL;

        int item = aux->item;

        aux->next = NULL;
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
        return f->begin->item;
    }
    return -1;
}

int queue_end(QUEUE *f)
{
    if (f != NULL && !queue_empty(f))
    {
        return f->end->item;
    }
    return -1;
}

int queue_size(QUEUE *f)
{
    if (f != NULL)
        return f->size;
    else
        return 0;
}

boolean queue_empty(QUEUE *f)
{
    if (f == NULL)
        return ERROR;
    if (f->size == 0)
        return TRUE;
    else
        return FALSE;
}

// Imprime os itens da fila do inicio ao fim
void queue_show(QUEUE *f)
{
    if (f == NULL || queue_empty(f))
        return;
    node *n = f->begin;
    while (n != NULL)
    {
        printf(" %d ", n->item);
        n = n->next;
    }
    printf("\n");
}

void queue_delete(QUEUE **f)
{
    while (!queue_empty(*f))
    {
        if (*f != NULL)
        {
            (*f)->size--;

            node *aux = (node *)malloc(sizeof(node));
            aux = (*f)->begin;       //aux é o que vai sair
            (*f)->begin = aux->next; //inicio da fila alterado
            if ((*f)->end == aux)     //se for o ultimo item da lista
                (*f)->end = NULL;

            aux->next = NULL;
            aux->item = -1;
            free(aux);
            aux = NULL;
        }
    }
    free(*f);
    f = NULL;
}