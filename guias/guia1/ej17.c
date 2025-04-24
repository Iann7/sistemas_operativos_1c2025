#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"
int crear_pipe(int pipe_fds[2]){
    int temp = pipe(pipe_fds);
	if(temp){
		perror("Error al crear las pipes");
	}
    return temp;
}
int dameNumero(int pid){
    return 0;
}
int calcular(int numero){

}
void ejecutar_hijo(int pipe_hijo[2],int nro_hijo,int fds_pipes[][2],int N, int fds_pipes_vuelta[2]){
    int nro_secreto=0;
    close(pipe_hijo[PIPE_WRITE]);
    close(fds_pipes_vuelta[PIPE_READ]);
    
    read(pipe_hijo[PIPE_READ],&nro_secreto,sizeof(int));
    nro_secreto +=100;

    write(fds_pipes_vuelta[PIPE_WRITE],nro_secreto,sizeof(int));
    close(fds_pipes_vuelta[PIPE_WRITE]);
    exit(0);
}
void cerrar_pipes_lejanos(int nro_hijo,int pipe_fds[][2],int cant_pipes){

	for (int i = 0; i < cant_pipes ; i++){	
		if (i != nro_hijo){
			// cerrar_RW_pipe(pipe_fds[i]);
			close(pipe_fds[i][PIPE_READ]);
			close(pipe_fds[i][PIPE_WRITE]);
		}
	}
}
int main(){
    int N=2;
    int fds_pipes[N][2];
    int fds_pipes_vuelta[N][2];
    int children[N];
    for(int i=0;i<N;i++){
       crear_pipe(fds_pipes[i]);
       crear_pipe(fds_pipes_vuelta[i]);
    }
    for(int i=0;i<N;i++){
        children[i]=fork();
        //CASO HIJO
        if(children[i]==0){
            cerrar_pipes_lejanos(i,fds_pipes,N);
            cerrar_pipes_lejanos(i,fds_pipes_vuelta,N);
            ejecutar_hijo(fds_pipes[i],i,fds_pipes,N,fds_pipes_vuelta[i]);
        }
        //CASO PADRE
        else if(children[i]>0){

        } 
        //CASO ERROR
        else {

        }
    }
    //PADRE
    for(int i=0;i<N;i++){
        int numero_secreto=i;
        write(fds_pipes[i][PIPE_WRITE],numero_secreto,sizeof(numero_secreto));
        close(fds_pipes[i][PIPE_WRITE]);
        close(fds_pipes[i][PIPE_READ]);
    }
    for(int i=0;i<N;i++){
        int resultado_i=0;
        close(fds_pipes_vuelta[i][PIPE_WRITE]);
        read(fds_pipes_vuelta[i][PIPE_READ],&resultado_i,sizeof(int));
        close(fds_pipes_vuelta[i][PIPE_READ]);
        wait(NULL);
    }
    return 0;
}