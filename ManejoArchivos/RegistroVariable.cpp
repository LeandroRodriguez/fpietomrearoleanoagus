#include "RegistroVariable.h"
#include <stdio.h>
#include <stdlib.h>

RegistroVariable::RegistroVariable(const Bytes& dato) {
	this->dato = dato;
	this->vivo = true;
}

RegistroVariable::RegistroVariable() {
}

RegistroVariable::~RegistroVariable() {

}

void RegistroVariable::setDato(const Bytes& dato) {
	this->dato = dato;
}

Bytes RegistroVariable::getDato() const {
	return this->dato;
}

bool RegistroVariable::estaVivo() const {

	return this->vivo;
}

void RegistroVariable::matar() {

	this->vivo = false;
}

Bytes RegistroVariable::serializarse() {
	string serializacion;
	stringstream streamTamanio;
	stringstream streamUID;

	cantBytes tamanio = dato.getTamanio();
	streamTamanio << tamanio;
	streamUID << nRegistro;

	unsigned int tamanioDatos = streamTamanio.str().size();
	unsigned int tamanioUID = streamUID.str().size();

	//UID
	while (tamanioUID < LONGITUD_CANT_BYTES)//agrego "0" al principio del campo para completar el tamaño del campo
	{
		serializacion += "0";
		tamanioUID++;
	}
	serializacion += streamUID.str();//agrego el uid a la serializacion

	//Tamanio
	while (tamanioDatos < LONGITUD_CANT_BYTES)//agrego "0" al principio del campo para completar el tamaño del campo
	{
		serializacion += "0";
		tamanioDatos++;
	}
	serializacion += streamTamanio.str();//agrego el tamanio del dato a la serializacion

	//Vivo
	if(this->vivo)
		serializacion += "1";
	else
		serializacion += "0";
	
	//DATO
	serializacion += dato.toString();//agrego el dato a la serializacion

	return Bytes(serializacion);//devuelve una instancia de Bytes, que contiene la serializacion
}

void RegistroVariable::hidratarse(const Bytes& cadena) {
	if (cadena.getTamanio() <= 1) {
		return;
	}

	this->nRegistro = atoi(cadena.getSubBytes(0,LONGITUD_CANT_BYTES).toString().c_str());//tomo los primeros LONGITUD_CANT_BYTES bytes para el uid
	int tamanioRegistro = atoi(cadena.getSubBytes(LONGITUD_CANT_BYTES, LONGITUD_CANT_BYTES).toString().c_str());
	//tomo los segundos LONGITUD_CANT_BYTES bytes para el tamanioregitsro
	
	char a = cadena.getSubBytes(2 * LONGITUD_CANT_BYTES,1);
	this->vivo = (a=="1");

	this->setDato(cadena.getSubBytes(2 * LONGITUD_CANT_BYTES + 1,tamanioRegistro));
	this->tamanioDato = tamanioRegistro;
}

cantBytes RegistroVariable::getTamanioSerializado() {
	return 2 * LONGITUD_CANT_BYTES + this->dato.getTamanio();
}
