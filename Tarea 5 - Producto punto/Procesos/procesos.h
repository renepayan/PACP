#ifndef PROCESOS_H
#define PROCESO_H
#include "defs.h"
void proceso_hijo(int np, int pipefd[], int *A, int *B);
long long int proceso_padre(int pipefd[NUM_PROC][2] );
#endif
