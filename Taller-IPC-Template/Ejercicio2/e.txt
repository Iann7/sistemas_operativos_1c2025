#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"

// ejemplo: ./anillo N C S
// creamos un anillo de N procesos
// Padre le manda C a S
// S genera P 
// S manda C a su hermano comenzando una ronda
// Si C <= P empieza otra ronda
// Si no, le dice al padre C
int cant_pipes;
// int generar_secreto(int c){
// 	return c * 2;
// }

int pipe_anterior(int nro_hijo){
	if(nro_hijo == 0){
		return cant_pipes-1;
	}
	return nro_hijo - 1;
}

void crear_pipe(int pipe_fds[2]){
	if(pipe(pipe_fds)){
		perror("Error al crear las pipes");
	}
}
void cerrar_RW_pipe(int pipe_fds[2]){
	close(pipe_fds[PIPE_READ]);
	close(pipe_fds[PIPE_WRITE]);
}
void cerrar_pipes_lejanos(int nro_hijo,int pipe_fds[][2],int cant_pipes){

	for (int i = 0; i < cant_pipes ; i++){	
		if (i != nro_hijo && i != pipe_anterior(nro_hijo)){

			// cerrar_RW_pipe(pipe_fds[i]);
			close(pipe_fds[i][PIPE_READ]);
			close(pipe_fds[i][PIPE_WRITE]);
		}
	}
}

void hijo_start(int nro_hijo, int pipe_fds[][2],int pipes_fds_hijo_importante[2]){
	// int p = generate_random_number() + c + 51;
	int p = 10;
	int nro_actual=0;
	read(pipe_fds[pipe_anterior(nro_hijo)][PIPE_READ], &nro_actual, sizeof(int));
	printf("Hola soy hijo start. P es %d\n", p);
	while (1){
		printf("START: nro actual es %d\n", nro_actual);
		printf("START: Leo de %d y escribo en %d\n", pipe_anterior(nro_hijo), nro_hijo);
		if(p < nro_actual){
			// mandarle al padre
			printf("Nos pasamos de P! Volviendo a papa\n");
			break;
		} 
		else{
			//  printf("START: Le paso %d al que sigue\n", nro_actual);
			write(pipe_fds[nro_hijo][PIPE_WRITE], &nro_actual, sizeof(int));

			read(pipe_fds[pipe_anterior(nro_hijo)][PIPE_READ], &nro_actual, sizeof(int));
			//  printf("START: Me pasaron %d\n", nro_actual);

			nro_actual++;  
		}
	}
	// cerrar_RW_pipe(pipe_fds[pipe_anterior(nro_hijo)]);
	// cerrar_RW_pipe(pipes_fds_hijo_importante);
	write(pipes_fds_hijo_importante[PIPE_WRITE],&nro_actual,sizeof(int));
	close(pipe_fds[nro_hijo][PIPE_READ]);
	close(pipe_fds[nro_hijo][PIPE_WRITE]);
	close(pipe_fds[pipe_anterior(nro_hijo)][PIPE_READ]);

	close(pipe_fds[pipe_anterior(nro_hijo)][PIPE_WRITE]);
	close(pipes_fds_hijo_importante[PIPE_READ]);
	close(pipes_fds_hijo_importante[PIPE_WRITE]);	
	close(pipe_fds[nro_hijo][PIPE_WRITE]);
	exit(EXIT_SUCCESS);
}

void hijo_normal(int nro_hijo, int pipe_fds[][2]){
	close(pipe_fds[pipe_anterior(nro_hijo)][PIPE_WRITE]);
	int seguir_leyendo = 1;
	int nro_actual;
	while(seguir_leyendo){
		printf("%d: Leo de %d y escribo en %d\n", nro_hijo,pipe_anterior(nro_hijo), nro_hijo);
		seguir_leyendo = read(pipe_fds[pipe_anterior(nro_hijo)][PIPE_READ],&nro_actual,sizeof(int));
		//  printf("HIJO %d: Me pasaron %d\n", nro_hijo, nro_actual);
		if(seguir_leyendo == 0){break;}
		
		nro_actual++;
		//  printf("HIJO %d: Pasando %d\n", nro_hijo, nro_actual);
		write(pipe_fds[nro_hijo][PIPE_WRITE], &nro_actual,sizeof(int));
		
	}   

	
	printf("hieeee\n");
	//cerrar_RW_pipe(pipe_fds[nro_hijo]);
	close(pipe_fds[nro_hijo][PIPE_WRITE]);
	close(pipe_fds[nro_hijo][PIPE_READ]);

	
	//cerrar_RW_pipe(pipe_fds[pipe_anterior(nro_hijo)]);
	close(pipe_fds[pipe_anterior(nro_hijo)][PIPE_READ]);
	close(pipe_fds[pipe_anterior(nro_hijo)][PIPE_WRITE]);
	exit(EXIT_SUCCESS);
}



void ejecutar_hijo(int nro_hijo,int start,int pipes_fds[][2],int pipes_hijo_importante[2]){
	cerrar_pipes_lejanos(nro_hijo,pipes_fds,cant_pipes);
	if(nro_hijo==start){
		hijo_start(nro_hijo,pipes_fds,pipes_hijo_importante);
		}
	else{
		//cerrar_RW_pipe(pipes_hijo_importante);
		close(pipes_hijo_importante[PIPE_READ]);
		close(pipes_hijo_importante[PIPE_WRITE]);
		hijo_normal(nro_hijo,pipes_fds);
	}
}

int generate_random_number(){	return (rand() % 51);
}

int main(int argc, char **argv)
{	
	//Funcion para cargar nueva semilla para el numero aleatorio
	srand(time(NULL));

	int status, pid, n, start, buffer;
	n = atoi(argv[1]);
	buffer = atoi(argv[2]);
	start = atoi(argv[3]);

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}
    
  	/* COMPLETAR */
    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer, start);
	int  pipes_fds[n][2];
	int  pipe_fds_hijo_importante_padre[2]; 
	pid_t childs[n];
	cant_pipes=n;

	crear_pipe(pipe_fds_hijo_importante_padre);
	
	for (int i=0;i <cant_pipes;i++){
		crear_pipe(pipes_fds[i]);
	}
    for(int i = 0; i < cant_pipes; i++){
		pid = fork();
		//CASO HIJO
		if(pid == 0){
			// printf("SOY HIJO %d\n",i);
			ejecutar_hijo(i,start,pipes_fds,pipe_fds_hijo_importante_padre);
			break;
		} 
		//CASO PADRE 
		else if(pid > 0){
			childs[i] = pid;
		} 
		//CASO ERROR
		else{
			printf("Hubo un error al crear el hijo");
			exit(1);
		}
	}
	
	int c;
	// After creating all pipes and before waiting for the result
	write(pipes_fds[start][PIPE_WRITE], &buffer, sizeof(int));

	for (int i=0;i <cant_pipes;i++){
		close(pipes_fds[i][PIPE_READ]);
		close(pipes_fds[i][PIPE_WRITE]);	
	}
	close(pipe_fds_hijo_importante_padre[PIPE_WRITE]);	
	read(pipe_fds_hijo_importante_padre[PIPE_READ], &c, sizeof(int));
	close(pipe_fds_hijo_importante_padre[PIPE_READ]);
	printf("%d \n", c);
	for(int i=0;i<n;i++){
		wait(NULL);
	}

	exit(0);
}
