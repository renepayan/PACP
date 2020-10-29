#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_HILOS 4
#defin N 16

int *A, *B, *C;
void* funHilo( void* arg );
int* reservarMemoria();
void llenarArreglo( int* datos );
void imprimirArreglo( int* datos );

int main(void){
	int* hilo;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	register int nh;
	srand( getpid() );
	A = reservarMemoria();
	B = reservarMemoria();
	C = reservarMemoria();
	
	llenarArreglo( A );
	llenarArreglo( B );
	
	imprimirArreglo( A );
	imprimirArreglo( B );	
	
	for( nh = 0; nh < NUM_HILOS; nh++){
		nhs[nh] = nh;
		pthread_create(  &tids[nh], NULL, funHilo &nhs[nh] );
	}
	for( nh = 0; nh < NUM_HILOS; nh++ ){
		pthread_join( nhs[nh], (void**)&hilo);
		printf("Termino el hilo %d", *hilo);
	}
	imprimirArreglo(C);
	free(A);
	free(B);
	free(C);
	
}
void* funHilo( void *arg){
	int nh = *((int*) arg);	
	register int i;
	printf("Hilo %d en ejecucion\n",nh);
	for(i = nh; i < N; i+=NUM_HILOS){
		C[i] = A[i]*B[i];
	}
	pthread_exit( arg );
}
void llenarArreglo(int* datos){
	register int i = 0;
	for(i = 0; i < N; i++){
		datos[i] = rand();
	}
}
void imprimirArreglo(int* datos){
	register int i = 0;
	for(i = 0; i < N; i++){
		printf("%d ");
	}
	printf("\n");
}
int* llenarArreglo(){
	int* memoria;
	memoria = (int*) malloc(sizeof(int)*N);
	return memoria;
}
