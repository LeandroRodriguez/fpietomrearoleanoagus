#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include <iostream>
#include "ManejoArchivos/Bytes.h"
#include <malloc.h>
#include <string.h>
#include "InterfazSerializar.h"

class Key {

    private:
	char* LineaFerroviaria;

	int   Formacion;

	char* Falla;

	char* Accidente;

	char* FranjaHorariaDelSiniestro;

	string getTamString(string str);


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
    string Serializarse();
    void Hidratar(string str);
    bool esIgual(Key* clave2);

    void setLineaFerroviaria(char* linea){this->LineaFerroviaria = linea;}
    void setFormacion(int formacion){this->Formacion = formacion;}
    void setFalla(char* falla){this->Falla = falla;}
    void setAccidente(char* acc){this->Accidente= acc;}
    void setFranjaHorariaDelSiniestro(char* franja){this->FranjaHorariaDelSiniestro = franja;}
    void imprimir();

};

#endif // KEY_H_INCLUDED
