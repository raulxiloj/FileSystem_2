#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <qstring.h>
#include "nodo.h"
#include "structs.h"
#include "listamount.h"
#include "disco.h"

/*Variables globales*/
ListaMount *lista = new ListaMount();
Disco disco;
Sesion currentSession;
bool flag_global = true;
bool flag_login = false;

/* Declaracion de metodos y funciones */
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
void leerComando(char*);
void crearDisco(QString);
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
int nuevaCarpeta(FILE*,char,bool,char*,int);
int crearArchivo(QString,bool,int,QString);
int nuevoArchivo(FILE*,char,bool,char*,int,QString,int,char*);
int buscarCarpetaArchivo(FILE*,char*);
void bloqueCarpetaArchivo(FILE*,char*,int&,int&,int&,int&);
int byteInodoBloque(FILE*,int,char);
bool permisosDeEscritura(int,bool,bool);
bool permisosDeLectura(int,bool,bool);
bool permisosEscrituraRecursivo(FILE*,int);
bool permisosLecturaRecursivo(FILE*,int);
void eliminarCarpetaArchivo(FILE*,int);
void moverCarpetaArchivo(FILE*,int,char*,int);
void cambiarPermisosRecursivo(FILE*,int,int);
void guardarJournal(char*,int,int,char*,char*);
void systemLoss(QString);
void systemRecovery(QString);
Usuario getUsuario(QString,int,int);
bool isNumber(string);
InodoTable crearInodo(int,char,int);
BloqueCarpeta crearBloqueCarpeta();
int buscarContentLibre(FILE*,int,InodoTable&,BloqueCarpeta&,BloqueApuntadores&,int&,int&,int&);

#endif // MAINHEADER_H
