#include "Key.h"

    Key::Key(char* str){
        this->Hidratar(str);
    }

    Key::~Key(){
        delete this->Accidente;
        delete this->Falla;
        delete this->FranjaHorariaDelSiniestro;
        delete this->LineaFerroviaria;
    }

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

        int* pLong = new int;/* work around para poder usar memcopy, nada mas*/

        /*----------------------------*/
        *pLong = strlen(this->LineaFerroviaria);
		memcpy(str + cur, pLong , sizeof(int));
		cur += sizeof(int);
        memcpy(str + cur, &this->LineaFerroviaria , *pLong);
		cur += *pLong;
        /*----------------------------*/
		memcpy(str + cur, &this->Formacion , sizeof(this->Formacion));
		cur += sizeof(this->Formacion);
		/*----------------------------*/
        *pLong = strlen(this->Accidente);
		memcpy(str + cur, pLong , sizeof(int));
		cur += sizeof(int);
        memcpy(str + cur, &this->Accidente ,*pLong);
		cur += *pLong;
        /*----------------------------*/
        *pLong = strlen(this->Falla);
		memcpy(str + cur, pLong , sizeof(int));
		cur += sizeof(int);
        memcpy(str + cur, &this->Falla,*pLong);
		cur += *pLong;
        /*----------------------------*/
        *pLong = strlen(this->FranjaHorariaDelSiniestro);
		memcpy(str + cur, pLong , sizeof(int));
		cur += sizeof(int);
        memcpy(str + cur, &this->FranjaHorariaDelSiniestro,*pLong);
		cur += *pLong;
        /*----------------------------*/

        delete pLong;
		return  str;
	};

	void Key::Hidratar(char* str){

		unsigned int cur = 0;/*cur = cursor*/

        int* pLong = new int;/* work around para poder usar memcopy, nada mas*/

        /*----------------------------*/
		memcpy(pLong, str + cur, sizeof(int));
		cur += sizeof(int);

		this->LineaFerroviaria = new char[*pLong];

		memcpy(this->LineaFerroviaria, str + cur, *pLong);
		cur += *pLong;
        /*----------------------------*/
		memcpy(&this->Formacion ,str + cur,  sizeof(this->Formacion));
		cur += sizeof(this->Formacion);
        /*----------------------------*/
		memcpy(pLong, str + cur, sizeof(int));
		cur += sizeof(int);

        this->Accidente = new char[*pLong];

		memcpy(this->Accidente, str + cur, *pLong);
		cur += *pLong;
        /*----------------------------*/
		memcpy(pLong, str + cur, sizeof(int));
		cur += sizeof(int);

        this->Falla = new char[*pLong];

		memcpy(&this->Falla, str + cur, *pLong);
        /*----------------------------*/
		memcpy(pLong, str + cur, sizeof(int));
		cur += sizeof(int);

        this->FranjaHorariaDelSiniestro = new char[*pLong];

		memcpy(this->FranjaHorariaDelSiniestro, str + cur, *pLong);
		cur += *pLong;
        /*----------------------------*/

		delete pLong;

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

	bool Key::esIgual(Key* clave2){
		if(strcmp(this->LineaFerroviaria, (char*)clave2->getSubClaveSegunDim(0)) != 0)
			return false;

		if(this->Formacion != *((int*)(clave2->getSubClaveSegunDim(1))))
			return false;

		if(strcmp(this->Accidente, (char*)clave2->getSubClaveSegunDim(2)) != 0)
			return false;

		if(strcmp(this->Falla, (char*)clave2->getSubClaveSegunDim(3)) != 0)
            return false;

		if(strcmp(this->FranjaHorariaDelSiniestro, (char*)clave2->getSubClaveSegunDim(4)) != 0)
			return false;

		return true;
	}
