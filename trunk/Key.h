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

	string Formacion;

	string Falla;

	string Accidente;

	string FranjaHorariaDelSiniestro;

	string getTamString(string str);


    public:

	string* getSubClaveSegunDim( int dim );

	Key(){
	    this->Accidente="";
	    this->Falla="";
	    this->FranjaHorariaDelSiniestro="";
	    this->Formacion="-1";
	    this->LineaFerroviaria="";
	    };

	Key(string str);

    ~Key();

    unsigned long int getTamanioSerializado();

    string Serializarse();
    void Hidratar(string str);

    bool esIgual(Key* dato);

    void setLineaFerroviaria(string linea){this->LineaFerroviaria = linea;}
    void setFormacion(string formacion){this->Formacion = formacion;}
    void setFalla(string falla){this->Falla = falla;}
    void setAccidente(string acc){this->Accidente= acc;}
    void setFranjaHorariaDelSiniestro(string franja){this->FranjaHorariaDelSiniestro = franja;}
    void imprimir();
    /**************************/
    bool static EsIntEstaDimension(int n);
    int static getDimensionSegunAltura(int h);
    int static getSiguienteDimension(int n);
};

#endif // KEY_H_INCLUDED
