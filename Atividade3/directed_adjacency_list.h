#ifndef D_ADJ_LIST_H
#define D_ADJ_LIST_H

typedef struct dir_adjacency_list DirAdjList;

typedef struct list_head ListHead;

typedef struct list_edge ListEdge;

DirAdjList* create_graph(int num_vertex);

void insert_edge(DirAdjList* lst, int vertex1, int vertex2);

void remove_edge(DirAdjList* lst, int vertex1, int vertex2);

int get_value(DirAdjList *lst, int vertex, int index);

void show_adjacency_list(DirAdjList *lst);

void delete_graph(DirAdjList *lst);

#endif