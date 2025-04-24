# Practica Cuatro 
- Que pasa si hay variables compartidas entre dos o mas procesos?
- Que sucede al mezclar la concurrencia y memoria compartida?
## Atomicidad
### Operación Atomica 
Una operación es atómica cuando es **indivisible**. Es decir, cuando no puede ser interrumpida por el scheduler
- Variable atomica 
    - una variable atomica es un objeto que nos permite realizar operacions de manera atomica 
## Semaforos
- Signal o Wait 
- Es un tipo abs de datos que permite controlar el flujo del sistema 
- sem() devuelve un nuevo semaforo
- wait()
- signal()
- **No podemos saber cual es el proceso que se despierta en un signal**
- ¿Puedo consultar el valor de un semaforo? NO 
- ¿como podemos usar semaforos para resolver el problema de antes?
 