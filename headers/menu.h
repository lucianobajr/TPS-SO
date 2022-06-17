#ifndef MENU_h
#define MENU_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#include "./util/process_table.h"

/*
*menu
*/
int menu(process_table *process_table);

/*
 * Cada processo simulado é composto de um programa que 
    manipula (define/atualiza) o valor de variáveis inteiras
 * Lê um processo e executa este programa
*/

void reader(process_table *process_table,char *file_name);

#endif