#include <stdio.h>
#include <stdlib.h>
#include "adjacency_list.h"
#include "queue.h"

int main()
{
    int V; // Número de tarefas para produzir item
    int E; // Número de relações de dependência
    int a, b;   // b depende de a
    int time = 0; // Menor tempo necessário para a execução de todas as tarefas

    scanf(" %d", &V);
    scanf(" %d", &E);

    AdjList *dependents = create_graph(V);
    int* requirements = (int*) calloc(V, sizeof(int));
    QUEUE* queue = create_queue();

    for(int i = 0; i < E; i ++)
    {
        scanf(" %d", &a);
        scanf(" %d", &b);
        // insere na lista
        insert_edge(dependents, a, b);  // a aponta pra b (b como adj de a)
        requirements[b]++;
    }

    // No pior caso não teremos tarefas executadas em paralelo, tendo como menor tempo o número total de vértices
    for(int j = 0; j < V; j++)
    {
        // Procura vértices sem requisitos
        for(int i = 0; i < V; i++)
        {
            // Se vértice não tem requisitos ele é adicionado na fila e marcado como processado
            if(requirements[i] == 0)
            {
                requirements[i] = -1;
                queue_push(queue, i);
            }
        }

        // Caso fila esteja vazia todos os vértices possiveis já foram processados
        if(queue_empty(queue)) break;

        // Processa vértices encontrados
        while(!queue_empty(queue))
        {
            int v = queue_pop(queue);
            int next = get_value(dependents, v, 0);
            while(next != -1)
            {
                requirements[next]--;
                next = get_value(dependents, v, 0);
            }
        }
        time++;
    }

    // Checa se existe algum ciclo no grafo
    for(int i = 0; i < V; i++)
    {
        if(requirements[i] != -1)
        {
            time = -1;
            break;
        }
    }

    printf("%d", time);

    free(requirements);
    return 0;
}

/** *
 * criar uma lista de adj -> meus dependentes (dependents)
 * criar um array tamanho V inicializado com 0 (requirements) -> ir somando qtd de requisitos que ele tem
 *      cada vez que processar um vertice decrementa 1 de todos os adjacentes
 * criar uma fila para colocar os nós a serem processados na rodada
 * em cada rodada processar todos os que tem valor 0 no array
 *
 * procura os 0 no array
 * insere na fila e deixa como -1
 * enquanto a fila nao esta vazia
 *      tira o primeiro valor 
 *      processa -> decrementa todos os adj
 * time++
 * 
 * checa array inteiro -> se algum != -1 -> retorna -1 (existe um ciclo)
 */