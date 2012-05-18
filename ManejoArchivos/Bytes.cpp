#include "Bytes.h"

Bytes::Bytes() {

}

Bytes::Bytes(string bytes) {

	this->bytes = bytes;
}

Bytes::Bytes(const Bytes & byte) {

	this->bytes = byte.bytes;
}

unsigned int Bytes::getTamanio() const {

	return this->bytes.length();
}

bool Bytes::estaVacio() const {

	return (this->getTamanio() == 0);
}

string Bytes::toString() const {

	return this->bytes;
}

void Bytes::setBytes(const string &bytes) {

	this->bytes = bytes;
}

bool Bytes::vaciar() {

	this->bytes.clear();
	return true;
}

bool Bytes::agregar(const Bytes& bytes,offset offset) {

	if (offset > this->bytes.length()) {
		return false;
	}

	this->bytes.insert(offset,bytes.toString());//a partir de la posición offset, guardo bytes
	return true;
}

bool Bytes::agregar(const string &bytes,offset offset) {

	if (offset > this->bytes.length()) {
		return false;
	}

	this->bytes.insert(offset,bytes);//a partir de la posición offset, guardo bytes
	return true;
}

bool Bytes::agregar(void* dato, int tamanio, offset offset) {

	string str;
	char aux[tamanio];
	memcpy(aux,dato,tamanio);//copio en aux el dato y lo agrego a aux
	str.append(aux,tamanio);//agrega a str una copia de los primeros tamanio caracteres de aux

	return agregar(str,offset);//agrega a this->bytes el string str en la posición offset
}

bool Bytes::agregarAlFinal(const string &bytes) {

	this->bytes += bytes;
	return true;
}


bool Bytes::agregarAlFinal(const Bytes& bytes) {

	agregar(bytes,getTamanio());
	return true;
}

bool Bytes::agregarAlFinal(void* dato, int tamanio) {

	agregar(dato,tamanio,getTamanio());
	return true;
}

bool Bytes::leer(void* buffer, offset offsetLeer,cantBytes tamanio)const {
	Bytes b = this->getSubBytes(offsetLeer,tamanio);//pido el string que necesito
	if(b.getTamanio()==0){
		return false;
	}else{
		memcpy(buffer,b.bytes.data(),tamanio);
		return true;
	}
}

Bytes Bytes::getSubBytes(offset desde, cantBytes cantidad) const {

	if (desde + cantidad > getTamanio()) {
		return Bytes("");
	}

	return this->bytes.substr(desde,cantidad);
}

char Bytes::operator[](offset o){
	return bytes[o];
}

Bytes::~Bytes() {

}
