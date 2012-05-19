#include <iostream>
#include "NodoInterno.h"

NodoInterno::char* Serializarse() = 0;

        virtual      Hidratar(char* CodigoBinario ) =0;

        virtual unsigned long int getTamanioSerializado() = 0;

        virtual ~InterfazSerializar() {}


offset Nodo::getId(){
	return this->id;
}
