#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>

typedef struct node *pointer;
typedef struct node
{
    int index;// armazena os indices dos processos que estao em determinado estado
    pointer next;
} node;

typedef struct
{
    pointer front;
    pointer back;
} queue;

/*
* inicializa a fila
*/
void init_queue(queue *queue);

/*
* verifica se a fila esta vazia
*/
int verify_if_is_empty(queue *queue);

/*
* enfilera
*/
int to_queue(queue *queue, int index);

/*
* desenfilera
*/
int dequeue(queue *queue);

/*
* imprime a fila
*/
void print_queue(queue *queue);

/*
* ajusta os valores da fila
*/
void adjust_queue_values(queue *queue, int value);

#endif