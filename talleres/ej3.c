#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include <time.h>
#include <stdlib.h>
int contar=0;
char *path_programa; 

void algun_handler_padre(){
    wait();
    exit(0);
}

void algun_handler(){
    contar++;
    printf("Ahi va! \n");
    if (contar==5){
        kill(getppid(),SIGINT);
        execvp(path_programa, NULL);
    }
}

int main(int argc, char *argv[]){
    path_programa = argv[1];
    signal(SIGINT,algun_handler_padre);

    pid_t pid_hijo = fork();
    if(pid_hijo==0){    
        
        signal(SIGURG,algun_handler);
        while(1){
        }
    }else{
        for(int i=0;i<5;i++){
            sleep(1); 
            printf("sup\n");
            kill(pid_hijo,SIGURG);
        }
        while(1);
    }

    return 0;
}