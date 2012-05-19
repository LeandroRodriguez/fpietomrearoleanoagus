#include <iostream>
#include "Nodo.h"

/*include Key*/

struct SubClaveRef{
        Key subclave;
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

    void Inicializar( Key subclave ,unsigned long int ref );

    public:

    NodoInterno(){
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef>;
    }

    ~NodoInterno(){}

    bool InsertarNuevaSubClaveRef ( Key subclave,refAbloqueArbol );

    Nodo*   DevolverHijoSegunClave( Key clave );


}
