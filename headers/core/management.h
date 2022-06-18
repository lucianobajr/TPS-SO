#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "../../headers/core/scheduling.h"
#include "../../headers/shared/queue.h"
#include "../../headers/util/cpu.h"
#include "../../headers/util/process_table.h"

typedef enum
{
    MULTIPLE_QUEUES,
    FCFS
} escalation_policy;

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
    escalation_policy type_escalation_policy
} management;

/*
 * Inicializa o Gerenciador de Processos
 */
void init_management(management *management, char *file_name, int size, int type_escalation_policy);

/*
 * Leitura do arquivo de instruções
 */
char *read_instructions_file(cpu *cpu);

/*
 * Cria um novo processo
 */
void create_new_process(management *management, int number_of_instructions, int size, pid_t pid);

/*
 * Substituir a imagem atual de um processo
 */
void replace_current_image_process(management *management, char *instruction);

/*
 * Trocar contexto => Copia o estado do processo simulado em execução da CPU para a Tabela de Processos
 * E copiar o estado do recém escalonado processo simulado da tabela de processos para a CPU
 * Dispatcher
*/
void change_context(management *management, int index_next_process, int initial_state_process);

/*
 * Carrega o processo na CPU
 */
void load_cpu_process(management *management, int index_next_process);

/*
 * Simulado por uma imagem nova de processo
 */
void end_simulated_process(management *management, int *size, int *max_time);

/*
 * Retorna 1 caso o Quantum do processo tenha atingido o limite e 0 caso o contrário
 */
int verify_quantum(management *management);

/*
 * Imprime o Gerenciador de Processos
 */
void print_management(management *management, int size, int number_of_process, int longer_time);

#endif