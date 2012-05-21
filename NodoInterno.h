#include <iostream>
#include <list>
#include "Nodo.h"
#include "Key.cpp"

template<class T>
struct SubClaveRef<T>{
        T subclave;
        unsigned long int RefNodo;
    };

template<class T>
class NodoInterno<T>: public Nodo{

    /*Atributos de clase madre Nodo, se heredan como privados
        unsigned long int CantElem
        unsigned long int Altura
        Dimension         dimension
        unsigned long int  tamanioMaximoNodo;
        unsigned long int RefBloque;
    */

    private:

    unsigned long int Ref1erNodo;

    list< SubClaveRef<T> >* ListaSubClaveRef;

    void Inicializar( Key subclave ,unsigned long int ref );

    bool InsertarNuevaSubClaveRef ( T subclave,refAbloqueArbol ){
        }

    Nodo*   DevolverHijoSegunSubClave( T subclave ){
        }

    public:

    NodoInterno<T>(){
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef<T> >;
    }

    Nodo* DevolverHijoSegunClave(Key Clave){
        }

    ~NodoInterno(){}

};
