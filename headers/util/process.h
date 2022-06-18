#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./simulated_process.h"

typedef enum
{
    BLOCKED,
    READY,
    EXECUTING
} states;

typedef struct
{
    pid_t pid;
    pid_t ppid;
    int pc;
    int* data_structure;
    int priority;
    states state;
    int inital_time;
    int cpu_time;
    simulated_process* simulated_process;
} process;

#endif