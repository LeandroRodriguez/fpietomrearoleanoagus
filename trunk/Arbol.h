#ifndef ARBOL_H_
#define ARBOL_H_

#include "Nodo.h"
#include "Dato.h"
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

//	void ultimosAdisco();

	void cargaInicial(list<Dato*>* listaDeDatos);

	list<Dato*>* obtenerListaOrdenadaPorDimension(list<Dato*>* lista, int dimension);

	Dato* getElemento (list<Dato*>* lista, int index);

	void setElemento (list<Dato*>* lista, int index, Dato* dato);

	int cargaInicialConseguirParticionConNivel(list<Dato*>* subListaOrdenada, list<SubClaveRef<int>*>* listaClaves, list<list<Dato*>*>* listaListasDatosSubArboles, int  porcentajeDeEmpaquetamiento);

	int cargaInicialConseguirParticionConNivel(list<Dato*>* subListaOrdenada, list<SubClaveRef<string>*>* listaClaves, list<list<Dato*>*>* listaListasDatosSubArboles, int  porcentajeDeEmpaquetamiento);

	int conseguirNivelMayor(list<int>* listaMaestraNiveles);

	void* obtenerClavesSegunPos(list<list<SubClaveRef<int>*>*>* listaMaestraClaves, int j, int dimension);

	void* obtenerClavesSegunPos(list<list<SubClaveRef<string>*>*>* listaMaestraClaves, int j, int dimension);

	list<list<Dato*>*>* obtenerListasSegunPos(list<list<list<Dato*>*>*>* listaMaestraDatosSubArboles, int j);


	offset obtenerReferenciaNodosSegunPos(list<offset>* listaReferenciasNodosHios, int j);


	void* partirSubarbol(list<list<Dato*>*>* listaDatosSubArbol, int dimension, list<list<Dato*>*>* listasDatosSubArbolesNuevos);

	void reemplazarDatoListaDatos(list<list<list<Dato*>*>*>* listaMaestraDatosSubArboles, list<list<Dato*>*>* listasDatosSubArbolesNuevos, int j);

	void reemplazarDatoListaClaves(list<list<SubClaveRef<int>*>*>* listaMaestraClaves, list<SubClaveRef<int>*>* claveMediana, int j);

	void reemplazarDatoListaClaves(list<list<SubClaveRef<string>*>*>* listaMaestraClaves, list<SubClaveRef<string>*>* claveMediana, int j);

	offset insertarDatosEnNodoHoja(list<Dato*>* listaSubSubArboles, double porcentaje);

	offset insertarDatosEnNodoInterno(list<list<SubClaveRef<int>*>*>* listaMaestraClaves, list<offset>* listaReferenciasNodosHios, int i, int dimension);

	offset insertarDatosEnNodoInterno(list<list<SubClaveRef<string>*>*>* listaMaestraClaves, list<offset>* listaReferenciasNodosHios, int i, int dimension);

	list<offset>* insertarHijosEnNodoPadre(list<list<SubClaveRef<int>*>*>* listaMaestraClaves, list<offset>* listaRefsNodosArmados, int dimension);

	list<offset>* insertarHijosEnNodoPadre(list<list<SubClaveRef<string>*>*>* listaMaestraClaves, list<offset>* listaRefsNodosArmados, int dimension);

	list<offset>* cargaInicialArmarNodos(list<list<list<Dato*>*>*>* subListasDatos, int dimension, double porcentajeDeEmpaquetamiento);

private:
	PersistenciaArbol* persistir;

	Resultado LazyInicialization(offset nroBloque,offset nroRegistro,Key* dato);

};




#endif /* ARBOL_H_ */
