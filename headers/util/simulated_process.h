#include "cpu.h"
#ifndef SIMULATED_PROCESS_h
#define SIMULATED_PROCESS_h

typedef struct
{
    program *program;
    int* memory;
    int number_of_vars;
    int pc;
} simulated_process;

/* 
* Aloca uma quantidade de memória para as variáveis do processo simulado. 
* O valor desta quantidade é informado para a função
*/
void instruction_n(int number_of_variable_to_declare, int** memory);

/* 
* Após a memória do processo ter sido alocada,
* atribui o valor 0 para para a variável do índice especificado 
*/
void instruction_d(int index_of_variable_declared, int** memory);

/* 
* Define algum valor númerico para uma determinada variável do vetor 
* de memória do processo 
*/
void instruction_v(int index, int value, int** memory);

/* 
* Efetua a adição de um valor informado sobre alguma das variáveis 
* do vetor de memória do proccesso
*/
void instruction_a(int index, int value, int** memory);

/* 
* Efetua a subtração de um valor informado em alguma das variáveis
* do vetor de memória do processo
*/
void instruction_s(int index, int value, int** memory);

#endif