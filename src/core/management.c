#include "../../headers/core/management.h"

void init_management(management *management, char *file_name, int size)
{
    management->time = 0;
    management->process_table = (process_table *)malloc(sizeof(process_table));

    // filas
    init_queue(&(management->ready));
    init_queue(&(management->blocked));
    init_scheduling(&(management->scheduling));

    // O gerenciador de processos cria o primeiro processo simulado (process id = 0)
    simulated_process *new_simulated_process = (simulated_process *)malloc(sizeof(simulated_process));
    new_simulated_process->pc = 0;
    strcpy(new_simulated_process->file_name, file_name);

    // Registra o primeiro processo na tabela de processos
    management->process_table[0].process.pc = &(new_simulated_process->pc);
    management->process_table[0].process.simulated_process = new_simulated_process;
    management->process_table[0].process.inital_time = management->time;
    management->process_table[0].process.priority = 0;
    management->process_table[0].process.state = EXECUTING;

    management->executing_state = (size - 1);
    management->cpu.pc = new_simulated_process->pc;
    strcpy(management->cpu.file_name, new_simulated_process->file_name);
    management->cpu.memory = NULL;
    management->cpu.time = 0;
    management->cpu.size_memory = &(new_simulated_process->number_of_vars);
}

char *read_instructions_file(cpu *cpu)
{
    FILE *file;
    char *line = (char *)malloc(20 * sizeof(char));
    int counter = 0;

    file = fopen(cpu->file_name, "r");

    if (file == NULL)
    {
        pprintf("\033[38;5;1m");
        printf("Error! File not exists!\n");
        printf("\033[0m");
        return;
    }

    while (counter <= cpu->pc)
    {

        fgets(line, 20, file);

        counter++;
    }

    fclose(file);
    return line;
}

void create_new_process(management *management, int number_of_instructions, int size, pid_t pid, int scheduling_type)
{
    simulated_process *children = (simulated_process *)malloc(sizeof(simulated_process));

    children->pc = management->cpu.pc;
    strcpy(children->file_name, management->cpu.file_name);

    if (management->cpu.memory != NULL)
    {
        children->memory = (int *)malloc(*(management->cpu.size_memory) * sizeof(int));
        for (int i = 0; i < *(management->cpu.size_memory); i++)
        {
            children->memory[i] = management->cpu.memory[i];
        }
    }
    else
    {
        children->memory = NULL;
    }

    children->number_of_vars = *(management->cpu.size_memory);

    children->pc += 1;
    management->cpu.pc = management->cpu.pc + number_of_instructions + 1;

    management->process_table = realloc(management->process_table, size * sizeof(process_table));
    management->process_table[(size - 1)].process.pc = &(children->pc);
    management->process_table[(size - 1)].process.simulated_process = children;
    management->process_table[(size - 1)].process.inital_time = management->time;
    management->process_table[(size - 1)].process.pid = pid;
    management->process_table[(size - 1)].process.ppid = management->process_table[management->executing_state].process.pid;
    management->process_table[(size - 1)].process.cpu_time = 0;
    management->process_table[(size - 1)].process.state = READY;
    management->process_table[(size - 1)].process.priority = management->process_table[management->executing_state].process.priority;
    management->process_table[(size - 1)].process.data_structure = children->memory;

    if (scheduling_type == 1)
    {
        do_scheduling(&(management->scheduling), (size - 1), management->process_table[(size - 1)].process.priority);
    }
    else if (scheduling_type == 0)
    {
        to_queue(&(management->ready), (size - 1));
    }
}