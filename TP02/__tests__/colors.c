#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("\e[42m");
    for (int i = 0; i < 10; i++)
    {
        printf(" ");
    }
    printf("[10kb] \e[0m\e[47m");

    for (int i = 0; i < 20; i++)
    {
        printf(" ");
    }

    printf("[20kb] \e[0m\n");

    //--------------------------
    printf("\e[41m");
    for (int i = 0; i < 15; i++)
    {
        printf(" ");
    }
    printf("[15kb] \e[0m\e[47m");

    for (int i = 0; i < 20; i++)
    {
        printf(" ");
    }

    printf("[20kb] \e[0m\n");

    return 0;
}