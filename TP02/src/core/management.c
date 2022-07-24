#include "../../headers/core/management.h"

void init_management(management *management, char *file_name, int size, scheduler_policy type_escalation_policy)
{
    printf("COMEÇOU A ZUERA!");
    management->time = 0;
    management->process_table = (process_table *)malloc(sizeof(process_table));
    init_queue(&(management->ready));
    init_queue(&(management->blocked));
    init_scheduling(&(management->scheduler));

    // Cria o primeiro processo simulado
    simulated_process *processo = (simulated_process *)malloc(sizeof(simulated_process));
    processo->pc = 0;
    strcpy(processo->programa.file_name, file_name);

    // Registrar o primeiro processo na tabela de processos
    management->process_table[0].pc = &(processo->pc);
    management->process_table[0].process_reference = processo;
    management->process_table[0].inital_time = management->time;
    management->process_table[0].priority = 0;
    management->process_table[0].state = EXECUTING;

    // Processo está pronto para executar
    /* Variável armazena o tamanho da tabela de processos, tal valor subtraído de 1 gera o índice do processo na tabela */
    management->executing_state = (size - 1);
    management->cpu.pc = processo->pc;
    management->cpu.program = &(processo->programa);
    management->cpu.memory = NULL;
    management->cpu.time = 0;
    management->cpu.size_memory = &(processo->number_of_vars);
    management->type_escalation_policy = type_escalation_policy;
}

char *read_instructions_file(CPU *cpu)
{

    FILE *file;
    char *line = (char *)malloc(20 * sizeof(char));
    int counter = 0;

    file = fopen(cpu->program->file_name, "r");

    if (file == NULL)
    {
        logger("Error! File not exists!\n", ERROR_COLOR);
    }

    if (DEBUG)
    {
        logger("\n==========================\n\n", DEBUG_COLOR);
    }
    while (counter <= cpu->pc)
    {

        fgets(line, 20, file);

        if (DEBUG)
        {
            printf("\033[38;5;3m");
            printf("current line: %s\n", line);
            printf("\033[0m");
        }
        counter++;
    }
    if (DEBUG)
    {
        logger("==========================\n", DEBUG_COLOR);
    }

    fclose(file);
    return line;
}

void create_new_process(management *management, domain *process_manager_domain,int number_of_instructions, int size, int pid)
{
    // Cria processo
    simulated_process *create_child_process = (simulated_process *)malloc(sizeof(simulated_process));

    // Copia informações de contador de programa, nome do arquivo (vetor de programa) e memória (vetor com variáveis)
    create_child_process->pc = management->cpu.pc;
    strcpy(create_child_process->programa.file_name, management->cpu.program->file_name);

    if (management->cpu.memory != NULL)
    {
        create_child_process->memory = (int *)malloc(*(management->cpu.size_memory) * sizeof(int));
        for (int i = 0; i < *(management->cpu.size_memory); i++)
        {
            create_child_process->memory[i] = management->cpu.memory[i];
        }
    }
    else
    {
        create_child_process->memory = NULL;
    }

    // create_child_process->memoria = *(management->cpu.memory);
    create_child_process->number_of_vars = *(management->cpu.size_memory);

    // Ajusta os valores dos contadores de pograma
    create_child_process->pc += 1;
    management->cpu.pc = management->cpu.pc + number_of_instructions + 1;

    // Criar uma entrada na tabela de processos
    management->process_table = realloc(management->process_table, size * sizeof(process_table));
    management->process_table[(size - 1)].pc = &(create_child_process->pc);
    management->process_table[(size - 1)].process_reference = create_child_process;
    management->process_table[(size - 1)].inital_time = management->time;
    management->process_table[(size - 1)].pid = pid;
    management->process_table[(size - 1)].ppid = management->process_table[management->executing_state].pid;
    management->process_table[(size - 1)].cpu_time = 0;
    management->process_table[(size - 1)].state = READY;
    management->process_table[(size - 1)].priority = management->process_table[management->executing_state].priority;
    management->process_table[(size - 1)].data_structure = create_child_process->memory;

    allocate_new_process(process_manager_domain,&management->process_table[(size - 1)],FALSE);

    // Processo filho criado com estado pronto, adiciona na estrutura do tipo de escalonador escolhido
    if (management->type_escalation_policy == MULTIPLE_QUEUES)
    {
        do_scheduling(&(management->scheduler), (size - 1), management->process_table[(size - 1)].priority);
    }
    else if (management->type_escalation_policy == FCFS)
    {
        to_queue(&(management->ready), (size - 1));
    }
}

void load_cpu_process(management *management, int index_next_process)
{
    management->executing_state = index_next_process;
    management->process_table[index_next_process].state = EXECUTING;
    management->cpu.pc = *(management->process_table[management->executing_state].pc);
    management->cpu.time = 0;
    management->cpu.size_memory = &(management->process_table[management->executing_state].process_reference->number_of_vars);

    management->cpu.memory = (management->process_table[management->executing_state].data_structure);
    management->cpu.program = &(management->process_table[management->executing_state].process_reference->programa);
}

void change_context(management *management, int index_next_process, int initial_state_process)
{
    management->process_table[management->executing_state].cpu_time += management->cpu.time;
    management->process_table[management->executing_state].process_reference->pc = management->cpu.pc;
    management->process_table[management->executing_state].state = initial_state_process;
    management->process_table[management->executing_state].data_structure = management->cpu.memory;

    if (index_next_process >= 0)
    {
        load_cpu_process(management, index_next_process);
    }
    else
    {
        management->cpu.memory = NULL;
        management->cpu.program = NULL;
        management->executing_state = -1;
    }
}

void replace_current_image_process(management *management, char *instruction)
{
    int k;
    int response = (instruction[2] == '.' && instruction[3] == '/' && instruction[4] == 'd' && instruction[5] == 'a' && instruction[6] == 't' && instruction[7] == 'a' && instruction[8] == '/');

    // Copiando nome do arquivo

    if (response)
    {
        for (k = 2; k < (strlen(instruction)); k++)
        {
            management->cpu.program->file_name[k - 2] = instruction[k];
        }
    }
    else
    {
        // adicionando o path dos arquivos
        management->cpu.program->file_name[0] = '.';
        management->cpu.program->file_name[1] = '/';
        management->cpu.program->file_name[2] = 'd';
        management->cpu.program->file_name[3] = 'a';
        management->cpu.program->file_name[4] = 't';
        management->cpu.program->file_name[5] = 'a';
        management->cpu.program->file_name[6] = '/';

        for (k = 2; k < (strlen(instruction)); k++)
        {
            management->cpu.program->file_name[(k - 2) + 7] = instruction[k];
        }
    }

    // Colocando o '\0' para indicar fim de string

    k = !response ? 1 : 0;
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

void end_simulated_process(management *management, int *size, int *max_time)
{
    int index_process_finished = management->executing_state;
    int next_process_execute;
    int tempoTotal = management->process_table[index_process_finished].cpu_time + management->cpu.time;

    if (tempoTotal > *max_time)
    {
        *max_time = tempoTotal;
    }

    if (management->type_escalation_policy == MULTIPLE_QUEUES)
    {
        next_process_execute = dequeue_scheduling(&(management->scheduler));
    }
    else if (management->type_escalation_policy == FCFS)
    {
        next_process_execute = dequeue(&(management->ready));
    }

    change_context(management, next_process_execute, READY);

    // Liberando vetor de memória do processo simulado
    simulated_process *process = management->process_table[index_process_finished].process_reference;
    free(process->memory);

    // Ajustando as entradas da tabela de processo agora que um processo encerrou
    for (int k = index_process_finished; k < ((*size) - 1); k++)
    {
        management->process_table[k] = management->process_table[k + 1];
    }
    (*size) -= 1;

    management->process_table = realloc(management->process_table, (*size) * sizeof(process_table));

    adjust_queue_values(management->scheduler.first, index_process_finished);
    adjust_queue_values(management->scheduler.second, index_process_finished);
    adjust_queue_values(management->scheduler.third, index_process_finished);
    adjust_queue_values(management->scheduler.fourth, index_process_finished);
    adjust_queue_values(&(management->ready), index_process_finished);

    adjust_queue_values(&(management->blocked), index_process_finished);
    if (management->executing_state > index_process_finished)
    {
        management->executing_state -= 1;
    }
}

void print_management(management *management, int size, int number_of_process, int longer_time)
{
    int cycle_time;
    float percentage;
    char state_string[20];
    float average_time = management->time / number_of_process;

    logger("\t\t\t\t\t========================= SYSTEM INFORMATION ========================= \n\n", COMMUN_COLOR);

    printf("Number of processes:  %d\n", size);
    printf("System runtime so far: %d\n", management->time);
    printf("Average process execution time: %f\n", average_time);

    if (longer_time == -1)
    {
        printf("Longest runtime so far: -\n\n");
    }
    else
    {
        printf("Longest runtime so far: %d\n\n", longer_time);
    }

    logger("\t\t\t\t\t========================= Active Processes ========================= \n\n", COMMUN_COLOR);

    printf("==========================================================================================================================================\n");
    printf("| \033[38;5;196m pid \033[0m | \033[38;5;196m ppid \033[0m | \033[38;5;196m Table index \033[0m | \033[38;5;196m Cycle time \033[0m | \033[38;5;196m Initial Time \033[0m | \033[38;5;196m Used Percent. \033[0m | \033[38;5;196m PC \033[0m | \033[38;5;196m   State   \033[0m | \033[38;5;196m Num vars \033[0m |      \033[38;5;196m vars \033[0m      | \n");
    printf("\033[0m");
    printf("==========================================================================================================================================\n");

    for (int i = 0; i < size; i++)
    {
        if (management->executing_state == i)
        {
            cycle_time = management->process_table[i].cpu_time + management->cpu.time;
        }
        else
        {
            cycle_time = management->process_table[i].cpu_time;
        }

        percentage = ((float)cycle_time / (float)management->time);
        percentage *= 100;

        switch (management->process_table[i].state)
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

        int pid = management->process_table[i].pid;
        int ppid = management->process_table[i].ppid;
        int initial_time = management->process_table[i].inital_time;
        int pc = *management->process_table[i].pc;
        int number_of_vars = management->process_table[i].process_reference->number_of_vars;

        printf("| %-5d | %-6d | %-13d | %-12d | %-14d | %-14.2f%% | %-4d |", pid, ppid, i, cycle_time, initial_time, percentage, pc);

        switch (management->process_table[i].state)
        {
        case READY:
            printf("\033[38;5;68m");
            printf(" %-12s", state_string);
            printf("\033[0m |");
            break;
        case EXECUTING:
            printf("\033[38;5;3m");
            printf(" %-12s", state_string);
            printf("\033[0m |");
            break;
        case BLOCKED:
            printf("\033[38;5;1m");
            printf(" %-12s", state_string);
            printf("\033[0m |");
            break;
        default:
            break;
        }

        printf(" %-10d | ", number_of_vars);

        for (int ii = 0; ii < management->process_table[i].process_reference->number_of_vars; ii++)
        {
            if (management->executing_state == i)
            {
                if (management->cpu.memory != NULL)
                {
                    if (management->cpu.memory[ii] != INT_MAX)
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
                if (management->process_table[i].data_structure != NULL)
                {
                    if (management->process_table[i].data_structure[ii] != INT_MAX)
                    {
                        printf("%d ", management->process_table[i].data_structure[ii]);
                    }
                    else
                    {
                        printf("- ");
                    }
                }
            }
        }
        printf("\n==========================================================================================================================================\n");
    }

    printf("\nProcess in ready state (indexes): \n");
    if (management->type_escalation_policy == MULTIPLE_QUEUES)
    {
        printf("Queue 0: ");
        print_queue(management->scheduler.first);
        printf("Queue 1: ");
        print_queue(management->scheduler.second);
        printf("Queue 2: ");
        print_queue(management->scheduler.third);
        printf("Queue 3: ");
        print_queue(management->scheduler.fourth);
    }

    else if (management->type_escalation_policy == FCFS)
    {
        print_queue(&(management->ready));
    }

    printf("Process in blocked state (indexes): \n");
    print_queue(&(management->blocked));
    printf("------------------------------------------------------------\n");
}

int verify_quantum(management *management)
{

    int process_index = management->executing_state, priority;

    priority = process_index != -1 ? management->process_table[process_index].priority : UNDEFINED;

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

void multiple_queues(management management)
{
    if (verify_quantum(&management))
    {
        int process_index;
        int priority_process;
        int next_process;

        process_index = management.executing_state;
        if (management.process_table[process_index].priority != 4)
        {
            management.process_table[process_index].priority += 1;
        }
        priority_process = management.process_table[process_index].priority;

        do_scheduling(&(management.scheduler), process_index, priority_process);

        next_process = dequeue_scheduling(&(management.scheduler));
        change_context(&(management), next_process, READY);
    }
    else if (management.executing_state == -1)
    {
        int next_process_i;
        next_process_i = dequeue_scheduling(&(management.scheduler));
        if (next_process_i != -1)
        {

            load_cpu_process(&(management), next_process_i);
        }
    }
}

void first_come_first_serve(management management)
{
    if (management.executing_state == -1)
    { // caso não haja nenhum processo sendo executado
        int next_process_ii;
        next_process_ii = dequeue(&(management.ready));
        if (next_process_ii != -1)
        {
            load_cpu_process(&(management), next_process_ii);
        }
    }
}