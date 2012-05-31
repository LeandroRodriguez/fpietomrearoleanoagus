#ifndef DATO_H_INCLUDED
#define DATO_H_INCLUDED

#include <iostream>
#include "Constantes.h"
#include "Key.h"

class Dato{

    private:
	Key* clave;
	offset nroBloque;
	offset idRegistro;
    
    public:
	Dato(){
		this->clave = NULL;
		this->nroBloque = VACIO;
		this->idRegistro = VACIO;
	};
     	~Dato(){};

    Key* getClave(){
        return this->clave;
    }
    void setClave(Key* clave){
        this->clave = clave;
    }

    offset getIdRegistro(){
        return this->idRegistro;
    }
    void setIdRegistro(offset idRegistro){
        this->idRegistro = idRegistro;
    }

    offset getNroBoque(){
        return this->nroBloque;
    }
    void setNroBoque(offset nroBloque){
        this->nroBloque = nroBloque;
    }
    
};
#endif //
