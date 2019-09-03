#include "nodo.h"

Nodo::Nodo(QString t, QString v){
    tipo =t;
    valor = v;
    tipo_ = getTipo();
    hijos = QList<Nodo>();
}

int Nodo::getTipo()
{
    if(this->tipo=="MKDISK")return 1;
    if(this->tipo=="RMDISK")return 2;
    if(this->tipo=="FDISK")return 3;
    if(this->tipo=="MOUNT")return 4;
    if(this->tipo=="UNMOUNT")return 5;
    if(this->tipo=="REP")return 6;
    if(this->tipo=="PARAMETRO")return 7;
    if(this->tipo=="EXEC")return 8;
    if(this->tipo=="size")return 9;
    if(this->tipo=="fit")return 10;
    if(this->tipo=="unit")return 11;
    if(this->tipo=="path")return 12;
    if(this->tipo=="type")return 13;
    if(this->tipo=="delete")return 14;
    if(this->tipo=="name")return 15;
    if(this->tipo=="add")return 16;
    if(this->tipo == "id")return 17;
    return 0;
}

void Nodo::add(Nodo n){
    hijos.append(n);
}
