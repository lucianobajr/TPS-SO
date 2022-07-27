#include "../../headers/log/log.h"

void logger(char *text, int color)
{
    if (color == ERROR_COLOR)
    {
        printf("\033[38;5;1m");
    }
    else if (color == DEBUG_COLOR)
    {
        printf("\033[38;5;3m");
    }
    else if (color == COMMUN_COLOR)
    {
        printf("\033[38;5;68m");
    }

    printf("%s", text);
    printf("\033[0m");
}