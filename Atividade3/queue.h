#ifndef QUEUE_H
#define QUEUE_H

#define boolean int
#define TRUE 1
#define FALSE 0
#define ERROR -1

typedef struct queue_ QUEUE;
typedef struct node_ node;

QUEUE *create_queue();
boolean queue_push(QUEUE *f, int item);
int queue_pop(QUEUE *f);
int queue_begin(QUEUE *f);
int queue_end(QUEUE *f);
int queue_size(QUEUE *f);
boolean queue_empty(QUEUE *f);
void queue_show(QUEUE *f);
void queue_delete(QUEUE **f);

#endif