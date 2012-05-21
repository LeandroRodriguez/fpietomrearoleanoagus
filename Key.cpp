#include <iostream>
#include "ManejoArchivos/Bytes.h"

//por ahora dejamos los structs, despues si no los usamos los volamos
struct Horario {
        unsigned int hora;
        unsigned int minutos;
        unsigned int segundos;
        };

struct Fecha {
        unsigned int Dia;
        unsigned int Mes;
        unsigned int Anio;
        };

class FechaHora:public InterfazSerializar {

    private:

    Horario IzqHora;
    Horario DerHora;
    Fecha fecha;

    public:

    FechaHora(){
    }

    void Hidratar(Bytes* CodigoBinario){
        }

    bool Setear1erHora(unsigned int hora, unsigned int min,unsigned int sec){
        }

    bool Setear2daHora(unsigned int hora,unsigned int min, unsigned int sec){
        }

    bool SetearFecha(unsigned int Dia,unsigned int Mes,unsigned int Anio){
        }

    Fecha getFecha(){
        }

    Horario getIzqHorario(){
        }

    Horario getDerHorario(){
        }

    Bytes* Serializarse(){
    }

};

class Key:public InterfazSerializar{

    private:
	char* LineaFerroviaria;

	int   Formacion;

	char* Falla;

	char* Accidente;

	char* FranjaHorariaDelSiniestro;

    public:

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

	void Hidratar(Bytes* CodigoBinario){
		unsigned int cur = 0;/*cur = cursor*/

		memcpy(&this->LineaFerroviaria, bytes + cur, sizeof(this->LineaFerroviaria));
		cur += sizeof(this->LineaFerroviaria);
		
		memcpy(&this->Formacion, bytes + cur, sizeof(this->Formacion));
		cur += sizeof(this->Formacion);
		
		memcpy(&this->Accidente, bytes + cur, sizeof(this->Accidente));
		cur += sizeof(this->Accidente);
		
		memcpy(&this->Falla, bytes + cur, sizeof(this->Falla));
		cur += sizeof(this->Falla);
		
		memcpy(&this->Falla, bytes + cur, sizeof(this->Falla));
		cur += sizeof(this->Falla);
		
		return cur;

	}
	
	
	unsigned long int NodoHoja::getTamanioSerializado(){

		unsigned long int tamanioSerializado = 0;

		tamanioSerializado += sizeof(this->LineaFerroviaria);
		tamanioSerializado += sizeof(this->Formacion);
		tamanioSerializado += sizeof(this->Falla);
		tamanioSerializado += sizeof(this->Accidente);
		tamanioSerializado += sizeof(this->FranjaHorariaDelSiniestro);
		
		return tamanioSerializado;
	}




};
