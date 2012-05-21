#include "NodoHoja.h"

unsigned long int NodoHoja::getTamanioSerializado(){

	unsigned long int tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
	tamanioSerializado += sizeof(this->proximaHoja);
	
	this->listIdRegistros::iterator itRegistros;
	itRegistros= this->listIdRegistros.begin();

	for(itRegistros;itRegistros!=this->listIdRegistros.end();itRegistros++){
		tamanioSerializado += sizeof(  *itRegistros );
        }
	
	
	this->listNroBloque::iterator itBloques;
	itBloques= this->listNroBloque.begin();

	for(itBloques;itBloques!=this->listNroBloque.end();itBloques++){
		tamanioSerializado += sizeof(  *itBloques );
        }

	return tamanioSerializado;
}

char* NodoHoja::serializarse()
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
	
	this->listIdRegistros::iterator itRegistros;
	itRegistros= this->listIdRegistros.begin();
	
	this->listNroBloque::iterator itBloques;
	itBloques= this->listNroBloque.begin();

	for(itRegistros;itRegistros!=this->listIdRegistros.end();itRegistros++){
		memcpy(str + cur, *itRegistros , sizeof(*itRegistros));
		cur += sizeof(*itRegistros);
		
		memcpy(str + cur, *itBloques , sizeof(*itBloques));
		cur += sizeof(*itBloques);	
		
		itBloques++;
        }

	return str;
}

unsigned long int Nodo::hidratar(char* bytes){

	unsigned int cur = 0;/*cur = cursor*/

	memcpy(&this->CantElem, bytes + cur, sizeof(this->CantElem));
	cur += sizeof(this->CantElem);	
	
	memcpy(&this->Altura, bytes + cur, sizeof(this->Altura));
	cur += sizeof(this->Altura);
	
	memcpy(&this->dimension, bytes + cur, sizeof(this->dimension));
	cur += sizeof(this->dimension);
	
	memcpy(&this->proximaHoja, bytes + cur, sizeof(this->proximaHoja));
	cur += sizeof(this->proximaHoja);

	this->listIdRegistros::iterator itRegistros;
	itRegistros= this->listIdRegistros.begin();
	
	this->listNroBloque::iterator itBloques;
	itBloques= this->listNroBloque.begin();

	for(itRegistros;itRegistros!=this->listIdRegistros.end();itRegistros++){
		memcpy(*itRegistros, bytes + cur  , sizeof(*itRegistros));
		cur += sizeof(*itRegistros);
		
		memcpy(*itBloques, bytes + cur  , sizeof(*itBloques));
		cur += sizeof(*itBloques);
		
		itBloques++;
        }	
	return cur; 
}

