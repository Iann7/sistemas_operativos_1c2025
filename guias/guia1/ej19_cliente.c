#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(){
    int server_socket;
    struct sockaddr_un server_addr;

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error");
        exit(1);
    }
    int input=0;
    int i=0;
    while(input <50|| i==0){
        write(server_socket, input,  sizeof(input));
        printf("PING: %d",input);
        i = recv(server_socket,input,sizeof(input),0);
        input++;
    }

}