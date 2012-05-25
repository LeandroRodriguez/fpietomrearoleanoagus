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

	Key(){};

    ~Key(){};

    unsigned long int getTamanioSerializado();
    char* Serializarse();
    void Hidratar(char* bytes);

};

#endif // KEY_H_INCLUDED
