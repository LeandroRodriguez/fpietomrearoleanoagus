#ifndef ARBOL_H_
#define ARBOL_H_

/*#include "Constantes.h"*/
/*#include "Nodo.h"*/
#include "ManejoArchivos/PersistenciaArbol.h"
#include <list>

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

private:
	PersistenciaArbol* persistir;

};




#endif /* ARBOL_H_ */
