#ifndef INDICE_H_
#define INDICE_H_

#include <iostream>
#include "Arbol.h"

using namespace std;

class Indice {
protected:
	Arbol* arbol;

	Indice();


public:
	virtual char* serializarMetadata();
	virtual long int getTamanioSerializado();
	virtual bool hidratarMetada(char* metadata);

	PersistenciaArbol* persistencia;
	void imprimir();
	Resultado agregarDato(offset nroBloque, offset nroRegistro, Key* dato);
	Indice(string nombreArchivo);
	virtual ~Indice();
	void agregarDatosCargaInicial(list<Dato*>* listaDatosCargaInicial);
	//virtual offset buscar(Key* dato){}
};

#endif /* INDICE_H_ */
