#include "../../headers/core/control.h"
#include "../../headers/core/management.h"

void control(int fd[])
{

    FILE *file_pointer;
    management management;
    char instruction[SIZE];
    char *file_name = "../../data/init.txt";
    char input_command;
    int size = 1;
    int number_of_process = 1;
    int time = 0;
    int max_process = -1;
    pid_t pid;
    int non_blocked_process;

    file_pointer = fopen(file_name, "r");

    init_management(&management, file_name, size, 0);

    if (file_pointer == NULL)
    {
        printf("File is empty!!!");
    }
    else
    {
        do
        {
            read(fd[0], &input_command, sizeof(input_command));

            switch (fgetc(file_pointer))
            {
            case 'U':
                time++;
                management.time++;
                strcpy(instruction, read_instructions_file(&management.cpu));

                management.cpu.time++;
                if (instruction[0] != 'F' && instruction[0] != 'R')
                {
                    management.cpu.pc++;
                }

                // Needs to add the N D V A S B T F R instructions
                switch (instruction[0])
                {
                case 'N':
                    instruction_n(atoi(&instruction[2]), &(management.cpu.memory));
                    *(management.cpu.size_memory) = atoi(&instruction[2]);
                case 'D':
                    instruction_d(atoi(&instruction[2]), &management.cpu.memory);
                case 'V':
                    instruction_v(atoi(&instruction[2]), atoi(&instruction[4]), &management.cpu.memory);
                case 'A':
                    instruction_a(atoi(&instruction[2]), atoi(&instruction[4]), &management.cpu.memory);
                case 'S':
                    instruction_s(atoi(&instruction[2]), atoi(&instruction[4]), &(management.cpu.memory));
                case 'B':
                    management.process_table[management.executing_state].process.state = 2;
                    if (management.process_table[management.executing_state].process.priority > 0)
                    {
                        management.process_table[management.executing_state].process.priority -= 1;
                    }
                    to_queue(&management.blocked, management.executing_state);
                    if (management.type_escalation_policy == MULTIPLE_QUEUES)
                    {
                        change_context(&management, dequeue_scheduling(&management.scheduling), BLOCKED);
                    }
                    else if (management.type_escalation_policy == FCFS)
                    {
                        change_context(&management, dequeue(&management.ready), BLOCKED);
                    }

                case 'T':
                    end_simulated_process(&management, &size, &max_process);
                case 'F':
                    size++;
                    number_of_process++;
                    create_new_process(&management, atoi(&instruction[2]), size, number_of_process - 1);
                case 'R':
                    replace_current_image_process(&management, instruction);
                default:
                    break;
                }

                break;
            case 'L':
                non_blocked_process = dequeue(&management.blocked);

                if (non_blocked_process != -1)
                {
                    management.process_table[non_blocked_process].process.state = READY;
                    if (management.type_escalation_policy == MULTIPLE_QUEUES)
                    {
                        do_scheduling(&management.scheduling, non_blocked_process, management.process_table[non_blocked_process].process.priority);
                    }
                    else if (management.type_escalation_policy == FCFS)
                    {
                        to_queue(&management.ready, non_blocked_process);
                    }
                }
                break;
            case 'I':

                if ((pid = fork()) == -1)
                {
                    printf("Fork error!!!\n");
                    return;
                }

                if (pid == 0)
                {
                    print_management(&(management), size, number_of_process, time);
                    return;
                }
                break;

            case 'M':
                if ((pid = fork()) == -1)
                {
                    printf("Fork error!!!\n");
                    return;
                }
                if (pid == 0)
                {
                    print_management(&(management), size, number_of_process, time);
                    printf("Mean time for the cycle --> %.2f", (float)management.time / time);
                    return;
                }

                exit(0);
            default:
                printf("Not valid input!!!\n");
                break;
            }
            if (management.time == MULTIPLE_QUEUES)
            {
                if (verify_quantum(&management))
                {
                    int process_index;
                    int priority_process;
                    int next_process;

                    process_index = management.executing_state;
                    if (management.process_table[process_index].process.priority != 4)
                    {
                        management.process_table[process_index].process.priority += 1;
                    }
                    priority_process = management.process_table[process_index].process.priority;

                    do_scheduling(&(management.scheduling), process_index, priority_process);

                    next_process = dequeue_scheduling(&(management.scheduling));
                    change_context(&(management), next_process, READY);
                }
                else if (management.executing_state == -1)
                {
                    int next_process_i;
                    next_process_i = dequeue_scheduling(&(management.scheduling));
                    if (next_process_i != -1)
                    {
                        load_cpu_process(&(management), next_process_i);
                    }
                }
            }

            else if (management.time == FCFS)
            {
                if (management.executing_state == -1)
                {
                    int next_process_ii;
                    next_process_ii = dequeue(&(management.ready));
                    if (next_process_ii != -1)
                    {
                        load_cpu_process(&(management), next_process_ii);
                    }
                }
            }
        } while (input_command != 'M');

        close(fd[0]);
    }
}