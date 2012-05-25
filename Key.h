#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include <iostream>
#include "ManejoArchivos/Bytes.h"
#include <malloc.h>
#include <string.h>
#include "InterfazSerializar.h"

class Key : public InterfazSerializar {

    private:
	char* LineaFerroviaria;

	int   Formacion;

	char* Falla;

	char* Accidente;

	char* FranjaHorariaDelSiniestro;


    public:

	void* getSubClaveSegunDim( int dim );

	Key(){
	    this->Accidente=NULL;
	    this->Falla=NULL;
	    this->FranjaHorariaDelSiniestro=NULL;
	    this->Formacion=-1;
	    this->LineaFerroviaria=NULL;
	    };

	Key(char* str );

    ~Key();

    unsigned long int getTamanioSerializado();
    char* Serializarse();
    void Hidratar(char* str);

};

#endif // KEY_H_INCLUDED
