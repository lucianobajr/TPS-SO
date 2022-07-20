#include "../../headers/components/main_memory.h"

void print_main_memory(main_memory memory, int executing)
{
    int total_iterations_allocated = memory.allocated / 5;
    int total_iterations_empty = memory.empty / 5;

    if (executing)
    {
        printf("\e[42m");
    }
    else
    {
        printf("\e[41m");
    }

    for (int i = 0; i < total_iterations_allocated; i++)
    {
        printf(" ");
    }
    printf("[%dkb] \e[0m\e[47m", memory.allocated);

    for (int i = 0; i < 20; i++)
    {
        printf(" ");
    }

    printf("\e[1;30m[%dkb]\e[0m \e[0m\n", memory.empty);
}

void generate()
{
    FILE *file;
    const char *path = "data/memory.dat";

    file = fopen(path, "w");
    int *memory = (int *)malloc(sizeof(int) * SIZE);

    srand(time(NULL));

    for (int i = 0; i < MEMSIZE; i++)
    {
        // Increment any random element
        // from the array by 1
        memory[rand() % SIZE]++;
    }

    for (int i = 0; i < SIZE; i++)
    {
        i == SIZE - 1 ? fprintf(file, "%d %d", i, memory[i]) : fprintf(file, "%d %d\n", i, memory[i]);
    }

    fclose(file);
}

main_memory *init_main_memory()
{
    main_memory *memory = (main_memory *)malloc(SIZE * sizeof(main_memory));

    FILE *file;
    const char *path = "data/memory.dat";
    int index, value;

    file = fopen(path, "r");

    while (!feof(file))
    {
        fscanf(file, "%d %d", &index, &value);
        memory[index].empty = value;
        memory[index].allocated = 0;
    }

    return memory;
}

void next_fit(int blockSize[], int m, int processSize[], int n)
{
    // Stores block id of the block allocated to a
    // process
    int allocation[n], j = 0;

    // Initially no block is assigned to any process
    memset(allocation, -1, sizeof(allocation));

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i = 0; i < n; i++)
    {

        // Do not start from beginning
        while (j < m)
        {

            if (blockSize[j] >= processSize[i])
            {

                // allocate block j to p[i] process
                allocation[i] = j;

                // Reduce available memory in this block.
                blockSize[j] -= processSize[i];

                break;
            }

            // mod m will help in traversing the blocks from
            // starting block after we reach the end.
            j = (j + 1) % m;
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {

        printf(" %d \t\t %d \t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }
}

int highest_value_in_memory(main_memory *memory)
{
    int highest_value = memory[0].empty + memory[0].allocated;

    for (int i = 1; i < SIZE; i++)
    {
        if ((memory[i].empty + memory[i].allocated) > highest_value)
        {
            highest_value = memory[i].empty + memory[i].allocated;
        }
    }

    // retorna o maior valor + 40%
    return highest_value + ((highest_value * 40) / 100);
}

/*------------------------ALGORITMOS DE ALOCAÇÃO------------------------*/
void first_fit(main_memory *memory, int process_size)
{

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i = 0; i < SIZE; i++) // here, n -> number of processes
    {

        // allocated > 0 ?
        if (memory[i].empty >= process_size && memory[i].allocated == 0)
        {
            memory[i].empty = memory[i].empty - process_size;
            memory[i].allocated = process_size;

            break; // go to the next process in the queue
        }
    }
}

void best_fit_test(main_memory *memory, int process_size)
{

    int best_index = -1;
    for (int j = 0; j < SIZE; j++)
    {
        if (memory[j].allocated == 0 && (memory[j].empty >= process_size))
        {
            if (best_index == -1)
            {
                best_index = j;
            }
            else if (memory[j].empty < memory[best_index].empty)
            {
                best_index = j;
            }
        }
    }

    // If we could find a block for current process
    if (best_index != -1)
    {
        memory[best_index].empty = memory[best_index].empty - process_size;
        memory[best_index].allocated = process_size;
    }
}

void worst_fit(main_memory *memory, int process_size)
{

    int best_index = -1;
    for (int j = 0; j < SIZE; j++)
    {
        if (memory[j].allocated == 0 && (memory[j].empty >= process_size))
        {
            if (best_index == -1)
            {
                best_index = j;
            }
            else if (memory[j].empty >= memory[best_index].empty)
            {
                best_index = j;
            }
        }
    }

    // If we could find a block for current process
    if (best_index != -1)
    {
        memory[best_index].empty = memory[best_index].empty - process_size;
        memory[best_index].allocated = process_size;
    }
}