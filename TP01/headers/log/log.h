#ifndef LOG_H
#define LOG_H

#define ERROR_COLOR 0
#define DEBUG_COLOR 1
#define COMMUN_COLOR 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void logger(char *text, int color);

#endif