#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// 4096*1024
// Processo tem 4096 MB de memória
#define MEMSIZE 4194304

void generate(int size)
{
    FILE *file;
    const char *path = "data/memory.dat";

    file = fopen(path, "w");
    int *memory = (int *)malloc(sizeof(int) * size);

    srand(time(NULL));

    for (int i = 0; i < MEMSIZE; i++)
    {
        // Increment any random element
        // from the array by 1
        memory[rand() % size]++;
    }

    for (int i = 0; i < size; i++)
    {
        i == size - 1 ? fprintf(file, "%d %d", i, memory[i]) : fprintf(file, "%d %d\n", i, memory[i]);
    }

    fclose(file);
}

void main()
{
    generate(100);
}