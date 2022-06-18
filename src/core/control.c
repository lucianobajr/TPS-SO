#include "../../headers/core/control.h"

void control()
{
    FILE *file_pointer;

    char data_to_be_read[50];
    scanf("%c", &data_to_be_read);

    file_pointer = fopen(data_to_be_read, "r");

    if (file_pointer == NULL)
    {
        printf("File is empty!!!");
    }
    else
    {
        while (file_pointer != EOF)
        {
            switch (fgetc(file_pointer))
            {
            case 'U':
                
                break;
            case 'L':
                
                break;
            case 'I':

                break;
            case 'M':

                break;
            default:
                break;
            }
        }
    }
}