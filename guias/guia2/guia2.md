# Guia 2 
## Ejercicio 2 
Sean P0, P1 y P2 tales que
- P0 tiene ráfagas cortas de E/S a ciertos dispositivos.
- P1 frecuentemente se bloquea leyendo de la red.
- P2 tiene ráfagas prolongadas de alto consumo de CPU y luego de escritura a disco.
- a) Para planificar estos procesos, ¿convendría usar un algoritmo de Round Robin? ¿convendría
    usar uno de prioridades? Justifique su respuesta
    - PROS de RR: 
        - Es justo entre procesos
        - Evita starvation, o al menos no tiene ese problema 
    - CONS de RR:
        - No tiene prioridades
        - Procesos de rafagas cortas de CPU pueden tener tiempos de respuesta altos 
    - PROS de Prioridad: 
        - nos permite priorizar procesos de rafagas de CPU cortas para que tengan un response time mas corto
        - permite optimizar el tiempo de respuesta 
        - puede mejorar la eficiencia global del sistema 
    - CONS de Prioridad:
        - puede llevarnos a starvation si se aplica con FCFS que es el standard 
    Yo me quedo con RR por el tema de starvation, si tenemos procesos bloqueantes nos puede tranquilamente poner en una situación de starvation 
## Ejercicio 3 
El proceso representa un FCFS por que cuando el proceso esta en proceso *running* o se termina o sea bloquea por algun E/S
pero nunca le devuelve el tiempo de CPU al scheduler
## Ejercicio 4 
¿Cuáles de los siguientes algoritmos de scheduling pueden resultar en starvation (inanición) y en
qué condiciones?
- a) Round-robin.
- b) Por prioridad.
- c) SJF.
- d) SRTF.
- e) FIFO.
- f) Colas de multinivel.
- g) Colas de multinivel con feedback (aging)

De las politicas anteriores, las que nos pueden llevar a starvation son:
- Por prioridad
- SJB (Shortest Job First)
    - al darle prioridad a los proceso que se bloquean primero, si se tienen muchos procesos que se bloquean al mismo tiempo podes tener starvation 
- SRTF 
    - por las mismas razones que SJB 
- FIFO 
    - en el caso en el que un proceso nunca termine 
- Colas de multinivel
    -  si por que depende de como implementes las colas 
## Ejercicio 5 
Considere una modificación a round-robin en la que un mismo proceso puede estar encolado varias
veces en la lista de procesos ready. Por ejemplo, en un RR normal se tendrían en la cola ready a
P1,P2,P3,P4, con esta modificación se podría tener P1,P1,P2,P1,P3,P1,P4.

- a) ¿Qué impacto tendría esta modificación?
    Hacer esto es como tener un quantum dinamico segun el tipo de proceso,eso implica darle una prioridad 
    a un proceso antes que a otro 
- b) Dar ventajas y desventajas de este esquema. Piense en el efecto logrado, no en la forma de
implementarlo.
    - La ventaja es que podemos darle un quantum especifico y "dinamico" dependiendo del tipo de proceso
    - lo malo es que al no tener una politica definida de como handlear estos casos podriamos tener starvation
    - generamos desigualdades entre procesos  
- c) ¿Se le ocurre alguna otra modificación para mantener las ventajas sin tener que duplicar las
entradas en la lista de procesos ready?
    - cambiar el quantum
    - 

## Ejercicio 13
Explicar cómo los siguientes algoritmos favorecen (o desfavorecen) a los trabajos más cortos:
- a) FIFO.
    - Dependiendo del orden de llegada puede favorecer o desfavorecer (leer *Convoy Effect*)
- b) Round-robin.
    - si el quantum es bajo esto prioriza a los trabajos mas cortos, si el quantum es alto puede haber un proceso 
    con mucho tiempo en CPU lo que puede desfavorecer al trabajo corto
- c) Multilevel feedback queue.
    - Una de las prioridades de este algoritmo de scheduling es justamente priorizar trabajos mas cortos 

## Ejercicio 14
Se tiene un sistema donde hay trabajos interactivos y de procesamiento de datos. Los de procesa-
miento de datos leen archivos inmensos, hacen pequeñas cuentas y los vuelven a grabar.
Se desea que los usuarios interactivos tengan la sensación de buen tiempo de respuesta, pero sin
perjudicar excesivamente el throughput del sistema.
El scheduler puede funcionar con round-robin o con FCFS. ¿Qué política utilizaría y por qué?
Justificar especialmente por qué la política elegida permite cumplir con ambos objetivos del sistema

como se nos pide que los usuarios interactivos tengan la sensación de buen tiempo de respuesta necesitamos si o si 
no podemos usar FCFS, ya que implicaria que nos entre un trabajo de mucho uso de CPU, generando una mala sensación en el tiempo de respuesta. Por eso elijo RR, que nos permite dar un tiempo de respuesta aceptable dependiendo del quantum, mientras procesamos los programas con rafagas grandes. Habria que hacer un fine tuning del quantum 
## Ejercicio 15 
Una seriografía es una técnica para el estudio de los órganos en movimiento. Se realiza utilizando
un aparato llamado seriógrafo, que ejecuta varias radiografías por segundo y muestra en una pantalla
una serialización digital de estas imágenes, dando como resultado una especie de video.
Existen seriógrafos que permiten editar algunas características de las imágenes a medida que se
van generando, mientras se está llevando a cabo el estudio médico. Entre otras cosas, permiten ajustar
el brillo y el contraste de las imágenes, y hacer zoom-in y zoom-out. Así, se permite una edición “en
vivo” del video.
Se tienen entonces los siguientes procesos:
- uno que genera las imágenes digitales a partir de los valores resultantes al irradiar al paciente
- uno que responde a los botones de ajuste de brillo y contraste
- uno que responde a los botones de ajuste de zoom
¿Qué política de scheduling permite esta toma y edición de imágenes “en vivo” de manera eficiente?
Justificar. 

Cualquier politica de scheduling que priorize rafagas cortas de CPU para tener una buena respuesta de cambio de brillo y zoom balanceando los procesos con alto tiempo de CPU. **No podemos tener starvation**

Por ende, las politicas de scheduling que no podríamos usar son:
- FIFO/FCFS
- Prioridad 

Las que considero que son convenientes usar son:
- Round Robin 
- Colas multinivel con aging 