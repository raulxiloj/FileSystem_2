#ifndef LISTAMOUNT_H
#define LISTAMOUNT_H

#include <iostream>

#include "nodomount.h"

using namespace std;

class ListaMount
{
public:
    NodoMount *primero;
    ListaMount();
    int buscarLetra(QString direccion, QString nombre);
    int buscarNumero(QString direccion, QString nombre);
    void mostrarLista();
    void insertarNodo(NodoMount*);
    int eliminarNodo(QString);
    bool buscarNodo(QString, QString);
    QString getDireccion(QString);
    NodoMount* getNodo(QString);
};

#endif // LISTAMOUNT_H
