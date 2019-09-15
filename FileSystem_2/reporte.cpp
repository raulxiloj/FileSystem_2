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
 * @param QString extension: La extension que tendra nuestro reporte .jpg|.png|etc
 * @param int bm_inode_start: Byte donde inicia el bitmap de inodos de la particion
 * @param int inode_start: Byte donde inicia la tabla de inodos de la particion
 * @param int bm_block_start: Byte donde inicia el bitmap de bloques de la particion
*/
void Reporte::graficarInodos(QString direccion, QString destino, QString extension,int bm_inode_start,int inode_start,int bm_block_start){
    FILE *fp = fopen(direccion.toStdString().c_str(), "r");

    InodoTable inodo;
    char buffer;

    FILE *graph = fopen("grafica.dot","w");
    fprintf(graph,"digraph G{\n\n");
    int aux = bm_inode_start;
    int i = 0;
    while(aux < bm_block_start){
        fseek(fp,bm_inode_start + i,SEEK_SET);
        buffer = static_cast<char>(fgetc(fp));
        aux++;
        if(buffer == '1'){
            fseek(fp,inode_start + static_cast<int>(sizeof(InodoTable))*i,SEEK_SET);
            fread(&inodo,sizeof(InodoTable),1,fp);
            fprintf(graph, "    subgraph inode_%d{\n",i);
            fprintf(graph, "    nodo_%d [ shape=none label=<\n",i);
            fprintf(graph, "    <table> <tr> <td colspan=\'2\'> Inodo %d </td></tr>\n",i);
            fprintf(graph, "    <tr> <td> i_uid </td> <td> %d </td>  </tr>\n",inodo.i_uid);
            fprintf(graph, "    <tr> <td> i_gid </td> <td> %d </td>  </tr>\n",inodo.i_gid);
            fprintf(graph, "    <tr> <td> i_size </td> <td> %d </td> </tr>\n",inodo.i_size);
            struct tm *tm;
            char fecha[100];
            tm=localtime(&inodo.i_atime);
            strftime(fecha,100,"%d/%m/%y %H:%S",tm);
            fprintf(graph, "    <tr> <td> i_atime </td> <td> %s </td>  </tr>\n",fecha);
            tm=localtime(&inodo.i_ctime);
            strftime(fecha,100,"%d/%m/%y %H:%S",tm);
            fprintf(graph, "    <tr> <td> i_ctime </td> <td> %s </td>  </tr>\n",fecha);
            tm=localtime(&inodo.i_mtime);
            strftime(fecha,100,"%d/%m/%y %H:%S",tm);
            fprintf(graph, "    <tr> <td> i_mtime </td> <td> %s </td></tr>\n",fecha);
            for(int b = 0; b < 15; b++){
                fprintf(graph, "    <tr> <td> i_block_%d </td> <td> %d </td></tr>\n",b,inodo.i_block[b]);
            }
            fprintf(graph, "    <tr> <td> i_type </td> <td> %c </td>  </tr>\n",inodo.i_type);
            fprintf(graph, "    <tr> <td> i_perm </td> <td> %d </td>  </tr>\n",inodo.i_perm);
            fprintf(graph, "    </table>>]\n");
            fprintf(graph, "    }\n");
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

void Reporte::graficarBloques(QString direccion, QString destino, QString extension, int bm_inode_start, int inode_start, int bm_block_start){
    FILE *fp = fopen(direccion.toStdString().c_str(),"r");

    BloqueCarpeta carpeta;
    BloqueArchivo archivo;
    BloqueApuntadores apuntador;

    FILE *graph = fopen("grafica.dot","w");
    fprintf(graph,"digraph G{\n\n");

    fprintf(graph,"\n}");
    fclose(graph);

    fclose(fp);

    string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
    system(comando.c_str());
    cout << "Reporte generado con exito " << endl;
}
