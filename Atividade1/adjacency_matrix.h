#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

typedef struct adjacency_matrix AdjMatrix;

AdjMatrix* create_graph(int num_vertex);

void insert_edge(AdjMatrix* mat, int vertex1, int vertex2);

void remove_edge(AdjMatrix* mat, int vertex1, int vertex2);

void show_adjacency_matrix();

void delete_graph(AdjMatrix *mat);

#endif