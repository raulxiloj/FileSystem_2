#include "graficador.h"

#include <fstream>
#include <iostream>

Graficador::Graficador(Nodo *r)
{
    raiz = r;
    dot = "";
    cont = 0;
}

QString Graficador::generarCodigoGraphviz(){
    dot = "digraph G{\n";
    dot += "node [shape=\"box\"]\n";
    dot += "NodoAST0[label=\"" + limpiarString(""+raiz->tipo+" "+raiz->valor)+ "\"];\n";
    cont = 1;
    recorrerAST("NodoAST0",raiz);
    dot += "}";
    return dot;
}

void Graficador::recorrerAST(QString padre, Nodo *hijo){
    for(int i = 0; i < hijo->hijos.count(); i++)
    {
        Nodo nodoAST = hijo->hijos[i];
        QString nombreHijo = "NodoAST" +QString::number(cont);
        dot += nombreHijo + "[label= \"" +limpiarString("" +nodoAST.tipo + " " + nodoAST.valor + "")+"\"];\n";
        dot += padre + "->" + nombreHijo + ";\n";
        cont++;
        recorrerAST(nombreHijo,&nodoAST);
    }
}

QString Graficador::limpiarString(QString str){
    str = str.replace("\\", "\\\\");
    str = str.replace("\"", "\\\"");
    return str;
}

void Graficador::generarImagen(){
    FILE *archivo;
    generarCodigoGraphviz();
    archivo = fopen("temp.dot","w");
    QByteArray aux = dot.toLocal8Bit();
    char *aux2 = aux.data();
    fprintf(archivo, "%s",aux2);
    fclose(archivo);
    system("dot -Tjpg temp.dot -o AST.jpg");
    //system("eog AST.jpg");
}

