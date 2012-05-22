#include <iostream>
#include <list>
#include <string.h>
#include "Nodo.h"
#include "Key.cpp"

template<class T>
class SubClaveRef<T>{
    public
        T subclave;
        int RefNodo;

    bool SubClaveRef<T>::operator< (const SubClaveRef<T> ){

        return ( this->subclave < SubClaveRef.subclave );

        };

    SubClaveRef<T>(){
    };

    ~SubClaveRef(){
    };

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

    int Ref1erNodo;

    list< SubClaveRef<T>* >* ListaSubClaveRef;

    void Inicializar( Key subclave ,int ref );

    bool InsertarNuevaSubClaveRef ( T subclave,refAbloqueArbol );

    Nodo*   DevolverHijoSegunSubClave( T subclave );

    public:

    Bytes Serializarse();

    void Hidratar(char* cadena);

    void Hidratar(char* bytes);

    NodoInterno<T>(){
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef<T> >;
    }

    Nodo* DevolverHijoSegunClave(Key Clave);

    ~NodoInterno<T>(){}

};
