#include "Key.h"

    Key::Key(string str){
        this->Hidratar(str);
    }

    Key::~Key(){

    }

	string Key::getSubClaveSegunDim(int dim){ /*hardcodeadisimo */
		if (dim==0)return this->LineaFerroviaria;
		if (dim==1)return this->Formacion;
		if (dim==2)return this->Accidente;
		if (dim==3)return this->Falla;
		if (dim==4)return this->FranjaHorariaDelSiniestro;
		return NULL;
	}

	string Key::getTamString(string str){
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

		char* formacion;
		formacion =(&(str.substr(cur,t)[0]));
		this->Formacion= formacion;
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

	void Key::imprimir(){
		cout <<"LineaFerroviaria: " << this->LineaFerroviaria << ", Formacion: "<< this->Formacion << ", Accidente: "
				<< this->Accidente << ", Falla: " <<this->Falla << ", Franja horaria: " << this->FranjaHorariaDelSiniestro<< endl;
        cout << "-------------------" << endl;
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

   bool Key::EsIntEstaDimension(int n){
        if(n==1)return true;
        return false;
    }

    int Key::getDimensionSegunAltura(int h){
        if (h-1<0) return -1;
        int aux = (h-1)%5;
        return aux;
    }
        // dimension va de 0 a 4, o sea, 5 elementos
    int Key::getSiguienteDimension(int n){
        if( n<0 ||  n>5 )return -1;// (-infinito,-1] o [6,infinito)
        return (n+1)%5;
    }

	bool Key::esIgual(Key* dato){
        if(this->LineaFerroviaria != dato->LineaFerroviaria)
            return false;
        if(this->Formacion != dato->Formacion)
            return false;
        if(this->Accidente != dato->Accidente)
            return false;
        if(this->Falla != dato->Falla)
            return false;
        if(this->FranjaHorariaDelSiniestro != dato->FranjaHorariaDelSiniestro)
            return false;
        return true;
    };

