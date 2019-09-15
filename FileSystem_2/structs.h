#ifndef STRUCTS_H
#define STRUCTS_H

#include <time.h>
#include <QString>

//Header en donde se definen todos los structs que se usaran en el proyecto

/*
 * Structs necesarios para guardar la informacion de los discos
 * Los discos tendran informacion del MBR y el MBR tendra el espacio de las particiones
*/

typedef struct {
    char part_status; //Indica si la particion esta activa o no
    char part_type; //Indica el tipo de particion
    char part_fit; //Tipo de ajuste de la particion
    int part_start; //Indica en que byte del disco inicia la particion
    int part_size; //Contiene el tamano de la particion en bytes
    char part_name[16]; //Nombre de la particion
} Partition;

typedef struct{
    int mbr_size; //Tamano total del disco en bytes
    time_t mbr_date_created; //Fecha y hora de creacion del disco
    int mbr_disk_signature; //Numero random, que identifica de forma unica cada disco
    char mbr_disk_fit; //Tipo de ajuste
    Partition mbr_partition[4]; //4 particiones
}MBR;

typedef struct{
    char part_status; //Indica si la particion esta activa o no
    char part_fit; //Tipo de ajuste
    int part_start; //Indica en que byte del disco inicia la particion
    int part_size; //Contiene el tamano total de la particion en bytes
    int part_next; //Byte en el que esta el proxima EBR. -1 si no hay siguiente
    char part_name[16]; //Nombre de la particion
}EBR;

/*
 * Structs para sistema de archivos
*/

typedef struct{
    int s_filesystem_type; //Guarda el numero que identifica al sistea de archivos utilizados
    int s_inodes_count; //Guarda el numero total de inodos
    int s_blocks_count; //Guarda el numero total de bloques
    int s_free_blocks_count; //Contiene el numero de bloques libres
    int s_free_inodes_count; //Contiene el numero inodos libres
    time_t s_mtime; //Ultima fecha en el que el sistema fue montado
    time_t s_umtime; //Ultima fecha en que el sistema fue desmontado
    int s_mnt_count; //Indica cuantas veces se ha montado el sistema
    int s_magic; //Valor que identifica al sistema de archivos 0xEF53
    int s_inode_size; //Tamano del inodo
    int s_block_size; //Tamano del bloque
    int s_first_ino; //Primer inodo libre
    int s_first_blo; //Primero bloque libre
    int s_bm_inode_start; //Guardara el inicio del bitmap de inodos
    int s_bm_block_start; //Guardara el inicio del bitmap de bloques
    int s_inode_start; //Guarada el inicio de la tabla de inodos
    int s_block_start; //Guardara el inicio de la tabla de bloques
}SuperBloque;

typedef struct{
    int i_uid; //UID del usuario propiertario del archivo/carpeta
    int i_gid; //GID del grupo al que pertenece el archivo/carpeta
    int i_size; //Tamano del archivo en bytes
    int i_block[15]; //Array de bloques
    int i_type; //Indica si es archivo o carpeta
    int i_perm; //Guarada los permisos del archivo/carpeta
    time_t i_atime; //Ultima fecha en que se leyo el inodo sin modificarlo
    time_t i_ctime; //Fecha en que se creo el el inodo
    time_t i_mtime; //Ultima fecha en la que se modifco
}InodoTable;

typedef struct{
    char b_name[12];//Nombre carpeta/archivo
    int b_inodo;//Apuntador hacia un inodo asociado al archivo o carpeta
}Content;

typedef struct{
    Content b_content[4];//Array con el contenido de la carpeta
}BloqueCarpeta;

typedef struct{
    char b_content[64];
}BloqueArchivo;

typedef struct{
    int b_pointer[16];//Array con los apuntadores hacia bloques
}BloqueApuntadores;

typedef struct{
    int journal_operation_type;
    int journal_type;//Archivo/Carpeta
    char journal_name[50];
    char journal_content[100];
    time_t journal_date;
    char journal_owner[20];
    int journal_permissions;
}Journal;

/*Struct para guardar los datos del usuario loggeado*/
typedef struct{
    int id_user;
    int id_grp;
    int inicioSuper;
    QString direccion;
    char username[12];
    char password[12];
    char group[12];
    char fit;
}Sesion;

#endif // STRUCTS_H
