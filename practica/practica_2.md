# Practica 2 IPC (inter-process communications)

Ya sabemos como enviar señales, pero como hacemos para enviar *información*
Ahi es donde vienen los mecanismos de IPC! Vamos a ver un ejercicio con Pipes y con sockets

- El forkeado y el forkeador **no comparte memoria**

## Pipes 
Cuando creamos un pipe,es un buffer que esta en memoria y es FIFO

- **File descriptor**: numero que indexa en una FDT(File Descriptor Table)
    - Los mas conocidos son stdin,stdout,stderr 
- Los pipes son **unidireccionales**
- Archivos/Descriptores:
    - open
    - close
    - read
    - write 
- exec no crea nuevos procesos
- C no tiene manejo de errores 
- Podemos usar pipes para hablar entre un padre y un hijo! 
- **Read**: Operación bloqueante 
    - a blocking read operation on a file or network socket will wait until data is available before returning.

- ¿Como sabemos cuando se dejo de escribir?
Aca se introduce el EOF, que se ejecuta cuando hay 0 referencias en el pipe para buffers de escrituras 



## Ejercicio 3
Escriba un programa que cuenta los numeros pares en cierto rango.

Master -> workers...
¿Como estructuramos a este esquema?
    - pipes
    - pipe resultado donde todos los workers tienen acceso a este pipe 
      para mandar los resultados 
    - como le digo a cada worker el rango que tiene que procesar?
    - el proceso primario le informara a cada proceso el rango asignado con pipes 
    - en total tenemos n+1 pipes

    - proceso primario
        - crear los pipes
        - crear los procesos secundarios 
        - . . .

## Sockets
necesitamos otro mecanismo para comunicación entre procesos en diferentes computadoras,
pipes no podemos usar por que no comparten memoria

Un socker es el extremo de una conexión, constituida por una dirección ip y un puerto

Does procesos que se quieren comunicar deben ponerse de acuerdo usando los sockets correspondientes

Los **sockets** pueden trabajar en distintas máquinas 

Sólo se deben conocer de antemano las direcciones ip y los puertos utilizados para la conexión 

Cuando un socket es creado, el programa tiene que especificar el dominio de dirección y el tipo de socket
    - los dominios de direccion mas usados 
        - unix domain 
        - intenet domain 
    - Hay dos tipos de sockets 
        - stream sockets : tratan la comunicación como un stream continuo de caracteres
        - Datagram sockets: tiene que leer todo de corrida 

Servidor

- **Socket**:crea el socket 
- **Bind**: Bindeate a X puerto  
- **Listen**: Podes empezar a recibir conecciones 
- **Accept**: Bloqueante,esperando la conexión con el cliente

Cliente 
- Socket: crea el socket
- Connect: conecta a un socket remoto que debe estar escuchando 