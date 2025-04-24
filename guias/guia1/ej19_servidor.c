#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


int main(){
    int server_socket;
    int client_socket;
    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;
    unsigned int slen = sizeof(server_addr);
    unsigned int clen = sizeof(client_addr);
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");
    unlink(server_addr.sun_path);

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    bind(server_socket, (struct sockaddr *) &server_addr, slen);
    listen(server_socket, 1);
    printf("Escuchando a clientes");
    while(1) { 
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &clen);
        int input=0;
        int i;
        while(input<50 || i==0){
           i = recv(client_socket,input,sizeof(input),0);
           input++;
           print("PONG: %d",input);
           write(client_socket, input, sizeof(input));
        }
    }

}
