#ifndef CONTROL_H
#define CONTROL_H

#define TAM 30

#include "./management.h"

void print_menu1();
int control();
void command_i(pid_t pid, management management, int size, int total_of_process, int max_process);
#endif