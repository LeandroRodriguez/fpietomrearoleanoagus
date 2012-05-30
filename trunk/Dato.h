#ifndef DATO_H_INCLUDED
#define DATO_H_INCLUDED

#include <iostream>
#include "Constantes.h"
#include "Key.h"

class Dato{

    private:
	Key clave;
	offset nroBLoque;
	offset idRegistro;
    
    public:
	Nodo(){
		this->clave = null;
		this->nroBloque = -1;
		this->idRegistro = -1;
	};
     	~Nodo(){};

    int getClave(){
        return this->clave;
    }
    void setClave(clave){
        this->clave = clave;
    }

    offset getIdRegistro(){
        return this->idRegistro;
    }
    void setClave(idRegistro){
        this->idRegistro = idRegistro;
    }

    offset getNroBoque(){
        return this->nroBloque;
    }
    void setClave(nroBloque){
        this->nroBloque = nroBloque;
    }
    
};
#endif //
