#include "../headers/components/main_memory.h"

int main(int argc, char const *argv[])
{
    generate();
    main_memory *memory = init_main_memory();

    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        print_main_memory(memory[i], rand() % 2);
    }

    return 0;
}