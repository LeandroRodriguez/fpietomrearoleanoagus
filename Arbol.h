#ifndef ARBOL_H_
#define ARBOL_H_

#include "ManejoArchivos/PersistenciaArbol.h"
#include <list>
#include <typeinfo>

class Arbol {
    private:
	Nodo* raiz;

    public:
	int long cantidadElem;

	Arbol(PersistenciaArbol* persistencia);
	virtual ~Arbol();

	Resultado insertar(offset nroBloque, offset nroRegistro, Key* dato);

	Nodo* getRaiz();

	Nodo* crearRaiz();

	Nodo* crearNuevoNodo(char tipo) ;

	void imprimir();

private:
	PersistenciaArbol* persistir;

};




#endif /* ARBOL_H_ */
