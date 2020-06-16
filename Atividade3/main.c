#include <stdio.h>
#include <stdlib.h>
#include "directed_adjacency_list.h"
#include "queue.h"

int main()
{
    int V;        // Número de tarefas para produzir item
    int E;        // Número de relações de dependência
    int a, b;     // Vértices onde b depende de a
    int time = 0; // Menor tempo necessário para a execução de todas as tarefas

    // Leitura de dados
    scanf(" %d", &V);
    scanf(" %d", &E);

    // Estruturas de dados auxiliares
    DirAdjList *dependents = create_graph(V);              // Lista de Adjacencias para os dependentes de cada vértice
    int *requirements = (int *)calloc(V, sizeof(int));  // Array de inteiros para número de requisitos de cada vértice
    QUEUE *queue = create_queue();                      // Fila auxiliar para valores a serem processados ao mesmo tempo

    // Leitura das relações de dependência
    for (int i = 0; i < E; i++)
    {
        scanf(" %d", &a);
        scanf(" %d", &b);
        
        // Atualiza lista de adj. e array de requisitos
        insert_edge(dependents, a, b); 
        requirements[b]++;
    }

    // No pior caso não teremos tarefas executadas em paralelo, tendo como menor tempo o número total de vértices
    for (int j = 0; j < V; j++)
    {
        // Procura vértices sem requisitos
        for (int i = 0; i < V; i++)
        {
            // Se vértice não tem requisitos ele é adicionado na fila e marcado como processado
            if (requirements[i] == 0)
            {
                requirements[i] = -1;
                queue_push(queue, i);
            }
        }

        // Caso fila esteja vazia todos os vértices possiveis já foram processados
        if (queue_empty(queue))
            break;

        // Processa vértices encontrados
        while (!queue_empty(queue))
        {
            int v = queue_pop(queue);
            int i = 0;
            int next = get_value(dependents, v, i++);

            // Para cada nó adjacente decrementa o array de requisitos
            while (next != -1)
            {
                requirements[next]--;
                next = get_value(dependents, v, i++);
            }
        }
        time++;
    }

    // Checa se existe algum ciclo no grafo - array com algum valor diferente de -1
    for (int i = 0; i < V; i++)
    {
        if (requirements[i] != -1)
        {
            time = -1;
            break;
        }
    }

    printf("%d", time);

    free(requirements);
    delete_graph(dependents);
    return 0;
}