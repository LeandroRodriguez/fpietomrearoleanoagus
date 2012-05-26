#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include <iostream>
#include "InterfazSerializar.h"
#include "Key.h"

class Nodo : public InterfazSerializar {

    protected: /*asi al heredar los puede cambiar, si lo pongo private kb */

    unsigned int CantElem;
    unsigned int Altura;
    int  dimension;
    unsigned int  tamanioMaximoNodo;
    unsigned int  tamanioUsado;
    unsigned int idBloque;

    public:
    Nodo(){};
    virtual ~Nodo(){};

    int getIdDelNodo(){
        return this->idBloque;
    }

    void setIdDelNodo(int ref){
     this->idBloque= ref;
    }

    char getHojaOInterno(){
        if (this->Altura>0)return 'I';
        return 'H';

    }

    virtual Resultado insertarElemento(offset nroBloque, offset nroRegistro, Key* dato)=0;


};
#endif //
