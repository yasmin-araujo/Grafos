#include <stdio.h>
#include "adjacency_list.h"

int main()
{
    int V; // Número de tarefas para produzir item
    int E; // Número de relações de dependência
    int a, b;
    scanf(" %d", &V);
    scanf(" %d", &E);

    AdjList dependency = create_graph(V);
    AdjList dependents = create_graph(V);

    for(int i = 0; i < E; i ++)
    {
        scanf(" %d", &a);
        scanf(" %d", &b);
        // insere na lista
        insert_edge(dependents, a, b);
        insert_edge(dependency, b, a);
    }

    return 0;
}

/**
 * criar 2 listas de adj
 * - lista 1 : meus requisitos
 * - lista 2 : minhas dependentes
 * 
 * passar na lista 1 armazenando em um array[V] PROX os dados sem requisitos
 * para cada item da lista 2 em cada item armazenado em PROX
 *      ir na lista 1 e retirar o requisito
 * se listas nao vazias retornar -1
 * /