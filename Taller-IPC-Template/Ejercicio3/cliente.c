#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
	int server_socket;
    struct sockaddr_un server_addr;

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error");
        exit(1);
    }

    printf("Me conecte\n");


     
    while(1){
        char cuenta[100];
        printf("Ingrese una cuenta: ");
        scanf("%s", cuenta);
        if (strcmp(cuenta, "exit") == 0) {
            printf("Saliendo...\n");
            close(server_socket);
            break;
        }
        write(server_socket, cuenta,  strlen(cuenta) + 1); // ???
        int res=-1;
        read(server_socket, &res, sizeof(res));
        printf("Cliente: recibí %d del servidor!\n", res);
	}


    return 0;
	//  char *cuenta = "2+3";
    //  write(server_socket, cuenta,  strlen(cuenta) + 1); // ???
	//  printf("SE ENVIO EL WRITE!");
	//  int res=-1;
	//  read(server_socket, &res, sizeof(res));
    //  printf("Cliente: recibí %d del servidor!\n", res);
    //  close(server_socket);
    //  exit(0);

}
