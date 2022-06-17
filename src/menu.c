#include "../headers/menu.h"

int menu(process_table *process_table)
{
    process_table = create_process_table();
    char *file_name = "./data/init.txt";

    reader(process_table,file_name);
    print_process_table(process_table);
}

void reader(process_table *process_table,char *file_name)
{
    int PC = 0, index, numVar, declaration, value;
    char fileN[20];

    srand(time(NULL));

    FILE *file;

    char *buffer = (char *)malloc(sizeof(char));
    file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("\033[38;5;1m");
        printf("Error! File not found!\n");
        printf("\033[0m");
        return;
    }
    else
    {
        while (fscanf(file, "%s", buffer) != EOF)
        {
            process new_process = *create_process(rand() % 100, rand() % 100);

            if (strcmp(buffer, "N") == 0)
            {
                new_process.instructions[PC].command = 'N';
                fscanf(file, "%d", &numVar);
                new_process.instructions[PC].N.value = numVar;
                new_process.size++;
                PC++;
            }
            else if (strcmp(buffer, "D") == 0)
            {
                new_process.instructions[PC].command = 'D';
                fscanf(file, "%d", &index);
                new_process.instructions[PC].D.memory_reference = index;
                new_process.size++;
                PC++;
            }
            else if (strcmp(buffer, "V") == 0)
            {
                new_process.instructions[PC].command = 'V';
                fscanf(file, "%d %d", &index, &value);
                new_process.instructions[PC].operation.values.memory_reference = index;
                new_process.instructions[PC].operation.values.value = value;
                new_process.size++;
                PC++;
            }
            else if (strcmp(buffer, "A") == 0)
            {
                new_process.instructions[PC].command = 'A';
                fscanf(file, "%d %d", &index, &value);
                new_process.instructions[PC].operation.values.memory_reference = index;
                new_process.instructions[PC].operation.values.value = value;
                new_process.size++;
                PC++;
            }
            else if (strcmp(buffer, "S") == 0)
            {
                new_process.instructions[PC].command = 'S';
                fscanf(file, "%d %d", &index, &value);
                new_process.instructions[PC].operation.values.memory_reference = index;
                new_process.instructions[PC].operation.values.value = value;
                new_process.size++;
                PC++;
            }
            else if (strcmp(buffer, "B") == 0)
            {
                new_process.instructions[PC].command = 'B';
                new_process.size++;
                PC++;
            }
            else if (strcmp(buffer, "T") == 0)
            {
                new_process.instructions[PC].command = 'T';
                new_process.size++;
                PC++;
            }
            else if (strcmp(buffer, "F") == 0)
            {
                new_process.instructions[PC].command = 'F';
                fscanf(file, "%d", &value);
                new_process.instructions[PC].F.value = value;
                new_process.size++;
                PC++;
            }
            else if (strcmp(buffer, "R") == 0)
            {
                new_process.instructions[PC].command = 'R';
                fscanf(file, "%s", fileN);
                new_process.instructions[PC].R.file = (char *)malloc(strlen(fileN) * sizeof(char));
                strcpy(new_process.instructions[PC].R.file, fileN);
                new_process.size++;
                PC++;
            }
            else
            {
                printf("\033[38;5;1m");
                printf("\nError! Instruction not found!\n");
                printf("\033[0m");
            }

            insert_process_in_table(process_table, new_process);
        }

        fclose(file);
    }
}