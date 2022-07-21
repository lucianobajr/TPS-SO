#ifndef METRICS_h
#define METRICS_h

#define SIZE 10

#include "../../headers/shared/list.h"

/*
- A fragmentação interna é a perda de espaço dentro de uma área de tamanho fixo.
- A fragmentação externa quando há uma quantidade de área suficiente na memória
para satisfazer a solicitação de memória de um método. no entanto, a solicitação
de memória do processo não pode ser atendida porque a memória oferecida é de forma
não contígua.
*/

typedef struct
{
    int total;
    int denied;
} allocation_request;

typedef struct
{
    list external_fragmentation;
    list nodes_traveled;
    allocation_request allocation_request_metrics;
} metrics;

/*
 * Inicializa a Estrutura de dados
 */
void initialize_metrics(metrics *memory_metrics);

/*
 * Adiciona um fragment exeterno
 */
void add_external_fragment(metrics *memory_metrics, int value);

/*
 * Adiciona o número de nós percorridos na alocação
 */
void add_node_traveled(metrics *memory_metrics, int number_of_nodes);

/*
 * Incrementa total vez que se tem uma requisição de alocação
 */
void increment_total_allocation_request(metrics *memory_metrics);

/*
 * Incrementa total vez que se tem uma requisição de alocação negada
 */
void increment_denied_allocation_request(metrics *memory_metrics);

/*
 * Numero médio de fragmentos externos
 */
int average_number_of_external_fragments(metrics *memory_metrics);

/*
 * Tempo médio de alocação => número médios de nós percorridos na alocação
 */
int average_allocation_time(metrics *memory_metrics);

/*
 * Percentual de vezes que um requisição de alocação é negada
 */
int percentage_of_allocation_request_is_denied(metrics *memory_metrics);

#endif