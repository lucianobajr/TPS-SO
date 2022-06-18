#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "../../headers/util/cpu.h"
#include "../../headers/util/process_table.h"

#include "../../headers/shared/queue.h"

#include "../../headers/core/scheduling.h"

// Gerenciador de Processos
typedef struct
{
    cpu cpu;
    process_table *process_table;
    int executing_state;
    queue ready;
    queue blocked;
    int time;
    scheduling scheduling;
} management;

/*
 * Inicializa o Gerenciador de Processos
 */
void init_management(management *management, char *file_name, int size);

/*
 * Leitura do arquivo de instruções
 */
char *read_instructions_file(cpu *cpu);

/*
 * Cria um novo processo
 */
void create_new_process(management *management, int number_of_instructions, int size, pid_t pid, int scheduling_type);

#endif