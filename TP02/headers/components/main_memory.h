#ifndef MAIN_MEMORY_h
#define MAIN_MEMORY_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 

// 4096*1024
// Processo tem 4096 MB de memória
#define MEMSIZE 4194304
#define SIZE 100

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
void first_fit(int blockSize[], int m, int processSize[], int n);

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
void best_fit(int blockSize[], int m, int processSize[], int n);

/*
* Irá percorrer toda a lista para encontrar o espaço que
* “desperdiçará” o máximo possível, esse espaço desperdiçado
* pode ser depois alocado para outro processo
*/
void worst_fit(int blockSize[], int m, int processSize[], int n);

#endif