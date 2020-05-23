#ifndef LISTAADJ_H
#define LISTAADJ_H

typedef struct _no NO;
typedef struct _lista LISTA;
typedef struct _grafo GRAFO;

GRAFO *criagrafo(int n);

void inserearesta(GRAFO *grafo, int i, int j);

void removearesta(GRAFO *grafo, int i, int j);

int tamanho_lista(GRAFO *grafo, int vertice);

int get_valor(GRAFO *grafo, int vertice, int indice);

void exibelistaadj(GRAFO *grafo);

void deletagrafo(GRAFO *grafo);

#endif