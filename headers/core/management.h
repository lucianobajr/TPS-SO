#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#define SCHEDULER 2 //    1 => MULTIPLE_QUEUES ; 2 => FCFS
#define DEBUG 1

#include "./scheduling.h"
#include "../components/cpu.h"
#include "../components/process_table.h"
#include "../log/log.h"

typedef enum
{
    MULTIPLE_QUEUES,
    FCFS
} scheduller_policy;

typedef struct
{
    CPU cpu;
    process_table *process_table; // É um vetor 
    int executing_state;          // armazena o indice do processo do vetor da TabelaDeProcessos que esta em execucao
    queue ready;                  // enfilera os indices dos processos em estado pronto
    queue blocked;                // enfileira os indices dos processos em estado de bloqueio
    scheduling scheduler;       
    int time;                    // incrementado a cada instrução lida
    scheduller_policy type_escalation_policy;
} management;

/*
 * Inicializa o Gerenciador de Processos
 */
void init_management(management *management, char *file_name, int size, scheduller_policy type_escalation_policy);

/*
 * Leitura do arquivo de instruções
 */
char *read_instructions_file(CPU *cpu);

/*
 * Cria um novo processo
 */
void create_new_process(management *management, int number_of_instructions, int size, int pid);

/*
 * Carrega o processo na CPU
 */
void load_cpu_process(management *management, int index_next_process);

/*
 * Trocar contexto => Copia o estado do processo simulado em execução da CPU para a Tabela de Processos
 * E copiar o estado do recém escalonado processo simulado da tabela de processos para a CPU
 * Dispatcher
 */
void change_context(management *management, int index_next_process, int initial_state_process);

/*
 * Substituir a imagem atual de um processo
 */
void replace_current_image_process(management *management, char *instruction);

/*
 * Simulado por uma imagem nova de processo
 */
void end_simulated_process(management *management, int *size, int *max_time);

/*
 * Imprime o Gerenciador de Processos
 */
void print_management(management *management, int size, int number_of_process, int longer_time);

/*
 * Retorna 1 caso o Quantum do processo tenha atingido o limite e 0 caso o contrário
 */
int verify_quantum(management *management);

/*
 * Multiple-Level Queues 
 */
void multiple_queues(management management);
/*
 * First Come First Serve (FCFS)
 */
void first_come_first_serve(management management);

#endif