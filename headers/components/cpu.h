#ifndef CPU_h
#define CPU_h

#include "./program.h"

typedef struct
{
    program *program;
    int pc;           // referente ao contador do processo simulado em execucao
    int *memory;      // referente a memoria do processo simulado em execucao
    int *size_memory; // referente a qntDeVariaveis do processo simulado em execucao
    int time;         // referente tempoCPU da TabelaDeProcessos
} CPU;

#endif