#ifndef NODOMOUNT_H
#define NODOMOUNT_H

#include <qstring.h>

class NodoMount
{
public:
    NodoMount(QString, QString, char, int);
    QString direccion;
    QString nombre;
    char letra;
    int num;
    NodoMount *siguiente;
};

#endif // NODOMOUNT_H
