# Practica 5
Sabemos desde orga II que la memoria RAM es volatil, el disco es persistente
- **Multiplrogramción**: un monton de procesos listos para ejecutar  
    - ningún proceso debería estar compartido 
    - los procesos no deben pdoer molestarse entre si 
    -  no queremos que esto degrade la eficiencia de uso de CPU y memoria 
- Necesitamos **memory managment**
- La memoria de un proceso es una colección de segmento que ya lo vimos en orga jijo
- Esquema de memoria contigua 
    - se asignan a los proces a partes de memoria de tamaño variable, donde cada una exactamente contiene un proceso
- el OS mantiene una estructura (puede ser un bitmap o una linkedList) indicando que partes de la memoria estan disponibles 
- Los espacios de memoria disponible se ven como un conjunto de "huecos" de varios tamaños dispersos por la memoria. Cuando un proceso llega y necesita memoria, el sistema busca un "hueco con espacio suficiente para este proceso"
- estrategias para asignar memoria
    - **First-fit** : el primero que queda queda 
    - **Best-fit**: asigna el hueco mas chico lo suficientemente grande 
    - **Worst-fit**:asigna el hueco mas grande
- Asignación de memoria contigua 
    - problemas
        - una vez que lo cargue, el proceso no puede cambiar de lugar en la memoria
        - se debe conocer el tamaño del proceso antes de cargarlo 
        - Mientras los procesos se cargan y quitan de memoria, el espacio de memoria libre se fragmenta en pedacitos
- **Fragmentación externa**
    - Cuando hay suficiente memoria para satisfacer un pedido pero los espacios disponibles no son contiguos 
    - ¿Como evitar esto?
        - partir la memoria en bloques de tamaño fijo 
        - permitir que el espacio de direcciones fisicas de los procesos **no sean contiguos**
- **Memoria virtual**
    - problema: interceptar y traducir cada referencia a memoria es caro 
    - Solución: soporte de hardware 
- **MMU**
    - La MMU es un componente de hardware que administra memoria 
## Furfi Flashback
    - Base y limite 
- Estrategia de pasaje de direcciones
- Fragmentación interna: esa parte de la pagina que no estas usando y no se le puede asignar a otro proceso 
- Si no tenemos mucha memoria tiramos alguna cosa al disco duro 
- Con el SSD no estan costoso acceder a disco 
- Cuanto mas page fault tengo mas voy a tardar en accederlo 
- ¿Como se atendia un page fault?
    - cargar la pagina si hay un frame libre 
    - si no desalojar algo 
        - el desalojado se le llama frame victima 
## Reemplazo de paginas 
Si no hay frames libres se erquieren 2 transferencias de paginas, esto duplica el tiempo para atender page faults y el tiempo de acceso efectivo
    - Mejora 1: no todas las pagians deben ser escritas a disco 
    - Mejora 2: usar un bit de modificación(dirty bit) para ver si hay algo modificiado 
## Algoritmos de desalojo
- **FIFO** 
- **LRU**: Least recently used
- **Second Chance**: FIFO pero si justo la use hace poco le doy una segunda chance 
- Le doy una segunda chance y despues lo meto de vuelta a la lista pero a lo "ultimo de la fila" (para representar una ronda circular)
- El problema de FIFO es que no necesariamente lo que pusiste hace mucho no se este usando
- Second chance intenta balancear FIFO y LRU 
- Que algoritmo de reemplazo de paginas es mejor?
    - depende jijo
## Thrashing     
- Un proceso hace **trashing** si pasa mas tiempo cargando y descargando pagians que ejecutando procesos
- En una computadora personal, un usuario puede darse cuenta de que esta ocurriendo thrashing y matar algunos proceso "a mano"
- desde el SO, se pueden limitar los efectos del thrashing usando un reemplazo de paginas locales, es decir, que cada proceso solo pueda tomar frames de los que ya tiene asignados y no pueda robarle a otro proceso. 
- Pero para prevenir el thrashing, deberiamos proveer a un proceso con tantos frames como necesite
- Pero como se cuantos frames necesita un proceso? -> definir un modelo de **localidad** de ejecución 
