#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include <time.h>
#include <stdlib.h>
int N=5;//cantidad de procesos
int K=3;//cantidad de "rondas"
int J=2;//numero maldito
pid_t array_hijos_id[5];

int generate_random_number(){
    srand(time(NULL)^getpid());
    return rand()%(N);
}
void terminar_procesos_malditos(){
    int numero_random=generate_random_number();
    if(numero_random==J){
        printf("Me mori %d \n",getpid());
        exit(0);
    }
    //DECIDIR SI EL NUMERO ES MALDITO
    //DECIR SUS ULTIMAS PALABRAS 
    //EN CASO CONTRARIO SOBREVIVIR 
}
void terminar_procesos_restantes(){
    exit(0);
}

void conseguir_pid_hijo_muerto(){
   
    pid_t pid_hijo_muerto = wait(NULL);
    for(int i=0;i<N;i++){
        if(array_hijos_id[i]==pid_hijo_muerto){
            array_hijos_id[i]=-1;
        }
    }
}
int main(){
   
    signal(SIGCHLD,conseguir_pid_hijo_muerto);
    for(int i=0;i<N;i++){
        array_hijos_id[i]=fork();
        if(array_hijos_id[i]==0) {
            //CASO HIJO
            signal(SIGTERM,terminar_procesos_malditos);
            signal(SIGKILL,terminar_procesos_restantes);
            while(1){
                pause();
            }
        } else{
            //CASO PADRE
        }

    }
    //iteramos sobre cada ronda 
    for(int i=0;i<K;i++){
        //iteramos sobre cada hijo
        for(int j=0;j<N;j++){
            if(array_hijos_id[i]==-1)continue;
            else{
                kill(array_hijos_id[i],SIGTERM);
                sleep(1);
            }
        }
    }            
    //KILL EM ALL    
    for(int i=0;i<N;i++){
        if(array_hijos_id[i]!=-1){
            printf("GANE! SOY %d \n",array_hijos_id[i]);
            kill(SIGKILL,array_hijos_id[i]);
            //wait(); hace falta?    
        }
    }
    return 0;
}