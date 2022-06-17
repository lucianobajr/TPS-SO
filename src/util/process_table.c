#include "../../headers/util/process_table.h"

process_table *create_process_table()
{
    process_table *new_process_table = (process_table *)malloc(sizeof(process_table));

    new_process_table->size = 0;
    new_process_table->process = (process *)malloc(sizeof(process) * PROCESS_TABLE_SIZE);

    return new_process_table;
}

void print_process_table(process_table *process_table)
{
    printf("\n######################################## Tabela de processos ########################################\n");
    printf("| Indice | Pid | Ppid | State   | Time CPU | instructs | PC | Time start | Prio |\n");
    for (int i = 0; i < process_table->size; i++)
    {

        printf("| %-6d ", i);
        print_process(&process_table->process[i]);
        if (i + 1 < process_table->size)
            printf("\n");
    }
    printf("\n#####################################################################################################\n");
}

void insert_process_in_table(process_table *process_table, process process)
{
    int position;

    if (process_table->size < PROCESS_TABLE_SIZE)
    {
        process_table->process[process_table->size] = process;
        process_table->size++;
    }
    else
    {
        printf("\033[38;5;1m");
        printf("Error! The table is fulld!\n");
        printf("\033[0m");
    }
}