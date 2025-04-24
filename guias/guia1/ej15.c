#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int p[2];
int main(){
pid_t hijo_ls = fork();
if(pipe(p)==-1){
    perror("pipe");
    exit(1);
}
if(hijo_ls !=0){
    pid_t hijo_wc = fork();
    if(hijo_wc==0){
        //CASO HIJO WC 
        close( p[1] );
        dup2(p[0], STDIN_FILENO); // Redirect stdin to read end of pipe
        close(p[0]); // Close duplicated read end
        execlp("wc","wc","-l",NULL);
    } else{
        //CASO PADRE
        close( p[0] );
        close( p[1] );
    }
}else{
 //CASO HIJO_LS
 close(p[0]);
 dup2(p[1],STDOUT_FILENO);
 execlp("ls","ls","-l","-a",NULL);
}

}