#include <iostream>
#include "ManejoArchivos/Bytes.h"
#include <malloc.h>
#include "InterfazSerializar.cpp"

class Key : public InterfazSerializar{

    private:
	char* LineaFerroviaria;

	int   Formacion;

	char* Falla;

	char* Accidente;

	char* FranjaHorariaDelSiniestro;

    public:

	//ESTE METODO ES VOID NO PUEDE DEVOLVER INTS, CHARS*, ETC
	void* getSubClaveSegunDim( int dim ){ /*hardcodeadisimo */
		if (dim==0)return this->LineaFerroviaria;
		if (dim==1)return this->Formacion;
		if (dim==2)return this->Accidente;
		if (dim==3)return this->Falla;
		if (dim==4)return this->FranjaHorariaDelSiniestro;
		return NULL;
	}


	Bytes* Serializarse(){

		unsigned long int  tamanioTotal = this->getTamanioSerializado();


	}

    void Hidratar(Bytes* CodigoBinario){

		char* str =(char*) malloc(tamanioTotal * sizeof(char));
		unsigned int cur = 0;/*cur = cursor*/

		memcpy(str + cur, &this->LineaFerroviaria , sizeof(this->LineaFerroviaria));
		cur += sizeof(this->LineaFerroviaria);

		memcpy(str + cur, &this->Formacion , sizeof(this->Formacion));
		cur += sizeof(this->Formacion);

		memcpy(str + cur, &this->Accidente , sizeof(this->Accidente));
		cur += sizeof(this->Accidente);

		memcpy(str + cur, &this->Falla , sizeof(this->Falla));
		cur += sizeof(this->Falla);

		memcpy(str + cur, &this->FranjaHorariaDelSiniestro , sizeof(this->FranjaHorariaDelSiniestro));
		cur += sizeof(this->FranjaHorariaDelSiniestro);


		return Bytes(str);
	}

	unsigned long int getTamanioSerializado(){

		unsigned long int tamanioSerializado = 0;

		tamanioSerializado += sizeof(this->LineaFerroviaria);
		tamanioSerializado += sizeof(this->Formacion);
		tamanioSerializado += sizeof(this->Falla);
		tamanioSerializado += sizeof(this->Accidente);
		tamanioSerializado += sizeof(this->FranjaHorariaDelSiniestro);

		return tamanioSerializado;
	}
};
