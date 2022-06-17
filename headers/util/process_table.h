#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H

#define PROCESS_TABLE_SIZE 1000

#include "./process.h"

typedef struct
{
    process *process;
    int size;
} process_table;

/*
 * Cria uma Tabela de processos
 */
process_table *create_process_table();

/*
 * Printa a Tabela de processos
 */
void print_process_table(process_table *process_table);

/*
 * Insere um processo na Tabela e retorna a posição onde foi inserida
 */

void insert_process_in_table(process_table *process_table, process process);

#endif