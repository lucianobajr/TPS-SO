#include "../headers/menu.h"

void menu()
{
    FILE *fp;
    char file_name[SIZE];
    int choice;
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
    {
        printf("Pipe error!!!\n");
        return 1;
    }

    print_menu1();
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Insert the file name: \n");
        printf("---------->");
        scanf("%s", file_name);
        fp = fopen(file_name, "r");
    }

    if ((pid = fork()) == -1)
    {
        printf("Fork error!!!\n");
        return 1;
    }

    if (pid > 0)
    {
        char command;
        close(fd[0]);

        if (choice == 2)
        {
            printf("Commands: \n");
        }
        do
        {
            if (choice == 1)
            {
                fscanf(fp, "%c", &command);
                printf("---------->");
            }
            else
            {
                printf("---------->");
                scanf("%c", &command);
            }

            write(fd[1], &command, sizeof(command));
            if (choice == 1)
                sleep(1);

        } while (command != 'M');
        close(fd[1]);
        wait(NULL);
        return 1;
    }
    else
    {
        close(fd[1]);
        control(fd);
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
    printf("1 for file input or 2 for interative input");
    for (i = 0; i < 33; i++)
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
    printf("---------->");
    fflush(stdin);
}