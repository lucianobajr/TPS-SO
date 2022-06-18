#ifndef CPU_h
#define CPU_h

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char file_name[30];
    int pc;
    int *memory;
    int *size_memory;
    int time;
} cpu;

#endif