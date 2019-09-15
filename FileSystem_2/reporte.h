#ifndef REPORTE_H
#define REPORTE_H

#include <QString>
#include <string>
#include <iostream>
#include "structs.h"

using namespace std;

class Reporte
{
public:
    Reporte();
    void graficarMBR(QString, QString, QString);
    void graficarDisco(QString, QString, QString);
    void graficarInodos(QString,QString,QString,int,int,int);
    void graficarBloques(QString,QString,QString,int,int,int);
};

#endif // REPORTE_H
