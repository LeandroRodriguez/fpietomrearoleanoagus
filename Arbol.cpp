#include "Arbol.h"


Arbol::Arbol( PersistenciaArbol* persistencia) {
	this->persistir = persistencia;
	this->cantidadElem= 0;
	this->raiz = NULL;

	if (this->persistir->existeBloque( ID_RAIZ)){
		this->raiz = this->persistir->obtenerRaiz();

		//if (this->raiz!= NULL)
		//	this->raiz->setArbol(this);
		//por ahora esto no lo ponemos, es sucio
	}


};


Arbol::~Arbol() {
	if (this->raiz!=NULL)
		delete this->raiz;
};


Resultado Arbol::insertar(offset nroBloque, offset nroRegistro, Key* dato)
{
	bool overflow = false;
	Resultado res;

	if (!raiz) {
		//Es el primerElemento
		/*this->raiz = dynamic_cast<NodoHoja*> (this->crearRaiz());*/

		raiz->insertarElemento(nroBloque, nroRegistro, dato, res,overflow);
		if(res == RES_OK)
			this->cantidadElem  ++;

		return res;

	} else {
		//debo insertar recursivamente
		raiz->insertarElemento(nroBloque, nroRegistro, dato, res,overflow);
		/*
		this->setRaiz(this->raiz->getAdan());
		if (this->raiz->getHojaOInterno()== 'I')
			this->raiz->actualizarClaves();
		this->ultimosAdisco();
		esto despues hay que ver bien como lo hacemos, cuando tengamos los metodos en los nodos
		*/
		if(res == RES_OK)
			this->cantidadElem  ++;

		return res;
	}
};

Nodo* Arbol::getRaiz(){
	return this->raiz;
};


