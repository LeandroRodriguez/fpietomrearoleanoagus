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


}


Arbol::~Arbol() {
	if (this->raiz!=NULL)
		delete this->raiz;
}



Resultado Arbol::insertar(offset nroBloque, offset nroRegistro, Key* dato){
	Resultado res;

	if (!raiz) {
		//Es el primerElemento
		Nodo* aaa = this->crearRaiz();
		this->raiz = (NodoHoja*) (aaa);

        /*no entiendo porque esta funcion recibe TANTOS parametros :S  */
		res = raiz->insertarElemento(nroBloque, nroRegistro, dato);
		if(res == RES_OK)
			this->cantidadElem  ++;

		return res;

	} else {
		//debo insertar recursivamente
		res = raiz->insertarElemento(nroBloque, nroRegistro, dato);

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
}

Nodo* Arbol::crearRaiz() {

	Nodo* nuevaRaiz = this->crearNuevoNodo('H');
	return nuevaRaiz;
}

Nodo* Arbol::crearNuevoNodo(char tipo) {

	Nodo* nuevoNodo = NULL;
	if (tipo == 'H') {
		nuevoNodo = new NodoHoja();
	} else {
		//nuevoNodo = new NodoInterno();
	}

	this->persistir->agregarNodo( nuevoNodo);
	return nuevoNodo;

}

Nodo* Arbol::getRaiz(){
	return this->raiz;
};
