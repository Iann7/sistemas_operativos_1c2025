#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int init_or_finnish =0;
int cuenta=0;
pid_t id_hijo=-1;
void manejar_ping(int sig){
    cuenta++;
    if(cuenta<4) printf("PING!\n");
    kill(getppid(),SIGUSR1);
    if(cuenta==4){
        kill(getppid(),SIGUSR2);
        exit(0);
    }
}

void manejar_pong(){
    cuenta++;
    printf("PONG!\n");
    if(cuenta<4) kill(id_hijo,SIGUSR1);
    else{
        wait();
        exit(0);
    }
}

void init(){

    if (init_or_finnish==0){
        kill(id_hijo,SIGUSR1);
        init_or_finnish++;
    }
    else{
        wait();
        exit(0);
    }
}
int main(){
    signal(SIGUSR2,init);
    id_hijo = fork();
    if (id_hijo==0){
        signal(SIGUSR1,manejar_ping);
        kill(getppid(),SIGUSR2);
        //envolvemos el pause en while true para hacer el ping pong una N cantidad de veces en ves de una sola
        while(1){
            pause();
        }
    }else{
        signal(SIGUSR1,manejar_pong);
        while(1){
            pause();
        }
    }
}