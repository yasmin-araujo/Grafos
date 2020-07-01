// TAD Gafos - Lista de Adjacências para Grafo Direcionado
// ADT Graph - Adjacency List for Directed Graph

#include <stdio.h>
#include <stdlib.h>
#include "directed_adjacency_list.h"

/**
 * Struct para lista de adjacências
 * 
 * num_vertex: Número de vértices do gŕafico
 * list: Ponteiro pra lista
*/
struct dir_adjacency_list
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
    int size;
};

/**
 * Struct para nós da lista
 * 
 * value: Valor do nó
 * next: Ponteiro para próximo nó da lista
 * flight_time: Duração do voo
 * price: Preço da viagem
 * total_time: Tempo necessário de viagem desde a cidade de origem
*/
struct list_edge
{
    int value;
    ListEdge *next;
    int flight_time;
    int price;
};

/**
 * Cria um grafo com um determinado número de vértices, onde inicialmente não há arestas.
 * 
 * @param num_vertex: Número de vértices do grafo
 * @return lst: Ponteiro pra estrutura alocada na heap
 */
DirAdjList *create_graph(int num_vertex)
{
    DirAdjList *lst = (DirAdjList *)malloc(sizeof(DirAdjList));
    lst->list = (ListHead **)malloc(num_vertex * sizeof(ListHead *));
    lst->num_vertex = num_vertex;

    // Inicializa todas as listas com um nó cabeça
    for (int i = 0; i < num_vertex; i++)
    {
        ListHead *head = (ListHead *)malloc(sizeof(ListHead));
        head->first = NULL;
        head->last = NULL;
        head->size = 0;
        lst->list[i] = head;
    }

    return lst;
}

/** 
 * Cria uma aresta entre dois vértices do grafo, sendo do primeiro em direção ao segundo
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
 * @param vertex1: Primeiro vértice
 * @param vertex2: Segundo vértice
 * @param flight_time: Duração do voo
 * @param price: Preço da viagem
*/
void insert_edge(DirAdjList *lst, int vertex1, int vertex2, int flight_time, int price)
{
    // Confere se aresta já existe
    ListEdge *runner = lst->list[vertex1]->first;
    while (runner != NULL && runner->value != vertex2)
    {
        runner = runner->next;
    }
    if (runner != NULL)
        return;

    // Insere na lista inicializando os valores
    ListEdge *edge1 = (ListEdge *)malloc(sizeof(ListEdge));
    edge1->value = vertex2;
    edge1->next = NULL;
    edge1->flight_time = flight_time;
    edge1->price = price;

    // Checa se será o primeiro nó da lista
    if (lst->list[vertex1]->first == NULL)
    {
        lst->list[vertex1]->first = edge1;
    }
    else
    {
        lst->list[vertex1]->last->next = edge1;
    }

    lst->list[vertex1]->last = edge1;
    lst->list[vertex1]->size++;
}

/**
 * Remove uma aresta entre 2 vértices do grafo, sendo do primeiro em direção ao segundo
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
 * @param vertex1: Primeiro vértice
 * @param vertex2: Segundo vértice
*/
void remove_edge(DirAdjList *lst, int vertex1, int vertex2)
{
    // Remove da lista
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
    lst->list[vertex1]->size--;
}

/**
 * Retorna o tamanho da lista de adjacências de um vértice
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
 * @param vertex: Vértice a ter adjacências checadas
 * @return value: Tamanho da lista de adj. do vértice recebido
*/
int get_size(DirAdjList *lst, int vertex)
{
    return lst->list[vertex]->size;
}

/**
 * Retorna um valor da lista de adjacências
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
 * @param vertex: Vértice a ter adjacências checadas
 * @param index: Índice do valor a ser retornado
 * @return value: Valor obtido da lista do vertex no index recebido
*/
int get_value(DirAdjList *lst, int vertex, int index)
{
    int value = -1;

    // Checa se o valor pedido existe
    if (lst->list[vertex]->size == 0 || lst->list[vertex]->size <= index)
        return value;

    ListEdge *runner = lst->list[vertex]->first;

    while (index > 0)
    {
        runner = runner->next;
        index--;
    }

    value = runner->value;

    return value;
}

/**
 * Retorna um tempo de voo da lista de adjacências
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
 * @param vertex: Vértice a ter adjacências checadas
 * @param index: Índice do valor a ser retornado
 * @return flight_time: Valor de tempo de voo obtido da lista do vertex no index recebido
*/
int get_flight_time(DirAdjList *lst, int vertex, int index)
{
    int flight_time = -1;

    // Checa se o valor pedido existe
    if (lst->list[vertex]->size == 0 || lst->list[vertex]->size <= index)
        return flight_time;

    ListEdge *runner = lst->list[vertex]->first;

    while (index > 0)
    {
        runner = runner->next;
        index--;
    }

    flight_time = runner->flight_time;

    return flight_time;
}

/**
 * Retorna um preço da lista de adjacências
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
 * @param vertex: Vértice a ter adjacências checadas
 * @param index: Índice do valor a ser retornado
 * @return price: Preço obtido da lista do vertex no index recebido
*/
int get_price(DirAdjList *lst, int vertex, int index)
{
    int price = -1;

    // Checa se o valor pedido existe
    if (lst->list[vertex]->size == 0 || lst->list[vertex]->size <= index)
        return price;

    ListEdge *runner = lst->list[vertex]->first;

    while (index > 0)
    {
        runner = runner->next;
        index--;
    }

    price = runner->price;

    return price;
}

/**
 * Exibe na tela a lista de adjacências do grafo 
 * 
 * @param lst: Ponteiro pra estrutura que contém a lista
*/
void show_adjacency_list(DirAdjList *lst)
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
void delete_graph(DirAdjList *lst)
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