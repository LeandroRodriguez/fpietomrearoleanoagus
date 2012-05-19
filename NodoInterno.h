#include <iostream>
#include "Nodo.h"

class NodoInterno: public Nodo{

    /*Atributos de clase madre Nodo, se heredan como privados
        unsigned long int CantElem
        unsigned long int Altura
        Dimension         dimension
        unsigned long int  tamanioMaximoNodo;
        unsigned long int RefBloque;
    */

    private:

    /*hay que buscar alguna forma piola de administrar
    (ref subclave ref subclave ref subclave )*/


    bool InsertarNuevaSubClaveRef (/*SubClave */ subclave,refAbloqueArbol );

    public:

    NodoInterno(){
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
    }

    ~NodoInterno(){}

    Nodo*   DevolverHijoSegunClave( Clave clave )/*necesitamos nuestra propia clase Clave */




}
