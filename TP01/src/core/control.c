#include "../../headers/core/control.h"

int control(scheduler_policy type_escalation_policy)
{
    FILE *file;
    char file_name[TAM];
    int input_type;
    int fd[2]; /* Descritores de arquivo para o pipe, posições: 0 leitura - 1 escrita */
    pid_t pid; /* Variável para o fork*/

    if (pipe(fd) == -1)
    {
        logger("Error pipe\n", ERROR_COLOR);
        return 1;
    }

    print_menu1();

    do
    {
        scanf("%d", &input_type);

        if (input_type != 1 && input_type != 2)
        {
            logger("\nError! Invalid input!\n", ERROR_COLOR);
            printf("----------> ");
        }
    } while (input_type != 1 && input_type != 2);

    if (input_type == 1)
    { // ENTRADA POR ARQUIVO

        do
        {
            printf("Insert the file name: \n");
            printf("----------> ");
            scanf("%s", file_name);
            file = fopen(file_name, "r");

            if (file == NULL)
            {
                logger("Error! File not found!\n", ERROR_COLOR);
            }
        } while (file == NULL);
    }

    if ((pid = fork()) == -1)
    {
        printf("Error fork\n");
        return 1;
    }

    if (pid > 0)
    { /* Execução processo pai */ // O PROCESSO PAI SERÁ O PROCESSO CONTROLE
        char command;
        close(fd[0]); // fecha a leitura do pipe pq o processo controle irá apenas escrever

        if (input_type == 2)
        { // ENTRADA MANUAL
            printf("\nCommands:\n");
        }
        do
        {
            if (input_type == 1)
            { // ENTRADA POR ARQUIVO
                fscanf(file, " %c", &command);
                printf("---------->\n");
            }
            else
            {
                printf("---------->");
                scanf(" %c", &command);
            }

            write(fd[1], &command, sizeof(command)); // abre a leitura do pipe pra enviar os comandos para o processo gerenciador de processos
            if (input_type == 1)
                sleep(1); // coloca o sistema em modo de espera para que seja possível ver os resultados
        } while (command != 'M');

        close(fd[1]); // fecha o pipe de escrita para não ter risco de leak de memoria - ou dar outra coisa ruim pois é uma chamada de sistema
        wait(NULL);
        return 1;
    }
    else
    { /* Execução processo filho */ // O PROCESSO FILHO SERÁ O GERENCIADOR DE PROCESSOS

        // Iniciando a estrutura que representa o processo gerenciador
        management process_manager;
        // Recebe os comandos do processo controle e processa eles
        char process_command_control; // Variável para receber o comando do processo Controle
        char *name = "./data/init.txt";
        char instruction[50];
        int size = 1;             // Tabela de processos (1 porque é o primeiro processo) - pode variar de acordo com a qnt de processos atual (se for encerrado é retirado da tabela)
        int global_time = 0;      // inicializando a contagem de unidade de tempo (instruções) do gerenciador
        int total_of_process = 1; /* todos os processos, independente de terem sido encerrados ou não*/
        int non_blocked_process;  // pega o indice do primeiro processo bloqueado para ser desbloqueado
        int max_process = -1;     // para registrar qual tempo do processo mais longo
        pid_t pid2;               // identificador do processo de print_management

        close(fd[1]); // fecha o pipe de escrita para não ter risco de leak de memoria - ou dar outra coisa ruim pois é uma chamada de sistema

        init_management(&process_manager, name, size, type_escalation_policy);

        do
        {
            read(fd[0], &process_command_control, sizeof(process_command_control));

            switch (process_command_control)
            {
            /*
             * Fim de uma unidade de tempo
             */
            case 'U':
                /* Incrementando o tempo*/
                global_time++;
                process_manager.time++;
                /* Verifica se há um processo na CPU no momento*/
                if (process_manager.executing_state != -1)
                {
                    process_manager.cpu.time++;
                    strcpy(instruction, read_instructions_file(&(process_manager.cpu)));

                    if (instruction[0] != 'F' && instruction[0] != 'R')
                    {
                        process_manager.cpu.pc++;
                    }

                    if (DEBUG)
                    {
                        printf("---------------------------------------------------------\n");
                        printf("Current file name: %s\n", process_manager.cpu.program->file_name);
                        printf("Current input: ---> %d\n", process_manager.executing_state);
                        printf("Counter: --> %d, Instruction: --> %s", process_manager.cpu.pc, instruction);
                        printf("Priority: --> %d\n", process_manager.process_table[process_manager.executing_state].priority);
                        printf("---------------------------------------------------------\n");
                    }
                }
                else
                {
                    strcpy(instruction, "0");
                }

                switch (instruction[0])
                {
                case 'N':
                    instruction_n(atoi(&(instruction[2])), &(process_manager.cpu.memory));
                    *(process_manager.cpu.size_memory) = atoi(&(instruction[2]));
                    break;
                case 'D':
                    instruction_d(atoi(&(instruction[2])), &(process_manager.cpu.memory));
                    break;
                case 'V':
                    instruction_v(atoi(&(instruction[2])), atoi(&(instruction[4])), &(process_manager.cpu.memory));
                    break;
                case 'A':
                    instruction_a(atoi(&(instruction[2])), atoi(&(instruction[4])), &(process_manager.cpu.memory));
                    break;
                case 'S':
                    instruction_s(atoi(&(instruction[2])), atoi(&(instruction[4])), &(process_manager.cpu.memory));
                    break;
                case 'B':
                    process_manager.process_table[process_manager.executing_state].state = BLOCKED;
                    if (process_manager.process_table[process_manager.executing_state].priority > 0)
                    {
                        process_manager.process_table[process_manager.executing_state].priority -= 1;
                    }
                    to_queue(&(process_manager.blocked), process_manager.executing_state);

                    if (process_manager.type_escalation_policy == MULTIPLE_QUEUES)
                    {
                        change_context(&(process_manager), dequeue_scheduling(&(process_manager.scheduler)), BLOCKED);
                    }
                    else if (process_manager.type_escalation_policy == FCFS)
                    {
                        change_context(&(process_manager), dequeue(&(process_manager.ready)), BLOCKED);
                    }
                    break;
                case 'T':
                    end_simulated_process(&(process_manager), &size, &max_process);
                    break;
                case 'F':
                    size++;
                    total_of_process++;
                    create_new_process(&process_manager, atoi(&(instruction[2])), size, total_of_process - 1);
                    break;
                case 'R':
                    replace_current_image_process(&process_manager, instruction);
                    break;
                default:
                    logger("Invalid input!!!", ERROR_COLOR);
                    break;
                }
                break;
            case 'L':
                command_l(non_blocked_process, process_manager);
                break;
            case 'I': /* Criar um processo de Impressao */
                command_i(pid2, process_manager, size, total_of_process, max_process);
                break;
            case 'M':
                command_m(pid2, process_manager, size, total_of_process, max_process);
                break;
            default:
                logger("\nError! Invalid Input\n", ERROR_COLOR);
                break;
            }

            /*                       ------> Scheduler <------                           */
            if (process_manager.type_escalation_policy == MULTIPLE_QUEUES)
            { /* MULTIPLE LEVEL QUEUES SCHEDULLING*/
                multiple_queues(process_manager);
            }
            else if (process_manager.type_escalation_policy == FCFS)
            { /* FCFS SCHEDULLING */
                first_come_first_serve(process_manager);
            }

        } while (process_command_control != 'M');

        close(fd[0]);
    }
}

void instruction_b(management process_manager)
{
    process_manager.process_table[process_manager.executing_state].state = BLOCKED;
    if (process_manager.process_table[process_manager.executing_state].priority > 0)
    {
        process_manager.process_table[process_manager.executing_state].priority -= 1;
    }
    to_queue(&(process_manager.blocked), process_manager.executing_state);

    if (process_manager.type_escalation_policy == MULTIPLE_QUEUES)
    {
        change_context(&(process_manager), dequeue_scheduling(&(process_manager.scheduler)), BLOCKED);
    }
    else if (process_manager.type_escalation_policy == FCFS)
    {
        change_context(&(process_manager), dequeue(&(process_manager.ready)), BLOCKED);
    }
}

void command_i(pid_t pid, management management, int size, int total_of_process, int max_process)
{
    if ((pid = fork()) == -1)
    {
        printf("Error fork\n");
    }

    if (pid == 0)
    {
        print_management(&management, size, total_of_process, max_process);
        exit(0);
    }
}

void command_m(pid_t pid2, management process_manager, int size, int total_of_process, int max_process)
{
    /* Criar um processo de print_management */
    if ((pid2 = fork()) == -1)
    {
        logger("Error in Fork!\n", ERROR_COLOR);
    }

    if (pid2 == 0)
    {
        print_management(&process_manager, size, total_of_process, max_process);
        printf("\033[38;5;3m");
        printf("==================================\n");
        printf("   Average time per cycle: %.2f\n", (float)process_manager.time / total_of_process);
        printf("==================================\n");
        printf("\033[0m");

        exit(0);
    }

    exit(0);
}

void command_l(int non_blocked_process, management process_manager)
{
    non_blocked_process = dequeue(&(process_manager.blocked));

    if (non_blocked_process != -1)
    {
        process_manager.process_table[non_blocked_process].state = READY;
        if (process_manager.type_escalation_policy == MULTIPLE_QUEUES)
        {
            do_scheduling(&(process_manager.scheduler), non_blocked_process, process_manager.process_table[non_blocked_process].priority);
        }
        else if (process_manager.type_escalation_policy == FCFS)
        {
            to_queue(&(process_manager.ready), non_blocked_process);
        }
    }
}

void print_menu1()
{
    int i;
    fputs(" ", stdout);
    for (i = 0; i < 113; i++)
    {
        fputs("_", stdout);
    }
    printf("\n|");
    for (i = 0; i < 113; i++)
    {
        fputs(" ", stdout);
    }
    printf("|\n|");
    for (i = 0; i < 56; i++)
    {
        fputs(" ", stdout);
    }
    printf("MENU");
    for (i = 0; i < 53; i++)
    {
        fputs(" ", stdout);
    }
    printf("|");
    printf("\n");
    printf("|");
    for (i = 0; i < 113; i++)
    {
        fputs("_", stdout);
    }
    printf("|\n|");
    for (i = 0; i < 113; i++)
    {
        fputs(" ", stdout);
    }
    printf("|\n|                                      ");
    printf("(1) for file input or (2) for interative input");
    for (i = 0; i < 29; i++)
    {
        fputs(" ", stdout);
    }
    printf("|");

    printf("\n|");
    for (i = 0; i < 113; i++)
    {
        fputs("_", stdout);
    }
    printf("|");
    printf("\n");
    printf("----------> ");
    fflush(stdin);
}