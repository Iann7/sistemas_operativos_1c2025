#include<sys/wait.h>
#include<stdio.h>
int main(){
    printf("Abraham");
    pid_t id = fork();
    printf("EL ID ES: %d \n",id);
    if(id==0){
        printf("Homero");
        id = fork();
        printf("EL ID ES: %d \n",id);
        if(id==0){
            printf("Bart");
            exit(0);
        }else{
            wait(NULL);
        }
        id=fork();
        printf("EL ID ES: %d\n",id);
        if(id==0){
            printf("Lisa");
            exit(0);
        } else wait(NULL);
        id=fork();
        printf("EL ID ES: %d\n",id);
        if(id==0){
            printf("Maggie");
            exit(0);
        } else wait(NULL);
        exit(0);
    } else{
        wait(NULL);
        exit(0);
    }
    return 0;
}