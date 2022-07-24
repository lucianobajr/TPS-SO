#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H

#include "./simulated_process.h"

typedef enum
{
    EXECUTING,
    BLOCKED,
    READY
} states;

typedef struct
{
    int pid;
    int ppid;
    int *pc;             // referente ao contador do programa do processo simulado
    int *data_structure; // referente ao valor de memoria do processo simulado, ou seja, variaveis que ele tem (N da primeira instrucao)
    int priority;        // definida durante o escalonamento
    states state;        // 1 para em execução, 2 bloqueado e 3 pronto
    int inital_time;     // utiliza o tempo do gerenciador de processos como tempo inicial
    int cpu_time;        // contabiliza quantas instruções foram lidas
    simulated_process *process_reference;
    int memory_index[4]; // um index para cada algoritmo de alocação
} process_table;

#endif