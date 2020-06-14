#ifndef ADJ_LIST_H
#define ADJ_LIST_H

typedef struct adjacency_list AdjList;

typedef struct list_head ListHead;

typedef struct list_edge ListEdge;

AdjList* create_graph(int num_vertex);

void insert_edge(AdjList* lst, int vertex1, int vertex2);

void remove_edge(AdjList* lst, int vertex1, int vertex2);

int get_value(AdjList *lst, int vertex, int index);

void show_adjacency_list(AdjList *lst);

void delete_graph(AdjList *lst);

#endif