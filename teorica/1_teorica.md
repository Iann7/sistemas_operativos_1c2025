# Primer teorica Sistemas Operativos

---

## Un poco de historia

### **Decada de 1950:** aparecen las primeras computadoras comerciales. **IBM 7090**

- **Mainframe:**
  las computadoras ocupaban toda una sala.Eran muy caras y solo la podian comprar
  universiadades,empresas grandes;entre ellas se compra la **Clementina** 1961,
  traida por **Sadosky**,en la Argentina habia alguna que otra mas pero se contaban
  con las manos!.

  Operaban con valvulas,tenian que ser cambiadas frecuentemente por que se quemaban.
  Muy engorrosas,se operaban con **Tarjetas Perforadas**,las cuales tenian una grilla
  en donde se perforaba ciertos espacios que representaban un numero,una instrucción de
  lenguaje,etc.
- **Operador** :
  Primer intermediario entre el usuario y el hardware,de ahi sale el termino de
  Sistemas Operativos.Se aseguraba de que el resultado de "María" no se lo diesen a "Pedro".
- **Como aprovechamos el tiempo muerto de estas computadoras?:**
  De ahi nacen las cintas! en donde se aprovecha mucho mas el tiempo de ejecución y **paralelizas** un poco mas la ejecución del programa.
- **Sistemas Batch:** le das un "lote" de tareas a la computadora,en tandas(cada cinta)

### Fast Forward a la siguiente generación: La **IBM/360**

  Ya tenían un sistema operativo mas formal (OS/360)

- **"The mythical man/month" Brux. PARA LEER** : Argumenta como hacer software
- OS/360: Ya mas parecido a los OS mas modernos en terminos de responsabilidades
- **Multiprogramación:**
  Consiste en una manera de aumentar el *throughput* del sistema.
  El trabajo j1 toma el mismo tiempo o mas, pero j1+j2+... toma menos tiempo
- **La contención:**
  Varios programas pueden querer acceder a un mismo recurso a la vez, Problema muy dificil de resolver.La manera en la que los diferentes OS manejan este problema los diferencia muchisimo entre cada uno. **DEADLOCK**
- **El sistema batch es un bajón:**
  Empiezan a aparecer un sistema interactivo, donde podía darle al OS comandos!(desde la terminal). Se permite tener **varias terminales** trabajando al mismo tiempo
- Fun fact: las computadoras se ponian en el subsuelo con la idea de calentar a todo el edificio en invierno(polo norte)
- **Timesharing**:
  Variación de la multiprogramación,aprovecha los tiempos muertos de cada usuario para prestarle atención a los otros,dando la sensación de que esta atendiendo a todos en tiempo real cuando no es asi.
  -El pionero de este paradigma fue **MULTICS**,del que desciende **UNIX** *(Ken Thompson,Dennis Ritchie)*

  - **UNIX**: La rama "ganadora". Incluso **Windows** que no desciende de ahi toma muchas ideas de UNIX
  - **MINIX**: Modelo juguete de UNIX,creado por Tanenbaum.
  - **LINUX**: Inspirado en UNIX

## Como leer un disquette!

1. Empaquetar **13 parametros en 9 bytes**(Dirección del bloque, sectores por track,modo de acc fisico,separacion entre sectores)
2. Esperar un rato!
3. El controlador del floppy devuelve 23 campos de status y error empaquetados en 7 bytes
4. Prender y apagar explicitamente el motor,si se deja prendido el disquette se desgasta....

- **Tarea para el hogar:**
  tomar una computadora sin SO y hacer un programa que lea nombres del disco,los ordene y vuelva a escribir ordenados
- **La magia del OS es no tener que hacer este quilombo**,nos facilita la vida!

## Pasando en limpio

- UN SO es una pieza de software que hace de intermediario entre el Hardware y el usuario
- Tiene que manejar la contención y la concurrencia de manera tal de lograr:
  - Hacerlo con buen rendimiento
  - Hacerlo correctamente
- EL OS siempre corre en nivel de privlegio 0(máximo privilegio)

### Veamos cúanto ocupan algunos sistemas operativos:

- FreeBSD (2009): 5 CDs de instalación
- Ubuntu 24.04 LTS: 25gb de espacio
- Windows 11: 11.64gb

### Que es y que no es un OS

Por mucho que algunas cosas vengan **con** el Sistema Operativo,no necesariamente **SON** el Sistema Operativo

- El minesweeper no es parte del OS
- El task manager no es parte del OS
- La terminal tampoco es parte del OS

En esta materia no vamos a ver como desarrollar todo lo anterior, si no que vamos a ver como desarrollar un **Kernel** Del OS.

- Shell=Interfaz de usuario. Ejemplos en Unix: sh,csh,ksh,bash.
- La terminal carga un shell. shell != terminal?
- Cuando un programa esta corriendo, se lo llama **Proceso**
- **Archivo**: secuencia de bits con un nombre y una serie de atributos
- **Directorio**: colección de archivos y directorios que contiene un nombre y se organiza jerarquicamente
- **Dispositivo virtual**: una abstracción del dispositivo fisico bbajo la forma,en gral, de un archivo, de manera tal que se pueda abrir,leer,escribir,etc.
- **Sistema de archivos**: es la forma de organizar los datos en el disco para gestionar su acceso,permiso,etc.
- **Directorios del sistema**: son directorios donde el propio SO guarda archivos que necesita para su funcionamiento
- **Binario del sistema**: son archivos que viven en los directorios del sistema.No forman parte del kernel pero son clave
- **Usuario**: personas o entidades que puedan usar el OS. Sirve principalmente como una forma de aislar información entre si
- **Grupo**: una colección de usuarios

#### Pero entonces,que es un OS?

1. un admin de recursos
2. una interfaz de programación

## Procesos y API del SO

- Vamos a ver que cosas hay detrás del concepto del proceso
- Y que abstracciones nos presenta el SO para lidiar con ellas
- Es decir. Una parte de la API del SO
- Cuando un programa se **pone a ejecutar**.Lo que tenemos es un **proceso**
- A cada proceso se le asigna un **id**
- En **memoria** el proceso esta compuesto por:
  - Area de texto
  - Area de datos
  - Stack de proceso
  - Las variables locales se almacenan en el stack
- **¿Que puede hacer un proceso?**
  - Terminar
  - Lanzar un proceso hijo (system(),fork(),exec())
  - hacer un system call
  - Realizar entrada/salida a los dispositivos

### Actividades de un proceso

#### Terminación

- El proceso indica al sistema operativo que ya puede liberar sus recursos (exit())
- Indica su estado de terminación
- Este estado de terminación se le indica al **padre**

##### Árbol de procesos

- En realidad,todos los procesos estan organizados jerarquicamente,como un árbol.
- Cuando el SO comienza,lanza un proceso que se suele llama init o systemd
- Por eso es importante la capacidad de lanzar un proceso hijo:
  - **fork()** es una llamada al sistema que crea un proceso **exactamente** igual al actual
  - El resultado es el pid del proceso hijo,que es una copia exacta del padre
  - El padre peude decidir suspenderse hasta que termino el hijo,llamado wait()
  - cuando el hijo termina, el padre obtiene el codigo de status del hijo
  - El proceso hijo puede hacer lo mismo que el padre o algo distinto.O algo distinto
    En ese caso puede reemplazar su codigo binario por otro,llamado **exec()**
- Cuando lanzamos un programa desde el shell, lo que pasa es:
  - El shell hace un fork()
  - El hijo hace un exec()
  - **TIP:** si le agregamos un & a lo ultimo el padre no se queda en **wait()**

### Ejecutar en la CPU

- Una vez que el proceso esta ejecutándose,se dedica a:

  - hacer operaciones entre registros y dir de memoria
  - E/S
  - llamadas al sistema(Syscall)
- **Imaginemos el programa mas elemental, que solo hace lo primero**

  - **¿Por cuanto tiempo lo dejamos ejecutar?** (recordemos que solo un proceso puede estar en la CPU)
    - Hasta que termina (Lo mejor apra el proceso,pero no para el sistema, **puede NO terminar**)
    - Un "ratito". Ese "ratito" se llama **quantum**
- En general los SO modernos hacen **preemption**: cuando se acaba el **quantum**,le toca el turno al siguiente proceso
- **Surgen dos preguntas**

  - Que y a quien le toca
  - Que significa hacer que se ejecute otro proceso
- Para cambiar el programa que se ejecuta en la CPU. debemos Guardar mucha infromación **(Contexto)**
- A esto se le llama el **cambio de contexto/content switch**
- El IP y demas registros se guardan en una estructura de datos llamado **PCB(Process Control Block)**
- Notemos: el tiempo utilizado en cambios de contexto es **tiempo muerto**.Dos consecuencias de esto

  - Impacto en la atquitectura del HW: procesadores RISC
  - Fundamental determinar un **quantum** apropiado para minimizar los cambios de contexto

#### llamadas al sistema

Ya vimos algunas, exec(),fork(),etc.

También hay llamadas al sistema en actividades mucho mas comunes,como imprimir en pantalla a la larga termina llamando a write()

En todas ellas se debe llamar al **kernel**. A diferencia de una llamada de a subrutina

Estan definidas en el archivo unistd.h de la biblioteca estandar de C. Puede verse una lista de todas ellas usando **man syscalls**

las **syscalls** proveen una interfaz a los servicios brindados por el SO

### E/S

Es lenta,quedarse bloqueado esperando es un **desperdicio de tiempo**,ya que involucra **Busy Waiting**, es decir,gastar ciclos de CPU.

- Busy waiting : el proceso no libera CPU
- Polling : El proceso libera la cpu, pero todavia recibe un quantum que desperdicia hasta que la e/s es terminada
- Interrupciones: esto permite la multiprogramacion

## Scheduler

Aparece un componente esencial del SO, el scheduler o planificador. Su funcion es decidir a que proceso le corresponde ejecutar en cada momento.

- Es una parte fundamental del kernel
- Pocas cosas tienen **mayor impacto** en el rendimiento de un SO que su politica de *scheduling*

## Syscalls en Linux

2 niveles de privilegio

## POSIX

Portable Operating System Interface

- Core services:
  - Creacion y control de procesos
  - Pipes
  - Señales
  - Op de archivos y directorios
  - Excep
  - Errores del bus
  - Biblioteca de C

## Multi...

- Multiprocesador: Equipo con >1 procesador
- Multiprogramacion: la capacidad de un SO de tener varios programa en ejecución
- Multiprocesamiento: Parecido a lo anterior,en general se refiere mas al procesamiento que sucede en un multiprocesador
- Multitarea: es una forma especial de multiprogramación. Donde la conmutación entre procesos se hace de manera tan rapida que da la sensación que esta corriendo en simultaneo
- Multithread: son programas(procesos) en los cuales hay varios mini procesos corriendo en paralelo(de manera real o ficticia como en la multiprogramación)
- Multiuso: Nada que ver con la materia jijo.

## Multiprogramación desde el codigo

Hay alguna syscalls que permiten continuar al codigo si un proceso no termino. If not respuesta continua

## Estado de un proceso

- Terminado:
- Listo: Listo para ser ejecutado
- Corriendo: Usando la CPU
- Bloqueado: No puede ejecutar hasta que algo externo suceda

**Nota** carga del sistema = cantidad de procesos listos

- Es responsabilidad del sheduler elegir el siguiente proceso a ejecutar

## Señales

Son un mecanismo que incorporan los sistemas opeartivos POSIX y que permite notificar a un proceso
la ocurrencia de un evento

Cuando un proceso recibe una señal,su ejecución se interrumpe y ejecuta un **handler**

Cada tipo de señal tiene asociado un handler **por defecto**

Toda selak tiene asociado un numero que identifica su tipo. Estos numeros estan definidos como constantes en el header

Las señales SIGKILL y SIGSTOP **No pueden ser bloqueadas**,ni se pueden reemplazar su handlers 

Un usuario puede enviar desde la terminal una señal a un proceso con el comando kill. Un proceso puede enviar una señal a otro mediante la syscall kill()

- **Demonios** Procesos que estan corriendo siempre 


