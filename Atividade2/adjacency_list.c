// TAD Gafos - Lista de Adjacências
// ADT Graph - Adjacency List

#include <stdio.h>
#include <stdlib.h>
#include "adjacency_list.h"

/**
 * Struct para lista de adjacências
 * 
 * num_vertex: Número de vértices do gŕafico
 * list: Ponteiro pra lista
*/
struct adjacency_list
{
    int num_vertex;
    ListHead **list;
};

/**
 * Struct para nó cabeça da lista
 * 
 * first: Ponteiro para o primeiro nó
 * last: Ponteiro para o último nó
*/
struct list_head
{
    ListEdge *first;
    ListEdge *last;
};

/**
 * Struct para nós da lista
 * 
 * value: Valor do nó
 * next: Ponteiro para próximo nó da lista
*/
struct list_edge
{
    int value;
    ListEdge *next;
};

/**
 * Cria um grafo com um determinado número de vértices, onde inicialmente não há arestas.
 * 
 * @param num_vertex: Número de vértices do grafo
 * @return lst: Ponteiro pra estrutura alocada na heap
 */
AdjList *create_graph(int num_vertex)
{
    AdjList *lst = (AdjList *)malloc(sizeof(AdjList));
    lst->list = (ListHead **)malloc(num_vertex * sizeof(ListHead *));
    lst->num_vertex = num_vertex;

    // Inicializa todas as listas com um nó cabeça
    for (int i = 0; i < num_vertex; i++)
    {
        ListHead *head = (ListHead *)malloc(sizeof(ListHead));
        head->first = NULL;
        head->last = NULL;
        lst->list[i] = head;
    }

    return lst;
}

/** 
 * Cria uma aresta entre dois vértices do grafo
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
 * @param vertex1: Primeiro vértice
 * @param vertex2: Segundo vértice
*/
void insert_edge(AdjList *lst, int vertex1, int vertex2)
{
    // Confere se aresta já existe
    ListEdge *runner = lst->list[vertex1]->first;
    while(runner != NULL && runner->value != vertex2)
    {
        runner = runner->next;
    }
    if(runner != NULL) return;

    // Insere na primeira lista
    ListEdge *edge1 = (ListEdge *)malloc(sizeof(ListEdge));
    edge1->value = vertex2;
    edge1->next = NULL;

    if (lst->list[vertex1]->first == NULL)
    {
        lst->list[vertex1]->first = edge1;
    }
    else
    {
        lst->list[vertex1]->last->next = edge1;
    }

    lst->list[vertex1]->last = edge1;

    // Insere na segunda lista
    ListEdge *edge2 = (ListEdge *)malloc(sizeof(ListEdge));
    edge2->value = vertex1;
    edge2->next = NULL;

    if (lst->list[vertex2]->first == NULL)
    {
        lst->list[vertex2]->first = edge2;
    }
    else
    {
        lst->list[vertex2]->last->next = edge2;
    }

    lst->list[vertex2]->last = edge2;
}

/**
 * Remove uma aresta entre 2 vértices do grafo
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
 * @param vertex1: Primeiro vértice
 * @param vertex2: Segundo vértice
*/
void remove_edge(AdjList *lst, int vertex1, int vertex2)
{
    // Remove da primeira lista
    ListEdge *delete = NULL;
    ListEdge *runner = lst->list[vertex1]->first;

    // Se não existe lista
    if (runner == NULL)
        return;

    // Se nó a ser retirado é o primeiro
    if (runner->value == vertex2)
    {
        lst->list[vertex1]->first = runner->next;
        free(runner);
    }
    else
    {
        // Procura nó com valor certo e armazena o anterior
        while (runner->next != NULL && runner->next->value != vertex2)
            runner = runner->next;

        // Se não achou
        if (runner->next == NULL)
            return;

        delete = runner->next;
        runner->next = delete->next;
        free(delete);
    }

    // Remove da segunda lista
    runner = lst->list[vertex2]->first;

    // Se nó a ser retirado é o primeiro
    if (runner->value == vertex1)
    {
        lst->list[vertex2]->first = runner->next;
        free(runner);
    }
    else
    {
        // Procura nó com valor certo e armazena o anterior
        while (runner->next != NULL && runner->next->value != vertex1)
            runner = runner->next;

        // Se não achou
        if (runner->next == NULL)
            return;

        delete = runner->next;
        runner->next = delete->next;
        free(delete);
    }
    delete = NULL;
}

/**
 * Exibe na tela a lista de adjacências do grafo 
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
*/
void show_adjacency_list(AdjList *lst)
{
    ListEdge *runner;
    for (int i = 0; i < lst->num_vertex; i++)
    {
        runner = lst->list[i]->first;
        printf("%d: ", i);
        while (runner != NULL)
        {
            printf("%d ", runner->value);
            runner = runner->next;
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Desaloca arestas alocadas dinamicamente de modo recursivo
 * 
 * @param edge: Ponteiro para próximo nó da lista a ser desalocado
*/
void delete_edges(ListEdge *edge)
{
    if (edge == NULL)
        return;
    delete_edges(edge->next);
    free(edge);
    edge = NULL;
}

/**
 * Desaloca lista e estrutura alocadas dinamicamente
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
*/
void delete_graph(AdjList *lst)
{
    for (int i = 0; i < lst->num_vertex; i++)
    {
        delete_edges(lst->list[i]->first);
        free(lst->list[i]);
    }
    free(lst->list);
    free(lst);
    lst = NULL;
}