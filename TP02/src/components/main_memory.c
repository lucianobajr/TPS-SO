#include "../../headers/components/main_memory.h"

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
    char *line = (char *)malloc(20 * sizeof(char));
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

void first_fit(int blockSize[], int m, int processSize[], int n)
{
    int i, j;
    // Stores block id of the
    // block allocated to a process
    int allocation[n];

    // Initially no block is assigned to any process
    for (i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (i = 0; i < n; i++) // here, n -> number of processes
    {
        for (j = 0; j < m; j++) // here, m -> number of blocks
        {
            if (blockSize[j] >= processSize[i])
            {
                // allocating block j to the ith process
                allocation[i] = j;

                // Reduce available memory in this block.
                blockSize[j] -= processSize[i];

                break; // go to the next process in the queue
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %i\t\t\t", i + 1);
        printf("%i\t\t\t\t", processSize[i]);
        if (allocation[i] != -1)
            printf("%i", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }
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

void best_fit(int blockSize[], int m, int processSize[], int n)
{
    // Stores block id of the block allocated to a
    // process
    int allocation[n];

    // Initially no block is assigned to any process
    memset(allocation, -1, sizeof(allocation));

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i = 0; i < n; i++)
    {
        // Find the best fit block for current process
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        // If we could find a block for current process
        if (bestIdx != -1)
        {
            // allocate block j to p[i] process
            allocation[i] = bestIdx;

            // Reduce available memory in this block.
            blockSize[bestIdx] -= processSize[i];
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

void worst_fit(int blockSize[], int m, int processSize[], int n)
{
    // Stores block id of the block allocated to a
    // process
    int allocation[n];
  
    // Initially no block is assigned to any process
    memset(allocation, -1, sizeof(allocation));
  
    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i=0; i<n; i++)
    {
        // Find the best fit block for current process
        int wstIdx = -1;
        for (int j=0; j<m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (wstIdx == -1)
                    wstIdx = j;
                else if (blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }
  
        // If we could find a block for current process
        if (wstIdx != -1)
        {
            // allocate block j to p[i] process
            allocation[i] = wstIdx;
  
            // Reduce available memory in this block.
            blockSize[wstIdx] -= processSize[i];
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