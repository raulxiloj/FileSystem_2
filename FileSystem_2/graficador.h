#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include "nodo.h"

class Graficador
{
public:
    //Constructor
    Graficador(Nodo *root);
    //Atributos
    Nodo *raiz;
    QString dot;
    int cont;
    //Metodos, funciones
    QString generarCodigoGraphviz();
    QString limpiarString(QString str);
    void recorrerAST(QString padre, Nodo *hijo);
    void generarImagen();
};

#endif // GRAFICADOR_H
