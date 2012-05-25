#include "Key.h"

	void* Key::getSubClaveSegunDim( int dim ){ /*hardcodeadisimo */
		if (dim==0)return this->LineaFerroviaria;
		if (dim==1)return &this->Formacion;
		if (dim==2)return this->Accidente;
		if (dim==3)return this->Falla;
		if (dim==4)return this->FranjaHorariaDelSiniestro;
		return NULL;
	};


	char* Key::Serializarse(){

		unsigned long int  tamanioTotal = this->getTamanioSerializado();

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

		return  str;
	};

	void Key::Hidratar(char* bytes){

		unsigned int cur = 0;/*cur = cursor*/

		memcpy(&this->LineaFerroviaria, bytes + cur, sizeof(this->LineaFerroviaria));
		cur += sizeof(this->LineaFerroviaria);

		memcpy(&this->Formacion, bytes + cur, sizeof(this->Formacion));
		cur += sizeof(this->Formacion);

		memcpy(&this->Accidente, bytes + cur, sizeof(this->Accidente));
		cur += sizeof(this->Accidente);

		memcpy(&this->Falla, bytes + cur, sizeof(this->Falla));
		cur += sizeof(this->Falla);

		memcpy(&this->FranjaHorariaDelSiniestro, bytes + cur, sizeof(this->FranjaHorariaDelSiniestro));
		cur += sizeof(this->FranjaHorariaDelSiniestro);

	};

	unsigned long int Key::getTamanioSerializado(){

		unsigned long int tamanioSerializado = 0;

		tamanioSerializado += strlen(this->LineaFerroviaria);
		tamanioSerializado += sizeof(this->Formacion);
		tamanioSerializado += strlen(this->Falla);
		tamanioSerializado += strlen(this->Accidente);
		tamanioSerializado += strlen(this->FranjaHorariaDelSiniestro);

		return tamanioSerializado;
	};
