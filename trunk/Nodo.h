#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include <iostream>
#include "InterfazSerializar.h"

class Nodo : public InterfazSerializar {

    protected: /*asi al heredar los puede cambiar, si lo pongo private kb */

    unsigned int CantElem;
    unsigned int Altura;
    int  dimension;
    unsigned int  tamanioMaximoNodo;
    unsigned int  tamanioUsado;
    unsigned int RefBloque;

    public:
    Nodo();
    virtual ~Nodo();


};
#endif //
