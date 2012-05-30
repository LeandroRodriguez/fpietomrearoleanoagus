#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include <iostream>
#include "Key.h"

class Arbol;

class Nodo : public InterfazSerializar {

    protected: /*asi al heredar los puede cambiar, si lo pongo private kb */

    unsigned int CantElem;
    unsigned int Altura;
    int  dimension;
    unsigned int  tamanioMaximoNodo;
    unsigned int  tamanioUsado;
    unsigned int idBloque;
    Arbol* arbol;

    public:
     ~Nodo(){};
     Nodo();
     Nodo(Arbol* arbol);

    int getIdDelNodo(){
        return this->idBloque;
    }

    void setIdDelNodo(int ref);

    char getHojaOInterno();

    virtual Resultado insertarElemento(offset nroBloque, offset nroRegistro, Key* dato, double porcentaje) = 0;

	virtual void imprimir()=0;

	void setArbol(Arbol* arbol);

	bool tieneArbol(){
	    if(this->arbol!=NULL)return true;
	    return false;
	    }

};
#endif //
