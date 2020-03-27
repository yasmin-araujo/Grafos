#include <stdio.h>
#include "adjacency_matrix.h"

int main()
{
    int n;      // Número de vértices do grafo
    int m;      // Número de arestas do grafo
    int u, v;   // Variáveis auxiliares para ler valores dos vértices
    int q;      // Número de operações a serem executadas
    int q1;     // Operação a ser realizada
    int v1, v2; //

    // Leitura de num de vértices e arestas
    scanf("%d", &n);
    scanf("%d", &m);

    // Cria matriz
    AdjMatrix *mat = create_graph(n);

    // Recebe vértices conectados a cada aresta e insere na matriz
    for (int i = 0; i < m; i++)
    {
        scanf(" %d", &u);
        scanf(" %d", &v);
        insert_edge(mat, u, v);
    }

    // Leitura de número de operações
    scanf("%d", &q);

    // Direciona ação de acordo com cada opção
    for (int i = 0; i < q; i++)
    {
        scanf(" %d", &q1);

        if (q1 == 3)
        {
            show_adjacency_matrix(mat);
            continue;
        }

        scanf(" %d", &u);
        scanf(" %d", &v);

        if (q1 == 1)
            insert_edge(mat, u, v);
        else if (q1 == 2)
            remove_edge(mat, u, v);
    }

    delete_graph(mat);

    return 0;
}