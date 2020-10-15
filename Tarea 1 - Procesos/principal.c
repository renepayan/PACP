#include "procesos.h"
#include "defs.h"
#include "helper.h"
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
int main(void){
	register int i;
	pid_t[3] pids;
	int* datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);
	for(i = 0;i < NUM_PROC; i++){
		pids[i] = fork();
		if(pids[i] == -1){
			perror("Error al crear al hijo\n");
			exit(EXIT_FAILURE);
		}
		if(!pids[i]){
			procesoHijo(i, datos);
		}
	}
	procesoPadre(pids);
}
