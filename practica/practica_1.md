# Practica 1

- Las **syscalls** las utilizamos mediante la biblioteca estándar de C: unistd.h
  - Hay funciones de C que no son syscalls pero si utilizan syscalls

## Que es un programa?

un conjunto de instrucciones diseñadas para realizar una tarea

## Que es un proceso?

El proceso es una instancia de ejecución del programa

- **Process ID(PID)** : El identificador del proceso actual

## Creación de procesos

-**fork**: crea un nuevo proceso, que es un clon del primero
    - a partir del forkeo cada proceso **corre en espacios de memoria separados**
        - Comparten una dirección virtual,pero no una dirección fisica 
    - al hacer un fork, este le devuelve al padre le devuelve el PID original y al hijo le da 0, para que sepa que es el hijo. De esta forma podemos separar los codigos! :D

### Que pasa si el proceso padre termina su ejecución antes que el hijo?

Lo importante es que si queda huerfano es que el padre sea otro,por lo general
el proceso **init** queda como encargado o tambien quedan como hijos de los **"subreapers"**
que son procesos que se pueden autodeclarar como padres de procesos huerfanos que sean descendientes suyos

### Aclaraciones de Fork-Clone

Cuando se realiza el llamado a fork(). Por debajo se está llamando a la *syscall* clone

- **Wait**: Bloquea al padre hasta que el hijo ca,bie de estado(si no se indica ningun status).El cambio mas comun es cuando el hijo termina su ejecución
    - Si no se hace esta operación, cuando el proceso hijo muere, continua en un **estado zombie**, incluso si el hijo hace **exit**
    - **Por cada fork que hagas, hace un wait**
- **Waitipid**: lo mismo que wair pero espera al proceso correspondiente al pid indicado
- **exit**: Finaliza el proceso actual

### Copy on write
EL OS hace copias *lazy* (Ambos compartirán las mismas paginas fisicas hasta que alguna de ellas cambia de contenido) *"Copy on demand"*

- La familia de las syscalls exec reemplazan la imagen del proceso actual con una nueva. Una de las mas utilizadas es **execve**
    -**execve**:Sustituye la imagen de memoria del programa por la del programa ubicado en filename
    - Se le dice imagen a todo, reemplaza todo en definitiva, arranca un programa nuevo 

## Comunicacion entre proceso
hay dos paradigmas...
### Envio de mensajes 
- por Señales
    - Las señales son un mecanismo que incorporan los OS basados en POSIX,que permiten notificar la ocurrencia de un evento. Para implementarlos en C se usa signal.h

    Otra forma de pensar las señales es con interrupciones 

    **para enviar señales, se usa el comando kill**. Quedo el nombre por que antes la unica señal que habia era, en efecto, kill Loading
- por Pipes
- por Sockets 
### Memoria compartida 
Todavia no lo vimos 

## Señales 
- Sigchild: es enviada por el hijo cuando termina su ejecución/muere 

## Protección 
En linux se distinguen procesos con permisos  privilegiados (root) y no privilegiados
Un proceso **no root** no puede enviar señales a procesos root
Sin embargo, en linux es posible ya que divide los privilegios en **capabilities**, que pueden ser habilitadas o deshabilitadas 

## usando strace
herramienta que nos permite generar una traza legible de las lalmadas al sistema usadas por un programa 
- brk syscalls para pedir memoria 
- mmap para mapear memoria 