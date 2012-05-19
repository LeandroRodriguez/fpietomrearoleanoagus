#include "NodoHoja.h"

unsigned long int NodoHoja::getTamanioSerializado(){

	unsigned long int tamanioSerializado = 0;
	
	tamanioSerializado += sizeof(this->cantElem);
	tamanioSerializado += sizeof(this->nivel);
	tamanioSerializado += sizeof(this->dimension);

	for (unsigned int i = 0;i < this->listIdRegistros.size(); i++){
		tamanioSerializado += sizeof(this->listIdRegistros[i]);
		tamanioSerializado += sizeof(this->listNroBloque[i]);
	}

	return tamanioSerializado;
}
