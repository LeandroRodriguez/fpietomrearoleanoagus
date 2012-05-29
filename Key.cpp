#include "Key.h"

    Key::Key(char* str){
        this->Hidratar(str);
    }

    Key::~Key(){

    }

	void* Key::getSubClaveSegunDim( int dim ){ /*hardcodeadisimo */
		if (dim==0)return &this->LineaFerroviaria;
		if (dim==1)return &this->Formacion;
		if (dim==2)return &this->Accidente;
		if (dim==3)return &this->Falla;
		if (dim==4)return &this->FranjaHorariaDelSiniestro;
		return NULL;
	}

	string Key::getTamString(string str)
	{
		string serializacion = "";
		int tamanio = str.size();
		while (tamanio < 4)//maxima long de la subclave: 9999
			{
				serializacion += "0";
				tamanio++;
			}
		serializacion += str;
		return serializacion;
	}

	string Key::Serializarse(){

		string serializacion = "";
		stringstream streamTamanio;
        int f;
		f = this->LineaFerroviaria.size();
		streamTamanio << f;
        serializacion += this->getTamString(streamTamanio.str());

        serializacion += this->LineaFerroviaria;


        stringstream  streamTamanioForm;
        streamTamanioForm<<this->Formacion;
        serializacion += this->getTamString(streamTamanioForm.str());

        stringstream streamTamanioAcc;
		f = this->Accidente.size();
		streamTamanioAcc << f;
		serializacion += this->getTamString(streamTamanioAcc.str());

		serializacion += this->Accidente;

		stringstream streamTamanioFalla;
		f = this->Falla.size();
		streamTamanioFalla << f;
		serializacion += this->getTamString(streamTamanioFalla.str());

		serializacion += this->Falla;

		stringstream streamTamanioFranja;
		f = this->FranjaHorariaDelSiniestro.size();
		streamTamanioFranja << f;
		serializacion += this->getTamString(streamTamanioFranja.str());

		serializacion += this->FranjaHorariaDelSiniestro;
        std::cout<<serializacion<<endl;

		return  serializacion;
	}

	void Key::Hidratar(string str){
		int cur = 0;
		int t = atoi(str.substr(cur, 4).c_str());
		cur +=4;
		char* linea;
		linea = &(str.substr(4,t)[0]);
		this->LineaFerroviaria=(linea);
		cur += t;

		this->Formacion= (atoi(str.substr(cur, 4).c_str()));
		cur +=4;

		t = atoi(str.substr(cur, 4).c_str());
		cur +=4;
		char* acc = (&(str.substr(cur,t)[0]));
		this->Accidente = acc;
		cur += t;

		t = atoi(str.substr(cur, 4).c_str());
		cur +=4;
		char* falla = (&(str.substr(cur,t)[0]));
		this-> Falla = falla;
		cur += t;

		t = atoi(str.substr(cur, 4).c_str());
		cur +=4;
		char* franja = (&(str.substr(cur,t)[0]));
		this->FranjaHorariaDelSiniestro = franja;
		cur += t;
	}

	void Key::imprimir()
	{
		cout <<"LineaFerroviaria: " << this->LineaFerroviaria << ", Formacion: "<< this->Formacion << ", Accidente: "
				<< this->Accidente << ", Falla: " <<this->Falla << ", Franja horaria: " << this->FranjaHorariaDelSiniestro<< endl;
	}

	unsigned long int Key::getTamanioSerializado(){

		unsigned long int tamanioSerializado = 0;

		tamanioSerializado += this->LineaFerroviaria.size();
		tamanioSerializado += sizeof(this->Formacion);
		tamanioSerializado += this->Falla.size();
		tamanioSerializado += this->Accidente.size();
		tamanioSerializado += this->FranjaHorariaDelSiniestro.size();
		tamanioSerializado += 4*4;

		return tamanioSerializado;
	}

	bool Key::esIgual(Key* clave2){
		if(strcmp(this->LineaFerroviaria.c_str(), (char*)clave2->getSubClaveSegunDim(0)) != 0)
			return false;

		if(this->Formacion != *((int*)(clave2->getSubClaveSegunDim(1))))
			return false;

		if(strcmp(this->Accidente.c_str(), (char*)clave2->getSubClaveSegunDim(2)) != 0)
			return false;

		if(strcmp(this->Falla.c_str(), (char*)clave2->getSubClaveSegunDim(3)) != 0)
            return false;

		if(strcmp(this->FranjaHorariaDelSiniestro.c_str(), (char*)clave2->getSubClaveSegunDim(4)) != 0)
			return false;

		return true;
	};
