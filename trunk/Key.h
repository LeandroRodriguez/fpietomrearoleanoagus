#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include <iostream>
#include "ManejoArchivos/Bytes.h"
#include <malloc.h>
#include <string.h>
#include "InterfazSerializar.h"

class Key {

    private:
	string LineaFerroviaria;

	int   Formacion;

	string Falla;

	string Accidente;

	string FranjaHorariaDelSiniestro;

	string getTamString(string str);


    public:

	void* getSubClaveSegunDim( int dim );

	Key(){
	    this->Accidente="";
	    this->Falla="";
	    this->FranjaHorariaDelSiniestro="";
	    this->Formacion=-1;
	    this->LineaFerroviaria="";
	    };

	Key(char* str );

    ~Key();

    unsigned long int getTamanioSerializado();
    string Serializarse();
    void Hidratar(string str);
    bool esIgual(Key* clave2);

    void setLineaFerroviaria(string linea){this->LineaFerroviaria = linea;}
    void setFormacion(int formacion){this->Formacion = formacion;}
    void setFalla(string falla){this->Falla = falla;}
    void setAccidente(string acc){this->Accidente= acc;}
    void setFranjaHorariaDelSiniestro(string franja){this->FranjaHorariaDelSiniestro = franja;}
    void imprimir();

};

#endif // KEY_H_INCLUDED
