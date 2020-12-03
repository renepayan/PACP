#ifndef PROCESOS_H
#define PROCESO_H
#include "defs.h"
void proceso_hijo(int np, int pipefd[]);
void proceso_padre(int pipefd[NUM_PROC][2] );
void procesoHijoFuncionDiscreta(int np, int pipefd[]);
void proceso_padre_funcion_discreta(int pipefd[NUM_PROC][2] );
#endif
