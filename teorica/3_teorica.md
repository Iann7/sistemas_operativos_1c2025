# Tercera teorica - Sincronización entre procesos 

- Los OS en particular com la *multitarea* (varias cosas "a la vez" en un procesador) es donde se manifesto con mas claridad
- Concurrente vs paralela
- para ganar escala se programa de esta manera 
- chat esta bien esto chat? 
- **The more the merrier**
  - rapidamente esto trae problemas 

## Veamos un ejemplo - colecta solidaria
- Fondo de donaciones. Sorteo entre los donantes, hay que dar numeros 
- Tenemos solo un unico procesador 
### supongamos que dos procesos corren el mismo programa
- hay un problema de sincronización para el acceso de información compartida  
- **Condiciones de carrera** / **Race Conditions**
  - Significa que el resultado podria llegar a ser invalido para alguno de los scheduling posibles del programa 
  - es responsabiilidad de los programadores asegurarnos del funcionamiento correcto del programa ante cualquier scheduling **posible**
  - "la peste de la programación"
- este programa tiene una Race condition por que hay al menos un scheduling que hace incompatible el resultado 
- **¿Que podemos hacer al respecto?**
  - secciones criticas(alias CRIT)
    - determinamos una parte del programa donde requerimos **exclusión mutua**
    - **exclusión mutua**: esta parte no podemos procesarla de manera paralela
    - Solo hay un proceso a la vez en la seccion CRIT
    - todo proceso esperando a entrar a CRIT, entrará a CRIT
    - Ningun proceso fuera de CRIT puede bloquear a otro 
  - **a nivel de codigo se implementaría con dos llamadas:uno para entrar y otro para salir de crit**
  - **¿Se soluciona revoleando booleanos?**
    - sigue habiendo un problema de sincronización entre los bools 
    - ya que el mecanismo de exclusión mutua sigue estando atado al scheduler
  - otra alternativa es pedirle al OS es cuando entramos a CRIT suspenda al desalojo, pero trae muchisimos problemas
### Test And Set (TAS) 
- Solo sirve para poner una variable entera y ponerle un uno 
- instrucción que brinda el hardware con la garantia de que esto se ejecuta de **manera atomica (i.e indivisible)**
- no puede ser interrupido 
- siempre pone un uno pero te devuelve si antes habia un uno o un cero 
- si me devuelve un uno perdi, no fui yo el que puse el uno 
- si no gane y me llevo el lock jijubi 

### Con TAS resolvimos el problema,pero es eficiente? 
No esta muy bueno por que tenemos un big ass bottleneck 
Esto se llama **Busy Waiting** y no esta del todo bueno por que estas malgastando recursos esperando 
podemos poder un sleep! aunque no esta claro cuanto deberia durar el sleep, si es muy chico seguimos teniendo un busy waiting menos agresivos pero al fin y al cabo sigue siendo un busy waiting 

### Productor-Consumidor 
- Dijkstra propone resolver el problema de productor-consumidor (i.e bounded buffer) es un versión mas general del problema que estamos viendo.
- La idea es que tenemos un proceso que genera elementos que los va poniendo en un buffer(proceso productor), y hay otro (proceso consumidor) que los va agarrando
- **Lost wakeup problem**: se pierde de vuelta por una raised condition 

### SEMAFOROS - Dijkstra invento los semáforos(de computadora)
- Dijkstra, cooperating Sequential Processes
- Una variable con la siguientes caracteristicas:
  - Se la puede inicializar en cualquier valor
  - Solo se la puede manipular entre dos operaciones 
  - Una se llama  **wait** y otra se llama **signal** (tambien se llaman down o up)
  - La idea conceptual de **wait** es que mientras S sea NEGATIVA ME VOY A MIMIR Y cuando me despierten voy a decrementar a S
  - Lo que hace signal es incrementar S y si hay alguien esperando al semaforo le digo al sched que despierte a algun proceso, que lo ponga en ready  
- Semaforo de exclusión mutua(SEMAFORO BINARIO,MEJOR CONOCIDO COMO MUTEX) 
- Los semaforos pueden ser una solución a estos problemas **si se usan bien** pero son **dificiles de usar** ya que hay que estar muy muy atentos a los waits y a los signal 

### DEADLOCK
situación en la que un proceso esta esperando algo de otro y ese otro esta esperando algo del primero, ahi se genera un deadlock

el 90% de las colgadas de los sistemas UNIX eran por deadlocks hace un tiempo

### Spin locks  

- Hacer un wait o un signal en un semaforo puede ser **computacionalmente caro**
- los TAS no requieren pasar a modo kernel,solo hardware especializado(practicamente todo los procesadores de proposito general)
- como es tan rapido lo que voy a hacer el spinning de otros va a ser despreciable 

## Condiciones de coffman 
- Postula una serie de condiciones necesarias para la existencia de un deadlock
- El modelo tiene algunas falacias 
  - Exclusión mutua
    - un recurso no puede estar asignado a mas de un proceso
  - Hold and wait
    - los proceso que ya tienen algun recurso pueden solicitar otro 
  - Preemption
    - no hay mecanismo compulsivo para quitarle los recursos a un proceso 
  - Espera circular
    - Tiene que haber un ciclo de n>=2 procesos, tq pi espera a un recurso que tiene pi+1