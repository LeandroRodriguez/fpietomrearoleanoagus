#ifndef BYTES_H_
#define BYTES_H_

#include "../Constantes.h"

#include <string>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <string.h>

using namespace std;

class Bytes {

private: 

	string bytes;

public:

	Bytes();
	Bytes(string bytes);
	Bytes(const Bytes &bytes);

	virtual ~Bytes();

	unsigned int getTamanio() const;
	bool estaVacio() const;
	string toString() const;
	void setBytes(const string &bytes);
	bool vaciar();
	bool agregar(const Bytes& bytes,offset offset);
	bool agregar(const string& bytes,offset offset);
	bool agregar(void* dato, int tamanio,offset offset);
	bool agregarAlFinal(const string& bytes);
	bool agregarAlFinal(const Bytes& bytes);
	bool agregarAlFinal(void* dato, int tamanio);
	bool leer(void* buffer, offset offsetLeer,cantBytes tamanio)const;
	Bytes getSubBytes(offset desde, cantBytes cantidad) const;
	char operator[](offset o);

};

#endif /* BYTES_H_ */
