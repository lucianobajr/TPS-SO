#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./instructions.h"

#define INSTRUCTIONS_SIZE 1000
#define UNDEFINED -1

typedef enum
{
    BLOCKED,
    READY,
    EXECUTING
} states;

typedef struct
{
    int pid;
    int ppid;
    int pc;
    int priority;
    states state;
    float inital_time;
    float cpu_time;
    instructions instructions[INSTRUCTIONS_SIZE];
    int size;
} process;

/*
 * Inicializa o processo
 */
void init_process(process *process, int pid, int ppid);

/*
 * Cria um processo
 */
process *create_process(int pid, int ppid);

/*
 * Imprime um processo
 */
void print_process(process *process);

#endif