#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../headers/util/process.h"

/*
 * Função para calcular os comandos de controle (U L I M)
 */
void control(int fd[]);

#endif