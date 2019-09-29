#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <math.h>
#include <libgen.h>
#include <QFileInfo>

#include "scanner.h"
#include "parser.h"
#include "graficador.h"
#include "mainheader.h"
#include "disco.h"
#include "reporte.h"

extern int yyparse();
extern Nodo *raiz; // Raiz del arbol

using namespace std;

/*
 * Enumeracion que lista todos los comandos y sus parametros reconocidos por
 * el lenguaje que servira para el recorrido del arbol
*/
enum Choice
{
    /*Fase 1*/
    MKDISK = 1,
    RMDISK = 2,
    FDISK = 3,
    MOUNT = 4,
    UNMOUNT = 5,
    REP = 6,
    PARAMETRO = 7,
    EXEC = 8,
    SIZE = 9,
    FIT = 10,
    UNIT = 11,
    PATH = 12,
    TYPE = 13,
    DELETE = 14,
    NAME = 15,
    ADD = 16,
    ID = 17,
    /*Fase 2*/
    MKFS = 18,
    LOGIN = 19,
    LOGOUT = 20,
    MKGRP = 21,
    RMGRP = 22,
    MKUSR = 23,
    RMUSR = 24,
    CHMOD = 25,
    MKFILE = 26,
    CAT = 27,
    REM = 28,
    EDIT = 29,
    REN = 30,
    MKDIR = 31,
    CP = 32,
    MV = 33,
    FIND = 34,
    CHOWN = 35,
    CHGRP = 36,
    PAUSE = 37,
    RECOVERY = 38,
    LOSS = 39,
    FS = 40,
    USER = 41,
    PASSWORD = 42,
    GROUP = 43,
    UGO = 44,
    CONT = 45,
    FILEE = 46,
    P = 47,
    DEST = 48,
    R = 49,
    INODE = 50,
    JOURNALING = 51,
    BLOCK = 52,
    BM_INODE  = 53,
    BM_BLOCK = 54,
    TREE = 55,
    SB = 56,
};

/*  FUNCION PRINCIPAL */
int main()
{
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "|                             Sistema de archivos                              |" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "                                                          Raul Xiloj - 201612113" << endl;
    cout << endl;
    cout << "Por favor escriba algun comando:" << endl;
    while(flag_global){
        char input[500];
        cout << ">> ";
        fgets(input,sizeof (input),stdin);
        leerComando(input);
        memset(input,0,400);
    }
}

/*
 * Metodo para leer una linea tanto ingresada por el usuario como por un archivo
 * @param string comando: linea a leer
*/
void leerComando(char comando[400]){
    if(comando[0] != '#'){
        YY_BUFFER_STATE buffer;
        buffer = yy_scan_string(comando);
        if(yyparse() == 0){
            if(raiz!=nullptr){
                Graficador *g = new Graficador(raiz);
                g->generarImagen();
                reconocerComando(raiz);
            }
        }else
            cout << "Comando no reconocido" << endl;
    }
}

/*
 * Analisis semantico
 * Metodos para recorrer el arbol que genera cada comando y obtener sus valores
*/
void reconocerComando(Nodo *raiz)
{
    switch (raiz->tipo_)
    {
    case MKDISK:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerMKDISK(&n);
    }
        break;
    case RMDISK:
    {
        recorrerRMDISK(raiz);
    }
        break;
    case FDISK:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerFDISK(&n);
    }
        break;
    case MOUNT:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerMOUNT(&n);
    }
        break;
    case UNMOUNT:
    {
        recorrerUNMOUNT(raiz);
    }
        break;
    case REP:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerREP(&n);
    }
        break;
    case EXEC:
    {
        recorrerEXEC(raiz);
    }
        break;
    /*---------------------------------COMANDOS FASE 2------------------------------*/
    case MKFS:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerMKFS(&n);
    }
        break;
    case LOGIN:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerLOGIN(&n);
    }
        break;
    case LOGOUT:
    {
        log_out();
    }
        break;
    case MKGRP:
    {
        recorrerMKGRP(raiz);
    }
        break;
    case RMGRP:
    {
        recorrerRMGRP(raiz);
    }
        break;
    case MKUSR:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerMKUSR(&n);
    }
        break;
    case RMUSR:
    {
        recorrerRMUSR(raiz);
    }
        break;
    case CHMOD:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerCHMOD(&n);
    }
        break;
    case MKFILE:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerMKFILE(&n);
    }
        break;
    case CAT:
    {
        recorrerCAT(raiz);
    }
        break;
    case REM:
    {
        recorrerREM(raiz);
    }
        break;
    case EDIT:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerEDIT(&n);
    }
        break;
    case REN:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerREN(&n);
    }
        break;
    case MKDIR:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerMKDIR(&n);
    }
        break;
    case CP:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerCP(&n);
    }
        break;
    case MV:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerMV(&n);
    }
        break;
    case FIND:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerFIND(&n);
    }
        break;
    case CHOWN:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerCHOWN(&n);
    }
        break;
    case CHGRP:
    {
        Nodo n = raiz->hijos.at(0);
        recorrerCHGRP(&n);
    }
        break;
    case PAUSE:{
        cout << "Presiona enter para continuar ";
        getchar();
    }
        break;
    case RECOVERY:
    {

    }
        break;
    case LOSS:
    {

    }
        break;
    default: printf("ERROR no se reconoce el comando");

    }

}

void recorrerMKDISK(Nodo *raiz)
{
    /*Banderas para verificar cuando venga un parametro y si se repite*/
    bool flagSize = false;
    bool flagFit = false;
    bool flagUnit = false;
    bool flagPath = false;
    bool flag = false;//Si se repite un valor se activa esta bandera
    /*Variables para obtener los valores de cada nodo*/
    int valSize = 0;
    char valFit = 0;
    char valUnit = 0;
    QString valPath = "";

    for(int i = 0; i < raiz->hijos.count(); i++)
    {
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case SIZE:
        {
            if(flagSize){
                cout << "ERROR: Parametro -size ya definido" << endl;
                flag = true;
                break; //ERROR
            }
            flagSize = true;
            valSize = n.valor.toInt();
            if(!(valSize > 0)){
                flag = true;
                cout << "ERROR: Parametro -size menor a cero" << endl;
                break;
            }
        }
            break;
        case FIT:
        {
            if(flagFit){
                cout << "ERROR: Parametro -fit ya definido" << endl;
                flag = true;
                break; //ERROR
            }
            flagFit = true;
            valFit = n.hijos.at(0).valor.toStdString()[0];
            if(valFit == 'b'){
                valFit = 'B';
            }else if(valFit == 'f'){
                valFit = 'F';
            }else if(valFit == 'w'){
                valFit = 'W';
            }
        }
            break;
        case UNIT:
        {
            if(flagUnit){
                cout << "ERROR: Parametro -unit ya definido" << endl;
                flag = true;
                break;// ERROR;
            }
            flagUnit = true;
            string temp = n.valor.toStdString();
            valUnit = temp[0];
            if(valUnit == 'k'|| valUnit == 'K'){
                valUnit = 'k';
            }else if(valUnit == 'm' || valUnit == 'M'){
                valUnit = 'm';
            }else{
                cout << "ERROR: Valor del parametro -unit no reconocido" << endl;
                flag = true;
                break;
            }
        }
            break;
        case PATH:
        {
            if(flagPath){
                cout << "ERROR: Parametro -path ya definido" << endl;
                flag = true;
                break;
            }
            flagPath = true;
            valPath = n.valor;//Quitarle comillas si tiene
            valPath = valPath.replace("\"","");
        }
            break;
        }

    }

    if(!flag){//Flag para ver si hay parametros repetidos
        if(flagPath){//Parametro path obligatorio
            if(flagSize){//Parametro size obligatorio
                MBR masterboot;
                int total_size = 1024;
                //Archivo principal
                crearDisco(valPath);
                //Archivo raid
                QString auxRaid = getDirectorio(valPath);
                QString nameRaid = getFileName(valPath);
                QString valRaid = auxRaid+nameRaid+"_raid.disk";
                crearDisco(valRaid);

                masterboot.mbr_date_created = time(nullptr);
                masterboot.mbr_disk_signature = static_cast<int>(time(nullptr));

                if(flagUnit){//Si hay parametro unit
                    if(valUnit == 'm'){
                        masterboot.mbr_size = valSize*1048576;
                        total_size = valSize * 1024;
                    }else{
                        masterboot.mbr_size = valSize * 1024;
                        total_size = valSize;
                    }
                }else{
                    masterboot.mbr_size = valSize*1048576;
                    total_size = valSize * 1024;
                }

                if(flagFit)//Si hay parametro fit
                    masterboot.mbr_disk_fit = valFit;
                else
                    masterboot.mbr_disk_fit = 'F';

                //Se inicializan las particiones en el MBR
                for(int p = 0; p < 4; p++){
                    masterboot.mbr_partition[p].part_status = '0';
                    masterboot.mbr_partition[p].part_type = '0';
                    masterboot.mbr_partition[p].part_fit = '0';
                    masterboot.mbr_partition[p].part_size = 0;
                    masterboot.mbr_partition[p].part_start = -1;
                    strcpy(masterboot.mbr_partition[p].part_name,"");
                }

                /*Archivo principal*/
                //Comando para genera un archivo de cierto tamano
                string comando = "dd if=/dev/zero of=\""+valPath.toStdString()+"\" bs=1024 count="+to_string(total_size);
                system(comando.c_str());
                FILE *fp = fopen(valPath.toStdString().c_str(),"rb+");
                fseek(fp,0,SEEK_SET);
                fwrite(&masterboot,sizeof(MBR),1,fp);
                fclose(fp);

                /*Archivo raid*/
                string comando2 = "dd if=/dev/zero of=\""+valRaid.toStdString()+"\" bs=1024 count="+to_string(total_size);
                system(comando2.c_str());
                FILE *fp2 = fopen(valRaid.toStdString().c_str(),"rb+");
                fseek(fp2,0,SEEK_SET);
                fwrite(&masterboot,sizeof(MBR),1,fp2);
                fclose(fp2);

                cout << "Disco creado con exito" << endl;
            }else{
                cout << "ERROR Parametro -size no definido " << endl;
            }
        }else{
            cout << "<< ERROR Parametro -path  no definido" << endl;
        }
    }

}

void recorrerRMDISK(Nodo *raiz)
{
    QString valPath = raiz->hijos.at(0).valor;
    valPath = valPath.replace("\"","");
    FILE *fp;
    if((fp=fopen(valPath.toStdString().c_str(),"r"))){
        string opcion = "";
        cout << ">> ¿Seguro que desea eliminar el disco? Y/N : ";
        getline(cin,opcion);
        if(opcion.compare("Y") == 0 || opcion.compare("y") == 0){
            string comando = "rm \""+valPath.toStdString()+"\"";
            system(comando.c_str());
            cout <<"Disco eliminado con exito" << endl;
        }else if(opcion.compare("N") || opcion.compare("n") == 0){
            cout << "Cancelado con exito" << endl;;
        }else{
            cout << "Opcion incorrecta" << endl;
        }
        fclose(fp);
    }else{
        cout << "No existe el disco a eliminar" << endl;
    }
}

void recorrerFDISK(Nodo *raiz)
{
    /*Banderas para verificar cuando venga un parametro y si se repite*/
    bool flagSize = false;
    bool flagUnit = false;
    bool flagPath = false;
    bool flagType = false;
    bool flagFit = false;
    bool flagDelete = false;
    bool flagName = false;
    bool flagAdd = false;
    bool flag = false;
    /*Variables para obtener los valores de cada nodo*/
    int valSize = 0;
    int valAdd = 0;
    char valUnit = 0;
    char valType = 0;
    char valFit = 0;
    QString valPath = "";
    QString valName = "";
    QString valDelete = "";

    for(int i = 0; i < raiz->hijos.count(); i++)
    {
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_)
        {
        case SIZE:
        {
            if(flagSize){
                cout << "<< ERROR: Parametro -size ya definido" << endl;
                flag = true;
                break;
            }
            flagSize = true;
            valSize = n.valor.toInt();
            if(!(valSize > 0)){
                cout << "<< ERROR: parametro -size menor a cero" << endl;
                flag = true;
                break;
            }
        }
            break;
        case UNIT:
        {
            if(flagUnit){
                cout << "<< ERROR: Parametro -unit ya definido" << endl;
                flag = true;
                break;
            }
            flagUnit = true;
            string temp = n.valor.toStdString();
            valUnit = temp[0];
            if(valUnit == 'B' || valUnit == 'b'){
                valUnit = 'b';
            }else if(valUnit == 'K' || valUnit == 'k'){
                valUnit = 'k';
            }else if(valUnit == 'M' || valUnit == 'm'){
                valUnit = 'm';
            }else{
                cout << "<< ERROR: Valor del parametro unit no reconocido" << endl;
                flag = true;
                break;
            }

        }
            break;
        case PATH:
        {
            if(flagPath){
                cout << "<< ERROR: Parametro -path ya definido" << endl;
                flag = true;
                break;
            }
            flagPath = true;
            valPath = n.valor;
            valPath = valPath.replace("\"","");
        }
            break;
        case TYPE:
        {
            if(flagType){
                cout << "<< ERROR: Parametro -type ya definido" << endl;
                flag = true;
                break;
            }
            flagType = true;
            string temp = n.valor.toStdString();
            valType = temp[0];
            if(valType == 'P' || valType == 'p'){
                valType = 'P';
            }else if(valType == 'E' || valType == 'e'){
                valType = 'E';
            }else if(valType == 'L' || valType == 'l'){
                valType = 'L';
            }else{
                cout << "<< ERROR: Valor del parametro -type no reconocido" << endl;
                flag = true;
                break;
            }
        }
            break;
        case FIT:
        {
            if(flagFit)
            {
                cout << "<< ERROR: Parametro -fit ya definido" << endl;
                flag = true;
                //ERROR
            }
            flagFit = true;
            valFit = n.hijos.at(0).valor.toStdString()[0];
            if(valFit == 'b'){
                valFit = 'B';
            }else if(valFit == 'f'){
                valFit = 'F';
            }else if(valFit == 'w'){
                valFit = 'W';
            }
        }
            break;
        case DELETE:
        {
            if(flagDelete){
                cout << "<< ERROR: Parametro -delete ya definido" << endl;
                flag = true;
                break;
            }
            flagDelete = true;
            valDelete = n.valor;
        }
            break;
        case NAME:
        {
            if(flagName){
                cout << "<< ERROR: Parametro -name ya definido" << endl;
                flag = true;
                break;
            }
            flagName = true;
            valName = n.valor;
            valName = valName.replace("\"", "");
        }
            break;
        case ADD:
        {
            if(flagAdd){
                cout << "<< ERROR: Parametro -add ya definido" << endl;
                flag = true;
                break;
            }
            flagAdd = true;
            valAdd = n.valor.toInt();
        }
            break;
        }
    }

    //Archivo RAID
    QString auxRaid = getDirectorio(valPath);
    QString raidName = getFileName(valPath);
    QString valRaid = auxRaid + raidName + "_raid.disk";

    if(!flag){//Flag para ver si hay parametros repetidos
        if(flagPath){//Parametro obligatorio
            if(flagName){//Parametro obligatorio
                if(flagSize){//Parametro obligatorio al crear una particion
                    if(flagDelete || flagAdd){
                        cout << "<< ERROR: Parametro -delete|-add demas" << endl;
                    }else{
                        if(flagType){//Si especifica tipo de particion
                            if(valType == 'P'){
                                //Archivo principal
                                disco.crearParticionPrimaria(valPath, valName, valSize, valFit, valUnit,"principal");
                                //Archivo raid
                                disco.crearParticionPrimaria(valRaid, valName, valSize, valFit, valUnit,"raid");
                            }else if(valType == 'E'){
                                //Archivo principal
                                disco.crearParticionExtendida(valPath, valName, valSize, valFit, valUnit,"principal");
                                //Archivo raid
                                disco.crearParticionExtendida(valRaid, valName, valSize, valFit, valUnit,"raid");
                            }else if(valType == 'L'){
                                //Archivo principal
                                disco.crearParticionLogica(valPath, valName, valSize, valFit, valUnit,"principal");
                                //Archivo raid
                                disco.crearParticionLogica(valRaid, valName, valSize, valFit, valUnit,"raid");
                            }
                        }else{//Si no especifica se considera particion primaria
                            //Archivo principal
                            disco.crearParticionPrimaria(valPath, valName, valSize, valFit, valUnit,"principal");
                            //Archivo raid
                            disco.crearParticionPrimaria(valRaid, valName, valSize, valFit, valUnit,"raid");
                        }
                    }
                }else if(flagAdd){
                    if(flagSize || flagDelete){
                        cout << "<< ERROR: Parametros -size|-delete demas" << endl;
                    }else{
                        //Verificar que la particion no este montada
                        bool mount = lista->buscarNodo(valPath,valName);
                        if(flagUnit){
                            if(!mount){
                                //Archivo principal
                                disco.agregarQuitarParticion(valPath, valName, valAdd, valUnit,"principal");
                                //Archivo raid
                                disco.agregarQuitarParticion(valRaid, valName, valAdd, valUnit,"raid");
                            }else
                                cout << "ERROR desmote primero la particion para poder eliminarlo" << endl;
                        }else{
                            cout << "<< ERROR parametro -unit no definido "<< endl;
                        }
                    }
                }else if(flagDelete){
                    if(flagSize || flagAdd || flagFit || flagType){
                        cout << "<< ERROR: Parametros demas" << endl;
                    }else{
                        bool mount = lista->buscarNodo(valPath,valName);
                        if(!mount){
                            //Archivo principal
                            disco.eliminarParticion(valPath, valName, valDelete,"principal");
                            //Archivo raid
                            disco.eliminarParticion(valRaid, valName, valDelete,"raid");
                        }else
                            cout << "ERROR desmote primero la particion para poder eliminarlo" << endl;
                    }
                }
            }else {
                cout << "<< ERROR parametro -name no definido" << endl;
            }
        }else{
            cout << "<< ERROR parametro -path no definido" << endl;
        }
    }
}

void recorrerMOUNT(Nodo *raiz){
    bool flagPath = false;
    bool flagName = false;
    bool flag = false;
    QString valPath = "";
    QString valName = "";
    for(int i = 0; i < raiz->hijos.count(); i++)
    {
        Nodo n = raiz->hijos.at(i);
        switch(n.tipo_)
        {
        case PATH:
        {
            if(flagPath){
                flag = true;
                cout << "ERROR: Parametro -path ya definido" << endl;
                break;
            }
            flagPath = true;
            valPath = n.valor;
            valPath = valPath.replace("\"","");
        }
            break;
        case NAME:
        {
            if(flagName){
                flag = true;
                cout << "ERROR: Parametro -name ya definido" << endl;
                break;
            }
            flagName = true;
            valName = n.valor;
            valName = valName.replace("\"","");
        }
            break;
        }
    }

    if(!flag){
        if(flagPath){//Parametro obligatorio
            if(flagName){//Parametro obligtaorio
                int indexP = disco.buscarParticion_P_E(valPath,valName);
                if(indexP != -1){
                    FILE *fp;
                    if((fp = fopen(valPath.toStdString().c_str(),"rb+"))){
                        MBR masterboot;
                        fseek(fp, 0, SEEK_SET);
                        fread(&masterboot, sizeof(MBR),1,fp);
                        masterboot.mbr_partition[indexP].part_status = '2';
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        fclose(fp);
                        int letra = lista->buscarLetra(valPath,valName);
                        if(letra == -1){
                            cout << "ERROR la particion ya esta montada" << endl;
                        }else{
                            int num = lista->buscarNumero(valPath, valName);
                            char auxLetra = static_cast<char>(letra);
                            string id = "vd";
                            id += auxLetra + to_string(num);
                            NodoMount *n = new NodoMount(valPath,valName,auxLetra,num);
                            lista->insertarNodo(n);
                            cout << "Particion montada con exito" << endl;
                            lista->mostrarLista();
                        }
                    }else{
                        cout << "ERROR no se encuentra el disco" << endl;
                    }
                }else{//Posiblemente logica
                    int indexP = disco.buscarParticion_L(valPath,valName);
                    if(indexP != -1){
                        FILE *fp;
                        if((fp = fopen(valPath.toStdString().c_str(), "rb+"))){
                            EBR extendedBoot;
                            fseek(fp, indexP, SEEK_SET);
                            fread(&extendedBoot, sizeof(EBR),1,fp);
                            extendedBoot.part_status = '2';
                            fseek(fp,indexP,SEEK_SET);
                            fwrite(&extendedBoot,sizeof(EBR),1, fp);
                            fclose(fp);

                            int letra = lista->buscarLetra(valPath,valName);
                            if(letra == -1){
                                cout << "ERROR la particion ya esta montada" << endl;
                            }else{
                                int num = lista->buscarNumero(valPath,valName);
                                char auxLetra = static_cast<char>(letra);
                                string id = "vd";
                                id += auxLetra + to_string(num);
                                NodoMount *n = new NodoMount(valPath, valName, auxLetra, num);
                                lista->insertarNodo(n);
                                cout << "Particion montada con exito" << endl;
                                lista->mostrarLista();
                            }
                        }else{
                            cout << "ERROR no se encuentra el disco" << endl;
                        }
                    }else{
                        cout << "ERROR no se encuentra la particion a montar" << endl;
                    }
                }
            }else{
                cout << "ERROR parametro -name no definido" << endl;
            }
        }else{
            cout << "ERROR parametro -path no definido" << endl;
        }
    }

}

void recorrerUNMOUNT(Nodo *raiz){
    QString valID = raiz->hijos.at(0).valor;
    int eliminado = lista->eliminarNodo(valID);
    if(eliminado == 1)
        cout << "Unidad desmontada con exito" << endl;
    else
        cout << "ERROR no se encuentra esa unidad montada" << endl;
}

void recorrerREP(Nodo *raiz)
{
    bool flagName = false;
    bool flagPath = false;
    bool flagID = false;
    bool flag = false;
    QString valName = "";
    QString valPath = "";
    QString valID = "";

    for(int i = 0; i < raiz->hijos.count(); i++)
    {
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_)
        {
        case NAME:
        {
            if(flagName){
                cout << "ERROR parametro -name ya definido" << endl;
                flag = true;
                break;
            }
            flagName = true;
            valName = n.valor;
        }
            break;
        case PATH:
        {
            if(flagPath){
                cout << "ERROR parametro -path ya definido" << endl;
                flag = true;
                break;
            }
            flagPath = true;
            valPath = n.valor;
            valPath = valPath.replace("\"","");
        }
            break;
        case ID:
        {
            if(flagID){
                cout << "ERROR parametro -id ya definido" << endl;
                flag = true;
                break;
            }
            flagID = true;
            valID = n.valor;
        }
            break;
        }

    }

    if(!flag){
        if(flagPath){
            if(flagName){
                if(flagID){
                    NodoMount *aux = lista->getNodo(valID);
                    QString ext = getExtension(valPath);
                    if(aux !=  nullptr){
                        QString directorio = getDirectorio(valPath);
                        string comando = "sudo mkdir -p \'"+directorio.toStdString()+"\'";
                        system(comando.c_str());
                        string comando2 = "sudo chmod -R 777 \'"+directorio.toStdString()+"\'";
                        system(comando2.c_str());
                        Reporte r;
                        if(valName == "mbr")
                            r.graficarMBR(aux->direccion,valPath,ext);
                        else if(valName == "disk")
                            r.graficarDisco(aux->direccion,valPath,ext);
                        else if(valName == "inode"){
                            int index = disco.buscarParticion_P_E(aux->direccion,aux->nombre);
                            if(index != -1){//Primaria|Extendida
                                MBR masterboot;
                                SuperBloque super;
                                FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                fread(&masterboot,sizeof(MBR),1,fp);
                                fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
                                fread(&super,sizeof(SuperBloque),1,fp);
                                fclose(fp);
                                r.graficarInodos(aux->direccion,valPath,ext,super.s_bm_inode_start,super.s_inode_start,super.s_bm_block_start);
                            }else{//Logica
                                int index = disco.buscarParticion_L(aux->direccion,aux->nombre);
                                if(index != -1){
                                    EBR extendedBoot;
                                    SuperBloque super;
                                    FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                    fseek(fp,index,SEEK_SET);
                                    fread(&extendedBoot,sizeof(EBR),1,fp);
                                    fread(&super,sizeof(SuperBloque),1,fp);
                                    fclose(fp);
                                    r.graficarInodos(aux->direccion,valPath,ext,super.s_bm_inode_start,super.s_inode_start,super.s_bm_block_start);
                                }
                            }
                        }else if(valName == "journaling"){

                        }else if(valName == "block"){
                            int index = disco.buscarParticion_P_E(aux->direccion,aux->nombre);
                            if(index != -1){//Primaria|Extendida
                                MBR masterboot;
                                SuperBloque super;
                                FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                fread(&masterboot,sizeof(MBR),1,fp);
                                fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
                                fread(&super,sizeof(SuperBloque),1,fp);
                                fclose(fp);
                                r.graficarBloques(aux->direccion,valPath,ext,super.s_bm_block_start,super.s_block_start,super.s_inode_start);
                            }else{//Logica
                                int index = disco.buscarParticion_L(aux->direccion,aux->nombre);
                                if(index != -1){
                                    EBR extendedBoot;
                                    SuperBloque super;
                                    FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                    fseek(fp,index,SEEK_SET);
                                    fread(&extendedBoot,sizeof(EBR),1,fp);
                                    fread(&super,sizeof(SuperBloque),1,fp);
                                    fclose(fp);
                                    r.graficarBloques(aux->direccion,valPath,ext,super.s_bm_block_start,super.s_block_start,super.s_inode_start);
                                }
                            }
                        }else if(valName == "bm_inode"){
                            int index = disco.buscarParticion_P_E(aux->direccion,aux->nombre);
                            if(index != -1){//Primaria|Extendida
                                MBR masterboot;
                                SuperBloque super;
                                FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                fread(&masterboot,sizeof(MBR),1,fp);
                                fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
                                fread(&super,sizeof(SuperBloque),1,fp);
                                fclose(fp);
                                r.reporteBM(aux->direccion,valPath,super.s_bm_inode_start,super.s_inodes_count);
                            }else{//Logica
                                int index = disco.buscarParticion_L(aux->direccion,aux->nombre);
                                if(index != -1){
                                    EBR extendedBoot;
                                    SuperBloque super;
                                    FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                    fseek(fp,index,SEEK_SET);
                                    fread(&extendedBoot,sizeof(EBR),1,fp);
                                    fread(&super,sizeof(SuperBloque),1,fp);
                                    fclose(fp);
                                     r.reporteBM(aux->direccion,valPath,super.s_bm_inode_start,super.s_inodes_count);
                                }
                            }
                        }else if(valName == "bm_block"){
                            int index = disco.buscarParticion_P_E(aux->direccion,aux->nombre);
                            if(index != -1){//Primaria|Extendida
                                MBR masterboot;
                                SuperBloque super;
                                FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                fread(&masterboot,sizeof(MBR),1,fp);
                                fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
                                fread(&super,sizeof(SuperBloque),1,fp);
                                fclose(fp);
                                r.reporteBM(aux->direccion,valPath,super.s_bm_block_start,super.s_blocks_count);
                            }else{//Logica
                                int index = disco.buscarParticion_L(aux->direccion,aux->nombre);
                                if(index != -1){
                                    EBR extendedBoot;
                                    SuperBloque super;
                                    FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                    fseek(fp,index,SEEK_SET);
                                    fread(&extendedBoot,sizeof(EBR),1,fp);
                                    fread(&super,sizeof(SuperBloque),1,fp);
                                    fclose(fp);
                                    r.reporteBM(aux->direccion,valPath,super.s_bm_block_start,super.s_blocks_count);
                                }
                            }
                        }else if(valName == "tree"){
                            int index = disco.buscarParticion_P_E(aux->direccion,aux->nombre);
                            QString destino = getDirectorio(valPath) + getFileName(valPath) + ".pdf";
                            if(index != -1){
                                MBR masterboot;
                                FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                fread(&masterboot,sizeof(MBR),1,fp);
                                fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
                                fclose(fp);
                                r.graficarTree(aux->direccion,valPath,ext,masterboot.mbr_partition[index].part_start);
                            }else{
                                int index = disco.buscarParticion_L(aux->direccion,aux->nombre);
                                if(index != -1){
                                    EBR extendedBoot;
                                    FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                    fseek(fp,index,SEEK_SET);
                                    fread(&extendedBoot,sizeof(EBR),1,fp);
                                    int start = static_cast<int>(ftell(fp));
                                    fclose(fp);
                                    r.graficarTree(aux->direccion,valPath,ext,start);
                                }
                            }
                        }else if(valName == "sb"){
                            int index = disco.buscarParticion_P_E(aux->direccion,aux->nombre);
                            if(index != -1){//Primaria|Extendida
                                MBR masterboot;
                                FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                fread(&masterboot,sizeof(MBR),1,fp);
                                fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
                                fclose(fp);
                                r.graficarSuper(aux->direccion,valPath,ext,masterboot.mbr_partition[index].part_start);
                            }else{
                                int index = disco.buscarParticion_L(aux->direccion,aux->nombre);
                                if(index != -1){
                                    EBR extendedBoot;
                                    FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                                    fseek(fp,index,SEEK_SET);
                                    fread(&extendedBoot,sizeof(EBR),1,fp);
                                    int start = static_cast<int>(ftell(fp));
                                    fclose(fp);
                                    r.graficarSuper(aux->direccion,valPath,ext,start);
                                }
                            }
                        }else if(valName == "file"){

                        }else if(valName == "ls"){

                        }
                    }else
                        cout << "ERROR no se encuentra la particion" << endl;
                }else
                    cout << "ERROR parametro -id no definido" << endl;
            }else
                cout << "ERROR parametro -name no definido" << endl;
        }else
            cout << "ERROR parametro -path no definido" << endl;
    }


}

void recorrerEXEC(Nodo *raiz)
{
    QString valPath = raiz->hijos.at(0).valor;
    string auxPath = valPath.toStdString();
    FILE *fp;
    if((fp = fopen(auxPath.c_str(),"r"))){
        char line[400]="";
        memset(line,0,sizeof(line));
        while(fgets(line,sizeof line,fp)){
            if(line[0]!='\n'){
                cout << ">> "<< line;
                leerComando(line);
            }
            memset(line,0,sizeof(line));
        }
        fclose(fp);
    }else
        cout << "ERROR: script no encontrado" << endl;
}

/*
 * Metodo que creara el directorio de carpetas hacia el archivo
 * y dara permisos en las carpetas y creara el archivo que simula ser un disco.
 * @param QString direccion: ruta en donde se creara el archivo
*/
void crearDisco(QString direccion){
    QString aux = getDirectorio(direccion);
    string comando = "sudo mkdir -p \'"+aux.toStdString()+"\'";
    system(comando.c_str());
    string comando2 = "sudo chmod -R 777 \'"+aux.toStdString()+"\'";
    system(comando2.c_str());
    string arch = direccion.toStdString();
    FILE *fp = fopen(arch.c_str(),"wb");
    if((fp = fopen(arch.c_str(),"wb")))
        fclose(fp);
    else
        cout << "Error al crear el archivo" << endl;
}

/*
 * Funcion que devuleve el directorio en donde se creara el archivo
 * @param QString direccion: ruta donde se creara el archivo
*/
QString getDirectorio(QString direccion){
    string aux = direccion.toStdString();
    string delimiter = "/";
    size_t pos = 0;
    string res = "";
    while((pos = aux.find(delimiter))!=string::npos){
        res += aux.substr(0,pos)+"/";
        aux.erase(0,pos + delimiter.length());
    }
    return QString::fromStdString(res);
}

/*
 * Funcion que retorna la extension de un archivo
 * @param QString direccion: ruta del archivo
 * @return .pdf, jpg, png
*/
QString getExtension(QString direccion){
    string aux = direccion.toStdString();
    string delimiter = ".";
    size_t pos = 0;
    while((pos = aux.find(delimiter))!=string::npos){
        aux.erase(0,pos+delimiter.length());
    }
    return QString::fromStdString(aux);
}

/*
 * Funcion que retorna el nombre de un archivo
 * @param QString direccion: ruta del archivo
 * @return nombre del archivo
*/
QString getFileName(QString direccion){
    string aux = direccion.toStdString();
    string delimiter = "/";
    size_t pos = 0;
    string res = "";
    while((pos = aux.find(delimiter))!=string::npos){
        aux.erase(0,pos + delimiter.length());
    }
    delimiter = ".";
    pos = aux.find(delimiter);
    res = aux.substr(0,pos);
    return QString::fromStdString(res);
}

/*
 * --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                                               FASE 2
 * --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Analisis semantico
 * Metodos para recorrer el arbol que genera cada comando y obtener sus valores
*/
void recorrerMKFS(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro y si se repite*/
    bool flagID = false;
    bool flagType = false;
    bool flagFS = false;
    bool flag = false;//Si se repite un valor se activa esta bandera
    /*Variables para obtener los valores de cada nodo*/
    QString id = "";
    QString type = "";
    int fs = 2;

    for(int i = 0; i < raiz->hijos.count(); i++)
    {
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case ID:
        {
            if(flagID){
                cout << "ERROR parametro -id ya definido" << endl;
                flag = true;
                break;
            }
            flagID = true;
            id = n.valor;
        }
            break;
        case TYPE:
        {
            if(flagType){
                cout << "ERROR parametro -type ya definido" << endl;
                flag = true;
                break;
            }
            flagType = true;
            type = n.valor;
        }
            break;
        case FS:
        {
            if(flagFS){
                cout << "ERROR parametro -fs ya definido " << endl;
                flag = true;
                break;
            }
            flagFS = true;
            if(n.valor == "3fs")
                fs = 3;
            else
                fs = 2;
        }
            break;
        }
    }

    if(!flag){
        if(flagID){//Parametro obligatorio
            NodoMount *aux = lista->getNodo(id);
            if(aux!=nullptr){
                int index = disco.buscarParticion_P_E(aux->direccion,aux->nombre);
                if(index != -1){
                    MBR masterboot;
                    FILE *fp = fopen(aux->direccion.toStdString().c_str(),"rb+");
                    fread(&masterboot,sizeof(MBR),1,fp);
                    int inicio = masterboot.mbr_partition[index].part_start;
                    int tamano = masterboot.mbr_partition[index].part_size;
                    if(fs == 3)
                        formatearEXT3(inicio,tamano,aux->direccion);
                    else
                        formatearEXT2(inicio,tamano,aux->direccion);
                    fclose(fp);
                }else{
                    index = disco.buscarParticion_L(aux->direccion,aux->nombre);
                }
            }else
                cout << "ERROR no se encuentra ninguna particion montada con ese id" << endl;
        }else
            cout << "ERROR parametro -id no definidp" << endl;
    }
}

void recorrerLOGIN(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro y si se repite*/
    bool flagUser = false;
    bool flagPassword = false;
    bool flagID = false;
    bool flag = false;
    /*Variables para obtener los valores de cada nodo*/
    QString user = "";
    QString password = "";
    QString id = "";

    for(int i = 0; i < raiz->hijos.count(); i++) {
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case USER:
        {
            if(flagUser){
                cout << "ERROR parametro -usr ya definido" << endl;
                flag = true;
                break;
            }
            flagUser = true;
            user = n.valor;
            user = user.replace("\"","");
        }
            break;
        case PASSWORD:
        {
            if(flagPassword){
                cout << "ERROR parametro -pwd ya definido" << endl;
                flag = true;
                break;
            }
            flagPassword = true;
            password = n.valor;
            user = user.replace("\"","");
        }
            break;
        case ID:
        {
            if(flagID){
                cout << "ERROR parametro -id ya definido" << endl;
                flag = true;
                break;
            }
            flagID = true;
            id = n.valor;
        }
            break;
        }
    }

    if(!flag){
        if(flagUser){
            if(flagPassword){
                if(flagID){
                    if(!flag_login){
                        NodoMount *aux = lista->getNodo(id);
                        if(aux != nullptr){
                            int res = log_in(aux->direccion,aux->nombre,user,password);
                            if(res == 1){
                                flag_login = true;
                                cout << "Sesion iniciada con exito" << endl;
                            }else if(res == 2)
                                cout << "ERROR Contrasena incorrecta" << endl;
                            else if(res == 0)
                                cout << "ERROR Usuario no encontrado" << endl;
                        }else
                            cout << "ERROR no se encuentra ninguna particion montada con ese id " << endl;
                    }else
                        cout << "ERROR sesion activa, cierre sesion para poder volver a iniciar sesion" << endl;
                }else
                    cout << "ERROR parametro -id no definido" << endl;
            }else
                cout << "ERROR parametro -pwd no definido" << endl;
        }else
            cout << "ERROR parametro -usr no definido" << endl;
    }
}

void recorrerMKGRP(Nodo *raiz){
    QString grpName = raiz->hijos.at(0).valor;
    grpName = grpName.replace("\"","");
    if(flag_login){
        if(currentSession.id_user == 1 && currentSession.id_grp == 1){//Usuario root
            if(grpName.length() <= 10){
                int grupo = buscarGrupo(grpName);
                if(grupo == -1){
                    int idGrp = getID_grp();
                    QString nuevoGrupo = QString::number(idGrp)+",G,"+grpName+"\n";
                    agregarUsersTXT(nuevoGrupo);
                    cout << "Grupo creado con exito "<< endl;
                }else
                    cout << "ERROR ya existe un grupo con ese nombre" << endl;
            }else
                cout << "ERROR el nombre del grupo no puede exceder los 10 caracters" << endl;
        }else
            cout << "ERROR solo el usuario root puede ejecutar este comando" << endl;
    }else
        cout << "ERROR necesita iniciar sesion para poder ejecutar este comando" << endl;
}

void recorrerRMGRP(Nodo *raiz){
    QString grpName = raiz->hijos.at(0).valor;
    grpName = grpName.replace("\"","");
    if(flag_login){
        if(currentSession.id_user == 1 && currentSession.id_grp == 1){//Usuario root
            int grupo = buscarGrupo(grpName);
            if(grupo != -1){
                eliminarGrupo(grpName);
            }else
                cout << "ERROR el grupo no existe" << endl;
        }else
           cout << "ERROR solo el usuario root puede ejecutar este comando" << endl;
    }else
        cout << "ERROR necesita iniciar sesion para poder ejecutar este comando" << endl;
}

void recorrerMKUSR(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro y si se repite*/
    bool flagUser = false;
    bool flagPassword = false;
    bool flagGroup = false;
    bool flag = false;//Si se repite un valor se activa esta bandera
    /*Variables para obtener los valores de cada nodo*/
    QString user = "";
    QString pass = "";
    QString group = "";

    for(int i = 0; i < raiz->hijos.count(); i++){
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case USER:
        {
            if(flagUser){
                cout << "ERROR parametro -usr ya definido" << endl;
                flag = true;
                break;
            }
            flagUser = true;
            user = n.valor;
            user = user.replace("\"","");
        }
            break;
        case PASSWORD:
        {
            if(flagPassword){
                cout << "ERROR parametro -pwd ya definido" << endl;
                flag = true;
                break;
            }
            flagPassword = true;
            pass = n.valor;
            pass = pass.replace("\"","");
        }
            break;
        case GROUP:
        {
            if(flagGroup){
                cout << "ERROR parametro -grp ya definido" << endl;
                flag = true;
                break;
            }
            flagGroup = true;
            group = n.valor;
            group = group.replace("\"","");
        }
            break;
        }
    }

    if(!flag){
        if(flagUser){
            if(flagPassword){
                if(flagGroup){
                    if(user.length() <= 10){
                        if(pass.length() <= 10){
                            if(group.length() <= 10){
                                if(flag_login){
                                    if(currentSession.id_user == 1 && currentSession.id_grp == 1){//Usuario root
                                        if(buscarGrupo(group) != -1){
                                            if(!buscarUsuario(user)){
                                                int id = getID_usr();
                                                QString datos = QString::number(id) + ",U,"+group+","+user+","+pass+"\n";
                                                agregarUsersTXT(datos);
                                                cout << "Usuario creado con exito " << endl;
                                            }else
                                                cout << "ERROR el usuario ya existe" <<endl;
                                        }else
                                            cout << "ERROR no se encuentra el grupo al que pertenecera el usuario " << endl;
                                    }else
                                        cout << "ERROR solo el usuario root puede ejecutar este comando" << endl;
                                }else
                                    cout << "ERROR necesita iniciar sesion para poder ejecutar este comando" << endl;
                            }else
                                cout << "ERROR grupo del usuario excede de los 10 caracteres permitidos" << endl;
                        }else
                            cout << "ERROR contrasena de usuario excede de los 10 caracteres permitidos" << endl;
                    }else
                        cout << "ERROR nombre de usuario excede de los 10 caracteres permitidos" << endl;
                }else
                    cout << "ERROR parametro -grp no definido" << endl;
            }else
                cout << "ERROR parametro -pwd no definido"<< endl;
        }else
            cout << "ERROR parametro -usr no definido " << endl;
    }

}

void recorrerRMUSR(Nodo *raiz){
    QString userName = raiz->hijos.at(0).valor;
    userName = userName.replace("\"","");
    if(flag_login){
        if(currentSession.id_user == 1 && currentSession.id_grp == 1){//Usuario root
            if(buscarUsuario(userName)){
                eliminarUsuario(userName);
            }else
                cout << "ERROR el usuario no existe" << endl;
        }else
           cout << "ERROR solo el usuario root puede ejecutar este comando" << endl;
    }else
        cout << "ERROR necesita iniciar sesion para poder ejecutar este comando" << endl;
}

void recorrerCHMOD(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro y si se repite*/
    bool flagPath = false;
    bool flagUgo = false;
    bool flagR = false;
    bool flag = false; //Si se repite un valor se activa esta bandera

    for(int i = 0; i < raiz->hijos.count(); i++){
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case PATH:
        {
            if(flagPath){
                cout << "ERROR parametro -path ya definido" << endl;
                flag = true;
                break;
            }
            flagPath = true;
        }
            break;
        case UGO:
        {
            if(flagUgo){
                cout << "ERRROR parametro -ugo ya definido" << endl;
                flag = true;
                break;
            }
            flagUgo = true;
        }
            break;
        case R:
        {
            if(flagR){
                cout << "ERROR parametro -r ya definido" << endl;
                flag = true;
                break;
            }
            flagR = true;
        }
            break;
        }
    }

    if(!flag){
        if(flagPath){
            if(flagUgo){

            }else
                cout << "ERROR parametro -ugo no definido" << endl;
        }else
            cout << "ERROR parametro -path no definido" << endl;
    }
}

void recorrerMKFILE(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro y si se repite*/
    bool flagPath = false;
    bool flagP = false;
    bool flagSize = false;
    bool flagCont = false;
    bool flag = false;//Si se repite un valor se activa esta bandera
    /*Variables para obtener los valores de cada nodo*/
    QString valPath = "";
    QString valCont = "";
    int valSize = 0;

    for(int i = 0; i < raiz->hijos.count(); i++){
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case PATH:
        {
            if(flagPath){
                cout << "ERROR parametro -path ya definido"<< endl;
                flag = true;
                break;
            }
            flagPath = true;
            valPath = n.valor;
            valPath = valPath.replace("\"","");
        }
            break;
        case P:
        {
            if(flagP){
                cout << "ERROR parametro -p ya definido "<< endl;
                flag = true;
                break;
            }
            flagP = true;
        }
            break;
        case SIZE:
        {
            if(flagSize){
                cout << "ERROR parametro -size ya definido" << endl;
                flag = true;
                break;
            }
            flagSize = true;
            valSize = n.valor.toInt();
            if(!(valSize > 0)){
                cout << "ERROR: parametro -size menor a cero" << endl;
                flag = true;
                break;
            }
        }
            break;
        case CONT:
        {
            if(flagCont){
                cout << "ERROR parametro -cont ya definido " << endl;
                flag = true;
                break;
            }
            flagCont = true;
            valCont = n.valor;
            valCont = valCont.replace("\"","");
        }
            break;
        }
    }

    if(!flag){
        if(flagPath){
            QFileInfo fileName(valPath);
            QString name = fileName.fileName();
            if(name.length() <= 11){
                if(flag_login){
                    int result = crearArchivo(valPath,flagP,valSize,valCont);
                    if(result == 1){
                        cout << "Archivo creado con exito" << endl;
                    }else if(result == 2)
                        cout << "ERROR el usuario actual no tiene permisos de escritura" << endl;
                    else if(result == 3)
                        cout << "ERROR el archivo contenido no existe" << endl;
                    else if(result == 4)
                        cout << "ERROR no existe la ruta y no se tiene el parametro -p" << endl;
                }else
                    cout << "ERROR necesita iniciar sesion para poder ejecutar este comando" << endl;
            }else
                cout << "ERROR el nombre del archivo es mas grande de lo esperado" << endl;

        }else
            cout << "ERROR parametro -path no definido" << endl;
    }
}

void recorrerCAT(Nodo *raiz){
   QString path = raiz->hijos.at(0).valor;
   char auxPath[500];
   strcpy(auxPath,path.toStdString().c_str());
   if(flag_login){
       FILE *fp = fopen(currentSession.direccion.toStdString().c_str(),"rb+");
       int carpeta = buscarCarpetaArchivo(fp,auxPath);
       if(carpeta != -1){
           SuperBloque super;
           InodoTable inodo;
           string cadena = "";
           fseek(fp,currentSession.inicioSuper,SEEK_SET);
           fread(&super,sizeof(SuperBloque),1,fp);
           fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*carpeta,SEEK_SET);
           fread(&inodo,sizeof(InodoTable),1,fp);
           bool permisos = permisosDeLectura(inodo.i_perm,(inodo.i_uid == currentSession.id_user),(inodo.i_gid == currentSession.id_grp));
           if(permisos || (currentSession.id_user == 1 && currentSession.id_grp == 1)){
               for (int i = 0; i < 12; i++) {
                   if(inodo.i_block[i] != -1){
                       BloqueArchivo archivo;
                       fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*inodo.i_block[i],SEEK_SET);
                       fread(&archivo,sizeof(BloqueCarpeta),1,fp);
                       cadena += archivo.b_content;
                   }
               }
               cout << cadena << endl;
           }else
               cout << "ERROR el usuario no tiene permisos de lectura" << endl;
       }else
           cout << "ERROR no se encuentra el archivo " << path.toStdString() << endl;
       fclose(fp);
   }else
       cout << "ERROR para ejecutar este comando necesita iniciar sesion" << endl;
}

void recorrerREM(Nodo *raiz){
    QString path = raiz->hijos.at(0).valor;
    char auxPath[500];
    strcpy(auxPath,path.toStdString().c_str());
    if(flag_login){
        FILE *fp = fopen(currentSession.direccion.toStdString().c_str(),"rb+");
        int existe = buscarCarpetaArchivo(fp,auxPath);
        strcpy(auxPath,path.toStdString().c_str());
        if(existe != -1){
            bool permisos = permisosEscrituraRecursivo(fp,existe);
            if(permisos){
                SuperBloque super;
                BloqueCarpeta carpeta;
                int bloque = 0;
                int posicion = 0;
                fseek(fp,currentSession.inicioSuper,SEEK_SET);
                fread(&super,sizeof(SuperBloque),1,fp);
                //Obtenemos el bloque y la poisicion de la carpeta/archivo a eliminar
                bloqueCarpetaArchivo(fp,auxPath,bloque,posicion);
                //Eliminar la referencia carpeta/archivo del bloque carpeta
                fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bloque,SEEK_SET);
                fread(&carpeta,sizeof(BloqueCarpeta),1,fp);
                memset(carpeta.b_content[posicion].b_name,0,sizeof(carpeta.b_content[posicion].b_name));
                carpeta.b_content[posicion].b_inodo = -1;
                fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bloque,SEEK_SET);
                fwrite(&carpeta,sizeof(BloqueCarpeta),1,fp);
                //Eliminar la carpeta/archivo
                eliminarCarpetaArchivo(fp,existe);
            }else
                cout << "ERROR: alguna carpeta hija no posee permisos de escritura" << endl;
        }else
            cout << "ERROR: no se encuentra la direccion" << endl;
        fclose(fp);
    }else
        cout << "ERROR: para ejecutar este comando necesita iniciar sesion" << endl;
}

void recorrerEDIT(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro*/
    bool flagPath = false;
    bool flagCont = false;
    bool flag = false; //Si se repite un valor se activa esta bandera

    for(int i = 0; i < raiz->hijos.count(); i++){
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case PATH:
        {
            if(flagPath){
                cout << "ERROR parametro -path ya definido "<< endl;
                flag = true;
                break;
            }
            flagPath = true;
        }
            break;
        case CONT:
        {
            if(flagCont){
                cout << "ERROR parametro -cont ya definido" << endl;
                flag = true;
                break;
            }
            flagCont = true;
        }
            break;
        }
    }

    if(!flag){
        if(flagPath){
            if(flagCont){

            }else
                cout << "ERROR parametro -cont no definido" << endl;
        }else
            cout << "ERROR parametro -path no definido"<< endl;
    }
}

void recorrerREN(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro*/
    bool flagPath = false;
    bool flagName = false;
    bool flag = false;//Si se repite una bandera se activa esta bandera

    for(int i = 0; i < raiz->hijos.count(); i++){
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case PATH:
        {
            if(flagPath){
                cout << "ERROR parametro -path ya definido" << endl;
                flag = true;
                break;
            }
            flagPath = true;
        }
            break;
        case NAME:
        {
            if(flagName){
                cout << "ERROR parametro -name ya definido" << endl;
                flag = true;
                break;
            }
            flagName = true;
        }
            break;
        }
    }

    if(!flag){
        if(flagPath){
            if(flagName){

            }else
                cout << "ERROR parametro -name no definido" << endl;
        }else
            cout << "ERROR parametro -path no definido" << endl;
    }
}

void recorrerMKDIR(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro*/
    bool flagPath = false;
    bool flagP = false;
    bool flag = false; //Si se repite un parametro se activa esta bandera
    /*Variables para obtener los valores de cada nodo*/
    QString valPath = "";
    bool valP = false;

    for(int i = 0; i < raiz->hijos.count(); i++){
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case PATH:
        {
            if(flagPath){
                cout << "ERROR parametro -path ya definido" << endl;
                flag = true;
                break;
            }
            flagPath = true;
            valPath = n.valor;
            valPath = valPath.replace("\"","");
        }
            break;
        case P:
        {
            if(flagP){
                cout << "ERROR parametro -p ya definido" << endl;
                flag = true;
                break;
            }
            flagP = true;
            valP = true;
        }
            break;
        }
    }

    if(!flag){
        if(flagPath){
            QFileInfo fileName(valPath);
            QString name = fileName.fileName();
            if(name.length() <= 11){
                if(flag_login){
                    int result = crearCarpeta(valPath,valP);
                    if(result == 0)
                        cout << "La carpeta ya existe" << endl;
                    else if(result == 1){
                        cout << "Carpeta creada con exito" << endl;
                    }else if(result == 2)
                        cout << "No se tienen permisos de escritura" << endl;
                    else if(result == 3){

                    }
                }else
                    cout << "ERROR necesita iniciar sesion para poder ejecutar este comando" << endl;
            }else
                cout << "ERROR el nombre de la carpeta es mas grande de lo esperado" << endl;
        }else
            cout << "ERROR parametro -path no definido" << endl;
    }
}

void recorrerCP(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro*/
    bool flagPath = false;
    bool flagDest = false;
    bool flag = false; //Si se repite un parametro se activa

    for(int i = 0; i < raiz->hijos.count(); i ++){
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case PATH:
        {
            if(flagPath){
                cout << "ERROR parametro -path ya definido "<< endl;
                flag = true;
                break;
            }
            flagPath = true;
        }
            break;
        case DEST:
        {
            if(flagDest){
                cout << "ERROR parametro -dest ya definido" << endl;
                flag = true;
                break;
            }
            flagDest = true;
        }
            break;
        }
    }

    if(!flag){
        if(flagPath){
            if(flagDest){

            }else
                cout << "ERROR parametro -dest no definido "<< endl;
        }else
            cout << "ERROR parametro -path no definido" << endl;
    }
}

void recorrerMV(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro*/
    bool flagPath = false;
    bool flagDest = false;
    bool flag = false; //Si se repite un parametro se activa

    for(int i = 0; i < raiz->hijos.count(); i ++){
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case PATH:
        {
            if(flagPath){
                cout << "ERROR parametro -path ya definido "<< endl;
                flag = true;
                break;
            }
            flagPath = true;
        }
            break;
        case DEST:
        {
            if(flagDest){
                cout << "ERROR parametro -dest ya definido" << endl;
                flag = true;
                break;
            }
            flagDest = true;
        }
            break;
        }
    }

    if(!flag){
        if(flagPath){
            if(flagDest){

            }else
                cout << "ERROR parametro -dest no definido "<< endl;
        }else
            cout << "ERROR parametro -path no definido" << endl;
    }
}

void recorrerFIND(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro y si se repite*/
    bool flagPath = false;
    bool flagName = false;
    bool flag = false;

    for(int i = 0; i < raiz->hijos.count(); i++){
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case PATH:
        {
            if(flagPath){
                cout << "ERROR parametro -path ya definido "<< endl;
                flag = true;
                break;
            }
            flagPath = true;
        }
            break;
        case NAME:
        {
            if(flagName){
                cout << "ERRRO parametro -name ya definido "<< endl;
                flag = true;
                break;
            }
            flagName = true;
        }
            break;
        }
    }

    if(!flag){
        if(flagPath){
            if(flagName){

            }else
                cout <<"ERROR parametro -name no definido" << endl;
        }else
            cout << "ERROR parametro -path no definido " << endl;
    }
}

void recorrerCHOWN(Nodo *raiz){
    /*Banderas para verificar cuando venga un parametro y si se repite*/
    bool flagPath = false;
    bool flagR = false;
    bool flagUser = false;
    bool flag = false;

    for (int i = 0; i < raiz->hijos.count(); i++) {
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case PATH:
        {
            if(flagPath){
                cout <<"ERRRO parametro -path ya definido" << endl;
                flag = true;
                break;
            }
            flagPath = true;
        }
            break;
        case R:
        {
            if(flagR){
                cout <<"ERRRO parametro -r ya definido" << endl;
                flag = true;
                break;
            }
            flagR= true;
        }
            break;
        case USER:
        {
            if(flagUser){
                cout <<"ERRRO parametro -user ya definido" << endl;
                flag = true;
                break;
            }
            flagUser = true;
        }
            break;
        }
    }

    if(!flag){
        if(flagPath){
            if(flagUser){

            }else
                cout << "ERROR parametro -usr no definido" << endl;
        }else
            cout << "ERROR parametro -path no definido" << endl;
    }

}

void recorrerCHGRP(Nodo *raiz){
    /*Banderas para verificar cuando un parametro venga y si se repite*/
    bool flagUser = false;
    bool flagGroup = false;
    bool flag = false;

    for (int i = 0; i < raiz->hijos.count(); i++) {
        Nodo n = raiz->hijos.at(i);
        switch (n.tipo_) {
        case USER:
        {
            if(flagUser){
                cout << "ERROR parametro -usr ya definido "<< endl;
                flag = true;
                break;
            }
            flagUser = true;
        }
            break;
        case GROUP:
        {
            if(flagGroup){
                cout << "ERROR parametro -grp ya definido "<< endl;
                flag = true;
                break;
            }
            flagGroup = true;
        }
            break;
        }
    }

    if(!flag){
        if(flagUser){
            if(flagGroup){

            }else
                cout << "ERROR parametro -grp no definido" << endl;
        }else
            cout << "ERROR parametro -usr no definido" << endl;
    }
}

/* Metodo encargado de formatear una particion con formato EXT2
 * @param int inicio: Byte donde inicia la particion en el disco
 * @param int tamano: Tamano de la particion
 * @param QString direccion: ruta del disco
*/
void formatearEXT2(int inicio, int tamano, QString direccion){
    double n = (tamano - static_cast<int>(sizeof(SuperBloque)))/(4 + static_cast<int>(sizeof(InodoTable)) +3*static_cast<int>(sizeof(BloqueArchivo)));
    int num_estructuras = static_cast<int>(floor(n));//Numero de inodos
    int num_bloques = 3*num_estructuras;

    SuperBloque super;
    super.s_filesystem_type = 2;
    super.s_inodes_count = num_estructuras;
    super.s_blocks_count = num_bloques;
    super.s_free_blocks_count = num_bloques -2;
    super.s_free_inodes_count = num_estructuras -2;
    super.s_mtime = time(nullptr);
    super.s_umtime = 0;
    super.s_mnt_count = 0;
    super.s_magic = 0xEF53;
    super.s_inode_size = sizeof(InodoTable);
    super.s_block_size = sizeof(BloqueArchivo);
    super.s_first_ino = 2;
    super.s_first_blo = 2;
    super.s_bm_inode_start = inicio + static_cast<int>(sizeof(SuperBloque));
    super.s_bm_block_start = inicio + static_cast<int>(sizeof(SuperBloque)) + num_estructuras;
    super.s_inode_start = inicio + static_cast<int>(sizeof (SuperBloque)) + num_estructuras + num_bloques;
    super.s_block_start = inicio + static_cast<int>(sizeof(SuperBloque)) + num_estructuras + num_bloques + (static_cast<int>(sizeof(InodoTable))*num_estructuras);

    InodoTable inodo;
    BloqueCarpeta bloque;

    char buffer = '0';
    char buffer2 = '1';
    char buffer3 = '2';

    FILE *fp = fopen(direccion.toStdString().c_str(),"rb+");

    /*-------------------SUPERBLOQUE------------------*/
    fseek(fp,inicio,SEEK_SET);
    fwrite(&super,sizeof(SuperBloque),1,fp);
    /*----------------BITMAP DE INODOS----------------*/
    for(int i = 0; i < num_estructuras; i++){
        fseek(fp,super.s_bm_inode_start + i,SEEK_SET);
        fwrite(&buffer,sizeof(char),1,fp);
    }
    /*----------bit para / y users.txt en BM----------*/
    fseek(fp,super.s_bm_inode_start,SEEK_SET);
    fwrite(&buffer2,sizeof(char),1,fp);
    fwrite(&buffer2,sizeof(char),1,fp);
    /*---------------BITMAP DE BLOQUES----------------*/
    for(int i = 0; i < num_bloques; i++){
        fseek(fp,super.s_bm_block_start + i,SEEK_SET);
        fwrite(&buffer,sizeof(char),1,fp);
    }
    /*----------bit para / y users.txt en BM----------*/
    fseek(fp,super.s_bm_block_start,SEEK_SET);
    fwrite(&buffer2,sizeof(char),1,fp);
    fwrite(&buffer3,sizeof(char),1,fp);
    /*------------inodo para carpeta root-------------*/
    inodo.i_uid = 1;
    inodo.i_gid = 1;
    inodo.i_size = 0;
    inodo.i_atime = time(nullptr);
    inodo.i_ctime = time(nullptr);
    inodo.i_mtime = time(nullptr);
    inodo.i_block[0] = 0;
    for(int i = 1; i < 15;i++){
        inodo.i_block[i] = -1;
    }
    inodo.i_type = '0';
    inodo.i_perm = 664;
    fseek(fp,super.s_inode_start,SEEK_SET);
    fwrite(&inodo,sizeof(InodoTable),1,fp);
    /*------------Bloque para carpeta root------------*/
    strcpy(bloque.b_content[0].b_name,".");//Actual (el mismo)
    bloque.b_content[0].b_inodo=0;

    strcpy(bloque.b_content[1].b_name,"..");//Padre
    bloque.b_content[1].b_inodo=0;

    strcpy(bloque.b_content[2].b_name,"users.txt");
    bloque.b_content[2].b_inodo=1;

    strcpy(bloque.b_content[3].b_name,".");
    bloque.b_content[3].b_inodo=-1;
    fseek(fp,super.s_block_start,SEEK_SET);
    fwrite(&bloque,sizeof(BloqueCarpeta),1,fp);
    /*-------------inodo para users.txt-------------*/
    inodo.i_uid = 1;
    inodo.i_gid = 1;
    inodo.i_size = 27;
    inodo.i_atime = time(nullptr);
    inodo.i_ctime = time(nullptr);
    inodo.i_mtime = time(nullptr);
    inodo.i_block[0] = 1;
    for(int i = 1; i < 15;i++){
        inodo.i_block[i] = -1;
    }
    inodo.i_type = '1';
    inodo.i_perm = 755;
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
    fwrite(&inodo,sizeof(InodoTable),1,fp);
    /*-------------Bloque para users.txt------------*/
    BloqueArchivo archivo;
    memset(archivo.b_content,0,sizeof(archivo.b_content));
    strcpy(archivo.b_content,"1,G,root\n1,U,root,root,123\n");
    fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta)),SEEK_SET);
    fwrite(&archivo,sizeof(BloqueArchivo),1,fp);

    cout << "EXT2" << endl;
    cout << "..." << endl;
    cout << "Disco formateado con exito" << endl;

    fclose(fp);
}

/* Metodo encargado de formatear una particion con formato EXT3
 * @param int inicio: Byte donde inicia la particion en el disco
 * @param int tamano: Tamano de la particion
 * @param QString direccion: ruta del disco
*/
void formatearEXT3(int inicio, int tamano, QString direccion){
    double n = (tamano - static_cast<int>(sizeof(SuperBloque)))/(4 + static_cast<int>(sizeof(InodoTable)) +3*static_cast<int>(sizeof(BloqueArchivo)));
    int num_estructuras = static_cast<int>(floor(n));//Bitmap indos
    int num_bloques = 3*num_estructuras;//Bitmap bloques
    int super_size = static_cast<int>(sizeof(SuperBloque));
    int journal_size = static_cast<int>(sizeof(Journal))*num_estructuras;

    SuperBloque super;
    super.s_filesystem_type = 3;
    super.s_inodes_count = num_estructuras;
    super.s_blocks_count = num_bloques;
    super.s_free_blocks_count = num_bloques - 2;
    super.s_free_inodes_count = num_estructuras - 2;
    super.s_mtime = time(nullptr);
    super.s_umtime = 0;
    super.s_mnt_count = 0;
    super.s_magic = 0xEF53;
    super.s_inode_size = sizeof(InodoTable);
    super.s_block_size = sizeof(BloqueArchivo);
    super.s_first_ino = 2;
    super.s_first_blo = 2;
    super.s_bm_inode_start = inicio + super_size + journal_size;
    super.s_bm_block_start = inicio + super_size + journal_size + num_estructuras;
    super.s_inode_start = inicio + super_size + journal_size + num_estructuras + num_bloques;
    super.s_block_start = inicio + super_size + journal_size + num_estructuras + num_bloques + static_cast<int>(sizeof(InodoTable))*num_estructuras;

    InodoTable inodo;
    BloqueCarpeta bloque;

    char buffer = '0';
    char buffer2 = '1';
    char buffer3 = '2';

    FILE *fp = fopen(direccion.toStdString().c_str(),"rb+");

    /*-------------------SUPERBLOQUE------------------*/
    fseek(fp,inicio,SEEK_SET);
    fwrite(&super,sizeof(SuperBloque),1,fp);
    /*----------------BITMAP DE INODOS----------------*/
    for(int i = 0; i < num_estructuras; i++){
        fseek(fp,super.s_bm_inode_start + i,SEEK_SET);
        fwrite(&buffer,sizeof(char),1,fp);
    }
    /*----------bit para / y users.txt en BM----------*/
    fseek(fp,super.s_bm_inode_start,SEEK_SET);
    fwrite(&buffer2,sizeof(char),1,fp);
    fwrite(&buffer2,sizeof(char),1,fp);
    /*---------------BITMAP DE BLOQUES----------------*/
    for(int i = 0; i < num_bloques; i++){
        fseek(fp,super.s_bm_block_start + i,SEEK_SET);
        fwrite(&buffer,sizeof(char),1,fp);
    }
    /*----------bit para / y users.txt en BM----------*/
    fseek(fp,super.s_bm_block_start,SEEK_SET);
    fwrite(&buffer2,sizeof(char),1,fp);
    fwrite(&buffer3,sizeof(char),1,fp);
    /*------------inodo para carpeta root-------------*/
    inodo.i_uid = 1;
    inodo.i_gid = 1;
    inodo.i_size = 0;
    inodo.i_atime = time(nullptr);
    inodo.i_ctime = time(nullptr);
    inodo.i_mtime = time(nullptr);
    inodo.i_block[0] = 0;
    for(int i = 1; i < 15;i++){
        inodo.i_block[i] = -1;
    }
    inodo.i_type = '0';
    inodo.i_perm = 664;
    fseek(fp,super.s_inode_start,SEEK_SET);
    fwrite(&inodo,sizeof(InodoTable),1,fp);
    /*------------Bloque para carpeta root------------*/
    strcpy(bloque.b_content[0].b_name,".");//Actual
    bloque.b_content[0].b_inodo=0;

    strcpy(bloque.b_content[1].b_name,"..");//Padre
    bloque.b_content[1].b_inodo=0;

    strcpy(bloque.b_content[2].b_name,"users.txt");
    bloque.b_content[2].b_inodo=1;

    strcpy(bloque.b_content[3].b_name,".");
    bloque.b_content[3].b_inodo=-1;
    fseek(fp,super.s_block_start,SEEK_SET);
    fwrite(&bloque,sizeof(BloqueCarpeta),1,fp);
    /*-------------inodo para users.txt-------------*/
    inodo.i_uid = 1;
    inodo.i_gid = 1;
    inodo.i_size = 27;
    inodo.i_atime = time(nullptr);
    inodo.i_ctime = time(nullptr);
    inodo.i_mtime = time(nullptr);
    inodo.i_block[0] = 1;
    for(int i = 1; i < 15;i++){
        inodo.i_block[i] = -1;
    }
    inodo.i_type = '1';
    inodo.i_perm = 755;
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
    fwrite(&inodo,sizeof(InodoTable),1,fp);
    /*-------------Bloque para users.txt------------*/
    BloqueArchivo archivo;
    memset(archivo.b_content,0,sizeof(archivo.b_content));
    strcpy(archivo.b_content,"1,G,root\n1,U,root,root,123\n");
    fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta)),SEEK_SET);
    fwrite(&archivo,sizeof(BloqueArchivo),1,fp);

    cout << "EXT3" << endl;
    cout << "..." << endl;
    cout << "Disco formateado con exito" << endl;

    fclose(fp);
}

/* Funcion para iniciar sesion
 * @param QString direccion: ruta del disco donde se encuentra la particion
 * @param QString nombre: nombre de la particion
 * @param QString user: Nombre del usuario
 * @param QString password: contrasena
 * @return 1 = login exitoso | 2 = contrasena incorrecta | 0 = usuario no encontrado
*/
int log_in(QString direccion, QString nombre, QString user, QString password){
    int index = disco.buscarParticion_P_E(direccion,nombre);
    if(index != -1){
        MBR masterboot;
        SuperBloque super;
        InodoTable inodo;
        FILE *fp = fopen(direccion.toStdString().c_str(),"rb+");
        fread(&masterboot,sizeof(MBR),1,fp);
        fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
        fread(&super,sizeof(SuperBloque),1,fp);
        fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
        fread(&inodo,sizeof(InodoTable),1,fp);
        fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
        inodo.i_atime = time(nullptr);
        fwrite(&inodo,sizeof(InodoTable),1,fp);
        fclose(fp);
        currentSession.inicioSuper = masterboot.mbr_partition[index].part_start;
        currentSession.fit = masterboot.mbr_partition[index].part_fit;
        return verificarDatos(user,password, direccion);
    }else{
        index = disco.buscarParticion_L(direccion, nombre);
        if(index != -1){
            SuperBloque super;
            InodoTable inodo;
            FILE *fp = fopen(direccion.toStdString().c_str(),"rb+");
            fseek(fp,index + static_cast<int>(sizeof(EBR)),SEEK_SET);
            fread(&super,sizeof(SuperBloque),1,fp);
            fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
            fread(&inodo,sizeof(InodoTable),1,fp);
            fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
            inodo.i_atime = time(nullptr);
            fwrite(&inodo,sizeof(InodoTable),1,fp);
            fclose(fp);
            currentSession.inicioSuper = index + static_cast<int>(sizeof(EBR));
            currentSession.fit = getLogicFit(direccion,nombre);
            return verificarDatos(user,password,direccion);
        }
    }
    return 0;
}

/* Funcion para verificar datos
 * @QString user: Nombre del usuario
 * @param QString password: contrasena
 * @param QString direccion: ruta del disco donde se encuentra la particion
 * @return 1 = login exitoso | 2 = contrasena incorrecta | 0 = usuario no encontrado
*/
int verificarDatos(QString user, QString password, QString direccion){
    FILE *fp = fopen(direccion.toStdString().c_str(),"rb+");

    char cadena[400] = "\0";
    SuperBloque super;
    InodoTable inodo;

    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);
    //Leemos el inodo del archivo users.txt
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,fp);

    for(int i = 0; i < 15; i++){
        if(inodo.i_block[i] != -1){
            BloqueArchivo archivo;
            fseek(fp,super.s_block_start,SEEK_SET);
            for(int j = 0; j <= inodo.i_block[i]; j++){
                fread(&archivo,sizeof(BloqueArchivo),1,fp);
            }
            strcat(cadena,archivo.b_content);
        }
    }

    fclose(fp);

    char *end_str;
    char *token = strtok_r(cadena,"\n",&end_str);
    while(token != nullptr){
        char id[2];
        char tipo[2];
        QString group;
        char user_[12];
        char password_[12];
        char *end_token;
        char *token2 = strtok_r(token,",",&end_token);
        strcpy(id,token2);
        if(strcmp(id,"0") != 0){//Verificar que no sea un U/G eliminado
            token2=strtok_r(nullptr,",",&end_token);
            strcpy(tipo,token2);
            if(strcmp(tipo,"U") == 0){
                token2 = strtok_r(nullptr,",",&end_token);
                group = token2;
                token2 = strtok_r(nullptr,",",&end_token);
                strcpy(user_,token2);
                token2 = strtok_r(nullptr,",",&end_token);
                strcpy(password_,token2);
                if(strcmp(user_,user.toStdString().c_str()) == 0){
                    if(strcmp(password_,password.toStdString().c_str()) == 0){
                        currentSession.direccion = direccion;
                        currentSession.id_user = atoi(id);
                        currentSession.id_grp = buscarGrupo(group);
                        strcpy(currentSession.username,user_);
                        strcpy(currentSession.password,password_);
                        return 1;
                    }else
                        return 2;
                }
            }
        }
        token = strtok_r(nullptr,"\n",&end_str);
    }

    return 0;
}

/* Funcion para verificar la existencia de un grupo
 * @param QString name = nombre del grupo
 * @return # del grupo | -1 = no existe
*/
int buscarGrupo(QString name){
    FILE *fp = fopen(currentSession.direccion.toStdString().c_str(),"rb+");

    char cadena[400] = "\0";
    SuperBloque super;
    InodoTable inodo;

    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);
    //Leemos el inodo del archivo users.txt
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)), SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,fp);

    for(int i = 0; i < 15; i++){
        if(inodo.i_block[i] != -1){
            BloqueArchivo archivo;
            fseek(fp,super.s_block_start,SEEK_SET);
            for(int j = 0; j <= inodo.i_block[i]; j++){
                fread(&archivo,sizeof(BloqueArchivo),1,fp);
            }
            strcat(cadena,archivo.b_content);
        }
    }

    fclose(fp);

    char *end_str;
    char *token = strtok_r(cadena,"\n",&end_str);
    while(token != nullptr){
        char id[2];
        char tipo[2];
        char group[12];
        char *end_token;
        char *token2 = strtok_r(token,",",&end_token);
        strcpy(id,token2);
        if(strcmp(id,"0") != 0){//Verificar que no sea un U/G eliminado
            token2 = strtok_r(nullptr,",",&end_token);
            strcpy(tipo,token2);
            if(strcmp(tipo,"G") == 0){
                strcpy(group,end_token);
                if(strcmp(group,name.toStdString().c_str()) == 0) return atoi(id);
            }
        }
        token = strtok_r(nullptr,"\n",&end_str);
    }

    return -1;
}

/* Metodo que reinicia las variables de sesion */
void log_out(){
    if(flag_login){
        flag_login = false;
        currentSession.id_user = -1;
        //currentUser.id_grp -1;
        memset(currentSession.username,0,sizeof(currentSession.username));
        memset(currentSession.password,0,sizeof(currentSession.password));
        currentSession.direccion = "";
        currentSession.inicioSuper = -1;
        cout << "...\nSesion finalizada " << endl;
    }else
        cout << "ERROR no hay ninguna sesion activa" << endl;
}

/* Funcion para obtener el id del nuevo grupo
 * @return id del ultimo grupo + 1
*/
int getID_grp(){
    FILE *fp = fopen(currentSession.direccion.toStdString().c_str(),"rb+");

    char cadena[400] = "\0";
    int aux_id = -1;
    SuperBloque super;
    InodoTable inodo;
    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);
    //Leemos el inodo del archivo users.txt
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)), SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,fp);

    for(int i = 0; i < 15; i++){
        if(inodo.i_block[i] != -1){
            BloqueArchivo archivo;
            fseek(fp,super.s_block_start,SEEK_SET);
            for(int j = 0; j <= inodo.i_block[i]; j++){
                fread(&archivo,sizeof(BloqueArchivo),1,fp);
            }
            strcat(cadena,archivo.b_content);
        }
    }

    fclose(fp);

    char *end_str;
    char *token = strtok_r(cadena,"\n",&end_str);
    while(token != nullptr){
        char id[2];
        char tipo[2];
        char *end_token;
        char *token2 = strtok_r(token,",",&end_token);
        strcpy(id,token2);
        if(strcmp(id,"0") != 0){//Verificar que no sea un U/G eliminado
            token2 = strtok_r(nullptr,",",&end_token);
            strcpy(tipo,token2);
            if(strcmp(tipo,"G") == 0){
                aux_id = atoi(id);
            }

        }
        token = strtok_r(nullptr,"\n",&end_str);
    }
    return ++aux_id;
}

/* Metodo para agregar un grupo/usuario al archivo users.txt de una particion
 * @param QString name: Datos del nuevo grupo/usuario
*/
void agregarUsersTXT(QString datos){
    FILE *fp = fopen(currentSession.direccion.toStdString().c_str(), "rb+");

    SuperBloque super;
    InodoTable inodo;
    BloqueArchivo archivo;
    int blockIndex = 0;

    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);
    //Leemos el inodo del archivo users.txt
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)), SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,fp);

    for(int i = 0; i < 12; i++){
        if(inodo.i_block[i] != -1)
            blockIndex = inodo.i_block[i];//Ultimo bloque utilizado del archivo
    }

    fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*blockIndex,SEEK_SET);
    fread(&archivo,sizeof(BloqueArchivo),1,fp);
    int enUso = static_cast<int>(strlen(archivo.b_content));
    int libre = 63 - enUso;

    if(datos.length() <= libre){
        strcat(archivo.b_content,datos.toStdString().c_str());
        fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*blockIndex,SEEK_SET);
        fwrite(&archivo,sizeof(BloqueArchivo),1,fp);
        fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
        fread(&inodo,sizeof(InodoTable),1,fp);
        inodo.i_size = inodo.i_size + datos.length();
        inodo.i_mtime = time(nullptr);
        fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
        fwrite(&inodo,sizeof(InodoTable),1,fp);
    }else{
        QString aux = "";
        QString aux2 = "";
        int i = 0;

        for(i = 0; i < libre; i++)
            aux += datos.at(i);

        for(; i < datos.length(); i++)
            aux2  += datos.at(i);

        //Guardamos lo que cabe en el primer bloque
        strcat(archivo.b_content,aux.toStdString().c_str());
        fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*blockIndex,SEEK_SET);
        fwrite(&archivo,sizeof(BloqueArchivo),1,fp);
        BloqueArchivo auxArchivo;
        strcpy(auxArchivo.b_content,aux2.toStdString().c_str());
        int bit = buscarBit(fp,'B',currentSession.fit);
        /*Guardamos el bloque en el bitmap y en la tabla de bloques*/
        fseek(fp,super.s_bm_block_start + bit,SEEK_SET);
        fputc('2',fp);
        fseek(fp,super.s_block_start + (static_cast<int>(sizeof(BloqueArchivo))*bit),SEEK_SET);
        fwrite(&auxArchivo,sizeof(BloqueArchivo),1,fp);
        /*Guardamos el modificado del inodo*/
        fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
        fread(&inodo,sizeof(InodoTable),1,fp);
        inodo.i_size = inodo.i_size + datos.length();
        inodo.i_mtime = time(nullptr);
        inodo.i_block[blockIndex] = bit;
        fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
        fwrite(&inodo,sizeof(InodoTable),1,fp);
        /*Guardamos la nueva cantidad de bloques libres y el primer bloque libre*/
        super.s_first_blo = super.s_first_blo + 1;
        super.s_free_blocks_count = super.s_free_blocks_count - 1;
        fseek(fp,currentSession.inicioSuper,SEEK_SET);
        fwrite(&super,sizeof(SuperBloque),1,fp);
    }
    fclose(fp);
}

/* Funcion que devuelve el byte donde inicia la particion logica si esta existe
 * @param QString direccion: ruta del archivo
 * @param QString nombre: nombre de la particion
 * @return char: ajuste de la particion
*/
char getLogicFit(QString direccion, QString nombre){
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
                    return extendedBoot.part_fit;
                }
            }
        }
        fclose(fp);
    }
    return -1;
}

/* Funcion que devuelve el byte donde inicia la particion logica si esta existe
 * @param FILE fp: archivo en el que se esta leyendo/escribiendo
 * @param int tipo: tipo de bloque a buscar
 * @param char fit: ajuste del disco
 * @return -1 = Ya no existen bloques libres | # bit libre en el bitmap
*/
int buscarBit(FILE *fp, char tipo, char fit){
    SuperBloque super;
    int inicio_bm = 0;
    char tempBit = '0';
    int bit_libre = -1;
    int tam_bm = 0;

    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);

    if(tipo == 'I'){
        tam_bm = super.s_inodes_count;
        inicio_bm = super.s_bm_inode_start;
    }else if(tipo == 'B'){
        tam_bm = super.s_blocks_count;
        inicio_bm = super.s_bm_block_start;
    }

    /*----------------Tipo de ajuste a utilizar----------------*/
    if(fit == 'F'){//Primer ajuste
        for(int i = 0; i < tam_bm; i++){
            fseek(fp,inicio_bm + i,SEEK_SET);
            tempBit = static_cast<char>(fgetc(fp));
            if(tempBit == '0'){
                bit_libre = i;
                return bit_libre;
            }
        }

        if(bit_libre == -1)
            return -1;

    }else if(fit == 'B'){//Mejor ajuste
        int libres = 0;
        int auxLibres = -1;

        for(int i = 0; i < tam_bm; i++){//Primer recorrido
            fseek(fp,inicio_bm + i,SEEK_SET);
            tempBit = static_cast<char>(fgetc(fp));
            if(tempBit == '0'){
                libres++;
                if(i+1 == tam_bm){
                    if(auxLibres == -1 || auxLibres == 0)
                        auxLibres = libres;
                    else{
                        if(auxLibres > libres)
                            auxLibres = libres;
                    }
                    libres = 0;
                }
            }else if(tempBit == '1'){
                if(auxLibres == -1 || auxLibres == 0)
                    auxLibres = libres;
                else{
                    if(auxLibres > libres)
                        auxLibres = libres;
                }
                libres = 0;
            }
        }

        for(int i = 0; i < tam_bm; i++){
            fseek(fp,inicio_bm + i, SEEK_SET);
            tempBit = static_cast<char>(fgetc(fp));
            if(tempBit == '0'){
                libres++;
                if(i+1 == tam_bm)
                    return ((i+1)-libres);
            }else if(tempBit == '1'){
                if(auxLibres == libres)
                    return ((i+1) - libres);
                libres = 0;
            }
        }

        return -1;

    }else if(fit == 'W'){//Peor ajuste
        int libres = 0;
        int auxLibres = -1;

        for (int i = 0; i < tam_bm; i++) {//Primer recorrido
            fseek(fp,inicio_bm + i, SEEK_SET);
            tempBit = static_cast<char>(fgetc(fp));
            if(tempBit == '0'){
                libres++;
                if(i+1 == tam_bm){
                    if(auxLibres == -1 || auxLibres == 0)
                        auxLibres = libres;
                    else {
                        if(auxLibres < libres)
                            auxLibres = libres;
                    }
                    libres = 0;
                }
            }else if(tempBit == '1'){
                if(auxLibres == -1 || auxLibres == 0)
                    auxLibres = libres;
                else{
                    if(auxLibres < libres)
                        auxLibres = libres;
                }
                libres = 0;
            }
        }

        for (int i = 0; i < tam_bm; i++) {
            fseek(fp,inicio_bm + i, SEEK_SET);
            tempBit = static_cast<char>(fgetc(fp));
            if(tempBit == '0'){
                libres++;
                if(i+1 == tam_bm)
                    return ((i+1) - libres);
            }else if(tempBit == '1'){
                if(auxLibres == libres)
                    return ((i+1) - libres);
                libres = 0;
            }
        }

        return -1;
    }

    return 0;
}

/* Metodo para eliminar un grupo del archivo users.txt de una particion
 * @param QString name: Datos del nuevo grupo
*/
void eliminarGrupo(QString name){
    FILE *fp = fopen(currentSession.direccion.toStdString().c_str(),"rb+");

    SuperBloque super;
    InodoTable inodo;
    BloqueArchivo archivo;

    int col = 1;
    char actual;
    int posicion = 0;
    int numBloque = 0;
    int id = -1;
    char tipo = '\0';
    string grupo = "";
    string palabra = "";
    bool flag = false;


    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);
    //Nos posicionamos en el inodo del archivo users.txt
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,fp);

    for (int i = 0; i < 12; i++) {
        if(inodo.i_block[i] != -1){
            fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*inodo.i_block[i],SEEK_SET);
            fread(&archivo,sizeof(BloqueArchivo),1,fp);
            for(int j = 0; j < 63; j++){
                actual = archivo.b_content[j];
                if(actual=='\n'){
                    if(tipo == 'G'){
                        grupo = palabra;
                        if(strcmp(grupo.c_str(),name.toStdString().c_str()) == 0){
                            fseek(fp,super.s_block_start+static_cast<int>(sizeof(BloqueArchivo))*numBloque,SEEK_SET);
                            fread(&archivo,sizeof(BloqueCarpeta),1,fp);
                            archivo.b_content[posicion] = '0';
                            fseek(fp,super.s_block_start+static_cast<int>(sizeof(BloqueArchivo))*numBloque,SEEK_SET);
                            fwrite(&archivo,sizeof(BloqueArchivo),1,fp);
                            cout << "Grupo eliminado con exito" << endl;
                            flag = true;
                            break;
                        }
                    }
                    col = 1;
                    palabra = "";
                }else if(actual != ','){
                    palabra += actual;
                    col++;
                }else if(actual == ','){
                    if(col == 2){
                        id = atoi(palabra.c_str());
                        posicion = j-1;
                        numBloque = inodo.i_block[i];
                    }
                    else if(col == 4)
                        tipo = palabra[0];
                    col++;
                    palabra = "";
                }
            }
            if(flag)
                break;
        }
    }

    fclose(fp);
}

/* Funcion para verificar la existencia de un usuario
 * @param QString name = nombre del usuario
 * @return true = existe | false = no existe
*/
bool buscarUsuario(QString name){
    FILE *fp = fopen(currentSession.direccion.toStdString().c_str(),"rb+");

    char cadena[400] = "\0";
    SuperBloque super;
    InodoTable inodo;

    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);
    //Nos posicionamos en el inodo del archivo users.txt
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)), SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,fp);

    for(int i = 0; i < 15; i++){
        if(inodo.i_block[i] != -1){
            BloqueArchivo archivo;
            fseek(fp,super.s_block_start,SEEK_SET);
            for(int j = 0; j <= inodo.i_block[i]; j++){
                fread(&archivo,sizeof(BloqueArchivo),1,fp);
            }
            strcat(cadena,archivo.b_content);
        }
    }

    fclose(fp);

    char *end_str;
    char *token = strtok_r(cadena,"\n",&end_str);
    while(token != nullptr){
        char id[2];
        char tipo[2];
        char user[12];
        char *end_token;
        char *token2 = strtok_r(token,",",&end_token);
        strcpy(id,token2);
        if(strcmp(id,"0") != 0){//Verificar que no sea un U/G eliminado
            token2 = strtok_r(nullptr,",",&end_token);
            strcpy(tipo,token2);
            if(strcmp(tipo,"U") == 0){
                token2 = strtok_r(nullptr,",",&end_token);
                token2 = strtok_r(nullptr,",",&end_token);
                strcpy(user,token2);

                if(strcmp(user,name.toStdString().c_str()) == 0)
                    return true;
            }
        }
        token = strtok_r(nullptr,"\n",&end_str);
    }

    return false;
}

/* Funcion para obtener el id del nuevo usuario
 * @return id del ultimo usuario + 1
*/
int getID_usr(){
    FILE *fp = fopen(currentSession.direccion.toStdString().c_str(),"rb+");

    char cadena[400] = "\0";
    int res = 0;
    SuperBloque super;
    InodoTable inodo;

    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);
    //Nos posicionamos en el inodo del archivo users.txt
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)), SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,fp);

    for(int i = 0; i < 15; i++){
        if(inodo.i_block[i] != -1){
            BloqueArchivo archivo;
            fseek(fp,super.s_block_start,SEEK_SET);
            for(int j = 0; j <= inodo.i_block[i]; j++){
                fread(&archivo,sizeof(BloqueArchivo),1,fp);
            }
            strcat(cadena,archivo.b_content);
        }
    }

    fclose(fp);

    char *end_str;
    char *token = strtok_r(cadena,"\n",&end_str);
    while(token != nullptr){
        char id[2];
        char tipo[2];
        char *end_token;
        char *token2 = strtok_r(token,",",&end_token);
        strcpy(id,token2);
        if(strcmp(id,"0") != 0){//Verificar que no sea un U/G eliminado
            token2 = strtok_r(nullptr,",",&end_token);
            strcpy(tipo,token2);
            if(strcmp(tipo,"U") == 0)
                res++;
        }
        token = strtok_r(nullptr,"\n",&end_str);
    }
    return ++res;
}

/* Metodo para eliminar un usuario del archivo users.txt de una particion
 * @param QString name: nombre del usuario a eliminar
*/
void eliminarUsuario(QString name){
    FILE *fp = fopen(currentSession.direccion.toStdString().c_str(),"rb+");

    SuperBloque super;
    InodoTable inodo;
    BloqueArchivo archivo;

    int col = 1;
    char actual;
    string palabra = "";
    int posicion = 0;
    int numBloque = 0;
    int id = -1;
    char tipo = '\0';
    string grupo = "";
    string usuario = "";
    bool flag = false;

    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);
    //Nos posicionamos en el inodo del archivo users.txt
    fseek(fp,super.s_inode_start + static_cast<int>(sizeof(InodoTable)),SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,fp);

    for (int i = 0; i < 12; i++) {
        if(inodo.i_block[i] != -1){
            fseek(fp,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*inodo.i_block[i],SEEK_SET);
            fread(&archivo,sizeof(BloqueArchivo),1,fp);
            for(int j = 0; j < 63; j++){
                actual = archivo.b_content[j];
                if(actual=='\n'){
                    if(tipo == 'U'){
                        if(strcmp(usuario.c_str(),name.toStdString().c_str()) == 0){
                            fseek(fp,super.s_block_start+static_cast<int>(sizeof(BloqueArchivo))*numBloque,SEEK_SET);
                            fread(&archivo,sizeof(BloqueArchivo),1,fp);
                            archivo.b_content[posicion] = '0';
                            fseek(fp,super.s_block_start+static_cast<int>(sizeof(BloqueArchivo))*numBloque,SEEK_SET);
                            fwrite(&archivo,sizeof(BloqueArchivo),1,fp);
                            cout << "Usuario eliminado con exito" << endl;
                            flag = true;
                            break;
                        }
                        usuario = "";
                        grupo = "";
                    }
                    col = 1;
                    palabra = "";
                }else if(actual != ','){
                    palabra += actual;
                    col++;
                }else if(actual == ','){
                    if(col == 2){
                        id = atoi(palabra.c_str());
                        posicion = j-1;
                        numBloque = inodo.i_block[i];
                    }
                    else if(col == 4)
                        tipo = palabra[0];
                    else if(grupo == "")
                        grupo = palabra;
                    else if(usuario == "")
                        usuario = palabra;
                    col++;
                    palabra = "";
                }
            }
            if(flag)
                break;
        }
    }

    fclose(fp);
}

/* Funcion para crear una carpeta
 * @param QString path;
 * @param bool p;
 * @return 0 = ya existe
 *       | 1 = carpeta creada exitosamente
 *       | 2 = error por permisos
 *       | 3 = no existe el directorio y no esta el parametro -p
*/
int crearCarpeta(QString path, bool p){
    FILE *fp = fopen(currentSession.direccion.toStdString().c_str(),"rb+");

    SuperBloque super;
    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);

    string aux = path.toStdString();
    char auxPath[500];
    strcpy(auxPath,aux.c_str());
    int existe = buscarCarpetaArchivo(fp,auxPath);
    strcpy(auxPath,aux.c_str());
    int response = -1;

    if(existe != -1)
        response = 0;
    else
        response = nuevaCarpeta(fp,currentSession.fit,p,auxPath,0);

    fclose(fp);

    return response;
}

/* Funcion para crear una carpeta
 * @param FILE *stream;
 * @param char fit;
 * @param bool flagP;
 * @param char *path;
 * @param int index = numero de inodo
 * @return 1 = carpeta creada
 *       | 2 = no se tienen permisos de escritura
 *       | 3 = no existe el directorio y no esta el parametro -p
*/
int nuevaCarpeta(FILE *stream, char fit, bool flagP, char *path, int index){
    SuperBloque super;
    InodoTable inodo,inodoNuevo;
    BloqueCarpeta carpeta, carpetaNueva, carpetaAux;
    BloqueApuntadores apuntadores;
    QList<string> lista = QList<string>();
    char copiaPath[500];
    char directorio[500];
    char nombreCarpeta[80];

    strcpy(copiaPath,path);
    strcpy(directorio,dirname(copiaPath));
    strcpy(copiaPath,path);
    strcpy(nombreCarpeta,basename(copiaPath));
    char *token = strtok(path,"/");
    int cont = 0;
    int numInodo = index;
    int response = 0;

    while(token != nullptr){
        cont++;
        lista.append(token);
        token = strtok(nullptr,"/");
    }

    fseek(stream,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,stream);

    if(cont == 1){//Solo es una carpeta '/home' | '/archivos'
        int libre = 0;
        int content = 0;
        int bloque = 0;
        int pointer = 0;
        fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
        fread(&inodo,sizeof(InodoTable),1,stream);
        //Buscamos un espacio libre en el bloque carpeta
        for (int i = 0; i < 15; i++) {
            if(inodo.i_block[i] != -1){
                if(i == 12){//Apuntador indirecto simple
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*inodo.i_block[i],SEEK_SET);
                    fread(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                    for(int j = 0; j < 16; j++){
                        if(apuntadores.b_pointer[j] != -1){
                            fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*apuntadores.b_pointer[j],SEEK_SET);
                            fread(&carpeta,sizeof(BloqueCarpeta),1,stream);
                            for(int k = 0; k < 4; k++){
                                if(carpeta.b_content[k].b_inodo == -1){
                                    libre = 1;
                                    bloque = i;
                                    pointer = j;
                                    content = k;
                                    break;
                                }
                            }
                        }
                        if(libre == 1)
                            break;
                    }
                }else if(i == 13){//Apuntador indirecto doble

                }else if(i == 14){//Apuntador indirecto triple

                }else{//Apuntadores directos
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*inodo.i_block[i],SEEK_SET);
                    fread(&carpeta,sizeof(BloqueCarpeta),1,stream);
                    for(int j = 0; j < 4; j++){
                        if(carpeta.b_content[j].b_inodo == -1){
                            libre = 1;
                            bloque = i;
                            content = j;
                            break;
                        }
                    }
                }
            }
            if(libre == 1)
                break;
        }

        if(libre == 1){
            if(bloque == 12){//Apuntador indirecto simple
                bool permissions = permisosDeEscritura(inodo.i_perm,(inodo.i_uid == currentSession.id_user),(inodo.i_gid == currentSession.id_grp));
                if(permissions || (currentSession.id_user == 1 && currentSession.id_grp == 1) ){
                    char buffer = '1';
                    int bitInodo = buscarBit(stream,'I',fit);
                    //Agregamos la carpeta al espacio libre en el bloque
                    carpeta.b_content[content].b_inodo = bitInodo;
                    strcpy(carpeta.b_content[content].b_name,nombreCarpeta);
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*apuntadores.b_pointer[pointer],SEEK_SET);
                    fwrite(&carpeta,sizeof(BloqueCarpeta),1,stream);
                    //Creamos el nuevo inodo carpeta
                    inodoNuevo.i_uid = currentSession.id_user;
                    inodoNuevo.i_gid = currentSession.id_grp;
                    inodoNuevo.i_size = 0;
                    inodoNuevo.i_atime = time(nullptr);
                    inodoNuevo.i_ctime = time(nullptr);
                    inodoNuevo.i_mtime = time(nullptr);
                    int bitBloque = buscarBit(stream,'B',fit);
                    inodoNuevo.i_block[0] = bitBloque;
                    for (int i = 1; i < 15;i++)
                        inodoNuevo.i_block[i] = -1;
                    inodoNuevo.i_type = '0';
                    inodoNuevo.i_perm = 664;
                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*bitInodo,SEEK_SET);
                    fwrite(&inodoNuevo,sizeof(InodoTable),1,stream);
                    //Guardamos el bit del inodo en el bitmap
                    fseek(stream,super.s_bm_inode_start + bitInodo,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Creamos el nuevo bloque carpeta
                    carpetaNueva.b_content[0].b_inodo = bitInodo;
                    carpetaNueva.b_content[1].b_inodo = numInodo;
                    carpetaNueva.b_content[2].b_inodo = -1;
                    carpetaNueva.b_content[3].b_inodo = -1;
                    strcpy(carpetaNueva.b_content[0].b_name,".");
                    strcpy(carpetaNueva.b_content[1].b_name,"..");
                    strcpy(carpetaNueva.b_content[2].b_name,"");
                    strcpy(carpetaNueva.b_content[3].b_name,"");
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bitBloque,SEEK_SET);
                    fwrite(&carpetaNueva,sizeof(BloqueCarpeta),1,stream);
                    //Guardamos el bit del bloque en el bitmap
                    fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Sobreescribimos el super bloque
                    super.s_free_inodes_count = super.s_free_inodes_count - 1;
                    super.s_free_blocks_count = super.s_free_blocks_count - 1;
                    super.s_first_ino = super.s_first_ino + 1;
                    super.s_first_blo = super.s_first_blo + 1;
                    fseek(stream,currentSession.inicioSuper,SEEK_SET);
                    fwrite(&super,sizeof(SuperBloque),1,stream);
                    return 1;
                }else
                    return 2;
            }else if(bloque == 13){//Apuntador indirecto doble

            }else if(bloque == 14){//Apuntador indirecto triple

            }else{//Apuntadores directos
                bool permisos = permisosDeEscritura(inodo.i_perm,(inodo.i_uid == currentSession.id_user),(inodo.i_gid == currentSession.id_grp));
                if(permisos || (currentSession.id_user == 1 && currentSession.id_grp == 1) ){
                    char buffer = '1';
                    int bitInodo = buscarBit(stream,'I',fit);
                    //Agregamos la carpeta al espacio libre en el bloque
                    carpeta.b_content[content].b_inodo = bitInodo;
                    strcpy(carpeta.b_content[content].b_name,nombreCarpeta);
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*inodo.i_block[bloque],SEEK_SET);
                    fwrite(&carpeta,sizeof(BloqueCarpeta),1,stream);
                    //Creamos el nuevo inodo
                    inodoNuevo.i_uid = currentSession.id_user;
                    inodoNuevo.i_gid = currentSession.id_grp;
                    inodoNuevo.i_size = 0;
                    inodoNuevo.i_atime = time(nullptr);
                    inodoNuevo.i_ctime = time(nullptr);
                    inodoNuevo.i_mtime = time(nullptr);
                    int bitBloque = buscarBit(stream,'B',fit);
                    inodoNuevo.i_block[0] = bitBloque;
                    for (int i = 1; i < 15;i++)
                        inodoNuevo.i_block[i] = -1;
                    inodoNuevo.i_type = '0';
                    inodoNuevo.i_perm = 664;
                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*bitInodo,SEEK_SET);
                    fwrite(&inodoNuevo,sizeof(InodoTable),1,stream);
                    //Creamos el nuevo bloque carpeta
                    carpetaNueva.b_content[0].b_inodo = bitInodo;
                    carpetaNueva.b_content[1].b_inodo = numInodo;
                    carpetaNueva.b_content[2].b_inodo = -1;
                    carpetaNueva.b_content[3].b_inodo = -1;
                    strcpy(carpetaNueva.b_content[0].b_name,".");
                    strcpy(carpetaNueva.b_content[1].b_name,"..");
                    strcpy(carpetaNueva.b_content[2].b_name,"");
                    strcpy(carpetaNueva.b_content[3].b_name,"");
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bitBloque,SEEK_SET);
                    fwrite(&carpetaNueva,sizeof(BloqueCarpeta),1,stream);
                    //Guardamos los bits en los bitmaps
                    fseek(stream,super.s_bm_inode_start + bitInodo,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Sobreescribimos el super bloque
                    super.s_free_inodes_count = super.s_free_inodes_count - 1;
                    super.s_free_blocks_count = super.s_free_blocks_count - 1;
                    super.s_first_ino = super.s_first_ino + 1;
                    super.s_first_blo = super.s_first_blo + 1;
                    fseek(stream,currentSession.inicioSuper,SEEK_SET);
                    fwrite(&super,sizeof(SuperBloque),1,stream);
                    return 1;
                }else
                    return 2;
            }
        }else if(libre == 0){//Todos bloques estan llenos
            bool flag = false;//Primera vez
            pointer = -1;
            fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
            fread(&inodo,sizeof(InodoTable),1,stream);
            for (int i = 0; i < 15; i++) {
                if(i == 12){//Apuntador indirecto simple
                    if(inodo.i_block[i] == -1){//Primera vez
                        bloque = 12;
                        flag = true;
                        break;
                    }else{
                        fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*inodo.i_block[12],SEEK_SET);
                        fread(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                        for(int j = 0; j < 16; j++){
                            if(apuntadores.b_pointer[j] == -1){
                                bloque = 12;
                                pointer = j;
                                break;
                            }
                        }
                    }
                    if(flag || pointer!= -1)
                        break;
                }else if(i == 13){

                }else if(i == 14){

                }else{
                    if(inodo.i_block[i] == -1){
                        bloque = i;
                        break;
                    }
                }
            }

            if(bloque == 12 && flag){//Apuntador indirecto simple
                bool permissions = permisosDeEscritura(inodo.i_perm,(inodo.i_uid == currentSession.id_user),(inodo.i_gid == currentSession.id_grp));
                if(permissions || (currentSession.id_user == 1 && currentSession.id_grp == 1) ){
                    char buffer = '1';
                    char buffer3 = '3';
                    //Guardamos el bloque en el inodo
                    int bitBloque = buscarBit(stream,'B',fit);//Apuntador
                    inodo.i_block[bloque] = bitBloque;
                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                    fwrite(&inodo,sizeof(InodoTable),1,stream);
                    //Escribimos el bit del bloque apuntador en el bitmap
                    fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                    fwrite(&buffer3,sizeof(char),1,stream);
                    //Creamos el bloque de apuntadores como es simple solo se debe crear uno
                    int bitBloqueCarpeta = buscarBit(stream,'B',fit);//Carpeta
                    apuntadores.b_pointer[0] = bitBloqueCarpeta;
                    for(int i = 1; i < 16; i++)
                        apuntadores.b_pointer[i] = -1;
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*bitBloque,SEEK_SET);
                    fwrite(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                    //Creamos la carpeta del apuntador
                    int bitInodo = buscarBit(stream,'I',fit);
                    carpetaAux.b_content[0].b_inodo = bitInodo;
                    carpetaAux.b_content[1].b_inodo = -1;
                    carpetaAux.b_content[2].b_inodo = -1;
                    carpetaAux.b_content[3].b_inodo = -1;
                    strcpy(carpetaAux.b_content[0].b_name,nombreCarpeta);
                    strcpy(carpetaAux.b_content[1].b_name,"");
                    strcpy(carpetaAux.b_content[2].b_name,"");
                    strcpy(carpetaAux.b_content[3].b_name,"");
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bitBloqueCarpeta,SEEK_SET);
                    fwrite(&carpetaAux,sizeof(BloqueCarpeta),1,stream);
                    //Escribimos el bit del bloque carpeta en el bitmap
                    fseek(stream,super.s_bm_block_start + bitBloqueCarpeta,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Creamos el nuevo inodo carpeta
                    inodoNuevo.i_uid = currentSession.id_user;
                    inodoNuevo.i_gid = currentSession.id_grp;
                    inodoNuevo.i_size = 0;
                    inodoNuevo.i_atime = time(nullptr);
                    inodoNuevo.i_ctime = time(nullptr);
                    inodoNuevo.i_mtime = time(nullptr);
                    bitBloque = buscarBit(stream,'B',fit);//Carpeta
                    inodoNuevo.i_block[0] = bitBloque;
                    for (int i = 1; i < 15;i++)
                        inodoNuevo.i_block[i] = -1;
                    inodoNuevo.i_type = '0';
                    inodo.i_perm = 664;
                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*bitInodo,SEEK_SET);
                    fwrite(&inodoNuevo,sizeof(InodoTable),1,stream);
                    //Escribimos el bit del inodo en el bitmap
                    fseek(stream,super.s_bm_inode_start + bitInodo,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Creamos el nuevo bloque carpeta
                    carpetaNueva.b_content[0].b_inodo = bitInodo;
                    carpetaNueva.b_content[1].b_inodo = numInodo;
                    carpetaNueva.b_content[2].b_inodo = -1;
                    carpetaNueva.b_content[3].b_inodo = -1;
                    strcpy(carpetaNueva.b_content[0].b_name,".");
                    strcpy(carpetaNueva.b_content[1].b_name,"..");
                    strcpy(carpetaNueva.b_content[2].b_name,"");
                    strcpy(carpetaNueva.b_content[3].b_name,"");
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bitBloque,SEEK_SET);
                    fwrite(&carpetaNueva,sizeof(BloqueCarpeta),1,stream);
                    //Guardamos el bit en el bitmap de bloques
                    fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Sobreescribimos el super bloque
                    super.s_free_inodes_count = super.s_free_inodes_count - 1;
                    super.s_free_blocks_count = super.s_free_blocks_count - 3;
                    super.s_first_ino = super.s_first_ino + 1;
                    super.s_first_blo = super.s_first_blo + 3;
                    fseek(stream,currentSession.inicioSuper,SEEK_SET);
                    fwrite(&super,sizeof(SuperBloque),1,stream);
                    return 1;
                }else
                    return 2;
            }else if(bloque == 12 && !flag){
                char buffer = '1';
                //Escribir el numero de bloque en el bloque de apuntadores
                int bitBloque = buscarBit(stream,'B',fit);
                apuntadores.b_pointer[pointer] = bitBloque;
                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*inodo.i_block[12],SEEK_SET);
                fwrite(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                //Creamos el bloque auxiliar
                int bitInodo = buscarBit(stream,'I',fit);
                carpetaAux.b_content[0].b_inodo = bitInodo;
                carpetaAux.b_content[1].b_inodo = -1;
                carpetaAux.b_content[2].b_inodo = -1;
                carpetaAux.b_content[3].b_inodo = -1;
                strcpy(carpetaAux.b_content[0].b_name,nombreCarpeta);
                strcpy(carpetaAux.b_content[1].b_name,"");
                strcpy(carpetaAux.b_content[2].b_name,"");
                strcpy(carpetaAux.b_content[3].b_name,"");
                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bitBloque,SEEK_SET);
                fwrite(&carpetaAux,sizeof(BloqueCarpeta),1,stream);
                //Escribimos el bit del bloque carpeta en el bitmap
                fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                fwrite(&buffer,sizeof(char),1,stream);
                //Creamos el nuevo inodo carpeta
                inodoNuevo.i_uid = currentSession.id_user;
                inodoNuevo.i_gid = currentSession.id_grp;
                inodoNuevo.i_size = 0;
                inodoNuevo.i_atime = time(nullptr);
                inodoNuevo.i_ctime = time(nullptr);
                inodoNuevo.i_mtime = time(nullptr);
                bitBloque = buscarBit(stream,'B',fit);//Carpeta
                inodoNuevo.i_block[0] = bitBloque;
                for (int i = 1; i < 15;i++)
                    inodoNuevo.i_block[i] = -1;
                inodoNuevo.i_type = '0';
                inodo.i_perm = 664;
                fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*bitInodo,SEEK_SET);
                fwrite(&inodoNuevo,sizeof(InodoTable),1,stream);
                //Escribimos el bit del inodo en el bitmap
                fseek(stream,super.s_bm_inode_start + bitInodo,SEEK_SET);
                fwrite(&buffer,sizeof(char),1,stream);
                //Creamos el nuevo bloque carpeta
                carpetaNueva.b_content[0].b_inodo = bitInodo;
                carpetaNueva.b_content[1].b_inodo = numInodo;
                carpetaNueva.b_content[2].b_inodo = -1;
                carpetaNueva.b_content[3].b_inodo = -1;
                strcpy(carpetaNueva.b_content[0].b_name,".");
                strcpy(carpetaNueva.b_content[1].b_name,"..");
                strcpy(carpetaNueva.b_content[2].b_name,"");
                strcpy(carpetaNueva.b_content[3].b_name,"");
                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bitBloque,SEEK_SET);
                fwrite(&carpetaNueva,sizeof(BloqueCarpeta),1,stream);
                //Guardamos el bit en el bitmap de bloques
                fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                fwrite(&buffer,sizeof(char),1,stream);
                //Sobreescribimos el super bloque
                super.s_free_inodes_count = super.s_free_inodes_count - 1;
                super.s_free_blocks_count = super.s_free_blocks_count - 2;
                super.s_first_ino = super.s_first_ino + 1;
                super.s_first_blo = super.s_first_blo + 2;
                fseek(stream,currentSession.inicioSuper,SEEK_SET);
                fwrite(&super,sizeof(SuperBloque),1,stream);
                return 1;
            }
            else if(bloque == 13){//Apuntador indirecto doble

            }else if(bloque == 14){//Apuntador indirecto triple

            }else{//Apuntadores directos
                bool permissions = permisosDeEscritura(inodo.i_perm,(inodo.i_uid == currentSession.id_user),(inodo.i_gid == currentSession.id_grp));
                if(permissions || (currentSession.id_user == 1 && currentSession.id_grp == 1) ){
                    char buffer = '1';
                    int bitBloque = buscarBit(stream,'B',fit);
                    inodo.i_block[bloque] = bitBloque;
                    //Sobreescribimos el inodo
                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                    fwrite(&inodo,sizeof(InodoTable),1,stream);
                    //Bloque carpeta auxiliar
                    int bitInodo = buscarBit(stream,'I',fit);
                    carpetaAux.b_content[0].b_inodo = bitInodo;
                    carpetaAux.b_content[1].b_inodo = -1;
                    carpetaAux.b_content[2].b_inodo = -1;
                    carpetaAux.b_content[3].b_inodo = -1;
                    strcpy(carpetaAux.b_content[0].b_name,nombreCarpeta);
                    strcpy(carpetaAux.b_content[1].b_name,"");
                    strcpy(carpetaAux.b_content[2].b_name,"");
                    strcpy(carpetaAux.b_content[3].b_name,"");
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bitBloque,SEEK_SET);
                    fwrite(&carpetaAux,sizeof(BloqueCarpeta),1,stream);
                    //Escribimos el bit en el bitmap de blqoues
                    fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Creamos el nuevo inodo
                    inodoNuevo.i_uid = currentSession.id_user;
                    inodoNuevo.i_gid = currentSession.id_grp;
                    inodoNuevo.i_size = 0;
                    inodoNuevo.i_atime = time(nullptr);
                    inodoNuevo.i_ctime = time(nullptr);
                    inodoNuevo.i_mtime = time(nullptr);
                    bitBloque = buscarBit(stream,'B',fit);
                    inodoNuevo.i_block[0] = bitBloque;
                    for (int i = 1; i < 15;i++)
                        inodoNuevo.i_block[i] = -1;
                    inodoNuevo.i_type = '0';
                    inodo.i_perm = 664;
                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*bitInodo,SEEK_SET);
                    fwrite(&inodoNuevo,sizeof(InodoTable),1,stream);
                    //Escribimos el bit en el bitmap de inodos
                    fseek(stream,super.s_bm_inode_start + bitInodo,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Creamos el nuevo bloque carpeta
                    carpetaNueva.b_content[0].b_inodo = bitInodo;
                    carpetaNueva.b_content[1].b_inodo = numInodo;
                    carpetaNueva.b_content[2].b_inodo = -1;
                    carpetaNueva.b_content[3].b_inodo = -1;
                    strcpy(carpetaNueva.b_content[0].b_name,".");
                    strcpy(carpetaNueva.b_content[1].b_name,"..");
                    strcpy(carpetaNueva.b_content[2].b_name,"");
                    strcpy(carpetaNueva.b_content[3].b_name,"");
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bitBloque,SEEK_SET);
                    fwrite(&carpetaNueva,sizeof(BloqueCarpeta),1,stream);
                    //Guardamos el bit en el bitmap de bloques
                    fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Sobreescribimos el super bloque
                    super.s_free_inodes_count = super.s_free_inodes_count - 1;
                    super.s_free_blocks_count = super.s_free_blocks_count - 2;
                    super.s_first_ino = super.s_first_ino + 1;
                    super.s_first_blo = super.s_first_blo + 2;
                    fseek(stream,currentSession.inicioSuper,SEEK_SET);
                    fwrite(&super,sizeof(SuperBloque),1,stream);
                    return 1;
                }else
                    return 2;
            }

        }
    }else{//Es un directorio '/home/usac/archivos'
        //Verificar que exista el directorio
        int existe = buscarCarpetaArchivo(stream,directorio);
        if(existe == -1){
            if(flagP){
                int index = 0;
                string aux = "";
                //Crear posibles carpetas inexistentes
                for(int i = 0; i < cont; i++){
                    aux += "/"+lista.at(i);
                    char dir[500];
                    char auxDir[500];
                    strcpy(dir,aux.c_str());
                    strcpy(auxDir,aux.c_str());
                    int carpeta = buscarCarpetaArchivo(stream,dir);
                    if(carpeta == -1){
                        response = nuevaCarpeta(stream,fit,false,auxDir,index);
                        strcpy(auxDir,aux.c_str());
                        index = buscarCarpetaArchivo(stream,auxDir);
                    }else
                        index = carpeta;
                }
            }else
                return 3;
        }else{//Solo crear la carpeta en el directorio
            char dir[100] = "/";
            strcat(dir,nombreCarpeta);
            return nuevaCarpeta(stream,fit,false,dir,existe);
        }
    }

    return response;
}

/* Funcion para crear un archivo
 * @param QString path; ruta absoluta del archivo a crear
 * @param bool p: bandera
 * @param int size: Tamano en bytes del archivo
 * @param QString cont:
 * @return 0 = ya existe
 *       | 1 = carpeta creada exitosamente
 *       | 2 = error por permisos
 *       | 3 = error archivo contenido no existe
 *       | 4 = error no existe el la ruta y no esta el parametro -p
*/
int crearArchivo(QString path, bool p, int size, QString cont){
    FILE *fp = fopen(currentSession.direccion.toStdString().c_str(),"rb+");

    SuperBloque super;
    fseek(fp,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,fp);

    char auxPath[500];
    char auxPath2[500];
    strcpy(auxPath,path.toStdString().c_str());
    strcpy(auxPath2,path.toStdString().c_str());
    int existe = buscarCarpetaArchivo(fp,auxPath);
    strcpy(auxPath,path.toStdString().c_str());
    int response = -1;

    if(existe != -1)
        response = 0;
    else
        response = nuevoArchivo(fp,currentSession.fit,p,auxPath,size,cont,0,auxPath2);

    fclose(fp);
    return response;
}

/* Funcion para crear un archivo
 * @param QString path; ruta absoluta del archivo a crear
 * @param bool p: bandera
 * @param int size: Tamano en bytes del archivo
 * @param QString cont:
 * @return 0 = ya existe
 *       | 1 = archivo creado exitosamente
 *       | 2 = error por permisos
 *       | 3 = error archivo contenido no existe
 *       | 4 = error no existe el la ruta y no esta el parametro -p
*/
int nuevoArchivo(FILE *stream, char fit, bool flagP, char *path, int size, QString contenido, int index,char *auxPath){
    SuperBloque super;
    InodoTable inodo,inodoNuevo;
    BloqueCarpeta carpeta, carpetaNueva;
    BloqueApuntadores apuntadores;
    QList<string> lista = QList<string>();
    char copiaPath[500];
    char directorio[500];
    char nombreCarpeta[80];
    string content = "";
    string contentSize = "0123456789";

    strcpy(copiaPath,path);
    strcpy(directorio,dirname(copiaPath));
    strcpy(copiaPath,path);
    strcpy(nombreCarpeta,basename(copiaPath));
    strcpy(copiaPath,path);
    char *token = strtok(path,"/");
    int cont = 0;
    int numInodo = index;
    int finalSize = size;

    while(token != nullptr){
        cont++;
        lista.append(token);
        token = strtok(nullptr,"/");
    }

    if(contenido.length() != 0){
        FILE *archivoCont;
        if((archivoCont = fopen(contenido.toStdString().c_str(),"r"))){
            fseek(archivoCont,0,SEEK_END);
            finalSize = static_cast<int>(ftell(archivoCont));
            fseek(archivoCont,0,SEEK_SET);
            for (int i = 0; i < finalSize; i++)
                content += static_cast<char>(fgetc(archivoCont));
        }else
            return 3;
    }

    fseek(stream,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,stream);

    if(cont == 1){
        int libre = 0;
        int bloque = 0;
        int pointer = 0;
        int b_content = 0;
        fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
        fread(&inodo,sizeof(InodoTable),1,stream);
        //Buscamos un espacio libre en un bloque carpeta
        for(int i = 0; i < 15; i++){
            if(inodo.i_block[i] != -1){
                if(i == 12){
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*inodo.i_block[i],SEEK_SET);
                    fread(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                    for(int j = 0; j < 16; j++){
                        if(apuntadores.b_pointer[j] != -1){
                            fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*apuntadores.b_pointer[j],SEEK_SET);
                            fread(&carpeta,sizeof(BloqueCarpeta),1,stream);
                            for(int k = 0; k < 4; k++){
                                if(carpeta.b_content[k].b_inodo == -1){
                                    libre = 1;
                                    bloque = i;
                                    pointer = j;
                                    b_content = k;
                                    break;
                                }
                            }
                        }
                    }
                }else if(i == 13){

                }else if(i == 14){

                }else{
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*inodo.i_block[i],SEEK_SET);
                    fread(&carpeta,sizeof(BloqueCarpeta),1,stream);
                    for(int j = 0; j < 4; j++){
                        if(carpeta.b_content[j].b_inodo == -1){
                            libre = 1;
                            bloque = i;
                            b_content = j;
                            break;
                        }
                    }
                }
                if(libre == 1)
                    break;
            }
        }

        if(libre == 1){
            bool permisos = permisosDeEscritura(inodo.i_perm,(inodo.i_uid == currentSession.id_user),(inodo.i_gid == currentSession.id_grp));
            if(permisos || (currentSession.id_user == 1 && currentSession.id_grp == 1)){
                char buffer = '1';
                char buffer2 = '2';
                char buffer3 = '3';
                //Agregamos el archivo al bloque correspondiente
                int bitInodo = buscarBit(stream,'I',fit);
                carpeta.b_content[b_content].b_inodo = bitInodo;
                strcpy(carpeta.b_content[b_content].b_name,nombreCarpeta);
                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*inodo.i_block[bloque],SEEK_SET);
                fwrite(&carpeta,sizeof(BloqueCarpeta),1,stream);
                //Creamos el nuevo inodo archivo
                inodoNuevo.i_uid = currentSession.id_user;
                inodoNuevo.i_gid = currentSession.id_grp;
                inodoNuevo.i_size = 0;
                inodoNuevo.i_atime = time(nullptr);
                inodoNuevo.i_ctime = time(nullptr);
                inodoNuevo.i_mtime = time(nullptr);
                for(int i = 0; i < 15; i++)
                    inodoNuevo.i_block[i] = -1;
                inodoNuevo.i_type = '1';
                inodoNuevo.i_perm = 664;
                fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*bitInodo,SEEK_SET);
                fwrite(&inodoNuevo,sizeof(InodoTable),1,stream);
                //Registramos el inodo en el bitmap
                fseek(stream,super.s_bm_inode_start + bitInodo,SEEK_SET);
                fwrite(&buffer,sizeof(char),1,stream);
                //Si viene el parametro -size/-cont
                if(finalSize != 0){
                    double n = static_cast<double>(finalSize)/static_cast<double>(63);
                    int numBloques = static_cast<int>(ceil(n));
                    int caracteres = finalSize;
                    size_t charNum = 0;
                    size_t contChar = 0;
                    numInodo = buscarCarpetaArchivo(stream,auxPath);
                    for (int i = 0; i < numBloques; i++) {
                        BloqueArchivo archivo;
                        memset(archivo.b_content,0,sizeof(archivo.b_content));
                        if(i == 12){
                            int bitBloqueA = buscarBit(stream,'B',fit);//Apuntador
                            //Guardamos el bloque en el inodo archivo
                            fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                            fread(&inodo,sizeof(InodoTable),1,stream);
                            inodo.i_block[i] = bitBloqueA;
                            fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                            fwrite(&inodo,sizeof(InodoTable),1,stream);
                            //Registramos el bloque apuntador en el bitmap
                            fseek(stream,super.s_bm_block_start + bitBloqueA,SEEK_SET);
                            fwrite(&buffer3,sizeof(char),1,stream);
                            //Creamos el bloque de apuntadores como es simple solo se debe crear uno
                            int bitBloque = buscarBit(stream,'B',fit);//Primer bloque archivo
                            apuntadores.b_pointer[0] = bitBloque;
                            for(int i = 1; i < 16; i++)
                                apuntadores.b_pointer[i] = -1;
                            fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*bitBloqueA,SEEK_SET);
                            fwrite(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                            //Empezamos con la creacion de bloques archivos
                            //Registramos el primer bloque en el bitmap
                            fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                            fwrite(&buffer2,sizeof(char),1,stream);
                            if(caracteres > 63){
                                for(int j = 0; j < 63; j++){
                                    if(content.length() != 0){//-cont
                                        archivo.b_content[j] = content[contChar];
                                        contChar++;
                                    }else{//-size
                                        archivo.b_content[j] = contentSize[charNum];
                                        charNum++;
                                        if(charNum == 10)
                                            charNum = 0;
                                    }
                                }
                                //Guardamos el bloque
                                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                                caracteres -= 63;
                            }else{
                                for (int j = 0; j < caracteres; j++) {
                                    if(content.length() != 0){
                                        archivo.b_content[j] = content[contChar];
                                        contChar++;
                                    }else{
                                        archivo.b_content[j] = contentSize[charNum];
                                        charNum++;
                                        if(charNum == 10)
                                            charNum = 0;
                                    }
                                }
                                //Guardamos el bloque
                                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                            }
                        }else if(i > 12 && i < 28){
                            int libre = 0;
                            fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                            fread(&inodo,sizeof(InodoTable),1,stream);
                            fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*inodo.i_block[12],SEEK_SET);
                            fread(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                            for (int a = 0; a < 16; a++) {
                                if(apuntadores.b_pointer[a] == -1){
                                    libre = a;
                                    break;
                                }
                            }
                            int bitBloque = buscarBit(stream,'B',fit);
                            apuntadores.b_pointer[libre] = bitBloque;
                            fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*inodo.i_block[12],SEEK_SET);
                            fwrite(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                            //Registramos el bloque en el bitmap
                            fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                            fwrite(&buffer2,sizeof(char),1,stream);
                            if(caracteres > 63){
                                for(int j = 0; j < 63; j++){
                                    if(content.length() != 0){//-cont
                                        archivo.b_content[j] = content[contChar];
                                        contChar++;
                                    }else{//-size
                                        archivo.b_content[j] = contentSize[charNum];
                                        charNum++;
                                        if(charNum == 10)
                                            charNum = 0;
                                    }
                                }
                                //Guardamos el bloque
                                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                                caracteres -= 63;
                            }else{
                                for (int j = 0; j < caracteres; j++) {
                                    if(content.length() != 0){
                                        archivo.b_content[j] = content[contChar];
                                        contChar++;
                                    }else{
                                        archivo.b_content[j] = contentSize[charNum];
                                        charNum++;
                                        if(charNum == 10)
                                            charNum = 0;
                                    }
                                }
                                //Guardamos el bloque
                                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                            }
                        }else if(i == 29){//Apuntador doble

                        }else{
                            int bitBloque = buscarBit(stream,'B',fit);
                            //Registramos el bloque en el bitmap
                            fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                            fwrite(&buffer2,sizeof(char),1,stream);
                            if(caracteres > 63){
                                for(int j = 0; j < 63; j++){
                                    if(content.length() != 0){//-cont
                                        archivo.b_content[j] = content[contChar];
                                        contChar++;
                                    }else{//-size
                                        archivo.b_content[j] = contentSize[charNum];
                                        charNum++;
                                        if(charNum == 10)
                                            charNum = 0;
                                    }
                                }
                                //Guardamos el bloque en el respectivo inodo archivo
                                fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                fread(&inodo,sizeof(InodoTable),1,stream);
                                inodo.i_block[i] = bitBloque;
                                inodo.i_size = finalSize;
                                fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                fwrite(&inodo,sizeof(InodoTable),1,stream);
                                //Guardamos el bloque
                                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                                caracteres -= 63;
                            }else{
                                for (int j = 0; j < caracteres; j++) {
                                    if(content.length() != 0){
                                        archivo.b_content[j] = content[contChar];
                                        contChar++;
                                    }else{
                                        archivo.b_content[j] = contentSize[charNum];
                                        charNum++;
                                        if(charNum == 10)
                                            charNum = 0;
                                    }
                                }
                                //Guardamos el bloque en el respectivo inodo archivo
                                fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                fread(&inodo,sizeof(InodoTable),1,stream);
                                inodo.i_block[i] = bitBloque;
                                inodo.i_size = finalSize;
                                fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                fwrite(&inodo,sizeof(InodoTable),1,stream);
                                //Guardamos el bloque
                                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                            }
                        }
                    }
                    //Modificamos el super bloque
                    super.s_free_blocks_count = super.s_free_blocks_count - numBloques;
                    super.s_free_inodes_count = super.s_free_inodes_count - 1;
                    super.s_first_ino = super.s_first_ino + 1;
                    super.s_first_blo = super.s_first_blo + numBloques;
                    fseek(stream,currentSession.inicioSuper,SEEK_SET);
                    fwrite(&super,sizeof(SuperBloque),1,stream);
                    return 1;
                }
                super.s_free_inodes_count = super.s_free_inodes_count - 1;
                super.s_first_ino = super.s_first_ino + 1;
                fseek(stream,currentSession.inicioSuper,SEEK_SET);
                fwrite(&super,sizeof(SuperBloque),1,stream);
                return 1;
            }else
                return 2;
        }else{//Todos los bloques estan llenos
            fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
            fread(&inodo,sizeof(InodoTable),1,stream);
            for (int i = 0; i < 15; i++) {
                if(inodo.i_block[i] == -1){
                    bloque = i;
                    break;
                }
            }
            if(bloque == 12){//Apuntador simple indirecto
                bool permissions = permisosDeEscritura(inodo.i_perm,(inodo.i_uid == currentSession.id_user),(inodo.i_gid == currentSession.id_grp));
                if(permissions || (currentSession.id_user == 1 && currentSession.id_grp == 1) ){

                }else
                    return 2;
            }else if(bloque == 13){//Apuntador doble indirecto

            }else if(bloque == 14){//Apuntador triple indirecto

            }else{//Apuntadores directos
                bool permisos = permisosDeEscritura(inodo.i_perm,(inodo.i_uid == currentSession.id_user),(inodo.i_gid == currentSession.id_grp));
                if(permisos || (currentSession.id_user == 1 && currentSession.id_grp == 1)){
                    char buffer = '1';
                    char buffer2 = '2';
                    char buffer3 = '3';
                    int bitBloque = buscarBit(stream,'B',fit);
                    //Guardamos el bloque en el inodo
                    inodo.i_block[bloque] = bitBloque;
                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                    fwrite(&inodo,sizeof(InodoTable),1,stream);
                    //Creamos el nuevo bloque carpeta
                    int bitInodo = buscarBit(stream,'I',fit);
                    carpetaNueva.b_content[0].b_inodo = bitInodo;
                    carpetaNueva.b_content[1].b_inodo = -1;
                    carpetaNueva.b_content[2].b_inodo = -1;
                    carpetaNueva.b_content[3].b_inodo = -1;
                    strcpy(carpetaNueva.b_content[0].b_name,nombreCarpeta);
                    strcpy(carpetaNueva.b_content[1].b_name,"");
                    strcpy(carpetaNueva.b_content[2].b_name,"");
                    strcpy(carpetaNueva.b_content[3].b_name,"");
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*bitBloque,SEEK_SET);
                    fwrite(&carpetaNueva,sizeof(BloqueCarpeta),1,stream);
                    //Registramos el bloque en el bitmap
                    fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Creamos el nuevo inodo
                    inodoNuevo.i_uid = currentSession.id_user;
                    inodoNuevo.i_gid = currentSession.id_grp;
                    inodoNuevo.i_size = finalSize;
                    inodoNuevo.i_atime = time(nullptr);
                    inodoNuevo.i_ctime = time(nullptr);
                    inodoNuevo.i_mtime = time(nullptr);
                    for (int i = 0; i < 15; i++)
                        inodoNuevo.i_block[i] = -1;
                    inodoNuevo.i_type = '1';
                    inodoNuevo.i_perm = 664;
                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*bitInodo,SEEK_SET);
                    fwrite(&inodoNuevo,sizeof(InodoTable),1,stream);
                    //Registramos el inodo en el bitmap
                    fseek(stream,super.s_bm_inode_start + bitInodo,SEEK_SET);
                    fwrite(&buffer,sizeof(char),1,stream);
                    //Si viene el parametro -size/-cont
                    if(finalSize != 0){
                        double n = static_cast<double>(finalSize)/static_cast<double>(63);
                        int numBloques = static_cast<int>(ceil(n));
                        int caracteres = finalSize;
                        size_t charNum = 0;
                        size_t contChar = 0;
                        numInodo = buscarCarpetaArchivo(stream,auxPath);
                        for (int i = 0; i < numBloques; i++) {
                            BloqueArchivo archivo;
                            memset(archivo.b_content,0,sizeof(archivo.b_content));
                            if(i == 12){
                                int bitBloqueA = buscarBit(stream,'B',fit);//Apuntador
                                //Guardamos el bloque en el inodo archivo
                                fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                fread(&inodo,sizeof(InodoTable),1,stream);
                                inodo.i_block[i] = bitBloqueA;
                                fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                fwrite(&inodo,sizeof(InodoTable),1,stream);
                                //Registramos el bloque apuntador en el bitmap
                                fseek(stream,super.s_bm_block_start + bitBloqueA,SEEK_SET);
                                fwrite(&buffer3,sizeof(char),1,stream);
                                //Creamos el bloque de apuntadores como es simple solo se debe crear uno
                                int bitBloque = buscarBit(stream,'B',fit);//Primer bloque archivo
                                apuntadores.b_pointer[0] = bitBloque;
                                for(int i = 1; i < 16; i++)
                                    apuntadores.b_pointer[i] = -1;
                                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*bitBloqueA,SEEK_SET);
                                fwrite(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                                //Empezamos con la creacion de bloques archivos
                                //Registramos el primer bloque en el bitmap
                                fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                                fwrite(&buffer2,sizeof(char),1,stream);
                                if(caracteres > 63){
                                    for(int j = 0; j < 63; j++){
                                        if(content.length() != 0){//-cont
                                            archivo.b_content[j] = content[contChar];
                                            contChar++;
                                        }else{//-size
                                            archivo.b_content[j] = contentSize[charNum];
                                            charNum++;
                                            if(charNum == 10)
                                                charNum = 0;
                                        }
                                    }
                                    //Guardamos el bloque
                                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                    fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                                    caracteres -= 63;
                                }else{
                                    for (int j = 0; j < caracteres; j++) {
                                        if(content.length() != 0){
                                            archivo.b_content[j] = content[contChar];
                                            contChar++;
                                        }else{
                                            archivo.b_content[j] = contentSize[charNum];
                                            charNum++;
                                            if(charNum == 10)
                                                charNum = 0;
                                        }
                                    }
                                    //Guardamos el bloque
                                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                    fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                                }
                            }else if(i > 12 && i < 28){
                                int libre = 0;
                                fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                fread(&inodo,sizeof(InodoTable),1,stream);
                                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*inodo.i_block[12],SEEK_SET);
                                fread(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                                for (int a = 0; a < 16; a++) {
                                    if(apuntadores.b_pointer[a] == -1){
                                        libre = a;
                                        break;
                                    }
                                }
                                int bitBloque = buscarBit(stream,'B',fit);
                                apuntadores.b_pointer[libre] = bitBloque;
                                fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueApuntadores))*inodo.i_block[12],SEEK_SET);
                                fwrite(&apuntadores,sizeof(BloqueApuntadores),1,stream);
                                //Registramos el bloque en el bitmap
                                fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                                fwrite(&buffer2,sizeof(char),1,stream);
                                if(caracteres > 63){
                                    for(int j = 0; j < 63; j++){
                                        if(content.length() != 0){//-cont
                                            archivo.b_content[j] = content[contChar];
                                            contChar++;
                                        }else{//-size
                                            archivo.b_content[j] = contentSize[charNum];
                                            charNum++;
                                            if(charNum == 10)
                                                charNum = 0;
                                        }
                                    }
                                    //Guardamos el bloque
                                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                    fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                                    caracteres -= 63;
                                }else{
                                    for (int j = 0; j < caracteres; j++) {
                                        if(content.length() != 0){
                                            archivo.b_content[j] = content[contChar];
                                            contChar++;
                                        }else{
                                            archivo.b_content[j] = contentSize[charNum];
                                            charNum++;
                                            if(charNum == 10)
                                                charNum = 0;
                                        }
                                    }
                                    //Guardamos el bloque
                                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                    fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                                }

                            }else if(i == 29){//Apuntador doble

                            }else{//Apuntadores simples
                                int bitBloque = buscarBit(stream,'B',fit);
                                //Registramos el bloque en el bitmap
                                fseek(stream,super.s_bm_block_start + bitBloque,SEEK_SET);
                                fwrite(&buffer2,sizeof(char),1,stream);
                                if(caracteres > 63){
                                    for(int j = 0; j < 63; j++){
                                        if(content.length() != 0){//-cont
                                            archivo.b_content[j] = content[contChar];
                                            contChar++;
                                        }else{//-size
                                            archivo.b_content[j] = contentSize[charNum];
                                            charNum++;
                                            if(charNum == 10)
                                                charNum = 0;
                                        }
                                    }
                                    //Guardamos el bloque en el respectivo inodo archivo
                                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                    fread(&inodo,sizeof(InodoTable),1,stream);
                                    inodo.i_block[i] = bitBloque;
                                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                    fwrite(&inodo,sizeof(InodoTable),1,stream);
                                    //Guardamos el bloque
                                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                    fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                                    caracteres -= 63;
                                }else{
                                    for (int j = 0; j < caracteres; j++) {
                                        if(content.length() != 0){
                                            archivo.b_content[j] = content[contChar];
                                            contChar++;
                                        }else{
                                            archivo.b_content[j] = contentSize[charNum];
                                            charNum++;
                                            if(charNum == 10)
                                                charNum = 0;
                                        }
                                    }
                                    //Guardamos el bloque en el respectivo inodo archivo
                                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                    fread(&inodo,sizeof(InodoTable),1,stream);
                                    inodo.i_block[i] = bitBloque;
                                    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*numInodo,SEEK_SET);
                                    fwrite(&inodo,sizeof(InodoTable),1,stream);
                                    //Guardamos el bloque
                                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueArchivo))*bitBloque,SEEK_SET);
                                    fwrite(&archivo,sizeof(BloqueArchivo),1,stream);
                                }
                            }
                        }
                        //Modificamos el super bloque
                        super.s_free_blocks_count = super.s_free_blocks_count - numBloques;
                        super.s_free_inodes_count = super.s_free_inodes_count - 1;
                        super.s_first_ino = super.s_first_ino + 1;
                        super.s_first_blo = super.s_first_blo + numBloques;
                        fseek(stream,currentSession.inicioSuper,SEEK_SET);
                        fwrite(&super,sizeof(SuperBloque),1,stream);
                        return 1;
                    }
                    super.s_free_inodes_count = super.s_free_inodes_count - 1;
                    super.s_first_ino = super.s_first_ino + 1;
                    fseek(stream,currentSession.inicioSuper,SEEK_SET);
                    fwrite(&super,sizeof(SuperBloque),1,stream);
                    return 1;
                }else
                    return 2;
            }
        }
    }else{//Directorio
        int existe = buscarCarpetaArchivo(stream,directorio);
        if(existe == -1){
            if(flagP){
                int index = 0;
                string aux = "";
                //Crear posibles carpetas inexistentes
                for (int i = 0; i < cont; i++) {
                    if(i == cont -1){
                        char dir[100] = "/";
                        strcat(dir,nombreCarpeta);
                        return nuevoArchivo(stream,fit,false,dir,size,contenido,index,auxPath);
                    }else{
                        aux += "/"+lista.at(i);
                        char dir[500];
                        char auxDir[500];
                        strcpy(dir,aux.c_str());
                        strcpy(auxDir,aux.c_str());
                        int carpeta = buscarCarpetaArchivo(stream,dir);
                        if(carpeta == -1){
                            nuevaCarpeta(stream,fit,false,auxDir,index);
                            strcpy(auxDir,aux.c_str());
                            index = buscarCarpetaArchivo(stream,auxDir);
                        }else
                            index = carpeta;
                    }
                }
            }else
                return 4;
        }else{//Crear el archivo en el directorio
            char dir[100] = "/";
            strcat(dir,nombreCarpeta);
            return nuevoArchivo(stream,fit,false,dir,size,contenido,existe,auxPath);
        }
    }

    return 0;
}

/* Metodo para eliminar una carpeta o archivo
 * @param FILE *stream: Fichero donde se esta leyendo actualmente
 * @param int n: Numero de inodo de la carpeta/archivo
*/
void eliminarCarpetaArchivo(FILE *stream, int n){
    SuperBloque super;
    InodoTable inodo;
    char buffer = '0';

    fseek(stream,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,stream);
    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*n,SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,stream);

    if(inodo.i_type == '0'){//Carpeta
        for (int i = 0; i < 12; i++) {
            if(inodo.i_block[i] != -1){
                char byte = '0';
                fseek(stream,super.s_bm_block_start + inodo.i_block[i],SEEK_SET);
                byte = static_cast<char>(fgetc(stream));
                if(byte == '1'){//Bloque carpeta
                    BloqueCarpeta carpeta;
                    fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*inodo.i_block[i],SEEK_SET);
                    fread(&carpeta,sizeof(BloqueCarpeta),1,stream);
                    for (int j = 0; j < 4; j++) {
                        if(carpeta.b_content[j].b_inodo != -1){
                            if(strcmp(carpeta.b_content[j].b_name,".")!=0 && strcmp(carpeta.b_content[j].b_name,"..")!=0)
                                eliminarCarpetaArchivo(stream,carpeta.b_content[j].b_inodo);
                        }
                    }
                    fseek(stream,super.s_bm_block_start + inodo.i_block[i],SEEK_SET);
                    fputc(buffer,stream);
                }
            }
        }
        //Eliminar inodo del bitmap
        fseek(stream,super.s_bm_inode_start + n,SEEK_SET);
        fputc(buffer,stream);
    }else{//Archivo
        //Eliminar bloques del bitmap
        for (int i = 0; i < 15; i++) {
            if(inodo.i_block[i] != -1){
                fseek(stream,super.s_bm_block_start + inodo.i_block[i],SEEK_SET);
                fputc(buffer,stream);
            }
        }
        //Eliminar inodo del bitmap
        fseek(stream,super.s_bm_inode_start + n,SEEK_SET);
        fputc(buffer,stream);
    }

}

/* Funcion para verificar la existencia de una carpeta o archivo
 * @param FILE *stream = Archivo en el cual se encuentra la particion
 * @param char* path = direccion de la carpeta o archivo
 * @return el numero de inodo en el que se encuentra la carpeta o archivo | -1 si no existe
*/
int buscarCarpetaArchivo(FILE *stream, char* path){
    SuperBloque super;
    InodoTable inodo;
    BloqueCarpeta carpeta;

    QList<string> lista = QList<string>();
    char *token = strtok(path,"/");
    int cont = 0;
    int numInodo = 0;

    while(token != nullptr){
        lista.append(token);
        cont++;
        token = strtok(nullptr,"/");
    }

    fseek(stream,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,stream);
    numInodo = super.s_inode_start;//Inodo 0 '/'

    for (int cont2 = 0; cont2 < cont; cont2++) {
        fseek(stream,numInodo,SEEK_SET);
        fread(&inodo,sizeof(InodoTable),1,stream);
        int siguiente = 0;
        for(int i = 0; i < 12; i++){
            if(inodo.i_block[i] != -1){
                int byteBloque = byteInodoBloque(stream,inodo.i_block[i],'2');
                fseek(stream,byteBloque,SEEK_SET);
                fread(&carpeta,sizeof(BloqueCarpeta),1,stream);
                for (int j = 0; j < 4; j++) {
                    if((cont2 == cont - 1) && (strcasecmp(carpeta.b_content[j].b_name,lista.at(cont2).c_str()) == 0)){//Tendria que ser la carpeta
                        return carpeta.b_content[j].b_inodo;
                    }else if((cont2 != cont - 1) && (strcasecmp(carpeta.b_content[j].b_name,lista.at(cont2).c_str()) == 0)){
                        numInodo = byteInodoBloque(stream,carpeta.b_content[j].b_inodo,'1');
                        siguiente = 1;
                        break;
                    }
                }
                if(siguiente == 1)
                    break;
            }
        }
    }

    return -1;
}

/* Metodo para obtener el bloque y la posicion en el bloque donde se encuentra la carpeta/archivo
 * @param FILE *stream = Archivo en el cual se encuentra la particion
 * @param char* path = direccion de la carpeta o archivo
 * @param int &block = Variable donde se almacenara el bloque donde se encuentra la carpeta/archivo
 * @param int &posicion = Variable donde se almacenara la posicion en el bloque donde se encuentra la carpeta/archivo
 * Los ultimos dos parametros son por referencia porque se modificara su valor
*/
void bloqueCarpetaArchivo(FILE *stream, char* path, int &block, int &posicion){
    SuperBloque super;
    InodoTable inodo;
    BloqueCarpeta carpeta;

    QList<string> lista = QList<string>();
    char *token = strtok(path,"/");
    int cont = 0;
    int numInodo = 0;

    while(token != nullptr){
        lista.append(token);
        cont++;
        token = strtok(nullptr,"/");
    }

    fseek(stream,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,stream);
    numInodo = super.s_inode_start;//Inodo 0 '/'

    for (int cont2 = 0; cont2 < cont; cont2++) {
        fseek(stream,numInodo,SEEK_SET);
        fread(&inodo,sizeof(InodoTable),1,stream);
        int siguiente = 0;
        for(int i = 0; i < 12; i++){
            if(inodo.i_block[i] != -1){
                int byteBloque = byteInodoBloque(stream,inodo.i_block[i],'2');
                fseek(stream,byteBloque,SEEK_SET);
                fread(&carpeta,sizeof(BloqueCarpeta),1,stream);
                for (int j = 0; j < 4; j++) {
                    if((cont2 == cont - 1) && (strcasecmp(carpeta.b_content[j].b_name,lista.at(cont2).c_str()) == 0)){//Tendria que ser la carpeta
                        block = inodo.i_block[i];
                        posicion = j;
                    }else if((cont2 != cont - 1) && (strcasecmp(carpeta.b_content[j].b_name,lista.at(cont2).c_str()) == 0)){
                        numInodo = byteInodoBloque(stream,carpeta.b_content[j].b_inodo,'1');
                        siguiente = 1;
                        break;
                    }
                }
                if(siguiente == 1)
                    break;
            }
        }
    }


}

/* Funcion que retorna el byte donde inicia un bloque o inodo
 * @param FILE stream: Archivo en el cual se encuentra la particion
 * @param int pos: Numero o posicion del bloque/Inodo a buscar
 * @param char tipo: '1'=Inodo | '2'=Bloque
 * @return numero de byte
*/
int byteInodoBloque(FILE *stream,int pos, char tipo){
    SuperBloque super;
    fseek(stream,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,stream);
    if(tipo == '1'){
        return (super.s_inode_start + static_cast<int>(sizeof(InodoTable))*pos);
    }else if(tipo == '2')
        return (super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*pos);
    return 0;
}

/* Funcion para verificar si el usuario actual tiene permisos para crear
 * una carpeta o archivo en la carpeta padre
 * @param int permisos = permisos del inodo
 * @param bool flagUser = bandera que indica si es el propietario de la carpeta padre
 * @param bool flagGroup = bandera que indica si el usuario actual pertenece al grupo de la carpeta padre
 * @return true = si tiene permisos | false = no tiene permisos
*/
bool permisosDeEscritura(int permisos, bool flagUser, bool flagGroup){
    string aux = to_string(permisos);
    char propietario = aux[0];
    char grupo = aux[1];
    char otros = aux[2];

    if((propietario == '2' || propietario == '3' || propietario == '6' || propietario || '7') && flagUser)
        return true;
    else if((grupo == '2' || grupo == '3' || grupo == '6' || grupo == '7') && flagGroup)
        return true;
    else if(otros == '2' || otros == '3' || otros == '6' || otros == '7')
        return true;

    return false;
}

/* Funcion para verificar si el usuario actual tiene permisos para leer
 * una carpeta o archivo en la carpeta padre
 * @param int permisos = permisos del inodo
 * @param bool flagUser = bandera que indica si es el propietario de la carpeta padre
 * @param bool flagGroup = bandera que indica si el usuario actual pertenece al grupo de la carpeta padre
 * @return true = si tiene permisos | false = no tiene permisos
*/
bool permisosDeLectura(int permisos, bool flagUser, bool flagGroup){
    string aux = to_string(permisos);
    int propietario = static_cast<int>(aux[0]);
    int grupo = static_cast<int>(aux[1]);
    int otros = static_cast<int>(aux[2]);

    if((propietario >= 3) && flagUser)
        return true;
    else if((grupo >= 3) && flagGroup)
        return true;
    else if(otros >= 3)
        return true;

    return false;
}

/* Funcion para verificar si el usuario actual tiene permisos para borrar una carpeta/archivo
 * Si es una carpeta padre tiene que tener permisos para poder borrar todas las hijas
 * @param FILE* stream = fichero que se esta leyendo
 * @param int n = numero de inodo de la carpeta/archivo
 * @return true = si tiene permisos | false = no tiene permisos
*/
bool permisosEscrituraRecursivo(FILE* stream, int n){
    SuperBloque super;
    InodoTable inodo;


    fseek(stream,currentSession.inicioSuper,SEEK_SET);
    fread(&super,sizeof(SuperBloque),1,stream);
    fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*n,SEEK_SET);
    fread(&inodo,sizeof(InodoTable),1,stream);

    bool permisos = permisosDeEscritura(inodo.i_perm,(inodo.i_uid == currentSession.id_user),(inodo.i_gid == currentSession.id_grp));
    if(permisos){
        bool response = true;
        if(inodo.i_type == '0'){//carpeta
            for (int i = 0; i < 12; i++) {//Solo apuntadores directos-falta revisar indirectos
                if(inodo.i_block[i] != -1){
                    char byte = '0';
                    fseek(stream,super.s_bm_block_start + inodo.i_block[i],SEEK_SET);
                    byte = static_cast<char>(fgetc(stream));
                    if(byte == '1'){//Carpeta
                        BloqueCarpeta carpeta;
                        fseek(stream,super.s_block_start + static_cast<int>(sizeof(BloqueCarpeta))*inodo.i_block[i],SEEK_SET);
                        fread(&carpeta,sizeof(BloqueCarpeta),1,stream);
                        for (int j = 0; j < 4; j++) {
                            if(carpeta.b_content[j].b_inodo != -1){
                                if(strcmp(carpeta.b_content[j].b_name,".")!=0 && strcmp(carpeta.b_content[j].b_name,"..")!=0)
                                    response = permisosEscrituraRecursivo(stream,carpeta.b_content[j].b_inodo);
                            }
                        }
                    }else{//Archivo
                        InodoTable inodoAux;
                        fseek(stream,super.s_inode_start + static_cast<int>(sizeof(InodoTable))*inodo.i_block[i],SEEK_SET);
                        fread(&inodoAux,sizeof(InodoTable),1,stream);
                        response = permisosDeEscritura(inodoAux.i_perm,(inodoAux.i_uid == currentSession.id_user),(inodoAux.i_gid == currentSession.id_grp));
                    }
                }
            }
            return response;
        }else //archivo
            return true;
    }else
        return false;
}

