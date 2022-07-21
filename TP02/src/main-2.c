#include "../headers/components/main_memory.h"
#include "../headers/log/log.h"

int main(int argc, char const *argv[])
{

    generate();
    main_memory *memory = init_main_memory();

    metrics memory_metrics;
    initialize_metrics(&memory_metrics);

    srand(time(NULL));

    int highest_value = highest_value_in_memory(memory);

    for (int i = 0; i < 6; i++)
    {
        int process_size = 1 + rand() % highest_value;

        printf("VALOR = %d\n", process_size);

        first_fit(memory, &memory_metrics, process_size);
        add_external_fragment(&memory_metrics, external_fragments(memory));
    }

    for (int i = 0; i < SIZE; i++)
    {
        print_main_memory(memory[i], 1);
    }

    printf("\nNUMERO MÉDIO DE FRAGMENTOS INTERNOS = %.2f\n", average_number_of_external_fragments(&memory_metrics));

    printf("\nTEMPO MÉDIO DE ALOCAÇÃO = %.2f\n", average_allocation_time(&memory_metrics));

    printf("\nPORCENTAGEM DA SOLICITAÇÃO DE ALOCAÇÃO É NEGADA = %.2f%%\n", percentage_of_allocation_request_is_denied(&memory_metrics));

    return 0;
}