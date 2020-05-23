#ifndef FILA_H
#define FILA_H

#define boolean int
#define TRUE 1
#define FALSE 0
#define ERRO -1

typedef struct fila_ FILA;
typedef struct no_ no;

FILA *fila_criar();
boolean fila_entra(FILA *f, int item);
int fila_sai(FILA *f);
int fila_frente(FILA *f);
int fila_fim(FILA *f);
int fila_tamanho(FILA *f);
boolean fila_vazia(FILA *f);
void fila_imprime(FILA *f);
void fila_apagar(FILA **f);

#endif