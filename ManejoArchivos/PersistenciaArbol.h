#ifndef PERSISTENCIAARBOL_H_
#define PERSISTENCIAARBOL_H_

#include <iostream>
#include <fstream>
#include "string"
#include "exception"
#include "iostream"/* por que va con " " esto?  */
#include "../NodoHoja.h"
#include "../NodoInterno.h"

class PersistenciaArbol {

protected:
	/*aca tengo el archivo con el que interactuo (el de nodos)*/
	fstream archivo;
	/*tendria que poner otro para el de datos?*/

	/*devuelvo el nro de nodo correspondiente para un nuevo nodo (autoincremental)=>(ultimoNroNodo+1). devuelvo -1 si*/
	offset NroNodoNuevo();

public:
	/*creo o abro el archivo al final, para editarlo*/
	PersistenciaArbol(string nombreArchivo);
	PersistenciaArbol();
	/*cierro el archivo, si esta abierto*/
	virtual ~PersistenciaArbol();

	/*guardo un nodo nuevo. Si pudo insertar retorno el nro de nodo*/
	offset agregarNodo(Nodo* nodo);
	/*devuelvo true si pude actualizar, false si no*/
	bool ActualizarNodo(Nodo* nodo);
	/*devuelvo true si pude actualizar, false si no*/
	bool guardarRaiz(Nodo* nodo);
	/*devuelvo puntero al nodo raiz del archivo*/
	Nodo* obtenerRaiz();
	/*me pasan un nro de nodo y devuelvo un puntero a ese nodo si existe. si hay algun error devuelvo null*/
	Nodo* leerNodo(offset nroNodo);
	/*si el archivo fue abierto, me fijo si esta vacio*/
	bool isVacio();
	/*me fijo si esta el nro de bloque buscado*/
	bool existeBloque(offset nro);


	// el bloque 0 para metadatos.
	/*devuelve un string de metadatos(bloque 0)*/
	char* leerMetaDatos();
	/*guardo los metadatos del arbol. Devuelve true si se pudo guardar, false si no*/
	bool cargarMetaDatos(char* metaData, long int tamanio);



};

#endif /* PERSISTENCIAINDICES_H_ */
