#include "main_memory.h"
#ifndef VIRTUAL_MEMORY_h
#define VIRTUAL_MEMORY_h

// Needs to decide the size of everything

const int PAGE_TABLE_SIZE = 256;
const int BUFFER_SIZE = 256;
const int PHYS_MEM_SIZE = 256;
const int TLB_SIZE = 16;

typedef struct TLB
{
    unsigned char TLBpage[16]; // Paging
    unsigned char TLBframe[16];
    int ind; //To address each allocated block
}TLB;

int readFromDisk (int pageNum, char *PM, int *OF);
int findPage(int logicalAddr, char* PT, struct TLB *tlb,  char* PM, int* OF, int* pageFaults, int* TLBhits);

#endif