#Archivo de prueba fase 2

#CREACION DE DISCOS
mkdisk -size=75 -unit=m -path=/home/archivos/fase2/Disco1.disk
mkdisk -size=51200 -unit=K -path=/home/archivos/fase2/Disco2.disk

#CREACION DE PARTICIONES
#Disco1
fdisk -type=P -unit=m -name=Part1 -size=20 -path=/home/archivos/fase2/Disco1.disk -fit=BF
fdisk -type=P -unit=m -name=Part2 -size=15 -path=/home/archivos/fase2/Disco1.disk -fit=BF
fdisk -type=P -unit=m -name=Part3 -size=20 -path=/home/archivos/fase2/Disco1.disk -fit=BF

#Disco2
fdisk -type=P -unit=M -name=Part1_D2 -size=20 -path=/home/archivos/fase2/Disco2.disk -fit=BF
fdisk -type=P -unit=M -name=Part2_D2 -size=10 -path=/home/archivos/fase2/Disco2.disk -fit=BF
fdisk -type=P -unit=M -name=Part3_D2 -size=10 -path=/home/archivos/fase2/Disco2.disk -fit=BF

#MONTAR PARTICIONES
mount -path=/home/archivos/fase2/Disco1.disk -name=Part1 #vda1
mount -path=/home/archivos/fase2/Disco1.disk -name=Part2 #vda2
mount -path=/home/archivos/fase2/Disco1.disk -name=Part3 #vda3

mount -path=/home/archivos/fase2/Disco2.disk -name=Part1_D2 #vdb1
mount -path=/home/archivos/fase2/Disco2.disk -name=Part2_D2 #vdb2
mount -path=/home/archivos/fase2/Disco2.disk -name=Part3_D2 #vdb3

#CREACION DEL SISTEMA DE ARCHIVOS EN LAS PARTICIONES
mkfs -type=fast -id=vda1 -fs=3fs
mkfs -type=full -id=vda2 -fs=3fs
mkfs -type=fast -id=vda3 -fs=3fs

#----------------REPORTES 1----------------
rep -id=vda1 -path="/home/archivos/reports2/reporte1_vda1_sb.pdf" -name=sb
rep -id=vda1 -path="/home/archivos/reports2/reporte1_vda1_tree.jpg" -name=tree
rep -id=vda2 -path="/home/archivos/reports2/reporte1_vda2_sb.pdf" -name=sb
rep -id=vda2 -path="/home/archivos/reports2/reporte1_vda2_tree.jpg" -name=tree
rep -id=vda3 -path="/home/archivos/reports2/reporte1_vda3_sb.pdf" -name=sb
rep -id=vda3 -path="/home/archivos/reports2/reporte1_vda3_tree.jpg" -name=tree
#pause

#LOGIN
#Login como root en el vda1 - Part1 de tipo EXT3
#Debe dar error porque no existe el usuario roca
login -pwd=567 -usr=roca -id=vda1
#debe dar error porque no existe nada activo
logout
#Debe dar error contraseña incorrecta
Login -pwd=12345 -usr=root -id=vda1
Login -pwd=123 -usr=root -id=vda1
#Debe dar error porque ya hay un login activo
login -pwd=error -usr=error -id=vda1
#pause

#CREANDO GRUPOS
mkgrp -name=Archivos
mkgrp -name=Arqui
mkgrp -name="Compi 2"
mkgrp -name="Compi 2"
cat -file=/users.txt
#pause

#BORRANDO GRUPOS
#ERROR no existe este grupo
rmgrp -name="DB2"
rmgrp -name=Arqui
cat -file=/users.txt
#pause

#CREACION DE USUARIOS
#crearemos 3 usuarios llamados user1, user2, user3
Mkusr -usr="user1" -grp=root -pwd=user1
mkusr -usr="user2" -grp="Compi 2" -pwd=user2
mkUsr -usr="user3" -grp="Compi 2" -pwd=user3
#Da error porque ya existe ese usuario
Mkusr -usr="user2" -grp="Compi 2" -pwd=user2
#Da error porque no existe ese grupo
Mkusr -usr="user2" -grp=Arqui -pwd=user2
Cat -file=/users.txt
#pause

#BORRANDO USUARIOS
rmusr -usr=user3
rmusr -usr=user3 #Debe dar error porque ya no existe
cat -file=/users.txt
#pause

#CREACION DE CARPETAS
mkdir -p -path=/home/archivos/mia/fase1
mkdir -p -path=/home/archivos/mia/carpeta2
mkdir -p -path=/home/archivos/mia/z
mkdir -p -path=/home/archivos/mia/carpeta3/carpeta7/carpeta8/carpeta9/carpeta10/carpeta11
mkdir -p -path=/home/archivos/mia/carpeta4/carpeta7/carpeta8/carpeta9/carpeta10/carpeta11/carpeta7/carpeta8/carpeta9/carpeta10/carpeta11
mkdir -path=/home/archivos/mia/carpeta2/a1
mkdir -path=/home/archivos/mia/carpeta2/a2
mkdir -path=/home/archivos/mia/carpeta2/a3
mkdir -path=/home/archivos/mia/carpeta2/a4
mkdir -path=/home/archivos/mia/carpeta2/a5
mkdir -path=/home/archivos/mia/carpeta2/a6
mkdir -path=/home/archivos/mia/carpeta2/a7
mkdir -path=/home/archivos/mia/carpeta2/a8
mkdir -path=/home/archivos/mia/carpeta2/a9
mkdir -path=/home/archivos/mia/carpeta2/a10

mkdir -p -path=/home/archivos/mia/fase2/a1
mkdir -path=/home/archivos/mia/fase2/a2
mkdir -path=/home/archivos/mia/fase2/a3
mkdir -path=/home/archivos/mia/fase2/a4
mkdir -path=/home/archivos/mia/fase2/a5
mkdir -path=/home/archivos/mia/fase2/a6
mkdir -path=/home/archivos/mia/fase2/a7
mkdir -path=/home/archivos/mia/fase2/a8
mkdir -path=/home/archivos/mia/fase2/a9
mkdir -path=/home/archivos/mia/fase2/a10
mkdir -path=/home/archivos/mia/fase2/a11
mkdir -path=/home/archivos/mia/fase2/a12
mkdir -path=/home/archivos/mia/fase2/a13
mkdir -path=/home/archivos/mia/fase2/a14
mkdir -path=/home/archivos/mia/fase2/a15
mkdir -path=/home/archivos/mia/fase2/a16
mkdir -path=/home/archivos/mia/fase2/a17
mkdir -path=/home/archivos/mia/fase2/a18
mkdir -path=/home/archivos/mia/fase2/a19
mkdir -path=/home/archivos/mia/fase2/a20
mkdir -path=/home/archivos/mia/fase2/a21
mkdir -path=/home/archivos/mia/fase2/a22
mkdir -path=/home/archivos/mia/fase2/a23
mkdir -path=/home/archivos/mia/fase2/a24
mkdir -path=/home/archivos/mia/fase2/a25
mkdir -path=/home/archivos/mia/fase2/a26
mkdir -path=/home/archivos/mia/fase2/a27
mkdir -path=/home/archivos/mia/fase2/a28
mkdir -path=/home/archivos/mia/fase2/a29
mkdir -path=/home/archivos/mia/fase2/a30
mkdir -path=/home/archivos/mia/fase2/a31
mkdir -path=/home/archivos/mia/fase2/a32
mkdir -path=/home/archivos/mia/fase2/a33
mkdir -path=/home/archivos/mia/fase2/a34
mkdir -path=/home/archivos/mia/fase2/a35
mkdir -path=/home/archivos/mia/fase2/a36
mkdir -path=/home/archivos/mia/fase2/a37
mkdir -path=/home/archivos/mia/fase2/a38
mkdir -path=/home/archivos/mia/fase2/a39
mkdir -path=/home/archivos/mia/fase2/a40
mkdir -path=/home/archivos/mia/fase2/a41
mkdir -path=/home/archivos/mia/fase2/a42
mkdir -path=/home/archivos/mia/fase2/a43
mkdir -path=/home/archivos/mia/fase2/a44
mkdir -path=/home/archivos/mia/fase2/a45
mkdir -path=/home/archivos/mia/fase2/a46
#Debe dar error porque ya existe a46
mkdir -path=/home/archivos/mia/fase2/a46

#Primer apuntador indirecto simple
mkdir -path="/home/archivos/mia/fase2/b1"
mkdir -path="/home/archivos/mia/fase2/b2"
mkdir -path="/home/archivos/mia/fase2/b3"
mkdir -path="/home/archivos/mia/fase2/b4"
mkdir -path="/home/archivos/mia/fase2/b5"
mkdir -path="/home/archivos/mia/fase2/b6"
mkdir -path="/home/archivos/mia/fase2/b7"
mkdir -path="/home/archivos/mia/fase2/b8"
mkdir -path="/home/archivos/mia/fase2/b9"
mkdir -path="/home/archivos/mia/fase2/b10"
mkdir -path="/home/archivos/mia/fase2/b11"
mkdir -path="/home/archivos/mia/fase2/b12"
mkdir -path="/home/archivos/mia/fase2/b13"
mkdir -path="/home/archivos/mia/fase2/b14"
mkdir -path="/home/archivos/mia/fase2/b15"
mkdir -path="/home/archivos/mia/fase2/b16"
mkdir -path="/home/archivos/mia/fase2/b17"
mkdir -path="/home/archivos/mia/fase2/b18"
mkdir -path="/home/archivos/mia/fase2/b19"
mkdir -path="/home/archivos/mia/fase2/b20"
mkdir -path="/home/archivos/mia/fase2/b21"
mkdir -path="/home/archivos/mia/fase2/b22"
mkdir -path="/home/archivos/mia/fase2/b23"
mkdir -path="/home/archivos/mia/fase2/b24"
mkdir -path="/home/archivos/mia/fase2/b25"
mkdir -path="/home/archivos/mia/fase2/b26"
mkdir -path="/home/archivos/mia/fase2/b27"
mkdir -path="/home/archivos/mia/fase2/b28"
mkdir -path="/home/archivos/mia/fase2/b29"
mkdir -path="/home/archivos/mia/fase2/b30"
mkdir -path="/home/archivos/mia/fase2/b31"
mkdir -path="/home/archivos/mia/fase2/b32"
mkdir -path="/home/archivos/mia/fase2/b33"
mkdir -path="/home/archivos/mia/fase2/b34"
mkdir -path="/home/archivos/mia/fase2/b35"
mkdir -path="/home/archivos/mia/fase2/b36"
mkdir -path="/home/archivos/mia/fase2/b37"
mkdir -path="/home/archivos/mia/fase2/b38"
mkdir -path="/home/archivos/mia/fase2/b39"
mkdir -path="/home/archivos/mia/fase2/b40"
mkdir -path="/home/archivos/mia/fase2/b41"
mkdir -path="/home/archivos/mia/fase2/b42"
mkdir -path="/home/archivos/mia/fase2/b43"
mkdir -path="/home/archivos/mia/fase2/b44"
mkdir -path="/home/archivos/mia/fase2/b45"
mkdir -path="/home/archivos/mia/fase2/b46"
mkdir -path="/home/archivos/mia/fase2/b47"
mkdir -path="/home/archivos/mia/fase2/b48"
mkdir -path="/home/archivos/mia/fase2/b49"
mkdir -path="/home/archivos/mia/fase2/b50"

#----------------REPORTES 2----------------
rep -id=vda1 -path="/home/archivos/reports2/reporte2_vda1_sb.jpg" -name=sb
rep -id=vda1 -path="/home/archivos/reports2/reporte2_vda1_tree.pdf" -name=tree
#pause

logout

login -usr=user1 -pwd=user1 -id=vda1

#CREACION DE ARCHIVOS
mkfile -path="/home/b1.txt" -size=75
mkfile -path ="/home/b1_1.txt" -size=1700 #1er indirecto
#Archivo con parametro -p
mkfile -p -path="/home/ahora/ya existe/b1.txt" -size=640
#Debe dar error porque la ruta no existe
mkfile -path="/home/NoExiste/b1.txt" -size=75
#Debe dar error por size negativo
mkfile -path="/home/b2.txt" -size=-45

#----------------REPORTES 3----------------
rep -id=vda1 -path="/home/archivos/reports2/reporte3_vda1_sb.jpg" -name=sb
rep -id=vda1 -path="/home/archivos/reports2/reporte3_vda1_tree.pdf" -name=tree
#pause

login -usr=user1 -pwd=user1 -id=vda1

#REMOVER
#Carpeta directos
rem -path=/home/archivos/mia/fase2/a46
#Carpeta indirectos
rem -path=/home/archivos/mia/fase2/b1

#----------------REPORTES 4----------------
rep -id=vda1 -path="/home/archivos/reports2/reporte4_vda1_sb.jpg" -name=sb
rep -id=vda1 -path="/home/archivos/reports2/reporte4_vda1_tree.pdf" -name=tree
pause

#MOVER
mv -path="/home/archivos/mia/fase2/b50" -dest="/home"
#debe dar error porque no existe
mv -path="/home/archivos/no existe" -dest="/home"

#----------------REPORTES 5----------------
#Reportes antes de la perdida
rep -id=vda1 -Path="/home/archivos/reports2/users.jpg" -ruta="/users.txt" -name=file
rep -id=vda1 -Path="/home/archivos/reports2/ls.pdf" -ruta="/home" -name=ls
rep -id=vda1 -Path="/home/archivos/reports2/reporte5_vda1_sb.jpg" -name=sb
rep -id=vda1 -Path="/home/archivos/reports2/reporte5_vda1_tree.pdf" -name=tree
rep -id=vda1 -Path="/home/archivos/reports2/reporte5_vda1_inode.pdf" -name=inode
rep -id=vda1 -Path="/home/archivos/reports2/reporte5_vda1_block.pdf" -name=block
rep -id=vda1 -Path="/home/archivos/reports2/reporte5_vda1_bm_inode.txt" -name=bm_inode
rep -id=vda1 -Path="/home/archivos/reports2/reporte5_vda1_bm_block.txt" -name=bm_block
rep -id=vda1 -Path="/home/archivos/reports2/reporte5_vda1_journaling.pdf" -name=journaling
#pause

#PERDIDA
Loss -id=vda1

#----------------REPORTES 6----------------
#Reportes despues de la perdida
rep -id=vda1 -Path="/home/archivos/reports2/reporte6_vda1_sb.jpg" -name=sb
rep -id=vda1 -Path="/home/archivos/reports2/reporte6_vda1_tree.pdf" -name=tree
rep -id=vda1 -Path="/home/archivos/reports2/reporte6_vda1_inode.pdf" -name=inode
rep -id=vda1 -Path="/home/archivos/reports2/reporte6_vda1_block.pdf" -name=block
rep -id=vda1 -Path="/home/archivos/reports2/reporte6_vda1_bm_inode.txt" -name=bm_inode
rep -id=vda1 -Path="/home/archivos/reports2/reporte6_vda1_bm_block.txt" -name=bm_block
rep -id=vda1 -Path="/home/archivos/reports2/reporte6_vda1_journaling.pdf" -name=journaling
#pause

#RECUPERACION
Recovery -id=vda1
#----------------REPORTES 7----------------
#Reportes despues del recovery
rep -id=vda1 -Path="/home/archivos/reports2/reporte7_vda1_sb.jpg" -name=sb
rep -id=vda1 -Path="/home/archivos/reports2/reporte7_vda1_tree.pdf" -name=tree
rep -id=vda1 -Path="/home/archivos/reports2/reporte7_vda1_inode.pdf" -name=inode
rep -id=vda1 -Path="/home/archivos/reports2/reporte7_vda1_block.pdf" -name=block
rep -id=vda1 -Path="/home/archivos/reports2/reporte7_vda1_bm_inode.txt" -name=bm_inode
rep -id=vda1 -Path="/home/archivos/reports2/reporte7_vda1_bm_block.txt" -name=bm_block
rep -id=vda1 -Path="/home/archivos/reports2/reporte7_vda1_journaling.pdf" -name=journaling
pause

logout

login -pwd=123 -usr=root -id=vda1

#CHMOD
chmod -path="/home/archivos/mia/carpeta2" -ugo=001 -r
chmod -path="/home/b1.txt" -ugo=001
logout

login -usr=user1 -pwd=user1 -id=vda1
#No debe dejar por permisos de escritura
Mkdir -p -path=/home/archivos/mia/carpeta2/esta/no/se/debe/crear/por/permisos
#No debe dejar por permisos de lectura
cat -file="/home/b1.txt"
logout
pause

#exec -path=/home/raul/Desktop/archivoMaster.sh
