#ifndef CONTROL_H
#define CONTROL_H

#define TAM 30

#include "./management.h"
#include "./scheduling.h"

/*
 * Primeiro print menu
 */
void print_menu1();

/*
 * Processo Controle
 */
int control();

/*
* Substitui o programa do processo simulado pelo programa
no arquivo nome_do_arquivo e define o contador de programa
para a primeira instrução desse novo programa.
*/
void instruction_b(management process_manager);

/*
 *  Imprime o tempo médio do ciclo e finaliza o sistema.
*/
void command_m(pid_t pid2, management process_manager, int size, int total_of_process, int max_process);

/*
* Desbloqueia o primeiro processo simulado na fila bloqueada
*/
void command_l(int non_blocked_process, management process_manager);

/*
* Imprime o estado atual do sistema
*/
void command_i(pid_t pid, management management, int size, int total_of_process, int max_process);

#endif