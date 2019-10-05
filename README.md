# Sistema de archivos EXT2/EXT3

Es una aplicacion en consola que simulara un sistema de archivos linux EXT2/EXT3. No distinguira entre mayúsculas y minúsculas. Solo se puede colocar un comando por línea. Toda la informacion se detalla mas en el archivo Fase2.pdf

## Instalacion
- Descargar repositorio
- Abrir el archivo FileSystem_2.pro desde Qt Creator

## Comandos
**A continuacion de se describe la funcion de cada comando. Los parametros y validaciones se encuentran en el enunciado del proyecto(fase2.pdf)**
* FASE 1
  - mkdisk: Creara un archivo binario, simulando un disco duro.
  - rmkdisk: Borrara el archivo.
  - fdisk: Administrara las operaciones que se hagan en una particion como crear, eliminar o quitar espacio.
  - mount: Montara una particion
  - unmount: Desmontara una particion
  - rep: Generara un reporte tipo imagen
  - exec: Ejecutara un archivo con comandos ya escritos. 
* FASE 2
  - mkfs: Realiza el formateo copleto de una particion. 
  - login: Inicia sesion en el sistema de una particion
  - logout: Cierra sesion en el sistema
* Los siguientes comandos *necesitan que exista una sesion en el sistema ya que se ejecuta sobre la particion en la que inicia sesion*
  - mkgrp: Creara un grupo para los usuarios de la particion
  - rmgrp: Eliminara un grupo de la particion
  - mkusr: Crea un usuario en la particion
  - rmusr: Elimina un usuario en la particion
  - chmod: Cambia los permisos de uno o varios archivos o carpetas
  - mkfile: Crea archivo 
  - cat: Muestra el contenido de un archivo
  - rem: Elimina un archivo o carpeta y todo su contenido
  - edit: Edita el contenido de un an achivo para asignarle otro contenido (pendiente)
  - ren: Permite cambiar el nombre de un archivo o carpeta (pendiente)
  - mkdir: Crea carpetas
  - cp: Realiza una copia de un archivo o carpeta y todo su contenido hacia otro destino(pendiente)
  - mv: Permite mover un archivo o carpeta y todo su contenido hacia otro destino
  - find: Realiza una busqueda por el nombre del archivo o carpeta especifica.
  - chown: Cambia el propietario de uno o varios archivos o carpetas
  - chgrp: Cambia el grpo al que pertenece el usuario 
  - pause: Realiza una pausa en la ejecucion
  - loss: Hace la simulacion de perdida de informacion del sistema, formateando los bloques e inodos del sistema
  - recovery: Realiza la recuperacion del sistema por medio del Super bloque y el Jorunaling (Solo EXT3)

## Tutorial


## Herramientas utilizadas:
- C/C++ (Lenguaje de programacion) 
- Qt Creator (IDE)
- Linux Ubuntu (Sistema operativo) 
- Flex / Bison para el analizador
- Graphviz (Para los reportes)

## Autor 
Raul Xiloj
