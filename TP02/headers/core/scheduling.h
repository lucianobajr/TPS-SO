#ifndef SCHEDULING_H
#define SCHEDULING_H

#define UNDEFINED -1
#define QUANTUM_PRIORITY_0 1
#define QUANTUM_PRIORITY_1 2
#define QUANTUM_PRIORITY_2 4
#define QUANTUM_PRIORITY_3 8

#include "../../headers/shared/queue.h"


// Escalonamento de múltiplas filas com classes de prioridade
typedef struct
{
    queue *first;
    queue *second;
    queue *third;
    queue *fourth;
} scheduling;

/*
 * Inicializa o escalonador
 */
void init_scheduling(scheduling *scheduling);

/*
 * Começa a escalonar
 */
void do_scheduling(scheduling *scheduling, int index, int priority);

/*
 * Desenfileira o escalonador
 */
int dequeue_scheduling(scheduling *scheduling);
#endif