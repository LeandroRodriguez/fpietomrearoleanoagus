#include "Arbol.h"
#include <string.h>

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

	if (!raiz) {//lazy initialization ?
		//Es el primerElemento
		Nodo* aaa = this->crearRaiz();
		this->raiz = (NodoHoja*) (aaa);
		aaa->setIdDelNodo(ID_RAIZ);

		res = raiz->insertarElemento(nroRegistro, nroBloque , dato, 1);
		if(res == RES_OK){
			this->cantidadElem  ++;
			this->actualizarNodo(this->raiz);
		}

		return res;

	} else {
		//debo insertar recursivamente
		res = raiz->insertarElemento(nroRegistro, nroBloque, dato, 1);
		this->ultimosAdisco();
		if(res == RES_OK)
			this->cantidadElem  ++;

		return res;
	}
}


void Arbol::ultimosAdisco() {
	/* La raiz la guardo siempre*/
	this->persistir->guardarRaiz(this->raiz);
	//this->actualizarNodo(this->raiz);
	//raiz = this->getNodo(1);
	/*Guardo solo los bloques que se modificaron*/
	/*for (list<Nodo*>::iterator it = ultimosAccedidos.begin(); it
			!= ultimosAccedidos.end(); ++it) {
		if ((*it)->getModificado() && (*it)->getId() != this->raiz->getId()) {
			this->actualizarNodo((*it));
		}
		if((*it)->getId() != this->raiz->getId())
			delete(*it);

	}

	ultimosAccedidos.clear();*/
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
	else{
		cout << "EL ARBOL NO TIENE ELEMENTOS " << endl;
	}
}

