#include "listamount.h"

ListaMount::ListaMount(){
    primero = nullptr;
}

/* Metodo para insertar al final de la lista
 * @param NodoMount nuevo: El nodo a insertar
*/
void ListaMount::insertarNodo(NodoMount *nuevo){
    NodoMount *aux = primero;
    if(primero == nullptr){
        primero = nuevo;
    }else{
        while(aux->siguiente!=nullptr){
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }

}

/* Funcion para eliminar un nodo de la lista
 * @param QString ID: identificador
 * @return 1 = se elimino exitosamente | 0 = No se encontro el nodo
*/
int ListaMount::eliminarNodo(QString ID){
    NodoMount *aux = primero;
    QString tempID = "vd";
    tempID += aux->letra + QString::number(aux->num);
    if(ID == tempID){
        primero = aux->siguiente;
        free(aux);
        return 1;
    }else{
        NodoMount *aux2 = nullptr;
        while(aux!=nullptr){
            tempID = "vd";
            tempID += aux->letra + QString::number(aux->num);
            if(ID == tempID){
                aux2->siguiente = aux->siguiente;
                return 1;
            }
            aux2 = aux;
            aux = aux->siguiente;
        }
    }
    return 0;
}

/* Funcion para verificar que letra asignarle al id de un nodo
 * @param QString direccion: Ruta del disco
 * @param QString nombre: nombre de la particion
 * @return -1 = ya esta montada | # = letra
*/
int ListaMount::buscarLetra(QString direccion, QString nombre){
    NodoMount *aux = primero;
    int retorno = 'a';
    while(aux!=NULL){
        if((direccion == aux->direccion) && (nombre == aux->nombre)){
            return -1;
        }else{
            if(direccion == aux->direccion){
                return aux->letra;
            }else if(retorno <= aux->letra){
                retorno++;
            }
        }
        aux = aux->siguiente;
    }
    return retorno;
}

/* Funcion para verificar que numero asignarle al id de un nodo
 * @param QString direccion: Ruta del disco
 * @param QString nombre: nombre de la particion
 * @return retorno = numero a asignar
*/
int ListaMount::buscarNumero(QString direccion, QString nombre){
    int retorno = 1;
    NodoMount *aux = primero;
    while(aux!=nullptr){
        if((direccion == aux->direccion) && (retorno == aux->num)){
            retorno++;
        }
        aux = aux->siguiente;
    }
    return retorno;
}

/* Funcion que retorna un booleano para verificar si existe un nodo
 * @param QString direccion: direccion del disco
 * @param QString nombre: nombre de la particion
 * @return true = si lo encuentra | false = si no lo encuentra
*/
bool ListaMount::buscarNodo(QString direccion, QString nombre){
    NodoMount *aux = primero;
    while(aux!=nullptr){
        if((aux->direccion == direccion) && (aux->nombre == nombre)){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

/* Funcion que retorna un nodo de la lista para verificar si una particion esta montada
 * @param QString id: identificador de la particion
 * @return aux = si lo encontro | nullptr = no lo encuentra
*/
NodoMount* ListaMount::getNodo(QString id){
    NodoMount *aux = primero;
    while(aux!=nullptr){
        QString tempID = "vd";
        tempID += aux->letra + QString::number(aux->num);
        if(id == tempID){
            return aux;
        }
        aux = aux->siguiente;
    }
    return nullptr;
}

/* Metodo para desplegar las particiones montadas
*/
void ListaMount::mostrarLista(){
    cout << "---------------------------------" << endl;
    cout << "|       Particiones montadas    |" << endl;
    cout << "---------------------------------" << endl;
    cout << "|      Nombre    |    ID        |" << endl;
    cout << "---------------------------------" << endl;
    NodoMount *aux = primero;
    while(aux!=nullptr){
        cout << "|     "<< aux->nombre.toStdString() << "          " << "vd"<<aux->letra<<aux->num << endl;
        cout << "---------------------------------" << endl;
        aux = aux->siguiente;
    }
}
