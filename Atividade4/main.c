#include <stdio.h>
#include <stdlib.h>
#include "directed_adjacency_list.h"
#include <limits.h>
// #define INT_MAX 5000

// Retorna cidade não processada com menor custo
int min(int *time_cost, int n, int *processed)
{
    int current_cost = INT_MAX;
    int city = -1;
    for (int i = 0; i < n; i++)
    {
        if (processed[i] == 0 && time_cost[i] < current_cost)
        {
            current_cost = time_cost[i];
            city = i;
        }
    }
    return city;
}

// imprime cidades do percurso
void print_cities(int city, int *predecessor)
{
    if(city == -1) return;
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

    // Array de custos para cada caminho a partir da origem
    int time_cost[n];
    int price_cost[n];
    int predecessor[n];
    int processed[n];

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

    // Define o custo da cidade de origem como 0
    time_cost[origin_city] = 0;
    price_cost[origin_city] = 0;

    int vertex; // Vértice a ser procesado

    for (int i = 0; i < n; i++)
    {
        vertex = min(time_cost, n, processed);
        if(processed[vertex] == 1) continue;

        // printf("\nNo vértice %d: ", vertex);

        for(int j = 0; j < get_size(graph, vertex); j++)
        {
            int adj_vertex = get_value(graph, vertex, j);

            if(processed[adj_vertex] == 1) continue;
            
            // printf(" Relaxa aresta %d de %d para ", adj_vertex, time_cost[adj_vertex]);

            int time =  get_flight_time(graph, vertex, j);
            int price = get_price(graph, vertex, j);
            if(time_cost[adj_vertex] > time_cost[vertex] + time)
            {
                time_cost[adj_vertex] = time_cost[vertex] + time;
                price_cost[adj_vertex] = price_cost[vertex] + price;
                predecessor[adj_vertex] = vertex;
            }
            // printf("%d (%d)\n", time_cost[adj_vertex], time_cost[vertex] + time);
        }
        processed[vertex] = 1;
    }

    // lista de cidades na rotina ótima
    int total_price = 0;
    print_cities(destination_city, predecessor);
    printf("\n%d %d\n", time_cost[destination_city], price_cost[destination_city]);
    
    delete_graph(graph);
    // tempo total da viagem e custo da viagem
    return 0;
}