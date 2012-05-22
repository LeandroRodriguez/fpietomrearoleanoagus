#ifndef ARBOL_H_
#define ARBOL_H_

#include "Constantes.h"
#include "Nodo.h"
#include "PersistenciaArbol.h"
#include <list>

class PersistenciaArbol;

class Arbol {
	Nodo* raiz;
	
public:
	int long cantidadElem;
	
	Arbol(PersistenciaArbol* persistencia);
	virtual ~Arbol();
	
	Resultado insertar(offset nroBloque, offset nroRegistro, Key* dato);
	
	Nodo* getRaiz();	
	
private:
	PersistenciaArbol* persistir;

}




#endif /* ARBOL_H_ */