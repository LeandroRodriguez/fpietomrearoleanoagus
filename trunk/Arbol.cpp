#include "Arbol.h"

Nodo* Arbol::DevolverNodoSegunID(int IdNodo){
    Nodo* aux = this->persistir->leerNodo(IdNodo);
	aux->setArbol(this);
	return aux;
}

void Arbol::actualizarNodo(Nodo* nodoAActualizar){
	bool respuesta = this->persistir->ActualizarNodo( nodoAActualizar);
    }

Arbol::Arbol( PersistenciaArbol* persistencia) {
	this->persistir=persistencia;
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
		aaa->setIdDelNodo(ID_RAIZ);

		res = raiz->insertarElemento(nroRegistro, nroBloque , dato, 1);
		if(res == RES_OK)
			this->cantidadElem  ++;

		return res;

	} else {
		//debo insertar recursivamente
		res = raiz->insertarElemento(nroRegistro, nroBloque, dato, 1);

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
	Nodo* nuevaRaiz = this->crearNuevoNodo('H',' ');
	return nuevaRaiz;
}

Nodo* Arbol::crearNuevoNodo(char nivel,char tipo ) {

	Nodo* nuevoNodo = NULL;
	if (nivel == 'H') {
		nuevoNodo = new NodoHoja();
	} else {
            if (tipo == 'i')nuevoNodo = new NodoInterno<int>();
            if (tipo == 's')nuevoNodo = new NodoInterno<string>();
      }

	this->persistir->agregarNodo( nuevoNodo);
	return nuevoNodo;

}

Nodo* Arbol::getRaiz(){
	return this->raiz;
}

void Arbol::imprimir(){
	if (raiz != NULL) {
		cout << "EL ARBOL: " << endl;
		this->raiz->imprimir();
	}
	else
		cout << "EL ARBOL NO TIENE ELEMENTOS " << endl;
}

