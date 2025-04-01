int main(int argc, char const *argv[]){
int dato = 0;
pid_t pid = fork();
//si no hay error, pid vale 0 para el hijo
//y el valor del process id del hijo para el padre
if (pid == -1) exit(EXIT_FAILURE);
//si es -1, hubo un error
else if (pid == 0) {
for (int i=0; i< 3; i++) {
dato++;
printf("Dato hijo: %d\n", dato);
}
}
else {
for (int i=0; i< 3; i++) {
printf("Dato padre: %d\n", dato);
}
}
exit(EXIT_SUCCESS); //cada uno finaliza su proceso
}

# Guia 1

# Ejercicio 1

**¿Cuáles son los pasos que deben llevarse a cabo para realizar un cambio de contexto?**
Para cambiar el programa que se ejecuta se necesita:

- Guardar los registros
- Guardar el IP(Instruction Pointer)
- Si es un programa nuevo, cargarlo en memoria
- Cargar los registros del nuevo
- Cargar el IP del nuevo
- y mucho mas
  A esto se lo llama un **Context switch**

# Ejercicio 2

`Ke_context_switch(PCB* pcb_0, PCB* pcb_1){`

pcb_0.STAT =KE_READY;

ke_reset_current_user_time();

//guardar todo el pcb en algun lugar/estructura?

set_current_process(pcb_1.P_ID);

ret();

`}`

# Ejercicio 3

¿Cual es la diferencia entre una *system call* y una llamada a función de biblioteca?

En una system call hay si o si un cambio de privilegio por que en definitiva, son las llamadas que usan los programas
con menos privilegio para poder a acceder a funcionalidades del kernel, una función de biblioteca no necesariamente se comunica con el kernel para devolver el resultado esperado

# Ejercicio 4

- Corriendo

  - Puede ir a:
    - Bloqueado: La ejecución se interrumpe por algun evento/señal y queda bloqueada
    - Terminado: La ejecución termino todo lo que tenia que hacer y se queda en el status terminado
    - Listo: Quizas cuando se acaba el quanto pasa de corriendo a listo sin pasar por bloqueado? Quizas el proceso devuelve el control al scheduler?
- Listo

  - Puede ir a:
    - Corriendo: el proceso es elegido por el scheduler para que corra
- Bloqueado

  - Puede ir a:
    - Listo: el scheduler determina que la aplicación puede volver a correr y la desbloquea
- Terminado

  - No va a ningun lado(sad)
- Nuevo

  - Puede ir a ready: el scheduler prepara a la aplicación para ser ejecutada

# Ejercicio 5

a)
Utilizando únicamente la llamada al sistema fork(), escribir un programa tal que construya un
árbol de procesos que represente la siguiente genealogía: Abraham es padre de Homero, Homero es
padre de Bart, Homero es padre de Lisa, Homero es padre de Maggie. Cada proceso debe imprimir
por pantalla el nombre de la persona que representa.

Se puede hacer mucho mas facil, hay codigo repetido pero no me esmere mucho en hacerlo:

```

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
```

b) Modificar el programa anterior para que cumpla con las siguientes condiciones: 1) Homero termine
sólo después que terminen Bart, Lisa y Maggie, y 2) Abraham termine sólo después que termine
Homero.

Creo que el codigo anterior ya cumple lo pedido

**OBSERVACIÓN**: El codigo imprime dos veces Abraham y dos veces Homero, aunque no estoy muy seguro de que genera este efecto,PREGUNTAR?

# Ejercicio 6

El sistema operativo del punto anterior es extendido con la llamada al sistema
void exec(const char *arg). Esta llamada al sistema reemplaza el programa actual por el código
localizado en el string (char *arg). Implementar una llamada al sistema que tenga el mismo compor-
tamiento que la llamada void system(const char *arg), usando las llamadas al sistema ofrecidas
por el sistema operativo. Nota: Revisar man system, como ayuda

`system_falso(const char *arg){`

pid_t id = fork();

if (id==0){

exec(arg);

} else{

//habra que hacer algo para el proceso padre?

}

`}`

# Ejercicio 8

¿Son iguales los resultados mostrados de la variable dato para el padre y para el hijo? ¿Qué está
sucediendo?

A mi parecer los datos deberían ser lo mismo por que los dos empiezan con dato=0 y el for loop es el mismo,pero dato padre no hace dato++

# Ejercicio 9 

