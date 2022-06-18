#ifndef SIMULATED_PROCESS_h
#define SIMULATED_PROCESS_h

typedef struct
{
    char file_name[30];
    int* memory;
    int number_of_vars;
    int pc;
} simulated_process;

#endif