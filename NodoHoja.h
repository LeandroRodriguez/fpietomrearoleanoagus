#ifndef NODOHOJA_H_INCLUDED
#define NODOHOJA_H_INCLUDED

#include <iostream>
#include <list>
#include "Nodo.h"
#include "Constantes.h"
#include <malloc.h>

class NodoHoja: public Nodo{

    //Atributos de clase madre Nodo, se heredan como privados

    private:
    list<int> listIdRegistros;
    list<int> listNroBloque;
    int proximaHoja;



    public:

    NodoHoja(int dimension, int refBloque);
    ~NodoHoja();

    unsigned long int getTamanioSerializado();
    char* serializarse();
    unsigned long int hidratar(char* bytes);

};

#endif
