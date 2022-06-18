#include "cpu.h"
#ifndef SIMULATED_PROCESS_h
#define SIMULATED_PROCESS_h

typedef struct
{
    program *program;
    int* memory;
    int number_of_vars;
    int pc;
} simulated_process;

#endif