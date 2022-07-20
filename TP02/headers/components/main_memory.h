#ifndef MAIN_MEMORY_h
#define MAIN_MEMORY_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 

// 2*1024
// Processo tem 2 MB de memória
#define MEMSIZE 2048 // em KBs
#define SIZE 10

typedef struct{
    int empty;
    int allocated;
} main_memory;

/*
* gera o arquivo .dat de memoria
*/
void generate();

/* 
* retorna um único vetor, para armazenar as  variáveis dos 
* processos simulados.  
*/
main_memory *init_main_memory();

/*
*  Irá alocar o processo no primeiro espaço livre do array
*/
void first_fit(main_memory *memory, int process_size);

/*
* Firt fit porém ele começa como o primeiro ajuste para encontrar
* uma partição livre, mas quando chamado na próxima vez, ele 
* começa a procurar de onde parou, não desde o início.
*/
void next_fit(int blockSize[], int m, int processSize[], int n);

/*
* Irá percorrer toda a lista para encontrar o espaço que 
* desperdiçará o mínimo possível
*/
void best_fit(main_memory *memory, int process_size);

/*
* Irá percorrer toda a lista para encontrar o espaço que
* “desperdiçará” o máximo possível, esse espaço desperdiçado
* pode ser depois alocado para outro processo
*/
void worst_fit(main_memory *memory, int process_size);

/*
* printa o espaço de memória
*/
void print_main_memory(main_memory memory, int executing);

/*
* Retorna o valor de teto do range aleatório do processo
*/
int highest_value_in_memory(main_memory *memory);

#endif