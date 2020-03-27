// TAD Gafos - Matriz de Adjacências
// ADT Graph - Adjacency Matrix

#include <stdio.h>
#include <stdlib.h>
#include "adjacency_matrix.h"

/**
 * Struct para matriz de adjacências
 * 
 * num_vertex: Número de vértices do gŕafico
 * matrix: Ponteiro pra matriz
*/
struct adjacency_matrix
{
    int num_vertex;
    int **matrix;
};

/**
 * Cria um grafo com um determinado número de vértices, onde inicialmente não há arestas.
 * 
 * @param num_vertex: Número de vértices do grafo
 * @return mat: Ponteiro pra estrutura alocada na heap
 */
AdjMatrix *create_graph(int num_vertex)
{
    AdjMatrix *mat = (AdjMatrix *)malloc(sizeof(AdjMatrix));
    mat->matrix = (int **)malloc(num_vertex * sizeof(int *));
    mat->num_vertex = num_vertex;

    // Aloca dinamicamente cada linha da matriz
    for (int i = 0; i < num_vertex; i++)
    {
        mat->matrix[i] = (int *)calloc(num_vertex, sizeof(int));
    }

    return mat;
}

/** 
 * Cria uma aresta entre dois vértices do grafo
 * 
 * @param mat: Ponteiro pra estrutura que contém a matriz
 * @param vertex1: Primeiro vértice
 * @param vertex2: Segundo vértice
*/
void insert_edge(AdjMatrix *mat, int vertex1, int vertex2)
{
    mat->matrix[vertex1][vertex2] = 1;
    mat->matrix[vertex2][vertex1] = 1;
}

/**
 * Remove uma aresta entre 2 vértices do grafo
 * 
 * @param mat: Ponteiro pra estrutura que contém a matriz
 * @param vertex1: Primeiro vértice
 * @param vertex2: Segundo vértice
*/
void remove_edge(AdjMatrix *mat, int vertex1, int vertex2)
{
    mat->matrix[vertex1][vertex2] = 0;
    mat->matrix[vertex2][vertex1] = 0;
}

/**
 * Exibe na tela a matriz de adjacências do grafo 
 * 
 * @param mat: Ponteiro pra estrutura que contém a matriz
*/ 
void show_adjacency_matrix(AdjMatrix *mat)
{
    for (int i = 0; i < mat->num_vertex; i++)
    {
        for (int j = 0; j < mat->num_vertex; j++)
        {
            printf("%d ", mat->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Desaloca matriz e estrutura alocadas dinamicamente
 * 
 * @param mat: Ponteiro pra estrutura que contém a matriz
*/
void delete_graph(AdjMatrix *mat)
{
    for (int i = 0; i < mat->num_vertex; i++)
    {
        free(mat->matrix[i]);
    }
    free(mat->matrix);
    free(mat);
}