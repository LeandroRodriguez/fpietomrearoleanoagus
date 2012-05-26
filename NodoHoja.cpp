#include "NodoHoja.h"

NodoHoja::NodoHoja(int dimension, int refBloque){
    //me pasan un numero de dimension. despues tendre que matchearlo con una de las dimensiones del accidente
    this->tamanioMaximoNodo=0;
    this->CantElem=0;
	this->dimension = dimension;
	this->RefBloque = refBloque;
	this->listIdRegistros = new list<int>();
	this->listNroBloque = new list<int>();

    };

unsigned long int NodoHoja::getTamanioSerializado(){

	unsigned long int tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
	tamanioSerializado += sizeof(this->proximaHoja);

	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		tamanioSerializado += sizeof(  *itRegistros );
        }


	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itBloques!=this->listNroBloque->end();itBloques++){
		tamanioSerializado += sizeof(  *itBloques );
        }

	return tamanioSerializado;
};

Bytes* NodoHoja::Serializarse()
{
	unsigned long int  tamanioTotal = this->getTamanioSerializado();

	char* str =(char*) malloc(tamanioTotal * sizeof(char));
	unsigned int cur = 0;/*cur = cursor*/

	memcpy(str + cur, &this->CantElem , sizeof(this->CantElem));
	cur += sizeof(this->CantElem);

	memcpy(str + cur, &this->Altura , sizeof(this->Altura));
	cur += sizeof(this->Altura);

	memcpy(str + cur, &this->dimension , sizeof(this->dimension));
	cur += sizeof(this->dimension);

	memcpy(str + cur, &this->proximaHoja , sizeof(this->proximaHoja));
	cur += sizeof(this->proximaHoja);

	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		memcpy(str + cur, &(*itRegistros) , sizeof(*itRegistros) );
		cur += sizeof(*itRegistros);

		memcpy(str + cur, &(*itBloques) , sizeof(*itBloques));
		cur += sizeof(*itBloques);

		itBloques++;
        }

	return new Bytes(str);
};

void NodoHoja::Hidratar(char* bytes){

	unsigned int cur = 0;/*cur = cursor*/

	memcpy(&this->CantElem, bytes + cur, sizeof(this->CantElem));
	cur += sizeof(this->CantElem);

	memcpy(&this->Altura, bytes + cur, sizeof(this->Altura));
	cur += sizeof(this->Altura);

	memcpy(&this->dimension, bytes + cur, sizeof(this->dimension));
	cur += sizeof(this->dimension);

	memcpy(&this->proximaHoja, bytes + cur, sizeof(this->proximaHoja));
	cur += sizeof(this->proximaHoja);

	while(cur < strlen(bytes) )
	{
		int idRegistro;
		memcpy(&idRegistro, bytes + cur  , sizeof(int) );
		cur += sizeof(int);
		this->listIdRegistros->push_back(idRegistro);

		int nroBloque;
		memcpy(&nroBloque, bytes + cur  , sizeof(int) );
		cur += sizeof(int);
		this->listNroBloque->push_back(nroBloque);
	}
};



Key* cargarDato(offset idRegistro, offset nroBloque){
	Key* dato = new Key();
	AlmacenamientoBloque almacena(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);

	Bytes bytes = almacena.recuperarRegistro(nroBloque, idRegistro);
	Bytes* b = &bytes;

	dato -> Hidratar(b);
	return dato;
};

int getTamanioConDatos()
{
	int tamanio;
	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		offset idReg = *itRegistros;
		offset nroBlo = *itBloques;
		Key* d = this->cargarDato(idReg, nroBlo)

		tamanio += dato->getTamanioSerializado();
		itBloques++;
        }
	tamanio += sizeof(this->proximaHoja);
	return tamanio;
	
};


Resultado NodoHoja::insertarElemento(Key* dato, offset idRegistro, offset nroBloque)
{
	/*Busca en el nodo si hay algún registro con los mismos identificadores que IdentificadorDato.
	Si lo encuentra, devuelve como resultado RES_DUPLICADO.

	Si el nodo hoja desborda, Devuelve  RES_DESBORDADO  
	sino, devuelve RES_OK
	*/
	
	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		offset idReg = *itRegistros;
		offset nroBlo = *itBloques;
		Key* d = this->cargarDato(idReg, nroBlo)
		if(dato->esIgual(d))
			return RES_DUPLICADO;
		itBloques++;
        }
	
	this->listIdRegistros->push_back(idRegistro);
	this->listNroBloque->push_back(nroBloque);
	
	//chequeo overflow	
	if(this->getTamanioConDatos() > LONGITUD_BLOQUE_NODO)		
		return RES_DESBORDADO;
	
	return RES_OK;

};


