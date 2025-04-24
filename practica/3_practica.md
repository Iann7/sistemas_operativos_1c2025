# Practica 3 (Scheduling)
## Repaso 
- **Multiprogramación**: tener proceso corriendo todo el tiempo para maximizar la utilizacion del CPU 
- Solo un proceso puede correr a la vez, los demas esperan 

## Rafagas de IO y CPU 
- la ejecución de un proceso consiste en un ciclo, entre ejecución de CPU y espera por IO 
- la ejecución siempre comienza con una rafaga de CPU, luego le sigue una rafaga de IO, ad infinitum
- un programa **intensivo en IO** por lo general usa rafagas de CPU coritas 
- un programa **intensivo en CPU** por lo general usa rafagas de CPU largas 
- Esto nos puede determinar politicas de scheduling 
## preemptive o nonpreemptive
    - **nonpreemptive o cooperativo**: sin desalojo. Una vez que un proceso obtiene la CPU. ejecuta la libraria de forma voluntaria -> si termina o si pasa a estado waiting 
    - **preemptive o no cooperativo**: Con desalojo. El schedulere puede determinar cuando sacarle a la CPU a un proceso. 
## Criterios y objetivos 
- **Maximizar uso de CPU**: mantener la CPU tan ocupada como sea posible
- **Maximizar Throughput**: cantidad de procesos terminados por unidad de tiempo
- **Minimizar Turnaround**: Mide cuanto le toma a un proceso terminar de ejecutar, cuenta **TODO** el ciclo de vida del proceso, inclusive los momentos donde no hace nada.
- **Minimizar Waiting time**: Cuanto espera un proceso a ser ejecutado,el momento en el que esta *ready* pero no esta ejecutandoo 
- **Minimizar Response Time**: Tiempo transcurrido desde que el proceso es "lanzado"
### ¿Como sabemos que una politica de shceduling es mejor que la otra?
- hay que definir los criterios para comparar
- para edir bien, deberiamos considerar muchos procesos con muchas rafagas de CPU e IO 
- por simplicidad en la materia vamos a considerar solo algunas rafgas de CPU por por proceso y comparar por waiting time y turnaround **promedio**.
- En general solo vamos a pensar en un unico core 

## Politicas 
### First-Come, First-Served (FCFS)
- es cooperativo
- se da el procesador al primero proceso que lo pide
- en gral se pone al final de la cola 
- **Diagrama de gantt**
- context switch lo vamos a considerar despreciable en gral 
- **Convoy effect**
    - largest process comes after you, and it increases the waiting time 
### Round Robin 
- el scheduler va siguiendo la cola ready en orden de llegada de cada proceso. dandole la CPU a cada proceso por un *quantum* de tiempo.
- Si se mete en una rafaga de IO antes de terminar su *quantum* el scheduler la desaloja 
- **¿que pasa si tengo un quantum muy rapido?** 
    - vas a tener un response time muy malo
- **¿que pasa si tengo un quantum muy chiquito?**
    - vas a tener un *overhead* muy grande (muchos context switches)
## Shortest Job First 
Se asocia a cada proceso el largu de su proxima rafaga de CPU y se elige para ejecutar el proceso que tenga la menor 
- SJF es optimo respecto al waiting time prometido, pero no se implementa en la practica por que no se puede saber la longitud de la proxima rafaga de CPU. se puede aproximar,pero es dificil
## Prioridad 
Se asocia a cada proceso una prioridad y se elige para ejecutar el proceso as prioritario en estado ready 
- **¿Que pasa si constantemente llegan procesos de alta prioridad?**
    - **Starvation**
        - la forma de prevenir esto es **Aging**: gradualmente incrementar la prioridad de los procesos que estan esperando hace mucho 
    - Con preemtion hay un poco de mitigiación de la Starvation 
- El tipo de proceso e define la prioridad 
- **¿Cuanto cuesta buscar en la cola ready el proceso con mayor prioridad?**
    - O(N)
- La prioridad es **absoluta**
## Multilevel queue 
se mantienen colas separadas para los diferentes niveles de prioridad 
- Una forma de particionar procesos:
    - Real time 
    - Interactivo 
    - Procesos batchs 
- Multilevel feedback queue: se permite al proceso cambiarse de cola
- Por lo general las real time tienden a ser IO 
- Capped aging 
- Tener en cuenta con un multilevel feedback queue scheduling: 
    - Cuantas colas vas a usar
    - que politica tiene cada cola 
    - por que pasaria un proces de una cola a otra 
    - por que bajariamos la prioridad de un proceso    
    - ¿Puede haber starvation?¿Por que?¿Puedo evitarlo?¿como?

## Ejercicio de diseño
- Hay tareas interactivas -> RR
    - esto sale rapido 
    - mucha io
    - poca entrada de CPU
- eventualmente se lanzan alarmas -> FCFS 
    - son urgentes 
    - real time 
    - a lo sumo una por sucursal 
    - puede sonar una alarma a la vez 
- Nos interesa el response time
- posibilidades de starvation
    - entre los procesos interactivos no puede haber starvation_ todos ejecutaran su quantum a su tiempo
    - entre los procesos de alarma no puede haber starvation:quneue lleguen constantemente alarmas, se resolveran rapido y permitiran pasar a las siguientes 
    - entre colas podria existir starvation en caso de llegar constantes alarmas 
        - pero si pasa eso medio que no me importa por que se me esta quemando todo 
## Sistemas tiempo real 
- **soft real time** 
- **hard real time** 
- **Event Latency**: el tiempo que pasa entre que ocurre un evento hasta que el proceso RT se ejecuta
- un sistema RT debe soportar un algoritmo de scheduling basado en **prioridades con preemption**
- **Earliest Deadline First** 
 