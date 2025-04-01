#include <stdio.h>
#include <string.h>
struct cliente{
    char nombre[100];
    char cuil[40];
    __uint8_t edad;
}cliente_t;
void verInfoUsuario(struct cliente *todos_los_clientes,int cant_clientes){
    struct cliente nuevo_cliente;
    int edad=-1;
    char nombre[100];
    printf("Inserte su edad: \n");
    scanf("%d", &nuevo_cliente.edad);
    printf("Inserte su nombre: \n");
    scanf("%s",nombre);
    strcpy(nuevo_cliente.nombre,&nombre);
    strcpy(nuevo_cliente.cuil, "1");
    todos_los_clientes[cant_clientes]=nuevo_cliente;
}
// ME QUEDARIA HACER EL EL REALLOC TODO 
int main(){
    struct cliente *todos_los_clientes = calloc(10,sizeof(cliente_t)); 
    int cant_clientes=0;
    int salir=1;
    printf("BIENVENIDO!\n");
    while (salir)
    {
        char input[]="";

        scanf("%s*", &input);
        if(strcmp(input,"salir")==0) break;
        else if(strcmp(input,"ver")==0){
            verInfoUsuario(todos_los_clientes,cant_clientes);
        }
        printf("DONE!");
    }
    
}

