#Archivo de prueba fase 2

#CREACION DE DISCO
mkdisk -size=20 -unit=m -path=/home/Discos/Disco1.disk
#CREACION DE PARTICION
fdisk -type=P -unit=K -name=Part1 -size=7680 -path=/home/Discos/Disco1.disk -fit=BF
#MOUNT
mount -path=/home/Discos/Disco1.disk -name=Part1 #vda1
#CREACION DE SISTEMA DE ARCHIVOS
mkfs -type=fast -id=vda1 -fs=3fs

#------------------------REPORTES 1----------------
rep -id=vda1 -path="/home/reportes/reporte1_sb.jpg" -name=sb
rep -id=vda1 -path="/home/reportes/reporte1_tree.jpg" -name=tree
pause

#LOGIN
login -usr=root -pwd=123 -id=vda1

#CREACION DE GRUPOS
mkgrp -name=usuarios
mkgrp -name=adm
mkgrp -name=mail
mkgrp -name=news
mkgrp -name=sys
cat -file=/users.txt
pause

#ELIMINANDO GRUPOS
rmgrp -name=mail
cat -file=/users.txt
pause

#CREACION DE USUARIOS
mkusr -usr="raulx" -pwd=password -grp=root
mkusr -usr="user1" -pwd=abc -grp=usuarios
mkusr -usr="user2" -pwd=abc -grp=usuarios
cat -file=/users.txt
pause

#ELIMINANDO USUARIOS
rmusr -usr=user2
cat -file=/users.txt
pause

#CREACION DE CARPETAS
mkdir -path=/bin
mkdir -path=/boot
mkdir -path=/cdrom
mkdir -path=/dev
mkdir -path=/etc
mkdir -path=/home
mkdir -path=/lib
mkdir -path=/lib64
mkdir -path=/media
mkdir -path=/mnt
mkdir -path=/opt
mkdir -path=/proc
mkdir -path=/run
mkdir -path=/sbin
mkdir -path=/snap
mkdir -path=/srv
mkdir -path=/sys
mkdir -path=/tmp
mkdir -path=/var
mkdir -path="/home/archivos 19"
mkdir -p -path=/home/user/docs/usac
mkdir -p -path=/home/carpeta1/carpeta2/carpeta3/carpeta4/carpeta5

#------------------------REPORTE 2----------------
rep -id=vda1 -path="/home/reportes/reporte2_tree.jpg" -name=tree
pause

logout

login -usr=raulx -pwd=password -id=vda1

#CREACION DE ARCHIVOS
mkfile -path=/home/user/docs/Tarea.txt -size=75
mkfile -path=/home/user/docs/Tarea2.txt -size=1700
#Para este comando hay que crear un archivo en la computadora y en cont poner la ruta de ese archivo
#En mi caso cree el archivo IA.txt en el escritorio 
mkfile -path=/home/user/docs/Tarea3.txt -cont=/home/raul/Desktop/IA.txt
#Debe dar error porque la ruta no existe
mkfile -path="/home/noexiste/b1.txt"
#Debe dar error por size negativo
mkfile -path="/home/b1.txt" -size=-45
#Archivo con parametro -p
mkfile -p -path=/home/user/docs/usac/archivos/proyectos/fase1/entrada.txt
cat -file=/home/user/docs/Tarea2.txt
cat -file=/home/user/docs/Tarea3.txt
pause


#------------------------REPORTE 3----------------
rep -id=vda1 -path="/home/reportes/reporte3_tree.jpg" -name=tree
pause

#REMOVER
rem -path=/home/user/docs/usac #Carpeta
rem -path=/home/user/docs/Tarea.txt #Archivo

#------------------------REPORTE 4----------------
rep -id=vda1 -path="/home/reportes/reporte4_tree.jpg" -name=tree
pause

#MOVER
mv -path=/home/user/docs/Tarea3.txt -dest=/home #archivo

#------------------------REPORTES 5----------------
#Reporte antes de la perdida
rep -id=vda1 -path="/home/reportes/reporte5_inode.jpg" -name=inode
rep -id=vda1 -path="/home/reportes/reporte5_block.pdf" -name=block
rep -id=vda1 -path="/home/reportes/reporte5_bm_inode.txt" -name=bm_inode
rep -id=vda1 -path="/home/reportes/reporte5_bm_block.txt" -name=bm_block
rep -id=vda1 -path="/home/reportes/reporte5_tree.jpg" -name=tree
rep -id=vda1 -path="/home/reportes/reporte5_sb.jpg" -name=sb
rep -id=vda1 -path="/home/reportes/reporte5_journaling.jpg" -name=journaling
rep -id=vda1 -path="/home/reportes/reporte5_file.jpg" -ruta=/home/Tarea3.txt -name=file
rep -id=vda1 -path="/home/reportes/reporte5_ls.jpg" -ruta=/home/Tarea3.txt -name=ls
pause

loss -id=vda1
#------------------------REPORTES 6----------------
#Reporte despues de la perdida
rep -id=vda1 -path="/home/reportes/reporte6_inode.jpg" -name=inode
rep -id=vda1 -path="/home/reportes/reporte6_block.pdf" -name=block
rep -id=vda1 -path="/home/reportes/reporte6_bm_inode.txt" -name=bm_inode
rep -id=vda1 -path="/home/reportes/reporte6_bm_block.txt" -name=bm_block
rep -id=vda1 -path="/home/reportes/reporte6_tree.jpg" -name=tree
rep -id=vda1 -path="/home/reportes/reporte6_sb.jpg" -name=sb
rep -id=vda1 -path="/home/reportes/reporte6_journaling.jpg" -name=journaling
pause

recovery -id=vda1
#------------------------REPORTES 7----------------
#Reportes despues del recovery
rep -id=vda1 -path="/home/reportes/reporte7_inode.jpg" -name=inode
rep -id=vda1 -path="/home/reportes/reporte7_block.jpg" -name=block
rep -id=vda1 -path="/home/reportes/reporte7_bm_inode.txt" -name=bm_inode
rep -id=vda1 -path="/home/reportes/reporte7_bm_block.txt" -name=bm_block
rep -id=vda1 -path="/home/reportes/reporte7_tree.jpg" -name=tree
rep -id=vda1 -path="/home/reportes/reporte7_sb.jpg" -name=sb
rep -id=vda1 -path="/home/reportes/reporte7_journaling.jpg" -name=journaling
pause

logout

login -usr=root -pwd=123 -id=vda1

#CHMOD cambio de permisos
chmod -r -path="/home/archivos 19" -ugo=001
chmod -path="/home/user/docs/Tarea2.txt" -ugo=001

logout

LOGIN -usr=raulx -pwd=password -id=vda1
#No debe dejar por permisos de escritura
mkdir -p -path="/home/archivos 19/no/tiene/que/hacerla/por/permisos"
#No debe dejar por permisos de lectura
cat -file=/home/user/docs/Tarea2.txt
pause

#Reportes despues de loss
rep -id=vda1 -path=/home/reports/inodeReport_loss.jpg -name=inode
rep -id=vda1 -path=/home/reports/blockReport_loss.jpg -name=block
rep -id=vda1 -path=/home/reports/tree_report_loss.jpg -name=tree
rep -id=vda1 -path=/home/reports/bm_block_report_loss.txt -name=bm_block
rep -id=vda1 -path=/home/reports/bm_inode_report_loss.txt -name=bm_inode
rep -id=vda1 -path=/home/reports/super_report_loss.jpg -name=sb
rep -id=vda1 -path=/home/reports/journal_report.jpg -name=journaling
pause

#Reportes despues de recovery
rep -id=vda1 -path=/home/reports/inodeReport_recovery.jpg -name=inode
rep -id=vda1 -path=/home/reports/blockReport_recovery.jpg -name=block
rep -id=vda1 -path=/home/reports/tree_report_recovery.jpg -name=tree
rep -id=vda1 -path=/home/reports/bm_block_report_recovery.txt -name=bm_block
rep -id=vda1 -path=/home/reports/bm_inode_report_recovery.txt -name=bm_inode
rep -id=vda1 -path=/home/reports/super_report_recovery.jpg -name=sb
rep -id=vda1 -path=/home/reports/journal_report_recovery.jpg -name=journaling

#exec -path=/home/raul/Desktop/archivoPrueba.sh
