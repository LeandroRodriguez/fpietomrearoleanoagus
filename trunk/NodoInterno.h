#include <iostream>
#include "Nodo.h"

/*include SubClave      */

struct SubClaveRef{
        SubClave subclave;
        unsigned long int RefNodo;
    }

class NodoInterno: public Nodo{

    /*Atributos de clase madre Nodo, se heredan como privados
        unsigned long int CantElem
        unsigned long int Altura
        Dimension         dimension
        unsigned long int  tamanioMaximoNodo;
        unsigned long int RefBloque;
    */

    private:

    unsigned long int Ref1erNodo;

    list<SubClaveRef>* ListaSubClaveRef;


    bool InsertarNuevaSubClaveRef (/*SubClave */ subclave,refAbloqueArbol );

    public:

    NodoInterno(){
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
    }

    ~NodoInterno(){}

    Nodo*   DevolverHijoSegunClave( Clave clave )/*necesitamos nuestra propia clase Clave */




}
