# Guia 0

## Ejercicio 1 (Comandos de información)

Utilizar man para responder las siguientes preguntas:

a) ¿Qué hace el comando whoami?

Printea el nombre asociado del userID actual

b) ¿Qué hace el comando uname? ¿Para qué sirve la opción -a?

Printea System information,con la opción a printea toda la infromación del sistema (operativo)

c) ¿Qué hace el comando id?

Printea la infrmación del usuario y de grupo para cada usuario
d) ¿Qué hace el comando ps? ¿Para qué sirve la opción -e?

Muestra la información de un grupo selecto de procesos, con -e se muestran todos los proceso

e) ¿Qué hace el comando top? ¿Qué sucede al ejecutar top -n 10?

Muestra todos los procesos/threads manejados por el kernel de linux , -n 10 especifica la cantidad de "frames" en las que top tiene que seguir ejecutandose

## Ejercicio 2 (Inspeccionar archivos y directorios)

- **pwd** devuelve la ruta absoluta de tu directorio actual
- **ls** sirve para listar todos los archivos en tu directorio actual

  - para ver los archivos de cualquier directorio: ls [PATH_TO_DIRECTORY]
  - al ejecutar ls / se devuelve root?
  - ls /bin para analizar todo sus archivos
- Consultá el manual para ls y explicá para qué sirven estas opciones:

  | Opción | Descripción                                                                    |
  | ------- | ------------------------------------------------------------------------------- |
  | -a      | no ignora a las entries que empiezen con .                                      |
  | -d      | solo printea los directories                                                    |
  | -h      | printea en el tamaño de un archivo formato legible para humanos                |
  | -l      | usa un formato "long listing"                                                   |
  | -S      | Sortea por tamaño de archivo,tamaño descendiente                              |
  | -t      | Sortea por tiempo,descendiente                                                  |
  | -r      | Invierte el orden del sorting (te muestra info de los permisos de cada archivo) |

**iv**. ¿Qué resultado se obtiene de ejecutar ls -la /etc?

    Se obtiene el long list con todas las entries del directorio  /etc

# Ejercicio 3  (Creando archivos y directorios)

**mkdir:** Utilizado para crear directorios

**cd:** **C**hange **D**irectory

**touch:** Crear Archivo

**stat:** para ver las modificaciones del archivo

| Símbolo | Path al que refiere |
| -------- | ------------------- |
| ∼       | Directorio Home     |
| /        | Directorio Root     |
| .        | Directorio actual   |
| ..       | Directorio padre    |

# Ejercicio 4 (Manejo de archivos y directorios)

**find**: nos sirve para encontrar archivos en X directorios
    - **-name**: flag de find que nos ayuda a encontrar archivos con cierto nombre, podemos usar esto para enviarle:
        -"*.formato" para encontrar a **todos los archivos** con formato .formato

**rm**: borra archivos
    - **-i** te pregunta antes de borrarlos por completo
    - **-r** para borrar directorios con **todo su contenido**
**rmdir**: borra directorios **si estan vacios**
**mv**: para mover archivos y renombrarlos
**cp**: para copiar
**chmod**: le otorga permisos a un archivo (r,w,x) + (u,g,o) + (+,-)
    **EJ**: chmod -r archivo_misterioso.txt le saca los permisos de lectura a todos los usuarios
            chmod +r archivo_misterioso.txt se los vuelve a agregar 
            chmod o+r archivo_misterioso.txt le da permisos de lectura solo a 'other'


## List files in long format

Type the ls -l command to list the contents of the directory in a table format with columns including:

    - content permissions (primera columna usuario,segunda grupo,tercera other) 
    - number of links to the content
    - owner of the content
    - group owner of the content
    - size of the content in bytes
    - last modified date / time of the content
    - file or directory name

# Ejercicio 6 (Archivos de texto: ver contenido)

**cat**: muestra el contenido de un archivo (si es muy largo solo te muestra la primera parte)
**more**: empezas desde el principio y con barra espaciadora cambias de pagina, salis con q o con spacebar
**less**: podes bajar con flechitas o con avpag o repag
**obs**: ni con more ni con less se vuelve a la linea de comando a llegar al final del archivo
**head**: devuelve las 10 primeras lineas de un archivo, con -<numero> se devuelve las primeras <numero> lineas
**tail**: lo mismo que head pero con las ultimas 10 lineas 

# Ejercicio 7 (Archivos de texto: extraer líneas y campos)

**grep**: especificas un patron y busca las lineas que cumplan con ese patrón 
    - **-n**: devuelve el line number del output
    - **-c**: devuelve las lineas que matchearon
    - **-i**: ignora si es mayus o minus 
    - **-v**: selecciona las que no matchean con los parametros dados
    - **-w**: selecciona a los matcheados que dan palabras completas

cuts TODO 