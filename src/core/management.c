#include "../../headers/core/management.h"

void init_management(management *management, char *file_name, int size, int type_escalation_policy)
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
    strcpy(new_simulated_process->program->file_name, file_name);

    // Registra o primeiro processo na tabela de processos
    management->process_table[0].process.pc = new_simulated_process->pc;
    management->process_table[0].process.simulated_process = new_simulated_process;
    management->process_table[0].process.inital_time = management->time;
    management->process_table[0].process.priority = 0;
    management->process_table[0].process.state = EXECUTING;

    management->executing_state = (size - 1);
    management->cpu.pc = new_simulated_process->pc;
    strcpy(management->cpu.program->file_name, new_simulated_process->program->file_name);
    management->cpu.memory = NULL;
    management->cpu.time = 0;
    management->cpu.size_memory = &(new_simulated_process->number_of_vars);

    //define a política de escalonamento
    management->type_escalation_policy = type_escalation_policy;
}

char *read_instructions_file(cpu *cpu)
{
    FILE *file;
    char *line = (char *)malloc(20 * sizeof(char));
    int counter = 0;

    file = fopen(cpu->program->file_name, "r");

    if (file == NULL)
    {
        printf("\033[38;5;1m");
        printf("Error! File not exists!\n");
        printf("\033[0m");
    }

    while (counter <= cpu->pc)
    {

        fgets(line, 20, file);

        counter++;
    }

    fclose(file);
    return line;
}

void create_new_process(management *management, int number_of_instructions, int size, pid_t pid)
{
    simulated_process *children = (simulated_process *)malloc(sizeof(simulated_process));

    children->pc = management->cpu.pc;
    strcpy(children->program->file_name, management->cpu.program->file_name);

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
    management->process_table[(size - 1)].process.pc = children->pc;
    management->process_table[(size - 1)].process.simulated_process = children;
    management->process_table[(size - 1)].process.inital_time = management->time;
    management->process_table[(size - 1)].process.pid = pid;
    management->process_table[(size - 1)].process.ppid = management->process_table[management->executing_state].process.pid;
    management->process_table[(size - 1)].process.cpu_time = 0;
    management->process_table[(size - 1)].process.state = READY;
    management->process_table[(size - 1)].process.priority = management->process_table[management->executing_state].process.priority;

    // Quando o processo filho é criado ele compartilha sua memória com o processo pai
    management->process_table[(size - 1)].process.data_structure = children->memory;

    if (management->type_escalation_policy == 1)
    {
        do_scheduling(&(management->scheduling), (size - 1), management->process_table[(size - 1)].process.priority);
    }
    else if (management->type_escalation_policy == 0)
    {
        to_queue(&(management->ready), (size - 1));
    }
}

void replace_current_image_process(management *management, char *instruction)
{

    int k;

    for (k = 2; k < (strlen(instruction)); k++)
    {
        management->cpu.program->file_name[k - 2] = instruction[k];
    }

    k = 0;

    while (1)
    {
        if (management->cpu.program->file_name[k] == '.')
        {
            break;
        }

        k++;
    }

    management->cpu.program->file_name[k + 4] = '\0';
    management->cpu.pc = 0;
    free((management->cpu.memory));
    management->cpu.memory = NULL;
}

void load_cpu_process(management *management, int index_next_process)
{
    management->executing_state = index_next_process;
    management->process_table[index_next_process].process.state = EXECUTING;
    management->cpu.pc = management->process_table[management->executing_state].process.pc;
    management->cpu.time = 0;
    management->cpu.size_memory = &(management->process_table[management->executing_state].process.simulated_process->number_of_vars);
    management->cpu.memory = management->process_table[management->executing_state].process.data_structure;
    strcpy(management->cpu.program->file_name, management->process_table[management->executing_state].process.simulated_process->program->file_name);
}

void change_context(management *management, int index_next_process, int initial_state_process)
{
    management->process_table[management->executing_state].process.cpu_time += management->cpu.time;
    management->process_table[management->executing_state].process.simulated_process->pc = management->cpu.pc;
    management->process_table[management->executing_state].process.state = initial_state_process;
    management->process_table[management->executing_state].process.data_structure = management->cpu.memory;

    if (index_next_process >= 0)
    {
        // carrega o processo na CPU
        load_cpu_process(management, index_next_process);
    }
    else
    {
        management->cpu.memory = NULL;
        management->executing_state = UNDEFINED;
    }
}

void end_simulated_process(management *management, int *size, int *max_time)
{
    int index_end_simulated_process = management->executing_state;
    int next_process;
    int total_time = management->process_table[index_end_simulated_process].process.cpu_time + management->cpu.time;

    if (total_time > *max_time)
    {
        *max_time = total_time;
    }

    if (management->type_escalation_policy == 1)
    {
        next_process = dequeue_scheduling(&(management->scheduling));
    }
    else if (management->type_escalation_policy == 0)
    {
        next_process = dequeue(&(management->ready));
    }

    change_context(management, next_process, READY);

    simulated_process *process = management->process_table[index_end_simulated_process].process.simulated_process;
    free(process->memory);

    for (int i = index_end_simulated_process; i < (*(size)-1); i++)
    {
        management->process_table[i] = management->process_table[i + 1];
    }

    *(size) -= 1;

    management->process_table = realloc(management->process_table, *(size) * sizeof(process_table));

    adjust_queue_values(management->scheduling.first, index_end_simulated_process);
    adjust_queue_values(management->scheduling.second, index_end_simulated_process);
    adjust_queue_values(management->scheduling.third, index_end_simulated_process);
    adjust_queue_values(management->scheduling.fourth, index_end_simulated_process);
    adjust_queue_values(&(management->ready), index_end_simulated_process);
    adjust_queue_values(&(management->blocked), index_end_simulated_process);

    if (management->executing_state > index_end_simulated_process)
    {
        management->executing_state -= 1;
    }
}

int verify_quantum(management *management)
{
    int process_index = management->executing_state, priority;

    priority = process_index != -1 ? management->process_table[process_index].process.priority : UNDEFINED;

    if (
        (priority == 0 && management->cpu.time == QUANTUM_PRIORITY_0) ||
        (priority == 1 && management->cpu.time == QUANTUM_PRIORITY_1) ||
        (priority == 2 && management->cpu.time == QUANTUM_PRIORITY_2) ||
        (priority == 3 && management->cpu.time == QUANTUM_PRIORITY_3))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_management(management *management, int size, int number_of_process, int longer_time)
{
    int cycle_time;
    float percentage;
    char state_string[20];
    float average_time = management->time / number_of_process;

    printf("\t\t=================== Informações do Sistema =================== \n\n");
    printf("Quantidade de processos:  %d\n", size);
    printf("Tempo de execução do sistema até agora: %d\n", management->time);
    printf("Tempo médio de execução processos: %f\n", average_time);

    if (longer_time == -1)
    {
        printf("Maior tempo de execução até agora: -\n\n");
    }
    else
    {
        printf("Maior tempo de execução até agora: %d\n\n", longer_time);
    }

    printf("\t\t=================== Processos Ativos ========================= \n\n");
    printf(" pid | ppid | Indice tabela | Tempo Ciclo | Tempo Inicio | Porcent. Usada | PC |   estado   | Num variaveis | variaveis \n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < size; i++)
    {
        if (management->executing_state == i)
        {
            cycle_time = management->process_table[i].process.cpu_time + management->cpu.time;
        }
        else
        {
            cycle_time = management->process_table[i].process.cpu_time;
        }

        percentage = ((float)cycle_time / (float)management->time);
        percentage *= 100;

        switch (management->process_table[i].process.state)
        {
        case READY:
            strcpy(state_string, "ready");
            break;
        case EXECUTING:
            strcpy(state_string, "executing");
            break;
        case BLOCKED:
            strcpy(state_string, "blocked");
            break;
        default:
            break;
        }

        int pid = management->process_table[i].process.pid;
        int ppid = management->process_table[i].process.ppid;
        int initial_time = management->process_table[i].process.inital_time;
        int pc = management->process_table[i].process.pc;
        int number_of_vars = management->process_table[i].process.simulated_process->number_of_vars;

        printf(" %-3d | %-4d | %-13d | %-11d | %-12d | %-13.2f%% | %-2d | %-10s | %-13d | ", pid, ppid, i, cycle_time, initial_time, percentage, pc, state_string, number_of_vars);

        for (int ii = 0; ii < management->process_table[i].process.simulated_process->number_of_vars; ii++)
        {
            if (management->executing_state == i)
            {
                if (management->cpu.memory != NULL)
                {
                    if (management->cpu.memory[ii] != __INT_MAX__)
                    {
                        printf("%d ", management->cpu.memory[ii]);
                    }
                    else
                    {
                        printf("- ");
                    }
                }
                else
                {
                    printf("- ");
                }
            }
            else
            {
                if (management->process_table[i].process.data_structure != NULL)
                {
                    if (management->process_table[i].process.data_structure[ii] != __INT_MAX__)
                    {
                        printf("%d ", management->process_table[i].process.data_structure[ii]);
                    }
                    else
                    {
                        printf("- ");
                    }
                }
            }
        }

        printf("\n");
    }

    printf("Processo em estado pronto (Índices): \n");
    if (management->type_escalation_policy == 1)
    {
        printf("Fila 0: ");
        print_queue(management->scheduling.first);
        printf("Fila 1: ");
        print_queue(management->scheduling.second);
        printf("Fila 2: ");
        print_queue(management->scheduling.third);
        printf("Fila 3: ");
        print_queue(management->scheduling.fourth);
    }
    else if (management->type_escalation_policy == 0)
    {
        print_queue(&(management->ready));
    }

    printf("Processos em estado bloqueado (Indices): \n");
    print_queue(&(management->blocked));
    printf("------------------------------------------------------------\n");
}