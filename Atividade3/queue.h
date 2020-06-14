#ifndef QUEUE_H
#define QUEUE_H

#define boolean int
#define TRUE 1
#define FALSE 0
#define ERRO -1

typedef struct queue_ QUEUE;
typedef struct no_ no;

QUEUE *create_queue();
boolean queue_push(QUEUE *f, int item);
int queue_pop(QUEUE *f);
int queue_begin(QUEUE *f);
int fila_fim(QUEUE *f);
int fila_tamanho(QUEUE *f);
boolean queue_empty(QUEUE *f);
void fila_imprime(QUEUE *f);
void fila_apagar(QUEUE **f);

#endif