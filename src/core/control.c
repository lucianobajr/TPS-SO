#include "../../headers/core/control.h"
#include "../../headers/core/management.h"
#define SIZE 50

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
    pid_t pid;

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

                //Needs to add the N D V A S B T F R instructions
                switch (instruction[0])
                {
                case 'N':
                    
                    break;
                case 'D':

                    break;
                case 'V':

                    break;
                case 'A':

                    break;
                case 'S':

                    break;
                case 'B':

                    break;
                case 'T':

                    break;
                case 'F':

                    break;
                case 'R':

                    break;
                default:
                    break;
                }
                

                break;
            case 'L':
                int blocked_process = dequeue(&management.blocked);

                if (blocked_process != -1)
                {
                    management.process_table[blocked_process].process.state = READY;
                    // Needs to decide the schedulling
                    do_scheduling(&(management).scheduling, blocked_process, management.process_table[blocked_process].process.priority);
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
        } while (input_command != 'M');
    }
}