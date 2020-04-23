#include <stdio.h>
#include "adjacency_list.h"

int main()
{
    int n;    // Número de vértices do grafo
    int m;    // Número de arestas do grafo
    int u, v; // Variáveis auxiliares para ler valores dos vértices
    int q;    // Número de operações a serem executadas
    int q1;   // Operação a ser realizada

    // Leitura de num de vértices e arestas
    scanf("%d", &n);
    scanf("%d", &m);

    // Cria lista
    AdjList *lst = create_graph(n);

    // Recebe vértices conectados a cada aresta e insere na lista
    for (int i = 0; i < m; i++)
    {
        scanf(" %d", &u);
        scanf(" %d", &v);
        insert_edge(lst, u, v);
    }

    // Leitura de número de operações
    scanf("%d", &q);

    // Direciona ação de acordo com cada opção
    for (int i = 0; i < q; i++)
    {
        scanf(" %d", &q1);

        if (q1 == 3)
        {
            show_adjacency_list(lst);
            continue;
        }

        scanf(" %d", &u);
        scanf(" %d", &v);

        if (q1 == 1)
            insert_edge(lst, u, v);
        else if (q1 == 2)
            remove_edge(lst, u, v);
    }

    delete_graph(lst);

    return 0;
}