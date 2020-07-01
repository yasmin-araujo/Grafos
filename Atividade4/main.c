#include <stdio.h>
#include <stdlib.h>
#include "directed_adjacency_list.h"
#define INT_MAX __INT_MAX__

/**
 * Função para descobrir próximo vértice a ser processado
 * 
 * @param time_cost: Array com os custos de tempo para cada cidade
 * @param n: Número total de cidades
 * @param processed: Array marcando quais vértices já foram processados
 * @return city: Vértice não processado com menor custo
*/
int min_cost(int *time_cost, int n, int *processed)
{
    int current_cost = INT_MAX;
    int city = -1;
    for (int i = 0; i < n; i++)
    {
        // Checa se vértice ainda não foi processado e tem um custo menor do que o current_cost
        if (processed[i] == 0 && time_cost[i] < current_cost)
        {
            current_cost = time_cost[i];
            city = i;
        }
    }
    return city;
} 

/**
 * Função que imprime recursivamente todas as cidades do percurso mais rápido
 * 
 * @param city: Número da cidade a ser imprimida - valor da cidade destino ao chamar a função externamente
 * @param predecessor: Array de inteiros marcando os predecessores de cada cidade
*/
void print_cities(int city, int *predecessor)
{
    if (city == -1)
        return;
    print_cities(city[predecessor], predecessor);
    printf("%d ", city);
}

int main()
{
    int n;                // Número de cidades
    int m;                // Número de vôos entre pares de cidades
    int origin_city;      // Cidade de início
    int destination_city; // Cidade destino
    int city1;            // Cidade 1
    int city2;            // Cidade 2
    int flight_time;      // Tempo de duração do voo
    int price;            // Custo da passagem

    // Recebe número de cidades e voos entre os pares
    scanf(" %d", &n);
    scanf(" %d", &m);

    int time_cost[n];   // Array de tempo necessário para cada caminho a partir da origem
    int price_cost[n];  // Array de preço total para cada caminho a partir da origem
    int predecessor[n]; // Array marcando os predecessores de cada cidade
    int processed[n];   // Array marcando quais vértices já foram processados

    // Inicializa todos os custos com o maior valor possível
    for (int i = 0; i < n; i++)
    {
        time_cost[i] = INT_MAX;
        price_cost[i] = 0;
        predecessor[i] = -1;
        processed[i] = 0;
    }

    // Cria lista de adjacências
    DirAdjList *graph = create_graph(n);

    // Leitura dos dados de cada voo
    for (int i = 0; i < m; i++)
    {
        scanf(" %d", &city1);
        scanf(" %d", &city2);
        scanf(" %d", &flight_time);
        scanf(" %d", &price);

        // Insere na lista de adjacências
        insert_edge(graph, city1, city2, flight_time, price);
    }

    scanf(" %d", &origin_city);
    scanf(" %d", &destination_city);

    // Define os custos da cidade de origem como 0
    time_cost[origin_city] = 0;
    price_cost[origin_city] = 0;

    // Processa cada um dos vértices
    for (int i = 0; i < n; i++)
    {
        int vertex = min_cost(time_cost, n, processed); // Vértice a ser processado


        // Checa se já foi processado
        if (processed[vertex] == 1)
            continue;

        // Para cada vértice adjacente
        for (int j = 0; j < get_size(graph, vertex); j++)
        {
            int adj_vertex = get_value(graph, vertex, j); // Vértice adjacente

            // Checa se já foi processado
            if (processed[adj_vertex] == 1)
                continue;

            // Pega valores de tempo e preço entre o vértice e o adjacente
            int time = get_flight_time(graph, vertex, j);
            int price = get_price(graph, vertex, j);

            // Relaxa aresta caso seja necessário e atualiza informações
            if (time_cost[adj_vertex] > time_cost[vertex] + time)
            {
                time_cost[adj_vertex] = time_cost[vertex] + time;
                price_cost[adj_vertex] = price_cost[vertex] + price;
                predecessor[adj_vertex] = vertex;
            }
        }

        // Marca vértice como processado
        processed[vertex] = 1;
    }

    // Imprime valores finais
    print_cities(destination_city, predecessor);
    printf("\n%d %d\n", time_cost[destination_city], price_cost[destination_city]);

    // Libera memória alocada dinamicamente
    delete_graph(graph);
    return 0;
}