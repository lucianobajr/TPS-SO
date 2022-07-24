#ifndef DOMAIN_h
#define DOMAIN_h

#define TRUE 1
#define FALSE 0

#define FIRST_FIT 1
#define NEXT_FIT 2
#define BEST_FIT 3
#define WORST_FIT 4

#include "../../headers/components/main_memory.h"
#include "../../headers/components/process_table.h"
#include "../../headers/metrics/metrics.h"
#include "../../headers/shared/queue.h"
#include "../../headers/shared/list.h"

typedef struct
{
    list allocation_algorithms; // lista com os algoritmos de alocação a serem utilizados

    main_memory *memory_first_fit; // memória principal => first fit
    main_memory *memory_next_fit;  // memória principal => next fit
    main_memory *memory_best_fit;  // memória principal => best fit
    main_memory *memory_worst_fit; // memória principal => worst fit

    metrics memory_metrics_first_fit; // métricas => first fit
    metrics memory_metrics_next_fit;  // métricas => next fit
    metrics memory_metrics_best_fit;  // métricas => best fit
    metrics memory_metrics_worst_fit; // métricas => worst fit

    queue denied_process_first_fit; // fila de processos negados => first fit
    queue denied_process_next_fit;  // fila de processos negados => next fit
    queue denied_process_best_fit;  // fila de processos negados => best fit
    queue denied_process_worst_fit; // fila de processos negados => worst fit

    int next_fit_index;
} domain;

/*
 * Inicializa a camada de domínio do Gerenciador de processos
 */
void init_domain(domain *process_manager_domain);

/*
 * Printa quais algoritmos de alocação estão sendo utilizados
 */
void allocation_algorithms_used(domain *process_manager_domain);

/*
 * Aloca um novo processo na memória
 */
void allocate_new_process(domain *process_manager_domain, process_table *new_process, int first_process);

/*
 * Printa as memórias
 */
void print_memories(domain *process_manager_domain);

/*
 * Printa as métricas
 */
void print_metrics(domain *process_manager_domain);

/*
 * Retorna o valor mais alto que um processo poderá ter
 */
int highest_value_by_allocation_algorithms(domain *process_manager_domain, int using_40_percent);

/*
 * Quando houvesse a liberação de memória por um processo, a alocação deste processo poderia ser tentada novamente.
 */
void relocate_process(domain *process_manager_domain);

#endif