#include "../../headers/util/process.h"

void init_process(process *process, int pid, int ppid)
{
    process->pid = pid;
    process->ppid = ppid;
    process->pc = 0; // o process começa inicialmente com PC = 0
    process->priority = 0;
    process->state = BLOCKED;
    process->inital_time = UNDEFINED;
    process->cpu_time = 0;
    process->size = 0;
}

process *create_process(int pid, int ppid)
{

    process *new_process = (process *)malloc(sizeof(process));

    init_process(new_process, pid, ppid);

    return new_process;
}

void print_process(process *process)
{
    printf("| ");
    printf("%-3d", process->pid);
    printf(" | ");
    printf("%-4d", process->ppid);
    printf(" | ");
    if (process->state == BLOCKED)
    {
        printf("%-5s", "BLOCKED");
    }
    else if (process->state == EXECUTING)
    {
        printf("%-5s", "READY");
    }
    else if (process->state == READY)
    {
        printf("%-5s", "EXECUTING");
    }
    printf(" | ");
    printf("%-8f", process->cpu_time);
    printf(" | ");
    printf("%-9d", process->size);
    printf(" | ");
    printf("%-2d", process->pc);
    printf(" | ");
    printf("%-10f", process->inital_time);
    printf(" | ");
    printf("%-4d", process->priority);
    printf(" |");
}