#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
int obtenerMayor(int* datos){
	register int i;
	if(N>0){
		int mayor = datos[0];
		for(i = 1; i < N; i++){
			if(datos[i] > mayor){
				mayor = datos[i];
			}
		}
		return mayor;
	}else{
		perror("No hay suficientes datos\n");
		exit(EXIT_FAILURE);
	}
}
int obtenerMenor(int* datos){
	register int i;
	if(N>0){
		int menor = datos[0];
		for(i = 1; i < N; i++){
			if(datos[i] < menor){
				menor = datos[i];
			}
		}
		return menor;
	}else{
		perror("No hay suficientes datos\n");
		exit(EXIT_FAILURE);
	}
}
int obtenerPromedio(int* datos){
	register int i;
	if(N>0){
		long long int suma = 0;
		for(i = 0; i < N; i++){
			suma += datos[i];
		}
		return (int)(suma/N);
	}else{
		perror("No hay suficientes datos\n");
		exit(EXIT_FAILURE);
	}
}
int obtenerNumeroDePares(int* datos){
	register int i;
	if(N>0){
		int numeroDePares = 0;
		for(i = 0; i < N; i++){
			if(datos[i] % 2 == 0){
				numeroDePares += 1;
			}
		}
		return numeroDePares;
	}else{
		perror("No hay suficientes datos\n");
		exit(EXIT_FAILURE);
	}
}