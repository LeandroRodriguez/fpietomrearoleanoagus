#ifndef NODOHOJA_H_INCLUDED
#define NODOHOJA_H_INCLUDED

#include <iostream>
#include <list>
#include "Nodo.h"
#include "Key.h"
#include "Constantes.h"
#include "ManejoArchivos/AlmacenamientoBloque.h"
#include <malloc.h>

class NodoHoja: public Nodo{

    //Atributos de clase madre Nodo, se heredan como privados

    private:
    list<int>* listIdRegistros;
    list<int>* listNroBloque;
    int proximaHoja;

    Key* cargarDato(offset idRegistro, offset nroBloque);



    public:

    NodoHoja(int dimension, int refBloque);
    ~NodoHoja(){};

    unsigned long int getTamanioSerializado();
    char* Serializarse();
    void Hidratar(char* bytes);
    int getTamanioConDatos();
    Resultado insertarElemento(Key* dato, offset idRegistro, offset nroBloque);

};

#endif
