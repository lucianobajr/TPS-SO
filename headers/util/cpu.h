#ifndef CPU_h
#define CPU_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Cpu{
    int current_value = 0;
    float time_slice;
    //Adicionar os registradores para armazenar os dados, como?
    
}Cpu;

typedef struct CellType *PointerType;
typedef struct CellType
{
    Cpu cpu;
    PointerType next;
}CellType;

typedef struct{
    PointerType First, Last;
} ListType;

#endif

