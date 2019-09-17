#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <qstring.h>
#include "nodo.h"
#include "structs.h"
#include "listamount.h"
#include "disco.h"

/*Variables globales*/
ListaMount *lista = new ListaMount();
Disco *disco = new Disco();
Sesion currentSession;
bool flag_global = true;
bool flag_login = false;

/* Declaracion de metodos y funciones */
void imprimirEncabezado();
void reconocerComando(Nodo*);
void recorrerMKDISK(Nodo*);
void recorrerRMDISK(Nodo*);
void recorrerFDISK(Nodo*);
void recorrerMOUNT(Nodo*);
void recorrerUNMOUNT(Nodo*);
void recorrerREP(Nodo*);
void recorrerEXEC(Nodo*);
void recorrerMKFS(Nodo*);
void recorrerLOGIN(Nodo*);
void recorrerMKGRP(Nodo*);
void recorrerRMGRP(Nodo*);
void recorrerMKUSR(Nodo*);
void recorrerRMUSR(Nodo*);
void recorrerCHMOD(Nodo*);
void recorrerMKFILE(Nodo*);
void recorrerCAT(Nodo*);
void recorrerREM(Nodo*);
void recorrerEDIT(Nodo*);
void recorrerREN(Nodo*);
void recorrerMKDIR(Nodo*);
void recorrerCP(Nodo*);
void recorrerMV(Nodo*);
void recorrerFIND(Nodo*);
void recorrerCHOWN(Nodo*);
void recorrerCHGRP(Nodo*);
void recorrerRECOVERY(Nodo*);
void recorrerLOSS(Nodo*);
void crearArchivo(QString);
void leerComando(char*);
QString getDirectorio(QString);
QString getExtension(QString);
QString getFileName(QString);

void formatearEXT2(int,int,QString);
void formatearEXT3(int,int,QString);
int log_in(QString, QString, QString, QString);
int verificarDatos(QString,QString,QString);
void log_out();
int buscarGrupo(QString);
int getID_grp();
void agregarUsersTXT(QString);
char getLogicFit(QString,QString);
int buscarBit(FILE*,char,char);
void eliminarGrupo(QString);
bool buscarUsuario(QString);
int getID_usr();
void eliminarUsuario(QString);
int crearCarpeta(QString, bool);
bool buscarCarpetaArchivo(FILE*,char*);
int byteInodoBloque(FILE *,int,char);
int nuevaCarpeta(FILE*,char,bool,char*);
bool permisos(int,bool,bool);

#endif // MAINHEADER_H
