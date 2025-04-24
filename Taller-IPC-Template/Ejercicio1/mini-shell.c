#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "mini-shell-parser.c"
int cant_pipes;
int cant_procesos;
enum pipes_read_writes {READ,WRITE};
void ejecutar_programa(char **argumentos,int indice_children,int pipes_fds[][2]){
	cerrar_pipes(pipes_fds);
	//CASO Solo Un Proceso
	if(cant_procesos==1){
		execvp(argumentos[0],argumentos);
	}else{
		//CASO Primer Proceso
		if(indice_children==0){

		}
		//CASO Proceso Medio 
		else if(indice_children!=0 && indice_children!=(cant_procesos-1)){

		} 
		//CASO Proceso Ultimo 
		else{

		}
	}
	
}
void cerrar_pipes(int pipes_fds[][2]){
	for(int i=0;i<cant_pipes;i++){
		close(pipes_fds[i][READ]);
		close(pipes_fds[i][WRITE]);
	}
}
int run(char ***progs,int count)
{	
	int r, status;
	//Reservo memoria para el arreglo de pids
	//TODO: Guardar el PID de cada proceso hijo creado en children[i]
	pid_t *children = malloc(sizeof(*children) * cant_procesos);
	int pipes_fds[cant_procesos][2];
	cant_procesos=count;
	cant_pipes = count-1;
	for(int i=0;i<cant_pipes;i++){
		if(pipe(pipes_fds[i])){
			printf("Pipe failed\n");
			exit(1);
		}
	}
	for(int i=0;i<cant_procesos;i++){
		pid_t pid = fork();
		//CASO HIJO
		if(pid==0){
			ejecutar_programa(progs[i],i,pipes_fds);
		} 
		//CASO PADRE
		else if(pid>0) {
			children[i]=pid;
		} 
		//CASO ERROR
		else {
			printf("Hubo un error al crear hijo %d",i);
			exit(1);
		}
	}
	cerrar_pipes(pipes_fds);
	//TODO: Para cada proceso hijo:
			//1. Redireccionar los file descriptors adecuados al proceso
			//2. Ejecutar el programa correspondiente

	//Espero a los hijos y verifico el estado que terminaron
	for (int i = 0; i < count; i++) {
		waitpid(children[i], &status, 0);

		if (!WIFEXITED(status)) {
			fprintf(stderr, "proceso %d no terminó correctamente [%d]: ",
			    (int)children[i], WIFSIGNALED(status));
			perror("");
			return -1;
		}
	}
	r = 0;
	free(children);

	return r;
}


int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("El programa recibe como parametro de entrada un string con la linea de comandos a ejecutar. \n"); 
		printf("Por ejemplo ./mini-shell 'ls -a | grep anillo'\n");
		return 0;
	}
	int programs_count;
	char*** programs_with_parameters = parse_input(argv, &programs_count);

	printf("status: %d\n", run(programs_with_parameters, programs_count));

	fflush(stdout);
	fflush(stderr);

	return 0;
}
