#include "../../headers/components/main_memory.h"
#include "../../headers/log/log.h"

void print_text_main_memory()
{
    printf("=============================================================================\n");
    printf("|                             MEMÓRIA PRINCIPAL                             |\n");
    printf("=============================================================================\n");
}

void print_main_memory(main_memory *memory)
{
    print_text_main_memory();

    int total_iterations_allocated, total_iterations_empty;

    for (int i = 0; i < SIZE; i++)
    {
        total_iterations_allocated = memory[i].allocated / 5;
        total_iterations_empty = memory[i].empty / 5;

        printf("\e[42m");

        for (int i = 0; i < total_iterations_allocated; i++)
        {
            printf(" ");
        }
        printf(" [%dkb] \e[0m\e[47m", memory[i].allocated);

        for (int i = 0; i < 20; i++)
        {
            printf(" ");
        }

        printf("\e[1;30m [%dkb] \e[0m \e[0m \n", memory[i].empty);
    }
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
        // incrementa 1KB de memória por vez
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

void first_fit(main_memory *memory, metrics *memory_metrics, queue *denied_process, int process_size)
{

    int index = -1;

    increment_total_allocation_request(memory_metrics);

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i = 0; i < SIZE; i++) // here, n -> number of processes
    {

        // allocated > 0 ?
        if (memory[i].empty >= process_size && memory[i].allocated == 0)
        {
            index = i;
            break; // go to the next process in the queue
        }
    }

    if (index != -1)
    {
        memory[index].empty = memory[index].empty - process_size;
        memory[index].allocated = process_size;

        add_node_traveled(memory_metrics, index);
    }
    else
    {
        to_queue(denied_process,process_size);
        increment_denied_allocation_request(memory_metrics);
    }
}

void best_fit(main_memory *memory, metrics *memory_metrics, queue *denied_process, int process_size)
{
    int index = -1;

    increment_total_allocation_request(memory_metrics);

    for (int j = 0; j < SIZE; j++)
    {
        if (memory[j].allocated == 0 && (memory[j].empty >= process_size))
        {
            if (index == -1)
            {
                index = j;
            }
            else if (memory[j].empty < memory[index].empty)
            {
                index = j;
            }
        }
    }

    // If we could find a block for current process
    if (index != -1)
    {
        memory[index].empty = memory[index].empty - process_size;
        memory[index].allocated = process_size;

        add_node_traveled(memory_metrics, index);
    }
    else
    {
        to_queue(denied_process,process_size);
        increment_denied_allocation_request(memory_metrics);
    }
}

void worst_fit(main_memory *memory, metrics *memory_metrics, queue *denied_process, int process_size)
{
    int index = -1;

    increment_total_allocation_request(memory_metrics);

    for (int j = 0; j < SIZE; j++)
    {
        if (memory[j].allocated == 0 && (memory[j].empty >= process_size))
        {
            if (index == -1)
            {
                index = j;
            }
            else if (memory[j].empty >= memory[index].empty)
            {
                index = j;
            }
        }
    }

    // If we could find a block for current process
    if (index != -1)
    {
        memory[index].empty = memory[index].empty - process_size;
        memory[index].allocated = process_size;

        add_node_traveled(memory_metrics, index);
    }
    else
    {
        to_queue(denied_process,process_size);
        increment_denied_allocation_request(memory_metrics);
    }
}

int external_fragments(main_memory *memory)
{
    int total = 0;

    for (int i = 0; i < SIZE; i++)
    {
        total += memory[i].empty;
    }

    return total;
}

void deallocate(main_memory *memory, int index)
{
    memory[index].empty = memory[index].empty + memory[index].allocated;
    memory[index].allocated = 0;
}

void print_memory_with_metrics(main_memory *memory, metrics *memory_metrics)
{
    float one = average_number_of_external_fragments(memory_metrics);
    float two = average_allocation_time(memory_metrics);
    float three = percentage_of_allocation_request_is_denied(memory_metrics);

    printf("\n");
    printf("\t     ====================================\n");
    printf("\t     |       \e[1;93mPERFORMANCE PARAMETERS  \033[0m   |\n");
    printf("\t     ====================================\n");
    printf("\t     | \033[38;5;196m    (1)   \033[0m | \033[38;5;196m  (2)  \033[0m | \033[38;5;196m   (3)  \033[0m  |\n");
    printf("\033[0m");
    printf("\t     ====================================\n");

    three > 0.00 ? printf("\t     | \e[1;97m  %.2f \033[0m | \e[1;97m  %.2f \033[0m | \e[1;97m  %2.2f%% \033[0m |\n", one, two, three) : printf("\t     | \e[1;97m  %.2f  \033[0m| \e[1;97m  %.2f \033[0m | \e[1;97m  %2.2f%%  \033[0m |\n", one, two, three);
    printf("\033[0m");
    printf("\t     ====================================\n\n");

    printf("==============================================================\n");
    printf("|                           \e[1;93mLEGEND\033[0m                           |\n");
    printf("==============================================================\n");
    printf("| \033[38;5;196m  (1) \e[1;97m - AVERAGE NUMBER OF EXTERNAL FRAGMENTS \033[0m             |\n");
    printf("==============================================================\n");
    printf("| \033[38;5;196m  (2) \e[1;97m - AVERAGE ALLOCATION TIME  \033[0m                         |\n");
    printf("==============================================================\n");
    printf("| \033[38;5;196m  (3) \e[1;97m - PERCENTAGE OF THE ALLOCATION REQUEST IS DENIED  \033[0m  |\n");
    printf("==============================================================\n");
}

void menu_main_memory()
{

    int i;
    fputs(" ", stdout);
    for (i = 0; i < 113; i++)
    {
        fputs("_", stdout);
    }
    printf("\n|");
    for (i = 0; i < 113; i++)
    {
        fputs(" ", stdout);
    }
    printf("|\n|");
    for (i = 0; i < 46; i++)
    {
        fputs(" ", stdout);
    }
    printf("ALLOCATION ALGORITHMS");
    for (i = 0; i < 46; i++)
    {
        fputs(" ", stdout);
    }
    printf("|");
    printf("\n");
    printf("|");
    for (i = 0; i < 113; i++)
    {
        fputs("_", stdout);
    }
    printf("|\n|");
    for (i = 0; i < 113; i++)
    {
        fputs(" ", stdout);
    }

    printf("|\n|");
    for (i = 0; i < 27; i++)
    {
        fputs(" ", stdout);
    }
    printf("(1) first fit, (2) next fit, (3) best fit and (4) worst fit");
    for (i = 0; i < 27; i++)
    {
        fputs(" ", stdout);
    }

    printf("|\n|");
    for (i = 0; i < 113; i++)
    {
        fputs(" ", stdout);
    }

    printf("|\n|");
    for (i = 0; i < 13; i++)
    {
        fputs(" ", stdout);
    }
    printf("obs: if you want to use more than one algorithm, separate the numbers with a blank space");
    for (i = 0; i < 12; i++)
    {
        fputs(" ", stdout);
    }

    printf("|\n|");
    for (i = 0; i < 113; i++)
    {
        fputs("_", stdout);
    }
    printf("|");
    printf("\n");
    printf("----------> ");
    fflush(stdin);
}