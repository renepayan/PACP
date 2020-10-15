#ifndef PROCESOS_H
#define PROCESO_H
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int procesoHijo(int np, int* datos);
void procesoPadre(pid_t pids[4]);
#endif
