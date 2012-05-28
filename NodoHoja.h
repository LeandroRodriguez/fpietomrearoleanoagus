#ifndef NODOHOJA_H_INCLUDED
#define NODOHOJA_H_INCLUDED

#include <typeinfo>
#include <iostream>
#include <list>
#include "Nodo.h"
#include "Arbol.h"
#include "ManejoArchivos/AlmacenamientoBloque.h"
#include <malloc.h>

template <class T> class NodoInterno;


class NodoHoja: public Nodo{

    //Atributos de clase madre Nodo, se heredan como privados

    private:
    list<int>* listIdRegistros;
    list<int>* listNroBloque;
    int proximaHoja;

    Key* cargarDato(offset idRegistro, offset nroBloque);



    public:

    NodoHoja();
    NodoHoja(Arbol* arbol);
    NodoHoja(char* str);
    ~NodoHoja(){};

    unsigned long int getTamanioSerializado();
    char* Serializarse();
    void Hidratar(char* bytes);
    int getTamanioConDatos();
    Resultado insertarElemento(offset idRegistro, offset nroBloque, Key* dato, double porcentaje);
    vector<int> getTamanios();
    void imprimir();

};

#endif
