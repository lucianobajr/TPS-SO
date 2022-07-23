#ifndef MAIN_MEMORY_h
#define MAIN_MEMORY_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../headers/metrics/metrics.h"
#include "../../headers/shared/queue.h"

// 2*1024
// Processo tem 2 MB de memória
#define MEMSIZE 2048 // em KBs
#define SIZE 10

typedef struct
{
    int empty;
    int allocated;
} main_memory;

/*
 * gera o arquivo .dat de memoria
 */
void generate();

/*
 * retorna um único vetor, para armazenar as  variáveis dos
 * processos simulados.
 */
main_memory *init_main_memory();

/*
 *  Irá alocar o processo no primeiro espaço livre do array
 */
void first_fit(main_memory *memory, metrics *memory_metrics, queue *denied_process, int process_size);

/*
 * Firt fit porém ele começa como o primeiro ajuste para encontrar
 * uma partição livre, mas quando chamado na próxima vez, ele
 * começa a procurar de onde parou, não desde o início.
 */
void next_fit(main_memory *memory, metrics *memory_metrics, queue *denied_process, int process_size, int *next_fit_index);

/*
 * Irá percorrer toda a lista para encontrar o espaço que
 * desperdiçará o mínimo possível
 */
void best_fit(main_memory *memory, metrics *memory_metrics, queue *denied_process, int process_size);

/*
 * Irá percorrer toda a lista para encontrar o espaço que
 * “desperdiçará” o máximo possível, esse espaço desperdiçado
 * pode ser depois alocado para outro processo
 */
void worst_fit(main_memory *memory, metrics *memory_metrics, queue *denied_process, int process_size);

/*
 * Printa o texto da antes de printar a memória
 */
void print_text_main_memory();

/*
 * printa o espaço de memória
 */
void print_main_memory(main_memory *memory);

/*
 * Retorna o valor de teto do range aleatório do processo
 * maior valor + 40% do maior valor
 */
int highest_value_in_memory(main_memory *memory);

/*
 * A fragmentação externa quando há uma quantidade de área suficiente na memória para
 * satisfazer a solicitação de memória de um método. no entanto, a solicitação de memória
 * do processo não pode ser atendida porque a memória oferecida é de forma não contígua.
 */
int external_fragments(main_memory *memory);

/*
 * Desaloca um processo na memória
 */
void deallocate(main_memory *memory, int index);

/*
 * Printa a memória com todas as métricas
 */
void print_memory_with_metrics(main_memory *memory, metrics *memory_metrics);

/*
 * Menu para escolha dos algoritmos de alocação
 */
void menu_main_memory();

#endif