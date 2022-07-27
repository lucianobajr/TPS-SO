#ifndef QUEUE_CUSTOM_H
#define QUEUE_CUSTOM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>

typedef struct node_custom *pointer_custom;
typedef struct node_custom
{
    int index; // armazena os indices dos processos que estao em determinado estado
    int size;  // tamanhos dos processos
    pointer_custom next;
} node_custom;

typedef struct
{
    pointer_custom front;
    pointer_custom back;
} queue_custom;

/*
* inicializa a fila
*/
void init_queue_custom(queue_custom *queue);

/*
* verifica se a fila esta vazia
*/
int verify_if_is_empty_custom(queue_custom *queue);

/*
* enfilera
*/
int to_queue_custom(queue_custom *queue, int index, int size);

/*
* desenfilera
*/
void dequeue_custom(queue_custom *queue,int *value);

/*
* imprime a fila
*/
void print_queue_custom(queue_custom *queue);

#endif