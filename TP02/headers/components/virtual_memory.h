#ifndef VIRTUAL_MEMORY_h
#define VIRTUAL_MEMORY_h

#include "main_memory.h"
#include <time.h>
#include <stdbool.h>

#define PAGE_TABLE_SIZE 256
#define BUFFER_SIZE 256
#define PHYS_MEM_SIZE 256
#define TLB_SIZE 16

// Page Table - 2^8 entradas
// TLB - 16 Entradas
// Page Size - 2^8 bytes
// Frame Size - 2^8 bytes
// Physical memory - 256 frames x 256 frames


typedef struct TLB
{
    unsigned char TLB_page[TLB_SIZE]; // Paginação
    unsigned char TLB_frame[TLB_SIZE]; // Moldura
    int ind;
}TLB;

/*
 *  Gera os endereços de forma randômica com um range de 0 a 65536
 */
void generate_address();
/*
 * Lê o endereço do disco
 */
int read_from_disk (int page_num, char *PM, int* OF);
/*
 * Encontra a página na memória virtual
 */
int find_page(int logical_addr, char* PT, TLB *tlb, char* PM, int* OF, int* page_faults, int* TLB_hits);
/* 
 *  Associar cada bloco da memória a um endereço virtual
 */
int made_address(main_memory *main_memory);

#endif