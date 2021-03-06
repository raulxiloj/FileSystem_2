#include "reporte.h"

Reporte::Reporte()
{

}

/* Metodo para graficar un disco con su estructura de las particiones
 * @param QString direccion: Es la direccion donde se encuentra la particion
 * @param QString destino: Es la ruta donde se creara el reporte
 * @param QString extension: La extension que tendra nuestro reporte .jpg|.png|etc
*/
void Reporte::graficarDisco(QString direccion, QString destino, QString extension){
    FILE *fp;
    FILE *graphDot;
    if((fp = fopen(direccion.toStdString().c_str(),"r"))){
        graphDot = fopen("grafica.dot","w");
        fprintf(graphDot,"digraph G{\n\n");
        fprintf(graphDot, "  tbl [\n    shape=box\n    label=<\n");
        fprintf(graphDot, "     <table border=\'0\' cellborder=\'2\' width=\'600\' height=\"200\" color=\'LIGHTSTEELBLUE\'>\n");
        fprintf(graphDot, "     <tr>\n");
        fprintf(graphDot, "     <td height=\'200\' width=\'100\'> MBR </td>\n");
        MBR masterboot;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        int total = masterboot.mbr_size;
        double espacioUsado = 0;
        for(int i = 0; i < 4; i++){
            int parcial = masterboot.mbr_partition[i].part_size;
            if(masterboot.mbr_partition[i].part_start != -1){//Particion vacia
                double porcentaje_real = (parcial*100)/total;
                double porcentaje_aux = (porcentaje_real*500)/100;
                espacioUsado += porcentaje_real;
                if(masterboot.mbr_partition[i].part_status != '1'){
                    if(masterboot.mbr_partition[i].part_type == 'P'){
                        fprintf(graphDot, "     <td height=\'200\' width=\'%.1f\'>PRIMARIA <br/> Ocupado: %.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                        //Verificar que no haya espacio fragmentado
                        if(i!=3){
                            int p1 = masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size;
                            int p2 = masterboot.mbr_partition[i+1].part_start;
                            if(masterboot.mbr_partition[i+1].part_start != -1){
                                if((p2-p1)!=0){//Hay fragmentacion
                                    int fragmentacion = p2-p1;
                                    double porcentaje_real = (fragmentacion*100)/total;
                                    double porcentaje_aux = (porcentaje_real*500)/100;
                                    fprintf(graphDot,"     <td height=\'200\' width=\'%.1f\'>LIBRE<br/> Ocupado: %.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                                }
                            }

                        }else{
                            int p1 = masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size;
                            int mbr_size = total + (int)sizeof(MBR);
                            if((mbr_size-p1)!=0){//Libre
                                double libre = (mbr_size - p1) + sizeof(MBR);
                                double porcentaje_real = (libre*100)/total;
                                double porcentaje_aux = (porcentaje_real*500)/100;
                                fprintf(graphDot, "     <td height=\'200\' width=\'%.1f\'>LIBRE<br/> Ocupado: %.1f%c</td>\n",porcentaje_aux, porcentaje_real, '%');
                            }
                        }
                    }else{//Extendida
                        EBR extendedBoot;
                        fprintf(graphDot,"     <td  height=\'200\' width=\'%.1f\'>\n     <table border=\'0\'  height=\'200\' WIDTH=\'%.1f\' cellborder=\'1\'>\n",porcentaje_real,porcentaje_real);
                        fprintf(graphDot,"     <tr>  <td height=\'60\' colspan=\'15\'>EXTENDIDA</td>  </tr>\n     <tr>\n");
                        fseek(fp, masterboot.mbr_partition[i].part_start,SEEK_SET);
                        fread(&extendedBoot,sizeof(EBR),1,fp);
                        if(extendedBoot.part_size != 0){//Si hay mas de alguna logica
                            fseek(fp, masterboot.mbr_partition[i].part_start,SEEK_SET);
                            while(fread(&extendedBoot,sizeof (EBR),1,fp)!=0 && (ftell(fp) < (masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size))){
                                parcial = extendedBoot.part_size;
                                porcentaje_real = (parcial*100)/total;
                                if(porcentaje_real!=0){
                                    if(extendedBoot.part_status != '1'){
                                        fprintf(graphDot, "     <td height=\'140\'>EBR</td>\n");
                                        fprintf(graphDot, "     <td height=\'140\'>LOGICA<br/>Ocupado: %.1f%c</td>\n",porcentaje_real,'%');
                                    }else{//Espacio no asignado
                                        fprintf(graphDot, "      <td height=\'150\'>LIBRE 1 <br/> Ocupado: %.1f%c</td>\n",porcentaje_real,'%');
                                    }
                                    if(extendedBoot.part_next==-1){
                                        parcial = (masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size) - (extendedBoot.part_start + extendedBoot.part_size);
                                        porcentaje_real = (parcial*100)/total;
                                        if(porcentaje_real!=0){
                                            fprintf(graphDot, "     <td height=\'150\'>LIBRE 2<br/> Ocupado: %.1f%c </td>\n",porcentaje_real,'%');
                                        }
                                        break;
                                    }else
                                        fseek(fp,extendedBoot.part_next,SEEK_SET);
                                }
                            }
                        }else{
                            fprintf(graphDot,"     <td height=\'140\'> Ocupado %.1f%c</td>",porcentaje_real,'%');
                        }
                        fprintf(graphDot,"     </tr>\n     </table>\n     </td>\n");
                        //Verificar que no haya espacio fragmentado
                        if(i!=3){
                            int p1 = masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size;
                            int p2 = masterboot.mbr_partition[i+1].part_start;
                            if(masterboot.mbr_partition[i+1].part_start != -1){
                                if((p2-p1)!=0){//Hay fragmentacion
                                    int fragmentacion = p2-p1;
                                    double porcentaje_real = (fragmentacion*100)/total;
                                    double porcentaje_aux = (porcentaje_real*500)/100;
                                    fprintf(graphDot,"     <td height=\'200\' width=\'%.1f\'>LIBRE<br/> Ocupado: %.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                                }
                            }
                        }else{
                            int p1 = masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size;
                            int mbr_size = total + (int)sizeof(MBR);
                            if((mbr_size-p1)!=0){//Libre
                                double libre = (mbr_size - p1) + sizeof(MBR);
                                double porcentaje_real = (libre*100)/total;
                                double porcentaje_aux = (porcentaje_real*500)/100;
                                fprintf(graphDot, "     <td height=\'200\' width=\'%.1f\'>LIBRE<br/> Ocupado: %.1f%c</td>\n",porcentaje_aux, porcentaje_real, '%');
                            }
                        }
                    }
                }else{//Espacio no asignado
                     fprintf(graphDot,"     <td height=\'200\' width=\'%.1f\'>LIBRE <br/> Ocupado: %.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                }
            }
        }

        //fprintf(graphDot,"     <td height='200'> ESPACIO LIBRE <br/> Ocupado: %.1f%c\n     </td>",(100-espacioUsado),'%');


        fprintf(graphDot,"     </tr> \n     </table>        \n>];\n\n}");
        fclose(graphDot);
        fclose(fp);
        string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
        system(comando.c_str());
        cout << "Reporte generado con exito " << endl;
    }else{
        cout << "ERROR al crear reporte, disco no encontrado" << endl;
    }
}

/* Metodo para generar un reporte del MBR de un disco
 * @param QString direccion: Es la direccion donde se encuentra la particion
 * @param QString destino: Es la ruta donde se creara el reporte
 * @param QString extension: La extension que tendra nuestro reporte .jpg|.png|etc
*/
void Reporte::graficarMBR(QString direccion, QString destino, QString extension){
    string auxDir = direccion.toStdString();
    FILE *fp;
    FILE *graphDot;
    if((fp = fopen(auxDir.c_str(),"r"))){
        graphDot = fopen("grafica.dot", "w");
        fprintf(graphDot,"digraph G{ \n");
        fprintf(graphDot,"subgraph cluster{\n label=\"MBR\"");
        fprintf(graphDot,"\ntbl[shape=box,label=<\n");
        fprintf(graphDot,"<table border=\'0\' cellborder=\'1\' cellspacing=\'0\' width=\'300\'  height=\'200\' >\n");
        fprintf(graphDot, "<tr>  <td width=\'150\'> <b>Nombre</b> </td> <td width=\'150\'> <b>Valor</b> </td>  </tr>\n");
        MBR masterBoot;
        fseek(fp,0,SEEK_SET);
        fread(&masterBoot,sizeof(MBR),1,fp);
        int tamano = masterBoot.mbr_size;
        fprintf(graphDot,"<tr>  <td><b>mbr_tamaño</b></td><td>%d</td>  </tr>\n",tamano);
        struct tm *tm;
        char fecha[100];
        tm = localtime(&masterBoot.mbr_date_created);
        strftime(fecha,100,"%d/%m/%y %H:%S",tm);
        fprintf(graphDot,"<tr>  <td><b>mbr_fecha_creacion</b></td> <td>%s</td>  </tr>\n",fecha);
        fprintf(graphDot,"<tr>  <td><b>mbr_disk_signature</b></td> <td>%d</td>  </tr>\n",masterBoot.mbr_disk_signature);
        fprintf(graphDot,"<tr>  <td><b>Disk_fit</b></td> <td>%c</td>  </tr>\n",masterBoot.mbr_disk_fit);

        int index_Extendida = -1;
        for (int i = 0; i < 4; i++){
            if(masterBoot.mbr_partition[i].part_start!=-1 && masterBoot.mbr_partition[i].part_status!='1'){
                if(masterBoot.mbr_partition[i].part_type == 'E'){
                    index_Extendida = i;
                }
                char status[3];
                if(masterBoot.mbr_partition[i].part_status == '0')
                    strcpy(status,"0");
                else if(masterBoot.mbr_partition[i].part_status == '2')
                    strcpy(status,"2");
                fprintf(graphDot,"<tr>  <td><b>part_status_%d</b></td> <td>%s</td>  </tr>\n",(i+1),status);
                fprintf(graphDot,"<tr>  <td><b>part_type_%d</b></td> <td>%c</td>  </tr>\n",(i+1),masterBoot.mbr_partition[i].part_type);
                fprintf(graphDot,"<tr>  <td><b>part_fit_%d</b></td> <td>%c</td>  </tr>\n",(i+1),masterBoot.mbr_partition[i].part_fit);
                fprintf(graphDot,"<tr>  <td><b>part_start_%d</b></td> <td>%d</td>  </tr>\n",(i+1),masterBoot.mbr_partition[i].part_start);
                fprintf(graphDot,"<tr>  <td><b>part_size_%d</b></td> <td>%d</td>  </tr>\n",(i+1),masterBoot.mbr_partition[i].part_size);
                fprintf(graphDot,"<tr>  <td><b>part_name_%d</b></td> <td>%s</td>  </tr>\n",(i+1),masterBoot.mbr_partition[i].part_name);
            }
        }

        fprintf(graphDot,"</table>\n");
        fprintf(graphDot, ">];\n}\n");

        if(index_Extendida != -1){
            int index_ebr = 1;
            EBR extendedBoot;
            fseek(fp,masterBoot.mbr_partition[index_Extendida].part_start,SEEK_SET);
            while(fread(&extendedBoot,sizeof(EBR),1,fp)!=0 && (ftell(fp) < masterBoot.mbr_partition[index_Extendida].part_start + masterBoot.mbr_partition[index_Extendida].part_size)) {
                if(extendedBoot.part_status != '1'){
                    fprintf(graphDot,"subgraph cluster_%d{\n label=\"EBR_%d\"\n",index_ebr,index_ebr);
                    fprintf(graphDot,"\ntbl_%d[shape=box, label=<\n ",index_ebr);
                    fprintf(graphDot, "<table border=\'0\' cellborder=\'1\' cellspacing=\'0\'  width=\'300\' height=\'160\' >\n ");
                    fprintf(graphDot, "<tr>  <td width=\'150\'><b>Nombre</b></td> <td width=\'150\'><b>Valor</b></td>  </tr>\n");
                    char status[3];
                    if(extendedBoot.part_status == '0')
                        strcpy(status,"0");
                    else if(extendedBoot.part_status == '2')
                        strcpy(status,"2");
                    fprintf(graphDot, "<tr>  <td><b>part_status_1</b></td> <td>%s</td>  </tr>\n",status);
                    fprintf(graphDot, "<tr>  <td><b>part_fit_1</b></td> <td>%c</td>  </tr>\n",extendedBoot.part_fit);
                    fprintf(graphDot, "<tr>  <td><b>part_start_1</b></td> <td>%d</td>  </tr>\n",extendedBoot.part_start);
                    fprintf(graphDot, "<tr>  <td><b>part_size_1</b></td> <td>%d</td>  </tr>\n",extendedBoot.part_size);
                    fprintf(graphDot, "<tr>  <td><b>part_next_1</b></td> <td>%d</td>  </tr>\n",extendedBoot.part_next);
                    fprintf(graphDot, "<tr>  <td><b>part_name_1</b></td> <td>%s</td>  </tr>\n",extendedBoot.part_name);
                    fprintf(graphDot, "</table>\n");
                    fprintf(graphDot, ">];\n}\n");
                    index_ebr++;
                }

                if(extendedBoot.part_next == -1)
                    break;
                else
                    fseek(fp,extendedBoot.part_next,SEEK_SET);
            }
        }
        fprintf(graphDot,"}\n");
        fclose(graphDot);
        fclose(fp);
        string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
        system(comando.c_str());
        cout << "Reporte generado con exito " << endl;
    }
}

/* Metodo para generar el reporte de inodos de una particion
 * @param QString direccion: Es la direccion donde se encuentra la particion
 * @param QString destino: Es la ruta donde se creara el reporte
 * @param QString extension: La extension que tendra el reporte .jpg|.png|etc
 * @param int bm_inode_start: Byte donde inicia el bitmap de inodos de la particion
 * @param int inode_start: Byte donde inicia la tabla de inodos de la particion
 * @param int bm_block_start: Byte donde inicia el bitmap de bloques de la particion
*/
void Reporte::graficarInodos(QString direccion, QString destino, QString extension,int bm_inode_start,int inode_start,int bm_block_start){
    FILE *fp = fopen(direccion.toStdString().c_str(), "r");

    InodoTable inodo;
    int aux = bm_inode_start;
    int i = 0;
    char buffer;

    FILE *graph = fopen("grafica.dot","w");
    fprintf(graph,"digraph G{\n\n");

    while(aux < bm_block_start){
        fseek(fp,bm_inode_start + i,SEEK_SET);
        buffer = static_cast<char>(fgetc(fp));
        aux++;
        if(buffer == '1'){
            fseek(fp,inode_start + static_cast<int>(sizeof(InodoTable))*i,SEEK_SET);
            fread(&inodo,sizeof(InodoTable),1,fp);
            fprintf(graph, "    nodo_%d [ shape=none fontname=\"Century Gothic\" label=<\n",i);
            fprintf(graph, "   <table border=\'0\' cellborder=\'1\' cellspacing=\'0\' bgcolor=\"royalblue\">");
            fprintf(graph, "    <tr> <td colspan=\'2\'> <b>Inodo %d</b> </td></tr>\n",i);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_uid </td> <td bgcolor=\"white\"> %d </td>  </tr>\n",inodo.i_uid);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_gid </td> <td bgcolor=\"white\"> %d </td>  </tr>\n",inodo.i_gid);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_size </td> <td bgcolor=\"white\"> %d </td> </tr>\n",inodo.i_size);
            struct tm *tm;
            char fecha[100];
            tm=localtime(&inodo.i_atime);
            strftime(fecha,100,"%d/%m/%y %H:%S",tm);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_atime </td> <td bgcolor=\"white\"> %s </td>  </tr>\n",fecha);
            tm=localtime(&inodo.i_ctime);
            strftime(fecha,100,"%d/%m/%y %H:%S",tm);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_ctime </td> <td bgcolor=\"white\"> %s </td>  </tr>\n",fecha);
            tm=localtime(&inodo.i_mtime);
            strftime(fecha,100,"%d/%m/%y %H:%S",tm);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_mtime </td> <td bgcolor=\"white\"> %s </td></tr>\n",fecha);
            for(int b = 0; b < 15; b++)
                fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_block_%d </td> <td bgcolor=\"white\"> %d </td> </tr>\n",b,inodo.i_block[b]);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_type </td> <td bgcolor=\"white\"> %c </td> </tr>\n",inodo.i_type);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_perm </td> <td bgcolor=\"white\"> %d </td> </tr>\n",inodo.i_perm);
            fprintf(graph, "   </table>>]\n");
        }
        i++;
    }
    fprintf(graph,"\n}");
    fclose(graph);

    fclose(fp);

    string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
    system(comando.c_str());
    cout << "Reporte de inodos generado con exito " << endl;
}

/* Metodo para generar el reporte de bloques de una particion
 * @param QString direccion: Es la direccion donde se encuentra la particion
 * @param QString destino: Es la ruta donde se creara el reporte
 * @param QString extension: La extension que tendra el reporte .jpg|.png|etc
 * @param int bm_block_start: Byte donde inicia el bitmap de bloques de la particion
 * @param int block_start: Byte donde inicia la tabla de bloques de la particion
 * @param int inode_start: Byte donde inicia la tabla de inodos
*/
void Reporte::graficarBloques(QString direccion, QString destino, QString extension, int bm_block_start, int block_start, int inode_start){
    FILE *fp = fopen(direccion.toStdString().c_str(),"r");

    BloqueCarpeta carpeta;
    BloqueArchivo archivo;
    BloqueApuntadores apuntador;

    int aux = bm_block_start;
    int i = 0;
    char buffer;

    FILE *graph = fopen("grafica.dot","w");
    fprintf(graph,"digraph G{\n\n");

    while(aux < inode_start){
        fseek(fp,bm_block_start + i,SEEK_SET);
        buffer = static_cast<char>(fgetc(fp));
        aux++;
        if(buffer == '1'){
            fseek(fp,block_start + static_cast<int>(sizeof(BloqueCarpeta))*i,SEEK_SET);
            fread(&carpeta,sizeof(BloqueCarpeta),1,fp);
            fprintf(graph, "    nodo_%d [ shape=none, fontname=\"Century Gothic\" label=< \n",i);
            fprintf(graph, "   <table border=\'0\' cellborder='1' cellspacing='0' bgcolor=\"seagreen\">");
            fprintf(graph, "    <tr> <td colspan=\'2\'> <b>Bloque Carpeta %d</b> </td></tr>\n",i);
            fprintf(graph, "    <tr> <td bgcolor=\"mediumseagreen\"> b_name </td> <td bgcolor=\"mediumseagreen\"> b_inode </td></tr>\n");
            for(int c = 0;c < 4;c++)
                fprintf(graph, "    <tr> <td bgcolor=\"white\"> %s </td> <td bgcolor=\"white\"> %d </td></tr>\n",carpeta.b_content[c].b_name,carpeta.b_content[c].b_inodo);
            fprintf(graph, "   </table>>]\n\n");
        }else if(buffer == '2'){
            fseek(fp,block_start + static_cast<int>(sizeof(BloqueArchivo))*i,SEEK_SET);
            fread(&archivo,sizeof(BloqueArchivo),1,fp);
            fprintf(graph, "    nodo_%d [ shape=none, label=< \n",i);
            fprintf(graph, "   <table border=\'0\' cellborder='1' cellspacing='0' bgcolor=\"sandybrown\">");
            fprintf(graph, "    <tr> <td colspan=\'2\'> <b>Bloque Archivo %d </b></td></tr>\n",i);
            fprintf(graph, "    <tr> <td colspan=\'2\' bgcolor=\"white\"> %s </td></tr>\n",archivo.b_content);
            fprintf(graph, "   </table>>]\n\n");
        }else if(buffer == '3'){
            fseek(fp,block_start + static_cast<int>(sizeof(BloqueApuntadores))*i,SEEK_SET);
            fread(&apuntador,sizeof(BloqueApuntadores),1,fp);
            fseek(fp,block_start + static_cast<int>(sizeof(BloqueApuntadores))*i,SEEK_SET);
            fread(&apuntador,sizeof(BloqueApuntadores),1,fp);
            fprintf(graph, "    bloque_%d [shape=plaintext fontname=\"Century Gothic\" label=< \n",i);
            fprintf(graph, "   <table border=\'0\' bgcolor=\"khaki\">\n");
            fprintf(graph, "    <tr> <td> <b>Pointer block %d</b></td></tr>\n",i);
            for(int j = 0; j < 16; j++)
                fprintf(graph, "    <tr> <td bgcolor=\"white\">%d</td> </tr>\n",apuntador.b_pointer[j]);
            fprintf(graph, "   </table>>]\n\n");
        }
        i++;
    }

    fprintf(graph,"\n}");
    fclose(graph);

    fclose(fp);

    string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
    system(comando.c_str());
    cout << "Reporte generado con exito " << endl;
}

/* Metodo para generar el reporte de bitmaps de una particion
 * @param QString direccion: Es la direccion donde se encuentra la particion
 * @param QString destino: Es la ruta donde se creara el reporte
 * @param int bm_start: Byte donde inicia el bitmap de la particion
 * @param int n: numero de bits
*/
void Reporte::reporteBM(QString direccion, QString destino, int start_bm, int n){
    FILE *fp = fopen(direccion.toStdString().c_str(),"rb+");

    char byte;
    FILE *report = fopen(destino.toStdString().c_str(),"w+");
    fseek(report,0,SEEK_SET);
    int cont = 0;

    for (int i = 0; i < n; i++) {
        fseek(fp,start_bm + i,SEEK_SET);
        byte = static_cast<char>(fgetc(fp));
        if(byte == '0')
            fprintf(report,"0 ");
        else
            fprintf(report,"1 ");
        if(cont == 19){
            cont = 0;
            fprintf(report, "\n");
        }else
            cont++;
    }
    fclose(report);

    fclose(fp);
    cout << "Reporte generado con exito " << endl;
}

/* Metodo para generar el reporte del SuperBloque de una particion
 * @param QString direccion: Es la direccion donde se encuentra la particion
 * @param QString destino: Es la ruta donde se creara el reporte
 * @param QString extension: La extension que tendra el reporte .jpg|.png
 * @param int start_super: Byte donde inicia el super bloque
*/
void Reporte::graficarSuper(QString direccion, QString destino, QString extension, int start_super){
    FILE* fp = fopen(direccion.toStdString().c_str(),"r");

    SuperBloque super;

    fseek(fp,start_super,SEEK_SET);
    fread(&super,sizeof (super),1,fp);

    FILE *graph = fopen("grafica.dot","w");
    fprintf(graph,"digraph G{\n");
    fprintf(graph, "    nodo [shape=none, fontname=\"Century Gothic\" label=<");
    fprintf(graph, "   <table border=\'0\' cellborder='1\' cellspacing=\'0\' bgcolor=\"cornflowerblue\">");
    fprintf(graph, "    <tr> <td COLSPAN=\'2\'> <b>SUPERBLOQUE</b> </td></tr>\n");
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_inodes_count </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_inodes_count);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_blocks_count </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_blocks_count);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_free_block_count </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_free_blocks_count);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_free_inodes_count </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_free_inodes_count);
    struct tm *tm;
    char fecha[100];
    tm=localtime(&super.s_mtime);
    strftime(fecha,100,"%d/%m/%y %H:%S",tm);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_mtime </td> <td bgcolor=\"white\"> %s </td></tr>\n",fecha);
    tm=localtime(&super.s_umtime);
    strftime(fecha,100,"%d/%m/%y %H:%S",tm);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_umtime </td> <td bgcolor=\"white\"> %s </td> </tr>\n",fecha);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_mnt_count </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_mnt_count);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_magic </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_magic);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_inode_size </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_inode_size);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_block_size </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_block_size);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_first_ino </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_first_ino);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_first_blo </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_first_blo);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_bm_inode_start </td> <td bgcolor=\"white\"> %d </td></tr>\n",super.s_bm_inode_start);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_bm_block_start </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_bm_block_start);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_inode_start </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_inode_start);
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> s_block_start </td> <td bgcolor=\"white\"> %d </td> </tr>\n",super.s_block_start);
    fprintf(graph, "   </table>>]\n");
    fprintf(graph,"\n}");
    fclose(graph);

    fclose(fp);

    string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
    system(comando.c_str());
    cout << "Reporte SuperBloque generado con exito " << endl;
}

/* Metodo para generar el reporte de permisos de un archivo/carpeta
 * @param QString direccion: Es la direccion donde se encuentra la particion
 * @param QString destino: Es la ruta donde se creara el reporte
 * @param QString extension: La extension que tendra el reporte .jpg|.png
 * @param int start_super: byte donde inicia el super bloque
 * @param int n: numero inodo del archivo/carpeta
 * @param Usuario user: Informacion del propietario del archivo/carpeta
 * @param name: nombre de la carpeta/archivo
*/
void Reporte::graficarPermisos(QString direccion, QString destino, QString extension, int start_super, int n, Usuario user, QString name){
    FILE *fp = fopen(direccion.toStdString().c_str(),"rb+");

    SuperBloque super;
    InodoTable inodo;

    fseek(fp,start_super,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*n,SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,fp);

    FILE *graph = fopen("grafica.dot","w");
    fprintf(graph,"digraph G{\n\n");
    fprintf(graph, "    nodo [ shape=none, fontname=\"Century Gothic\" \n");
    fprintf(graph, "    label=< <table border=\'0\' cellborder='1\' cellspacing=\'0\' bgcolor=\"lightsteelblue\">\n");
    fprintf(graph, "     <tr> <td><b>Permisos</b></td><td><b>Owner</b></td><td><b>Grupo</b></td><td><b>Size</b></td><td><b>Fecha</b></td><td><b>Hora</b></td><td><b>Tipo</b></td><td><b>Name</b></td> </tr>\n");

    string auxPermisos = to_string(inodo.i_perm);
    char propietario = auxPermisos[0];
    char grupo = auxPermisos[1];
    char otros = auxPermisos[2];
    char permisos[50];

    //Tipo de permisos para el propietario
    if(propietario == '0')
        strcpy(permisos,"---");
    else if(propietario == '1')
        strcpy(permisos,"--x");
    else if(propietario == '2')
        strcpy(permisos,"-w-");
    else if(propietario == '3')
        strcpy(permisos,"-wx");
    else if(propietario == '4')
        strcpy(permisos,"r--");
    else if(propietario == '5')
        strcpy(permisos,"r-x");
    else if(propietario == '6')
        strcpy(permisos,"rw-");
    else if(propietario == '7')
        strcpy(permisos,"rwx");

    //Tipo de permisos para grupo
    if(grupo == '0')
        strcat(permisos," ---");
    else if(grupo == '1')
        strcat(permisos," --x");
    else if(grupo == '2')
        strcat(permisos," -w-");
    else if(grupo == '3')
        strcat(permisos," -wx");
    else if(grupo == '4')
        strcat(permisos," r--");
    else if(grupo == '5')
        strcat(permisos," r-x");
    else if(grupo == '6')
        strcat(permisos," rw-");
    else if(grupo == '7')
        strcat(permisos," rwx");

    //Tipo de permisos para otros
    if(otros == '0')
        strcat(permisos," ---");
    else if(otros == '1')
        strcat(permisos," --x");
    else if(otros == '2')
        strcat(permisos," -w-");
    else if(otros == '3')
        strcat(permisos," -wx");
    else if(otros == '4')
        strcat(permisos," r--");
    else if(otros == '5')
        strcat(permisos," r-x");
    else if(otros == '6')
        strcat(permisos," rw-");
    else if(otros == '7')
        strcat(permisos," rwx");

    fprintf(graph,"<tr> <td bgcolor=\"white\">%s</td> ",permisos);
    fprintf(graph, "<td bgcolor=\"white\">%s</td>",user.username);
    fprintf(graph, "<td bgcolor=\"white\">%s</td>",user.group);
    fprintf(graph, "<td bgcolor=\"white\">%d</td>",inodo.i_size);

    struct tm *tm;
    char fecha[100];
    tm=localtime(&inodo.i_atime);
    strftime(fecha,100,"%d/%m/%y",tm);
    fprintf(graph, "<td bgcolor=\"white\">%s</td>",fecha);
    strftime(fecha,100,"%H:%S",tm);
    fprintf(graph,"<td bgcolor=\"white\">%s</td>",fecha);
    if(inodo.i_type == '0')
        fprintf(graph,"<td bgcolor=\"white\">%s</td>","Carpeta");
    else if(inodo.i_type == '1')
        fprintf(graph,"<td bgcolor=\"white\">%s</td>","Archivo");
    fprintf(graph, "<td bgcolor=\"white\">%s</td> </tr>\n",name.toStdString().c_str());

    fprintf(graph, "    </table>>]\n");
    fprintf(graph,"\n}");
    fclose(graph);

    fclose(fp);

    string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
    system(comando.c_str());
    cout << "Reporte ls generado con exito " << endl;
}

/* Metodo para generar el reporte del arbol de inodos con bloques de un sistema de archivos
 * @param QString direccion: Es la direccion donde se encuentra la particion
 * @param QString destino: Es la ruta donde se creara el reporte
 * @param QString extension: La extension que tendra el reporte .jpg|.png
 * @param int start_super: byte donde inicia el super bloque
*/
void Reporte::graficarTree(QString direccion, QString destino, QString extension, int start_super){
    FILE *fp = fopen(direccion.toStdString().c_str(),"r");

    SuperBloque super;
    InodoTable inodo;
    BloqueCarpeta carpeta;
    BloqueArchivo archivo;
    BloqueApuntadores apuntador;

    fseek(fp,start_super,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);

    int aux = super.s_bm_inode_start;
    int i = 0;

    char buffer;

    FILE *graph = fopen("grafica.dot", "w");
    fprintf(graph, "digraph G{\n\n");
    fprintf(graph, "    rankdir=\"LR\" \n");

    //Creamos los inodos
    while(aux < super.s_bm_block_start){
        fseek(fp,super.s_bm_inode_start + i,SEEK_SET);
        buffer = static_cast<char>(fgetc(fp));
        aux++;
        int port = 0;
        if(buffer == '1'){
            fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*i,SEEK_SET);
            fread(&inodo,sizeof(InodoTable),1,fp);
            fprintf(graph, "    inodo_%d [ shape=plaintext fontname=\"Century Gothic\" label=<\n",i);
            fprintf(graph, "   <table bgcolor=\"royalblue\" border=\'0\' >");
            fprintf(graph, "    <tr> <td colspan=\'2\'><b>Inode %d</b></td></tr>\n",i);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_uid </td> <td bgcolor=\"white\"> %d </td>  </tr>\n",inodo.i_uid);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_gid </td> <td bgcolor=\"white\"> %d </td>  </tr>\n",inodo.i_gid);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_size </td><td bgcolor=\"white\"> %d </td> </tr>\n",inodo.i_size);
            struct tm *tm;
            char fecha[100];
            tm=localtime(&inodo.i_atime);
            strftime(fecha,100,"%d/%m/%y %H:%S",tm);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_atime </td> <td bgcolor=\"white\"> %s </td> </tr>\n",fecha);
            tm=localtime(&inodo.i_ctime);
            strftime(fecha,100,"%d/%m/%y %H:%S",tm);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_ctime </td> <td bgcolor=\"white\"> %s </td> </tr>\n",fecha);
            tm=localtime(&inodo.i_mtime);
            strftime(fecha,100,"%d/%m/%y %H:%S",tm);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_mtime </td> <td bgcolor=\"white\"> %s </td> </tr>\n",fecha);
            for(int b = 0; b < 15; b++){
                fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_block_%d </td> <td bgcolor=\"white\" port=\"f%d\"> %d </td></tr>\n",port,b,inodo.i_block[b]);
                port++;
            }
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_type </td> <td bgcolor=\"white\"> %c </td>  </tr>\n",inodo.i_type);
            fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"> i_perm </td> <td bgcolor=\"white\"> %d </td>  </tr>\n",inodo.i_perm);
            fprintf(graph, "   </table>>]\n\n");
            //Creamos los bloques relacionados al inodo
            for (int j = 0; j < 15; j++) {
                port = 0;
                if(inodo.i_block[j] != -1){
                    fseek(fp,super.s_bm_block_start + inodo.i_block[j],SEEK_SET);
                    buffer = static_cast<char>(fgetc(fp));
                    if(buffer == '1'){//Bloque carpeta
                        fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*inodo.i_block[j],SEEK_SET);
                        fread(&carpeta,sizeof(BloqueCarpeta),1,fp);
                        fprintf(graph, "    bloque_%d [shape=plaintext fontname=\"Century Gothic\" label=< \n",inodo.i_block[j]);
                        fprintf(graph, "   <table bgcolor=\"seagreen\" border=\'0\'>\n");
                        fprintf(graph, "    <tr> <td colspan=\'2\'><b>Folder block %d</b></td></tr>\n",inodo.i_block[j]);
                        fprintf(graph, "    <tr> <td bgcolor=\"mediumseagreen\"> b_name </td> <td bgcolor=\"mediumseagreen\"> b_inode </td></tr>\n");
                        for(int c = 0;c < 4; c++){
                            fprintf(graph, "    <tr> <td bgcolor=\"white\" > %s </td> <td bgcolor=\"white\"  port=\"f%d\"> %d </td></tr>\n",carpeta.b_content[c].b_name,port,carpeta.b_content[c].b_inodo);
                            port++;
                        }
                        fprintf(graph, "   </table>>]\n\n");
                        //Relacion de bloques a inodos
                        for(int c = 0; c < 4; c++){
                            if(carpeta.b_content[c].b_inodo !=-1){
                                if(strcmp(carpeta.b_content[c].b_name,".")!=0 && strcmp(carpeta.b_content[c].b_name,"..")!=0)
                                    fprintf(graph, "    bloque_%d:f%d -> inodo_%d;\n",inodo.i_block[j],c,carpeta.b_content[c].b_inodo);
                            }
                        }
                    }else if(buffer == '2'){//Bloque archivo
                        fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*inodo.i_block[j],SEEK_SET);
                        fread(&archivo,sizeof(BloqueArchivo),1,fp);
                        fprintf(graph, "    bloque_%d [shape=plaintext fontname=\"Century Gothic\" label=< \n",inodo.i_block[j]);
                        fprintf(graph, "   <table border=\'0\' bgcolor=\"sandybrown\">\n");
                        fprintf(graph, "    <tr> <td> <b>File block %d</b></td></tr>\n",inodo.i_block[j]);
                        fprintf(graph, "    <tr> <td bgcolor=\"white\"> %s </td></tr>\n",archivo.b_content);
                        fprintf(graph, "   </table>>]\n\n");
                    }else if(buffer == '3'){//Bloque apuntador
                        fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*inodo.i_block[j],SEEK_SET);
                        fread(&apuntador,sizeof(BloqueApuntadores),1,fp);
                        fprintf(graph, "    bloque_%d [shape=plaintext fontname=\"Century Gothic\" label=< \n",inodo.i_block[j]);
                        fprintf(graph, "   <table border=\'0\' bgcolor=\"khaki\">\n");
                        fprintf(graph, "    <tr> <td> <b>Pointer block %d</b></td></tr>\n",inodo.i_block[j]);
                        for(int a = 0; a < 16; a++){
                            fprintf(graph, "    <tr> <td bgcolor=\"white\" port=\"f%d\">%d</td> </tr>\n",port,apuntador.b_pointer[a]);
                            port++;
                        }
                        fprintf(graph, "   </table>>]\n\n");
                        //Bloques carpeta/archivos del bloque de apuntadores
                        for (int x = 0; x < 16; x++) {
                            port = 0;
                            if(apuntador.b_pointer[x] != -1){
                                fseek(fp,super.s_bm_block_start + apuntador.b_pointer[x],SEEK_SET);
                                buffer = static_cast<char>(fgetc(fp));
                                if(buffer == '1'){
                                    fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*apuntador.b_pointer[x],SEEK_SET);
                                    fread(&carpeta,sizeof(BloqueCarpeta),1,fp);
                                    fprintf(graph, "    bloque_%d [shape=plaintext fontname=\"Century Gothic\" label=< \n",apuntador.b_pointer[x]);
                                    fprintf(graph, "   <table border=\'0\' bgcolor=\"seagreen\" >\n");
                                    fprintf(graph, "    <tr> <td colspan=\'2\'> <b>Folder block %d</b> </td></tr>\n",apuntador.b_pointer[x]);
                                    fprintf(graph, "    <tr> <td bgcolor=\"mediumseagreen\"> b_name </td> <td bgcolor=\"mediumseagreen\"> b_inode </td></tr>\n");
                                    for(int c = 0;c < 4; c++){
                                        fprintf(graph, "    <tr> <td bgcolor=\"white\"> %s </td> <td bgcolor=\"white\" port=\"f%d\"> %d </td></tr>\n",carpeta.b_content[c].b_name,port,carpeta.b_content[c].b_inodo);
                                        port++;
                                    }
                                    fprintf(graph, "   </table>>]\n\n");
                                    //Relacion de bloques a inodos
                                    for(int c = 0; c < 4; c++){
                                        if(carpeta.b_content[c].b_inodo !=-1){
                                            if(strcmp(carpeta.b_content[c].b_name,".")!=0 && strcmp(carpeta.b_content[c].b_name,"..")!=0)
                                                fprintf(graph, "    bloque_%d:f%d -> inodo_%d;\n",apuntador.b_pointer[x],c,carpeta.b_content[c].b_inodo);
                                        }
                                    }
                                }else if(buffer == '2'){
                                    fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*apuntador.b_pointer[x],SEEK_SET);
                                    fread(&archivo,sizeof(BloqueArchivo),1,fp);
                                    fprintf(graph, "    bloque_%d [shape=plaintext fontname=\"Century Gothic\" label=< \n",apuntador.b_pointer[x]);
                                    fprintf(graph, "   <table border=\'0\' bgcolor=\"sandybrown\">\n");
                                    fprintf(graph, "    <tr> <td> <b>File block %d</b></td></tr>\n",apuntador.b_pointer[x]);
                                    fprintf(graph, "    <tr> <td bgcolor=\"white\"> %s </td></tr>\n",archivo.b_content);
                                    fprintf(graph, "   </table>>]\n\n");
                                }else if(buffer == '3'){

                                }
                            }
                        }

                        //Relacion de bloques apuntador a bloques archivos/carpetas
                        for(int b = 0; b < 16; b++){
                            if(apuntador.b_pointer[b] != -1)
                                fprintf(graph, "    bloque_%d:f%d -> bloque_%d;\n",inodo.i_block[j],b,apuntador.b_pointer[b]);
                        }
                    }
                    //Relacion de inodos a bloques
                    fprintf(graph, "    inodo_%d:f%d -> bloque_%d; \n",i,j,inodo.i_block[j]);
                }
            }
        }
        i++;
    }

    fprintf(graph,"\n\n}");
    fclose(graph);

    fclose(fp);

    string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
    system(comando.c_str());
    cout << "Reporte Tree generado con exito " << endl;
}

/* Metodo para generar el reporte del Journaling de un sistema
 * @param QString direccion: Es la direccion donde se encuentra la particion
 * @param QString destino: Es la ruta donde se creara el reporte
 * @param QString extension: La extension que tendra el reporte .jpg|.png
 * @param int fin: byte donde finaliza el journaling
*/
void Reporte::graficarJournaling(QString direccion, QString destino, QString extension,int inicio_super){
    FILE *fp = fopen(direccion.toStdString().c_str(),"r");

    SuperBloque super;
    Journal j;
    fseek(fp,inicio_super,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);

    FILE *graph = fopen("grafica.dot","w");
    fprintf(graph,"digraph G{\n");
    fprintf(graph, "    nodo [shape=none, fontname=\"Century Gothic\" label=<\n");
    fprintf(graph, "   <table border=\'0\' cellborder='1\' cellspacing=\'0\'>\n");
    fprintf(graph, "    <tr> <td COLSPAN=\'7\' bgcolor=\"cornflowerblue\"> <b>JOURNALING</b> </td></tr>\n");
    fprintf(graph, "    <tr> <td bgcolor=\"lightsteelblue\"><b>Operacion</b></td> <td bgcolor=\"lightsteelblue\"><b>Tipo</b></td><td bgcolor=\"lightsteelblue\"><b>Nombre</b></td><td bgcolor=\"lightsteelblue\"><b>Contenido</b></td>\n");
    fprintf(graph, "    <td bgcolor=\"lightsteelblue\"><b>Propietario</b></td><td bgcolor=\"lightsteelblue\"><b>Permisos</b></td><td bgcolor=\"lightsteelblue\"><b>Fecha</b></td></tr>\n");
    //
    fseek(fp,inicio_super + static_cast<int>(sizeof(SuperBloque)),SEEK_SET);
    while(ftell(fp) < super.s_bm_inode_start){
        fread(&j,sizeof(Journal),1,fp);
        if(j.journal_type == 0 || j.journal_type == 1){
            struct tm *tm;
            char fecha[100];
            tm = localtime(&j.journal_date);
            strftime(fecha,100,"%d/%m/%y %H:%S",tm);
            fprintf(graph,"<tr><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%d</td><td>%d</td><td>%s</td></tr>\n",j.journal_operation_type,j.journal_type,j.journal_name,j.journal_content,j.journal_owner,j.journal_permissions,fecha);
        }
    }
    fprintf(graph, "   </table>>]\n");
    fprintf(graph,"}");
    fclose(graph);

    fclose(fp);

    string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
    system(comando.c_str());
    cout << "Reporte Journaling generado con exito " << endl;
}

/* Metodo para generar el reporte del Journaling de un sistema
 * @param QString direccion: Es la direccion donde se encuentra la particion
 * @param QString destino: Es la ruta donde se creara el reporte
 * @param QString extension: La extension que tendra el reporte .jpg|.png
 * @param QString name: El nombre del archivo
 * @param int start_super: byte donde inicia el super bloque
 * @param int n: numero de inodo del archivo
*/
void Reporte::graficarFILE(QString direccion, QString destino, QString extension, QString name,int start_super,int n){
    FILE *fp = fopen(direccion.toStdString().c_str(),"r");

    SuperBloque super;
    InodoTable inodo;
    BloqueArchivo archivo;

    fseek(fp,start_super,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*n,SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,fp);

    FILE *graph = fopen("grafica.dot","w");
    fprintf(graph,"digraph G{\n");
    fprintf(graph, "    nodo [shape=none, fontname=\"Century Gothic\" label=<");
    fprintf(graph, "   <table border=\'0\' cellborder='1\' cellspacing=\'0\' bgcolor=\"lightsteelblue\">");
    fprintf(graph, "    <tr><td align=\"left\"> <b>%s</b> </td></tr>\n",name.toStdString().c_str());
    fprintf(graph, "    <tr><td bgcolor=\"white\">");
    for (int i = 0; i < 15; i++) {
        if(inodo.i_block[i] != -1){
            if(i == 12){//Apuntador indirecto simple
                BloqueApuntadores apuntador;
                fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*inodo.i_block[i],SEEK_SET);
                fread(&apuntador,sizeof(BloqueApuntadores),1,fp);
                for(int j = 0; j < 16; j++){
                    if(apuntador.b_pointer[j] != -1){
                        fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*apuntador.b_pointer[j],SEEK_SET);
                        fread(&archivo,sizeof(BloqueArchivo),1,fp);
                        fprintf(graph,"%s <br/>",archivo.b_content);
                    }
                }
            }else if(i == 13){

            }else if(i == 14){

            }else{//Apuntadores directos
                fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*inodo.i_block[i],SEEK_SET);
                fread(&archivo,sizeof(BloqueArchivo),1,fp);
                fprintf(graph,"%s <br/>",archivo.b_content);
            }
        }
    }
    fprintf(graph, "    </td></tr>\n");
    fprintf(graph, "   </table>>]\n");
    fprintf(graph,"\n}");
    fclose(graph);

    fclose(fp);

    string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
    system(comando.c_str());
    cout << "Reporte file generado con exito " << endl;
}
