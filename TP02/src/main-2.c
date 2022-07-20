#include "../headers/components/main_memory.h"
#include "../headers/log/log.h"

int main(int argc, char const *argv[])
{
    generate();
    main_memory *memory = init_main_memory();

    srand(time(NULL));

    int highest_value = highest_value_in_memory(memory);

    for (int i = 0; i < 6; i++)
    {
        int process_size = rand() % highest_value;

        printf("VALOR = %d\n", process_size);

        worst_fit_test(memory, process_size);
    }

    for (int i = 0; i < SIZE; i++)
    {
        print_main_memory(memory[i], 1);
    }

    return 0;
}