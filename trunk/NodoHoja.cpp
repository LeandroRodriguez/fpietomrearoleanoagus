#include "NodoHoja.h"

unsigned long int NodoHoja::getTamanioSerializado(){

	unsigned long int tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
	tamanioSerializado += sizeof(this->proximaHoja);

	for (unsigned int i = 0;i < this->listIdRegistros.size(); i++){
		tamanioSerializado += sizeof(this->listIdRegistros[i]);
		tamanioSerializado += sizeof(this->listNroBloque[i]);
	}

	return tamanioSerializado;
}

Bytes NodoHoja::serializarse()
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


	for (unsigned int i = 0;i < this->listIdRegistros.size(); i++){
		memcpy(str + cur, this->listIdRegistros[i] , sizeof(this->listIdRegistros[i]));
		cur += sizeof(this->listIdRegistros[i]);

		memcpy(str + cur, this->listNroBloque[i] , sizeof(this->listNroBloque[i]));
		cur += sizeof(this->listNroBloque[i]);
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
	
	for (unsigned int i = 0;i < this->listIdRegistros.size(); i++){
		memcpy(&this->listIdRegistros[i], bytes + cur  , sizeof(this->listIdRegistros[i]));
		cur += sizeof(this->listIdRegistros[i]);
		
		memcpy(&this->listNroBloque[i], bytes + cur  , sizeof(this->listNroBloque[i]));
		cur += sizeof(this->listNroBloque[i]);		
	}	
	return cur;
}

