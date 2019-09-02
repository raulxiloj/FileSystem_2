#ifndef NODO_H
#define NODO_H

#include <qstring.h>
#include <QList>

class Nodo
{
public:
    Nodo(QString tipo, QString valor);
    QString tipo;
    QString valor;
    int linea;
    int columna;
    int tipo_; // Este nos servirá para la ejecución, ya que aquí no hay swicht(QString); vamos a hacer un Swicht(int);
    QString cadenaDot;
    QList<Nodo> hijos;
    int getTipo();
    void add(Nodo n);
};

#endif // NODO_H
