![](https://img.shields.io/github/stars/raulxiloj/FileSystem_2) ![](https://img.shields.io/github/forks/raulxiloj/FileSystem_2) ![](https://img.shields.io/github/issues/raulxiloj/FileSystem_2)
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
 - Empezaremos con la creacion de un disco de 20 MB y lo crearemos en el escritorio 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkdisk.png)
 - Luego crearemos una particion primaria de 7.5 MB 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/fdisk.png)
 - Montamos la particion creada 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mount.png)
 - Procedemos a darle formato a la particion montada y le daremos un EXT3 que praticamente es lo mismo que un EXT2 a diferencia que este tiene un registro por diario (journaling)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkfs.png)
 - Cuando se formatea una particion, se crea la carpeta raiz (Inodo 0) y se crea un archivo users.txt (Inodo 1) en la carpeta raiz. Creamos el primer reporte del arbol de inodos y bloques para entenderlo mejor.
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte1_tree.jpg)
 - Iniciamos sesion con el usuario root que viene por defecto y tiene todos los permisos del sistema
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/login.png)
 - Crearemos algunos grupos para poder asociar a los usuarios. Este comando solo lo puede utilizar el usuario root
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkgrp.png)
 - Eliminaremos los grupos 'mail' y 'news'. Este comando solo lo puede utilizar el usuario root
![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/rmgrp.png)
 - Mostramos el contenido del archivo users.txt que es donde se guardan los grupos y usuarios creados 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/cat.png)
 - Crearemos algunos usuarios en la particion. Este comando solo lo puede utilizar el usuario root
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkusr.png)
 - Eliminamos al user2 con el objetivo de mostrar el funcionamiento del comando
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/rmusr.png)
 - Volvemos a mostrar el contenido del archivo users.txt para ver como quedo
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/cat2.png)
 - Ahora crearemos carpetas, empezaremos creando la carpeta bin en la raiz y tambien crearemos el reporte arbol para ver como va creciendo. Cuando se crea una carptea se crea un inodo (Inodo 2) y un bloque de tipo carpeta (Bloque 4) en donde se almacenaran sus subcarpetas
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkdir1.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte2.1_tree.jpg)
 - Proseguimos con la creacion de carpetas, por motivos de ejemplo y que el arbol no sea muy grande para poder observar los cambios, crearemos solo 3 carpetas mas (dev, home, lib) en la carpeta raiz.
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkdir2.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte2.2_tree.jpg)
 - Ahora crearemos la carpeta "archivos 19" en la carpeta home 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkdir3.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte2.3_tree.jpg)
 - Ahora crearemos carpetas de manera recursiva, esto se logra gracias al parametro -p 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkdir4.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte2.4_tree.jpg)
 - Cerramos sesion del usuario root e iniciamos con el usuario 'raulx' 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/logoi.png)
 - Ahora crearemos archivos, empezaremos creando el archivo 'Tarea1.txt' con un tamano de 75 bytes en la carpeta docs. Cuando se crea un archivo, se crea un inodo y dependiendo si el archivo tiene el parametro -size o -cont se crean n bloques archivos necesarios para guardar la informacion de lo contrario no se crean bloques archivos solo el inodo. Los bloques archivos tienen una capacidad de 64 bytes, entonces si la informacion sobrepasa este tamaño se crea otro y asi sucesivamente hasta poder guardar toda la informacion. 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkfile1.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte3.1_tree.jpg)
 - Como ahora cuesta un poco mas ver los cambios pondremos una imagen auxiliar, en donde se ve mejor que es lo que paso
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte3.1_zoom.png)
 - Ahora crearemos el archivo 'Tarea2.txt' con un tamaño de 1700 bytes para poder ver el primer apuntador indirecto. 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkfile2.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte3.2_tree.jpg)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte3.2_zoom.png)
 - Ahora crearemos el archivo 'Tarea3.txt' que tendra el parametro -cont lo que indica que copiara el contenido de un archivo fisico de la computadora hacia el archivo creado en este caso Tarea3.txt
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkfile4.png)
 - El contenido del archivo IA.txt es el siguiente: 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/contenido.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte3.3_tree.jpg)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte3.3_zoom.png)
 - Y por ultimo crearemos un archivo de manera recursiva, o sea creando las carpetas si no existen. Esto se logra con el parametro -p y crearemos el archivo 'entrada.txt' en una ruta no existente
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mkfile3.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte3.4_tree.jpg)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte3.4_zoom.png)
 - Eliminaremos el archivo Tarea.txt que se encuentra en la carpeta docs, como se puede observar se elimino la referencia del bloque carpeta ahora esta como -1, desaparecio el inodo 15 y su respectivo bloque carpeta.
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/rem.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte4.1_tree.jpg)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte4.1_zoom.png)
 - Eliminaremos la carpeta usac, cuando se elimina una carpeta se elimina sus subcarpetas y archivos.
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/rem2.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte4.2_tree.jpg)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte4.2_zoom.png)
 - Movemos el archivo 'Tarea3.txt' a la carpeta home, si fuera una carpeta se moveria todo su contenido
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/mv.png)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte4.3_tree.jpg)
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte4.3_zoom.png)
 - Cerramos sesion del usuario 'raulx' e iniciamos sesion con el usuario root 
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/logoi2.png)
 - Cambiamos los permisos de la carpeta 'archivos 19' de manera recursiva, o sea que cualquier carpeta perteneciente a 'archivos 19' sera afectada. Y le cambiamos los permisos al archivo Tarea2.txt
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/chmod.png)
 - Cerramos sesion y volvemos a iniciar sesion con 'raulx'
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/logoi3.png)
 - Como el usuario root cambio los permisos ahora solo el puede escribir o leer en esa carpeta y archivo
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/errorPermisos.png)
 - Simulacion de perdida del sistema, se borra todo el contenido de bloques e inodos a excepcion del journaling y SB.
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/loss.png)
 - Gracias a que el sistema EXT3 cuenta con un registro por diario (journaling) se puede recuperar el sistema, lo cual consiste en formatear la particion y volver a crear los grupos, usuarios, archivos y carpetas creadas antes de la perdida.
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Comandos/recovery.png)
 - El arbol de inodos y bloques quedaria asi
 ![No se encuentra la imagen](https://github.com/raulxiloj/FileSystem_2/blob/master/Imagenes/Reportes/reporte7_tree.jpg)
 
## Herramientas utilizadas:
- C/C++ (Lenguaje de programacion) 
- Qt Creator (IDE)
- Linux Ubuntu (Sistema operativo) 
- Flex / Bison para el analizador
- Graphviz (Para los reportes)

## Autor 
Raul Xiloj
