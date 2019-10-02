#include "nodo.h"

Nodo::Nodo(QString t, QString v){
    tipo =t;
    valor = v;
    tipo_ = getTipo();
    hijos = QList<Nodo>();
}

int Nodo::getTipo()
{
    if(this->tipo == "MKDISK")     return 1;
    if(this->tipo == "RMDISK")     return 2;
    if(this->tipo == "FDISK")      return 3;
    if(this->tipo == "MOUNT")      return 4;
    if(this->tipo == "UNMOUNT")    return 5;
    if(this->tipo == "REP")        return 6;
    if(this->tipo == "PARAMETRO")  return 7;
    if(this->tipo == "EXEC")       return 8;
    if(this->tipo == "size")       return 9;
    if(this->tipo == "fit")        return 10;
    if(this->tipo == "unit")       return 11;
    if(this->tipo == "path")       return 12;
    if(this->tipo == "type")       return 13;
    if(this->tipo == "delete")     return 14;
    if(this->tipo == "name")       return 15;
    if(this->tipo == "add")        return 16;
    if(this->tipo == "id")         return 17;

    if(this->tipo == "MKFS")       return 18;
    if(this->tipo == "LOGIN")      return 19;
    if(this->tipo == "LOGOUT")     return 20;
    if(this->tipo == "MKGRP")      return 21;
    if(this->tipo == "RMGRP")      return 22;
    if(this->tipo == "MKUSR")      return 23;
    if(this->tipo == "RMUSR")      return 24;
    if(this->tipo == "CHMOD")      return 25;
    if(this->tipo == "MKFILE")     return 26;
    if(this->tipo == "CAT")        return 27;
    if(this->tipo == "REM")        return 28;
    if(this->tipo == "EDIT")       return 29;
    if(this->tipo == "REN")        return 30;
    if(this->tipo == "MKDIR")      return 31;
    if(this->tipo == "CP")         return 32;
    if(this->tipo == "MV")         return 33;
    if(this->tipo == "FIND")       return 34;
    if(this->tipo == "CHOWN")      return 35;
    if(this->tipo == "CHGRP")      return 36;
    if(this->tipo == "PAUSE")      return 37;
    if(this->tipo == "RECOVERY")   return 38;
    if(this->tipo == "LOSS")       return 39;
    if(this->tipo == "fs")         return 40;
    if(this->tipo == "user")       return 41;
    if(this->tipo == "password")   return 42;
    if(this->tipo == "group")      return 43;
    if(this->tipo == "ugo")        return 44;
    if(this->tipo == "cont")       return 45;
    if(this->tipo == "file")       return 46;
    if(this->tipo == "p")          return 47;
    if(this->tipo == "dest")       return 48;
    if(this->tipo == "r")          return 49;
    if(this->tipo == "inode")      return 50;
    if(this->tipo == "journaling") return 51;
    if(this->tipo == "block")      return 52;
    if(this->tipo == "bm_inode")   return 53;
    if(this->tipo == "bm_block")   return 54;
    if(this->tipo == "tree")       return 55;
    if(this->tipo == "sb")         return 56;
    if(this->tipo == "ruta")       return 57;
    return 0;
}

void Nodo::add(Nodo n){
    hijos.append(n);
}
