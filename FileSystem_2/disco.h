#ifndef DISCO_H
#define DISCO_H

#include <QString>
#include <string>
#include <iostream>
#include "structs.h"

using namespace std;

class Disco
{
public:
    Disco();
    void crearParticionPrimaria(QString, QString, int, char, char, QString);
    void crearParticionExtendida(QString, QString, int, char, char, QString);
    void crearParticionLogica(QString, QString, int, char, char, QString) ;
    void eliminarParticion(QString, QString, QString, QString);
    void agregarQuitarParticion(QString, QString ,int ,char,QString);
    bool existeParticion(QString, QString);
    int buscarParticion_P_E(QString, QString);
    int buscarParticion_L(QString, QString);
};

#endif // DISCO_H
