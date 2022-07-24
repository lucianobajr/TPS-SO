#ifndef VIRTUAL_MEMORY_h
#define VIRTUAL_MEMORY_h

#include "main_memory.h"
#include <time.h>
#include <stdbool.h>

// Needs to decide the size of everything
#define PAGE_TABLE_SIZE 256
#define BUFFER_SIZE 256
#define PHYS_MEM_SIZE 256
#define TLB_SIZE 16


typedef struct TLB
{
    unsigned char TLB_page[TLB_SIZE]; // Paging
    unsigned char TLB_frame[TLB_SIZE]; // Offset
    int ind; //To address each allocated block
}TLB;

// Generate address
void generate_address();
//
int read_from_disk (int page_num, char *PM, int* OF);
// Initialize TLB
int find_page(int logical_addr, char* PT, TLB *tlb, char* PM, int* OF, int* page_faults, int* TLB_hits);
// Turn a block of proccess into memory address
int made_address(main_memory *main_memory); 
// Function to translate the virtual address to translate to the physic memory
int compute_address(int address, int index, TLB *tlb);

#endif