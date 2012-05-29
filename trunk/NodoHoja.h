#ifndef NODOHOJA_H_INCLUDED
#define NODOHOJA_H_INCLUDED

#include <typeinfo>
#include <iostream>
#include <list>
#include "Nodo.h"
#include "ManejoArchivos/AlmacenamientoBloque.h"
#include <malloc.h>

class NodoHoja: public Nodo{

    //Atributos de clase madre Nodo, se heredan como privados

    private:
    list<int>* listIdRegistros;
    list<int>* listNroBloque;
    int proximaHoja;

    Key* cargarDato(offset idRegistro, offset nroBloque);

    void InsertarIdRegistro(int id){
        this->listIdRegistros->push_back(id);
        this->ActualizarCantElem();
    }
    void InsertarNroBloque(int Blo){
        this->listNroBloque->push_back(Blo);
        this->ActualizarCantElem();
    }

    void ActualizarCantElem(){
        bool Size = (this->listIdRegistros == this->listNroBloque);
        if (Size) {
            this->CantElem= Size;
            }
        }

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

    NodoHoja* PartirEn2();

};

#endif
