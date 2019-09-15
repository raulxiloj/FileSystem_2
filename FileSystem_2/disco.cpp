#include "disco.h"

Disco::Disco()
{

}

/* Metodo que se encarga de crear una particion primaria
 * @param QString direccion: direccion del disco
 * @param QString nombre: nombre de la particion
 * @param int size: tamano de la particion
 * @param char fit: ajuste de la particion
 * @param char unit: unidades del tamano (M K B)
 */
void Disco::crearParticionPrimaria(QString direccion, QString nombre, int size, char fit, char unit, QString archivo){
    char auxFit = 0;
    char auxUnit = 0;
    string auxPath = direccion.toStdString();
    int size_bytes = 1024;
    char buffer = '1';

    if(fit != 0)
        auxFit = fit;
    else
        auxFit = 'W';

    if(unit != 0){
        auxUnit = unit;
        if(auxUnit == 'b'){
            size_bytes = size;
        }else if(auxUnit == 'k'){
            size_bytes = size * 1024;
        }else{
            size_bytes = size*1024*1024;
        }
    }else{
        size_bytes = size * 1024;
    }

    FILE *fp;
    MBR masterboot;

    if((fp = fopen(auxPath.c_str(), "rb+"))){
        bool flagParticion = false;//Flag para ver si hay una particion disponible
        int numParticion = 0;//Que numero de particion es
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        //Verificar si existe una particion disponible
        for(int i = 0; i < 4; i++){
            if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                flagParticion = true;
                numParticion = i;
                break;
            }
        }

        if(flagParticion){
            //Verificar el espacio libre del disco
            int espacioUsado = 0;
            for(int i = 0; i < 4; i++){
                if(masterboot.mbr_partition[i].part_status!='1'){
                    espacioUsado += masterboot.mbr_partition[i].part_size;
                }
            }
            if(archivo == "principal"){
                cout << "Espacio disponible: " << (masterboot.mbr_size - espacioUsado) << " Bytes" << endl;
                cout << "Espacio necesario:  " << size_bytes << " Bytes" << endl;
            }
            //Verificar que haya espacio suficiente para crear la particion
            if((masterboot.mbr_size - espacioUsado) >= size_bytes){
                if(!existeParticion(direccion,nombre)){
                    if(masterboot.mbr_disk_fit == 'F'){//FIRST FIT
                        masterboot.mbr_partition[numParticion].part_type = 'P';
                        masterboot.mbr_partition[numParticion].part_fit = auxFit;
                        //start
                        if(numParticion == 0){
                            masterboot.mbr_partition[numParticion].part_start = sizeof(masterboot);
                        }else{
                            masterboot.mbr_partition[numParticion].part_start = masterboot.mbr_partition[numParticion-1].part_start + masterboot.mbr_partition[numParticion-1].part_size;
                        }
                        masterboot.mbr_partition[numParticion].part_size = size_bytes;
                        masterboot.mbr_partition[numParticion].part_status = '0';
                        strcpy(masterboot.mbr_partition[numParticion].part_name,nombre.toStdString().c_str());
                        //Se guarda de nuevo el MBR
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        //Se guardan los bytes de la particion
                        fseek(fp,masterboot.mbr_partition[numParticion].part_start,SEEK_SET);
                        for(int i = 0; i < size_bytes; i++){
                            fwrite(&buffer,1,1,fp);
                        }
                        if(archivo == "principal") cout << "...\n" << "Particion primaria creada con exito" <<  endl;
                    }else if(masterboot.mbr_disk_fit == 'B'){//BEST FIT
                        int bestIndex = numParticion;
                        for(int i = 0; i < 4; i++){
                            if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                                if(i != numParticion){
                                    if(masterboot.mbr_partition[bestIndex].part_size > masterboot.mbr_partition[i].part_size){
                                        bestIndex = i;
                                        break;
                                    }
                                }
                            }
                        }
                        masterboot.mbr_partition[bestIndex].part_type = 'P';
                        masterboot.mbr_partition[bestIndex].part_fit = auxFit;
                        //start
                        if(bestIndex == 0){
                            masterboot.mbr_partition[bestIndex].part_start = sizeof(masterboot);
                        }else{
                            masterboot.mbr_partition[bestIndex].part_start = masterboot.mbr_partition[bestIndex-1].part_start + masterboot.mbr_partition[bestIndex-1].part_size;
                        }
                        masterboot.mbr_partition[bestIndex].part_size = size_bytes;
                        masterboot.mbr_partition[bestIndex].part_status = '0';
                        strcpy(masterboot.mbr_partition[bestIndex].part_name,nombre.toStdString().c_str());
                        //Se guarda de nuevo el MBR
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        //Se guardan los bytes de la particion
                        fseek(fp,masterboot.mbr_partition[bestIndex].part_start,SEEK_SET);
                        for(int i = 0; i < size_bytes; i++){
                            fwrite(&buffer,1,1,fp);
                        }
                        if(archivo == "principal") cout << "...\n" << "Particion primaria creada con exito" <<  endl;
                    }else if(masterboot.mbr_disk_fit == 'W'){//WORST FIT
                        int  worstIndex= numParticion;
                        for(int i = 0; i < 4; i++){
                            if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                                if(i != numParticion){
                                    if(masterboot.mbr_partition[worstIndex].part_size < masterboot.mbr_partition[i].part_size){
                                        worstIndex = i;
                                        break;
                                    }
                                }
                            }
                        }
                        masterboot.mbr_partition[worstIndex].part_type = 'P';
                        masterboot.mbr_partition[worstIndex].part_fit = auxFit;
                        //start
                        if(worstIndex == 0){
                            masterboot.mbr_partition[worstIndex].part_start = sizeof(masterboot);
                        }else{
                            masterboot.mbr_partition[worstIndex].part_start = masterboot.mbr_partition[worstIndex-1].part_start + masterboot.mbr_partition[worstIndex-1].part_size;
                        }
                        masterboot.mbr_partition[worstIndex].part_size = size_bytes;
                        masterboot.mbr_partition[worstIndex].part_status = '0';
                        strcpy(masterboot.mbr_partition[worstIndex].part_name,nombre.toStdString().c_str());
                        //Se guarda de nuevo el MBR
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        //Se guardan los bytes de la particion
                        fseek(fp,masterboot.mbr_partition[worstIndex].part_start,SEEK_SET);
                        for(int i = 0; i < size_bytes; i++){
                            fwrite(&buffer,1,1,fp);
                        }
                        if(archivo == "principal") cout << "...\n" << "Particion primaria creada con exito" <<  endl;
                    }
                }else{
                    cout << "ERROR ya existe una particion con ese nombre" << endl;
                }

            }else{
                cout << "ERROR la particion a crear excede el espacio libre" << endl;
            }
        }else{
            cout << "ERROR: Ya existen 4 particiones, no se puede crear otra" << endl;
            cout << "Elimine alguna para poder crear una" << endl;
        }
    fclose(fp);
    }else{
        cout << "ERROR no existe el disco" << endl;
    }
}

/* Metodo que se encarga de crear una particion extendida
 * @param QString direccion: direccion del disco
 * @param QString nombre: nombre de la particion
 * @param int size: tamano de la particion
 * @param char fit: ajuste de la particion
 * @param char unit: unidades del tamano (M K B)
*/
void Disco::crearParticionExtendida(QString direccion, QString nombre, int size, char fit, char unit, QString archivo){
    char auxFit = 0;
    char auxUnit = 0;
    string auxPath = direccion.toStdString();
    int size_bytes = 1024;
    char buffer = '1';

    if(fit != 0)
        auxFit = fit;
    else
        auxFit = 'W';

    if(unit != 0){
        auxUnit = unit;
        if(auxUnit == 'b'){
            size_bytes = size;
        }else if(auxUnit == 'k'){
            size_bytes = size * 1024;
        }else{
            size_bytes = size*1024*1024;
        }
    }else{
        size_bytes = size * 1024;
    }

    FILE *fp;
    MBR masterboot;
    if((fp = fopen(auxPath.c_str(), "rb+"))){
        bool flagParticion = false;//Flag para ver si hay una particion disponible
        bool flagExtendida = false;//Flag para ver si ya hay una particion extendida
        int numParticion = 0;//Que numero de particion es
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        for(int i = 0; i < 4; i++){
            if (masterboot.mbr_partition[i].part_type == 'E'){
                flagExtendida = true;
                break;
            }
        }
        if(!flagExtendida){
            //Verificar si existe una particion disponible
            for(int i = 0; i < 4; i++){
                if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                    flagParticion = true;
                    numParticion = i;
                    break;
                }
            }
            if(flagParticion){
                //Verificar el espacio libre del disco
                int espacioUsado = 0;
                for(int i = 0; i < 4; i++){
                    if(masterboot.mbr_partition[i].part_status!='1'){
                       espacioUsado += masterboot.mbr_partition[i].part_size;
                    }
                }
                if(archivo == "principal"){
                    cout << "Espacio disponible: " << (masterboot.mbr_size - espacioUsado) <<" Bytes"<< endl;
                    cout << "Espacio necesario:  " << size_bytes << " Bytes" << endl;
                }
                //Verificar que haya espacio suficiente para crear la particion
                if((masterboot.mbr_size - espacioUsado) >= size_bytes){
                    if(!(existeParticion(direccion,nombre))){
                        if(masterboot.mbr_disk_fit == 'F'){
                            masterboot.mbr_partition[numParticion].part_type = 'E';
                            masterboot.mbr_partition[numParticion].part_fit = auxFit;
                            //start
                            if(numParticion == 0){
                                masterboot.mbr_partition[numParticion].part_start = sizeof(masterboot);
                            }else{
                                masterboot.mbr_partition[numParticion].part_start =  masterboot.mbr_partition[numParticion-1].part_start + masterboot.mbr_partition[numParticion-1].part_size;
                            }
                            masterboot.mbr_partition[numParticion].part_size = size_bytes;
                            masterboot.mbr_partition[numParticion].part_status = '0';
                            strcpy(masterboot.mbr_partition[numParticion].part_name,nombre.toStdString().c_str());
                            //Se guarda de nuevo el MBR
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            //Se guarda la particion extendida
                            fseek(fp, masterboot.mbr_partition[numParticion].part_start,SEEK_SET);
                            EBR extendedBoot;
                            extendedBoot.part_fit = auxFit;
                            extendedBoot.part_status = '0';
                            extendedBoot.part_start = masterboot.mbr_partition[numParticion].part_start;
                            extendedBoot.part_size = 0;
                            extendedBoot.part_next = -1;
                            strcpy(extendedBoot.part_name, "");
                            fwrite(&extendedBoot,sizeof (EBR),1,fp);
                            for(int i = 0; i < (size_bytes - (int)sizeof(EBR)); i++){
                                fwrite(&buffer,1,1,fp);
                            }
                            if(archivo == "principal") cout << "...\n" << "Particion extendida creada con exito"<< endl;
                        }else if(masterboot.mbr_disk_fit == 'B'){
                            int bestIndex = numParticion;
                            for(int i = 0; i < 4; i++){
                                if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                                    if(i != numParticion){
                                        if(masterboot.mbr_partition[bestIndex].part_size > masterboot.mbr_partition[i].part_size){
                                            bestIndex = i;
                                            break;
                                        }
                                    }
                                }
                            }
                            masterboot.mbr_partition[bestIndex].part_type = 'E';
                            masterboot.mbr_partition[bestIndex].part_fit = auxFit;
                            //start
                            if(bestIndex == 0){
                                masterboot.mbr_partition[bestIndex].part_start = sizeof(masterboot);
                            }else{
                                masterboot.mbr_partition[bestIndex].part_start =  masterboot.mbr_partition[bestIndex-1].part_start + masterboot.mbr_partition[bestIndex-1].part_size;
                            }
                            masterboot.mbr_partition[bestIndex].part_size = size_bytes;
                            masterboot.mbr_partition[bestIndex].part_status = '0';
                            strcpy(masterboot.mbr_partition[bestIndex].part_name,nombre.toStdString().c_str());
                            //Se guarda de nuevo el MBR
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            //Se guarda la particion extendida
                            fseek(fp, masterboot.mbr_partition[bestIndex].part_start,SEEK_SET);
                            EBR extendedBoot;
                            extendedBoot.part_fit = auxFit;
                            extendedBoot.part_status = '0';
                            extendedBoot.part_start = masterboot.mbr_partition[bestIndex].part_start;
                            extendedBoot.part_size = 0;
                            extendedBoot.part_next = -1;
                            strcpy(extendedBoot.part_name, "");
                            fwrite(&extendedBoot,sizeof (EBR),1,fp);
                            for(int i = 0; i < (size_bytes - (int)sizeof(EBR)); i++){
                                fwrite(&buffer,1,1,fp);
                            }
                            if(archivo == "principal") cout << "...\n" << "Particion extendida creada con exito"<< endl;
                        }else if(masterboot.mbr_disk_fit == 'W'){
                            int  worstIndex= numParticion;
                            for(int i = 0; i < 4; i++){
                                if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                                    if(i != numParticion){
                                        if(masterboot.mbr_partition[worstIndex].part_size < masterboot.mbr_partition[i].part_size){
                                            worstIndex = i;
                                            break;
                                        }
                                    }
                                }
                            }
                            masterboot.mbr_partition[worstIndex].part_type = 'E';
                            masterboot.mbr_partition[worstIndex].part_fit = auxFit;
                            //start
                            if(worstIndex == 0){
                                masterboot.mbr_partition[worstIndex].part_start = sizeof(masterboot);
                            }else{
                                masterboot.mbr_partition[worstIndex].part_start =  masterboot.mbr_partition[worstIndex-1].part_start + masterboot.mbr_partition[worstIndex-1].part_size;
                            }
                            masterboot.mbr_partition[worstIndex].part_size = size_bytes;
                            masterboot.mbr_partition[worstIndex].part_status = '0';
                            strcpy(masterboot.mbr_partition[worstIndex].part_name,nombre.toStdString().c_str());
                            //Se guarda de nuevo el MBR
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            //Se guarda la particion extendida
                            fseek(fp, masterboot.mbr_partition[worstIndex].part_start,SEEK_SET);
                            EBR extendedBoot;
                            extendedBoot.part_fit = auxFit;
                            extendedBoot.part_status = '0';
                            extendedBoot.part_start = masterboot.mbr_partition[worstIndex].part_start;
                            extendedBoot.part_size = 0;
                            extendedBoot.part_next = -1;
                            strcpy(extendedBoot.part_name, "");
                            fwrite(&extendedBoot,sizeof (EBR),1,fp);
                            for(int i = 0; i < (size_bytes - (int)sizeof(EBR)); i++){
                                fwrite(&buffer,1,1,fp);
                            }
                            if(archivo == "principal") cout << "...\n" << "Particion extendida creada con exito"<< endl;
                        }
                    }else{
                        cout << "ERROR ya existe una particion con ese nombre" << endl;
                    }
                }else{
                    cout << "ERROR la particion a crear excede el tamano libre" << endl;
                }
            }else{
                cout << "ERROR: Ya existen 4 particiones, no se puede crear otra" << endl;
                cout << "Elimine alguna para poder crear una" << endl;
            }
        }else{
            cout << "ERROR ya existe una particion extendida en este disco" << endl;
        }
    fclose(fp);
    }else{
        cout << "ERROR no existe el disco" << endl;
    }
}

/* Metodo que se encarga de crear una particion logica
 * @param QString direccion: direccion del disco
 * @param QString nombre: nombre de la particion
 * @param int size: tamano de la particion
 * @param char fit: ajuste de la particion
 * @param char unit: unidades del tamano (M K B)
*/
void Disco::crearParticionLogica(QString direccion, QString nombre, int size, char fit, char unit, QString archivo){
    char auxFit = 0;
    char auxUnit = 0;
    string auxPath = direccion.toStdString();
    int size_bytes = 1024;
    char buffer = '1';

    if(fit != 0)
        auxFit = fit;
    else
        auxFit = 'W';
    if(unit != 0){
        auxUnit = unit;
        if(auxUnit == 'b'){
            size_bytes = size;
        }else if(auxUnit == 'k'){
            size_bytes = size * 1024;
        }else{
            size_bytes = size*1024*1024;
        }
    }else{
        size_bytes = size * 1024;
    }

    FILE *fp;
    MBR masterboot;
    if((fp = fopen(auxPath.c_str(), "rb+"))){
        int numExtendida = -1;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        //Verificar si existe una particion extendida
        for(int i = 0; i < 4; i++){
            if(masterboot.mbr_partition[i].part_type == 'E'){
                numExtendida = i;
                break;
            }
        }
        if(!existeParticion(direccion,nombre)){
            if(numExtendida != -1){
                EBR extendedBoot;
                int cont = masterboot.mbr_partition[numExtendida].part_start;
                fseek(fp,cont,SEEK_SET);
                fread(&extendedBoot, sizeof(EBR),1,fp);
                if(extendedBoot.part_size == 0){//Si es la primera
                    if(masterboot.mbr_partition[numExtendida].part_size < size_bytes){
                        if(archivo == "principal") cout << "ERROR la particion logica a crear excede el espacio disponible de la particion extendida " << endl;
                    }else{
                        extendedBoot.part_status = '0';
                        extendedBoot.part_fit = auxFit;
                        extendedBoot.part_start = ftell(fp) - sizeof(EBR); //Para regresar al inicio de la extendida
                        extendedBoot.part_size = size_bytes;
                        extendedBoot.part_next = -1;
                        strcpy(extendedBoot.part_name, nombre.toStdString().c_str());
                        fseek(fp, masterboot.mbr_partition[numExtendida].part_start ,SEEK_SET);
                        fwrite(&extendedBoot,sizeof(EBR),1,fp);
                        if(archivo == "principal") cout << "...\nParticion logica creada con exito "<< endl;
                    }
                }else{
                    while((extendedBoot.part_next != -1) && (ftell(fp) < (masterboot.mbr_partition[numExtendida].part_size + masterboot.mbr_partition[numExtendida].part_start))){
                        fseek(fp,extendedBoot.part_next,SEEK_SET);
                        fread(&extendedBoot,sizeof(EBR),1,fp);
                    }
                    int espacioNecesario = extendedBoot.part_start + extendedBoot.part_size + size_bytes;
                    if(espacioNecesario <= (masterboot.mbr_partition[numExtendida].part_size + masterboot.mbr_partition[numExtendida].part_start)){
                        extendedBoot.part_next = extendedBoot.part_start + extendedBoot.part_size;
                        //Escribimos el next del ultimo EBR
                        fseek(fp,ftell(fp) - sizeof (EBR),SEEK_SET);
                        fwrite(&extendedBoot, sizeof(EBR),1 ,fp);
                        //Escribimos el nuevo EBR
                        fseek(fp,extendedBoot.part_start + extendedBoot.part_size, SEEK_SET);
                        extendedBoot.part_status = 0;
                        extendedBoot.part_fit = auxFit;
                        extendedBoot.part_start = ftell(fp);
                        extendedBoot.part_size = size_bytes;
                        extendedBoot.part_next = -1;
                        strcpy(extendedBoot.part_name,nombre.toStdString().c_str());
                        fwrite(&extendedBoot,sizeof(EBR),1,fp);
                        if(archivo == "principal") cout << "Particion logica creada con exito "<< endl;
                    }else{
                        cout << "ERROR la particion logica a crear excede el" << endl;
                        cout << "espacio disponible de la particion extendida" << endl;
                    }
                }
            }else{
                cout << "ERROR se necesita una particion extendida donde guardar la logica " << endl;
            }
        }else{
            cout << "ERROR ya existe una particion con ese nombre" << endl;
        }

    fclose(fp);
    }else{
        cout << "ERROR no existe el disco" << endl;
    }

}

/* Funcion que devuelve un booleano para comprobar la existencia del nombre de una particion en un disco
 * @param QString direccion: ruta del archivo
 * @param QString nombre: nombre de la particion
 * @return true = si existe | false = si no existe
*/
bool Disco::existeParticion(QString direccion, QString nombre){
    int extendida = -1;
    FILE *fp;
    if((fp = fopen(direccion.toStdString().c_str(),"rb+"))){
        MBR masterboot;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot, sizeof(MBR),1,fp);
        for(int i = 0; i < 4; i++){
            if(strcmp(masterboot.mbr_partition[i].part_name,nombre.toStdString().c_str()) == 0){
                fclose(fp);
                return true;
            }else if(masterboot.mbr_partition[i].part_type == 'E'){
                extendida = i;
            }
        }
        if(extendida != -1){
            fseek(fp, masterboot.mbr_partition[extendida].part_start,SEEK_SET);
            EBR extendedBoot;
            while((fread(&extendedBoot,sizeof(EBR),1,fp))!=0 && (ftell(fp) < (masterboot.mbr_partition[extendida].part_size + masterboot.mbr_partition[extendida].part_start))){
                if(strcmp(extendedBoot.part_name,nombre.toStdString().c_str()) == 0){
                    fclose(fp);
                    return true;
                }
                if(extendedBoot.part_next == -1){
                    fclose(fp);
                    return false;
                }
            }
        }
    }
    fclose(fp);
    return false;
}

/* Metodo que se encarga de eliminar una particion de cualquier tipo
 * @param QString direccion: ruta del archivo
 * @param QString nombre: nombre de la particion
 * @param valD: tipo de eliminacion fast|full
*/
void Disco::eliminarParticion(QString direccion, QString nombre, QString typeDelete, QString archivo){
    string auxPath = direccion.toStdString();
    string auxNombre = nombre.toStdString();
    FILE *fp;
    if((fp = fopen(auxPath.c_str(), "rb+"))){
        MBR masterboot;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof (MBR),1,fp);
        int index = -1;
        int index_Extendida = -1;
        bool flagExtendida = false;
        string opcion = "";
        char buffer = '\0';
        //Buscamos la particion primaria/extendida
        for(int i = 0; i < 4; i++){
            if((strcmp(masterboot.mbr_partition[i].part_name, auxNombre.c_str())) == 0){
                index = i;
                if(masterboot.mbr_partition[i].part_type == 'E')
                    flagExtendida = true;
                break;
            }else if(masterboot.mbr_partition[i].part_type == 'E'){
                index_Extendida = i;
            }
        }
        if(archivo == "principal"){
            cout << "¿Seguro que desea eliminar la particion? Y/N : " ;
            getline(cin, opcion);
        }else
            opcion = "Y";
        if(opcion.compare("Y") == 0 || opcion.compare("y") == 0){
            if(index != -1){//Si se encontro en las principales
                if(!flagExtendida){//primaria
                    if(typeDelete == "fast"){
                        masterboot.mbr_partition[index].part_status = '1';
                        strcpy(masterboot.mbr_partition[index].part_name,"");
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        if(archivo == "principal") cout << "Particion primaria eliminada con exito" << endl;

                    }else{//full
                        masterboot.mbr_partition[index].part_status = '1';
                        strcpy(masterboot.mbr_partition[index].part_name,"");
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
                        fwrite(&buffer,1,masterboot.mbr_partition[index].part_size,fp);
                        if(archivo == "principal") cout << "Particion primaria eliminada con exito" << endl;
                    }
                }else{//extendida
                    if(typeDelete == "fast"){
                        masterboot.mbr_partition[index].part_status = '1';
                        strcpy(masterboot.mbr_partition[index].part_name,"");
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        if(archivo == "principal")
                        cout << "Particion extendida eliminada con exito" << endl;
                    }else{//full
                        masterboot.mbr_partition[index].part_status = '1';
                        strcpy(masterboot.mbr_partition[index].part_name,"");
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
                        fwrite(&buffer,1,masterboot.mbr_partition[index].part_size,fp);
                        if(archivo == "principal")
                        cout << "Particion extendida eliminada con exito" << endl;
                    }
                }
            }else{//Si es una particion logica
                if(index_Extendida != -1){
                    bool flag = false;//Bandera para saber si existe
                    EBR extendedBoot;
                    fseek(fp,masterboot.mbr_partition[index_Extendida].part_start, SEEK_SET);
                    fread(&extendedBoot,sizeof(EBR),1,fp);
                    if(extendedBoot.part_size!=0){
                        fseek(fp, masterboot.mbr_partition[index_Extendida].part_start,SEEK_SET);
                        while((fread(&extendedBoot,sizeof(EBR),1,fp))!=0 && (ftell(fp) < (masterboot.mbr_partition[index_Extendida].part_start + masterboot.mbr_partition[index_Extendida].part_size))) {
                            if(strcmp(extendedBoot.part_name,nombre.toStdString().c_str()) == 0 && extendedBoot.part_status != '1'){
                                flag = true;
                                break;
                            }else if(extendedBoot.part_next == -1){//Ya es la ultima y no se encontro
                                break;
                            }
                        }
                    }
                    if(flag){
                        if(typeDelete == "fast"){
                            extendedBoot.part_status = '1';
                            strcpy(extendedBoot.part_name, "");
                            fseek(fp, ftell(fp)-sizeof(EBR),SEEK_SET);
                            fwrite(&extendedBoot,sizeof(EBR),1,fp);
                            if(archivo == "principal")
                            cout << "Particion logica eliminada con exito" << endl;
                        }else{//full
                            extendedBoot.part_status = '1';
                            strcpy(extendedBoot.part_name, "");
                            fseek(fp, ftell(fp)-sizeof(EBR),SEEK_SET);
                            fwrite(&extendedBoot,sizeof(EBR),1,fp);
                            fwrite(&buffer,1,extendedBoot.part_size,fp);
                            if(archivo == "principal")
                            cout << "Particion logica eliminada con exito" << endl;
                        }
                    }else{
                        cout << "ERROR no se encuentra la particion a eliminar" << endl;
                    }
                }else{
                    cout << "ERROR no se encuentra la particion a eliminar" << endl;
                }
            }
        }else if(opcion.compare("N") || opcion.compare("n") == 0){
            cout << "Cancelado con exito" << endl;;
        }else{
            cout << "Opcion incorrecta" << endl;
        }

        fclose(fp);
    }else{
        cout << "ERROR el disco donde se va a eliminar no existe" << endl;
    }
}

/* Metodo que se encarga de agregar o quitar espacio a una particion
 * @param QString direccion: ruta del archivo
 * @param QString nombre: nombre de la particion
 * @param units: unidades para agregar o quitar
*/
void Disco::agregarQuitarParticion(QString direccion, QString nombre, int add, char unit, QString archivo){
    string auxPath = direccion.toStdString();
    string auxNombre = nombre.toStdString();
    int size_Bytes = 0;
    QString tipo = "";

    if(add > 0)
        tipo = "add";

    if(tipo != "add")
        add = add*(-1);

    if(unit == 'm')
        size_Bytes = add * 1024 * 1024;
    else if(unit == 'k')
        size_Bytes = add * 1024;
    else
        size_Bytes = add;

    FILE *fp;
    if((fp = fopen(auxPath.c_str(), "rb+"))){
        MBR masterboot;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        int index = -1;
        int index_Extendida = -1;
        bool flagExtendida = false;
        //Buscamos la particion primaria/extendida
        for(int i = 0; i < 4; i++){
            if((strcmp(masterboot.mbr_partition[i].part_name, auxNombre.c_str())) == 0){
                index = i;
                if(masterboot.mbr_partition[i].part_type == 'E')
                    flagExtendida = true;
                break;
            }else if(masterboot.mbr_partition[i].part_type == 'E'){
                index_Extendida = i;
            }
        }
        if(index != -1){//Si se encontro en las principales
            if(!flagExtendida){//Primaria
                if(tipo == "add"){//Agregar
                    //Verificar que exista espacio libre a la derecha
                    if(index!=3){
                        int p1 = masterboot.mbr_partition[index].part_start + masterboot.mbr_partition[index].part_size;
                        int p2 = masterboot.mbr_partition[index+1].part_start;
                        if((p2 - p1) != 0){//Hay fragmentacion
                            int fragmentacion = p2-p1;
                            if(fragmentacion >= size_Bytes){
                                masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                fseek(fp,0,SEEK_SET);
                                fwrite(&masterboot,sizeof(MBR),1,fp);
                                if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                            }else{
                                cout << "ERROR no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                            }
                        }else{//Espacio no usado
                            if(masterboot.mbr_partition[index + 1].part_status == '1'){
                                if(masterboot.mbr_partition[index + 1].part_size >= size_Bytes){
                                    masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                    masterboot.mbr_partition[index + 1].part_size = (masterboot.mbr_partition[index + 1].part_size - size_Bytes);
                                    masterboot.mbr_partition[index + 1].part_start = masterboot.mbr_partition[index + 1].part_start + size_Bytes;
                                    fseek(fp,0,SEEK_SET);
                                    fwrite(&masterboot,sizeof(MBR),1,fp);
                                    if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                                }else{
                                    cout << "ERROR no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                                }
                            }
                        }
                    }else{
                        int p = masterboot.mbr_partition[index].part_start + masterboot.mbr_partition[index].part_size;
                        int total = masterboot.mbr_size + (int)sizeof(MBR);
                        if((total-p) != 0){
                            int fragmentacion = total - p;
                            if(fragmentacion >= size_Bytes){
                                masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                fseek(fp,0,SEEK_SET);
                                fwrite(&masterboot,sizeof(MBR),1,fp);
                                if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                            }else{
                                cout << "ERROR no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                            }
                        }else{
                            cout << "ERROR no es posible agregar espacio a la particion porque no hay espacio disponible a su derecha" << endl;
                        }
                    }
                }else{//Quitar espacio
                    //Que no borre la particion
                    if(size_Bytes >= masterboot.mbr_partition[index].part_size){
                        cout << "ERROR no es posible quitarle esta cantidad de espacio a la particion porque la borraria" << endl;
                    }else{
                        masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size - size_Bytes;
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        if(archivo == "principal") cout << "Se quito espacio a la particion de manera exitosa" << endl;
                    }
                }
            }else{//Extendida
                if(tipo == "add"){//Agregar
                    //Verificar que exista espacio libre a la derecha
                    if(index!=3){
                        int p1 = masterboot.mbr_partition[index].part_start + masterboot.mbr_partition[index].part_size;
                        int p2 = masterboot.mbr_partition[index+1].part_start;
                        if((p2 - p1) != 0){//Hay fragmentacion
                            int fragmentacion = p2-p1;
                            if(fragmentacion >= size_Bytes){
                                masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                fseek(fp,0,SEEK_SET);
                                fwrite(&masterboot,sizeof(MBR),1,fp);
                                if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                            }else{
                                cout << "ERROR no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                            }
                        }else{
                            if(masterboot.mbr_partition[index + 1].part_status == '1'){
                                if(masterboot.mbr_partition[index + 1].part_size >= size_Bytes){
                                    masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                    masterboot.mbr_partition[index + 1].part_size = (masterboot.mbr_partition[index + 1].part_size - size_Bytes);
                                    masterboot.mbr_partition[index + 1].part_start = masterboot.mbr_partition[index + 1].part_start + size_Bytes;
                                    fseek(fp,0,SEEK_SET);
                                    fwrite(&masterboot,sizeof(MBR),1,fp);
                                    if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                                }else{
                                    cout << "ERROR no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                                }
                            }
                        }
                    }else{
                        int p = masterboot.mbr_partition[index].part_start + masterboot.mbr_partition[index].part_size;
                        int total = masterboot.mbr_size + (int)sizeof(MBR);
                        if((total-p) != 0){//Hay fragmentacion
                            int fragmentacion = total - p;
                            if(fragmentacion >= size_Bytes){
                                masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                fseek(fp,0,SEEK_SET);
                                fwrite(&masterboot,sizeof(MBR),1,fp);
                                if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                            }else{
                                cout << "ERROR no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                            }
                        }else{
                            cout << "ERROR no es posible agregar espacio a la particion porque no hay espacio disponible a su derecha" << endl;
                        }
                    }
                }else{//Quitar espacio
                    //Que no borre la particion
                    if(size_Bytes >= masterboot.mbr_partition[index_Extendida].part_size){
                        cout << "ERROR no es posible quitarle esta cantidad de espacio a la particion porque la borraria" << endl;
                    }else{
                        EBR extendedBoot;
                        fseek(fp, masterboot.mbr_partition[index_Extendida].part_start,SEEK_SET);
                        fread(&extendedBoot,sizeof(EBR),1,fp);
                        while((extendedBoot.part_next != -1) && (ftell(fp) < (masterboot.mbr_partition[index_Extendida].part_size + masterboot.mbr_partition[index_Extendida].part_start))){
                            fseek(fp,extendedBoot.part_next,SEEK_SET);
                            fread(&extendedBoot,sizeof(EBR),1,fp);
                        }
                        int ultimaLogica = extendedBoot.part_start+extendedBoot.part_size;
                        int aux = (masterboot.mbr_partition[index_Extendida].part_start + masterboot.mbr_partition[index_Extendida].part_size) - size_Bytes;
                        if(aux > ultimaLogica){//No toca ninguna logica
                            masterboot.mbr_partition[index_Extendida].part_size = masterboot.mbr_partition[index_Extendida].part_size - size_Bytes;
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            if(archivo == "principal") cout << "Se quito espacio a la particion de manera exitosa" << endl;
                        }else{
                            cout << "ERROR si quita ese espacio danaria una logica" << endl;
                        }
                    }
                }
            }
        }else{//Posiblemente logica
            if(index_Extendida != -1){
                int logica = buscarParticion_L(direccion, nombre);
                if(logica != -1){
                    if(tipo == "add"){
                        //Verificar que exista espacio libre a su derecha
                        EBR extendedBoot;
                        fseek(fp,logica,SEEK_SET);
                        fread(&extendedBoot,sizeof(EBR),1,fp);

                    }else{//Quitar
                        //Verificar que no la elimine
                        EBR extendedBoot;
                        fseek(fp,logica,SEEK_SET);
                        fread(&extendedBoot,sizeof(EBR),1,fp);
                        if(size_Bytes >= extendedBoot.part_size){
                            cout << "ERROR si quita ese espacio eliminaria la logica" << endl;
                        }else{
                            extendedBoot.part_size = extendedBoot.part_size - size_Bytes;
                            fseek(fp,logica,SEEK_SET);
                            fwrite(&extendedBoot,sizeof(EBR),1,fp);
                            if(archivo == "principal") cout << "Se quito espacio a la particion de manera exitosa" << endl;
                        }
                    }
                }else{
                    cout << "ERROR no se encuentra la particion" << endl;
                }
            }else{
                cout << "ERROR no se encuentra la particion a redimensionar" << endl;
            }
        }
        fclose(fp);
    }else{
        cout << "ERROR el disco donde se desea agregar/quitar unidades no existe" << endl;
    }
}

/* Funcion que devuelve un entero para comprobar la existencia de una particion primaria o extendida en un disco
 * @param QString direccion: ruta del archivo
 * @param QString nombre: nombre de la particion
 * @return -1 = no se encuentra | # de la particion asociada a ese nombre
*/
int Disco::buscarParticion_P_E(QString direccion, QString nombre){
    string auxPath = direccion.toStdString();
    string auxName = nombre.toStdString();
    FILE *fp;
    if((fp = fopen(auxPath.c_str(),"rb+"))){
        MBR masterboot;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        for(int i = 0; i < 4; i++){
            if(masterboot.mbr_partition[i].part_status != '1'){
                if(strcmp(masterboot.mbr_partition[i].part_name,auxName.c_str()) == 0){
                    return i;
                }
            }
        }

    }
    return -1;
}

/* Funcion que devuelve el byte donde inicia la particion logica si esta existe
 * @param QString direccion: ruta del archivo
 * @param QString nombre: nombre de la particion
 * @return -1 = no se encuentra | # byte donde inicia la particion
*/
int Disco::buscarParticion_L(QString direccion, QString nombre){
    string auxPath = direccion.toStdString();
    string auxName = nombre.toStdString();
    FILE *fp;
    if((fp = fopen(auxPath.c_str(),"rb+"))){
        int extendida = -1;
        MBR masterboot;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        for(int i = 0; i < 4; i++){
            if(masterboot.mbr_partition[i].part_type == 'E'){
                extendida = i;
                break;
            }
        }
        if(extendida != -1){
            EBR extendedBoot;
            fseek(fp, masterboot.mbr_partition[extendida].part_start,SEEK_SET);
            while(fread(&extendedBoot,sizeof(EBR),1,fp)!=0 && (ftell(fp) < masterboot.mbr_partition[extendida].part_start + masterboot.mbr_partition[extendida].part_size)){
                if(strcmp(extendedBoot.part_name, auxName.c_str()) == 0){
                    return (ftell(fp) - sizeof(EBR));
                }
            }
        }
        fclose(fp);
    }
    return -1;
}

