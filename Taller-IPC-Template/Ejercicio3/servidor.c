#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>



int calcular(const char *expresion) {
    int num1, num2, resultado;
    char operador;

    // Usamos sscanf para extraer los dos números y el operador de la expresión
    if (sscanf(expresion, "%d%c%d", &num1, &operador, &num2) != 3) {
        printf("Formato incorrecto\n");
        return 0;  // En caso de error, retornamos 0.
    }

    // Realizamos la operación según el operador
    switch (operador) {
        case '+':
            resultado = num1 + num2;
            break;
        case '-':
            resultado = num1 - num2;
            break;
        case '*':
            resultado = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                resultado = num1 / num2;
            } else {
                printf("Error: División por cero\n");
                return 0;  // Si hay división por cero, retornamos 0.
            }
            break;
        default:
            printf("Operador no reconocido\n");
            return 0;  // Si el operador no es válido, retornamos 0.
    }

    return resultado;
}

void aaa(int client_socket,int server_socket){
    printf("Esperando cuenta desde ");
    while(1){
        char input[100]={0};
        int i = recv(client_socket,input,sizeof(input),0);
        if(i==0 || strcmp(input, "exit") == 0){
            printf("Hay que salir!!!\n");
            //close(server_socket); PREGUNTAR
            close(client_socket);
            break;
        }else{
            int res=calcular(input);
            printf("El resultado de la operación es: %d\n", res);
            send(client_socket, &res, sizeof(res),0);
        }
    
    }
    exit(0);
}


int main() {
     

    int server_socket;
    int client_socket;
    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;
    unsigned int slen = sizeof(server_addr);
    unsigned int clen = sizeof(client_addr);
    int num;

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");
    unlink(server_addr.sun_path);

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    bind(server_socket, (struct sockaddr *) &server_addr, slen);
    listen(server_socket, 1);

    printf("Servidor: esperando conexión del cliente...\n");

    //Loop para aceptar conexiones nuevas.   
    while(1) { 
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &clen);
        pid_t pid_hijo = fork();
        
        if(pid_hijo==0){
            printf("HIYAA");
            //aaa(client_socket,server_socket);
        } else{
            continue;
        }
    }
    printf("PROBANDO PRINTF");
     exit(0);
}

