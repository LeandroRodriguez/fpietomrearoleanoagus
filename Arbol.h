#ifndef ARBOL_H_
#define ARBOL_H_

#include "Nodo.h"
#include "ManejoArchivos/PersistenciaArbol.h"
#include <list>
#include <typeinfo>

class PersistenciaArbol;

class Arbol {
    private:
	Nodo* raiz;

    public:
	int long cantidadElem;

    Nodo* DevolverNodoSegunID(int IDnodo);

	Arbol(PersistenciaArbol* persistencia);
	virtual ~Arbol();

	Resultado insertar(offset nroBloque, offset nroRegistro, Key* dato);

	Nodo* getRaiz();

    NodoHoja* crearRaiz();

	Nodo* crearNuevoNodo(int nivel,char tipo) ;

	void imprimir();

	void actualizarNodo(Nodo* nodoAActualizar);

	void ultimosAdisco();

private:
	PersistenciaArbol* persistir;

};




#endif /* ARBOL_H_ */
