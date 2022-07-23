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

    queue denied_process;
    init_queue(&denied_process);

    menu_main_memory();

    printf("\n");
    for (int i = 0; i < 6; i++)
    {
        int process_size = 1 + rand() % highest_value;

        printf("VALOR = %d\n", process_size);

        best_fit(memory, &memory_metrics, &denied_process, process_size);
        add_external_fragment(&memory_metrics, external_fragments(memory));
    }

    print_main_memory(memory);

    print_memory_with_metrics(memory, &memory_metrics);

    return 0;
}