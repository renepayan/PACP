#include "procesos.h"
#include "defs.h"
#include "helper.h"
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
int main(void){
	register int i;
	pid_t pid;
	int* datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);
	for(i = 0;i < NUM_PROC; i++){
		pid = fork();
		if(pid == -1){
			perror("Error al crear al hijo\n");
			exit(EXIT_FAILURE);
		}
		if(!pid){
			procesoHijo(i, datos);
		}
	}
	procesoPadre();
}
