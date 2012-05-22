#ifndef NODOINTERNO_H_
#define NODOINTERNO_H_

#include <iostream>
#include <list>
#include <string.h>
#include "Nodo.h"
#include "Key.h"

template<class T> class SubClaveRef{
    public:
        T subclave;
        int RefNodo;

    bool operator< (const SubClaveRef otro ){

        return ( this->subclave < otro.subclave );

        };

    SubClaveRef(T sub,int ref){
        this->SubClaveRef=ref;
        this->RefNodo=ref;
    };

    ~SubClaveRef(){
    };

    };

template<class T>
class NodoInterno: public Nodo{

    /*Atributos de clase madre Nodo, se heredan como privados
        unsigned long int CantElem
        unsigned long int Altura
        Dimension         dimension
        unsigned long int  tamanioMaximoNodo;
        unsigned long int RefBloque;
    */

    private:

    int Ref1erNodo;

    list< SubClaveRef<T>* >* ListaSubClaveRef;

    void Inicializar( Key subclave ,int ref );

    bool InsertarNuevaSubClaveRef ( T subclave,int refAbloqueArbol );

    Nodo*   DevolverHijoSegunSubClave( T subclave );

    public:

    Bytes Serializarse();

    void Hidratar(char* cadena);

    NodoInterno(){
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef<T> >;
    }

    Nodo* DevolverHijoSegunClave(Key Clave);

    ~NodoInterno(){}

};

#endif
