#ifndef CPU_h
#define CPU_h

#include <stdio.h>
#include <stdlib.h>

typedef struct program
{
    char file_name[30];
}program;


typedef struct
{
    program *program;
    int pc;
    int *memory;
    int *size_memory;
    int time;
}cpu;

#endif