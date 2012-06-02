#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include "Indice.h"
#include "ManejoArchivos/AlmacenamientoBloque.h"
#include "exception"
#include "string"
#include "iostream"
#include <iostream>
#include "ManipuladorArchivos.h"

using namespace std;

class Controlador {
	string archivoArbol;/*nombre del archivo con el indice(mi arbol)*/

public:
	Indice* indice;
	// Crea el controlador y levanta todos los indices en /Archivos/Indices/
	Controlador();
	virtual ~Controlador();

	/*Inserto el dato pasado por parametro tanto en el archivo de data, como sus referencias en el arbol*/
	void InsertarDato(Key* dato);
	bool BuscarDato(Key* dato);
	list<Key*>* BuscarTrenesConFallaSegunFecha(string falla, string fechaInicio, string fechaFin);
	list<Key*>* BuscarTrenesConAccidenteSegunFecha(string accidente, string fechaInicio, string fechaFin);
	list<Key*>* BuscarTrenesConFormacionSegunFecha(string formacion, string fechaInicio, string fechaFin);
	list<Key*>* BuscarSegunFecha(string subclave, int dim , string fechaInicio, string fechaFin);

	void ListarTenesPorFalla(string falla, string fechaInicio, string fechaFin);
	void ListarTenesPorAccidente(string accidente, string fechaInicio, string fechaFin);
	void ListarFallasPorFormacion(string formacion, string fechaInicio, string fechaFin);
	void ListarAccidentesPorFormacion(string formacion, string fechaInicio, string fechaFin);
	void ListarFallas();
	void ListarForcaciones();
	void ListarLineas();
	void ListarAccidentes();

    void InsertarDatosCargaInicial(list<Key*>* listaDatos);

    list<Key*>* getListaKey(string path);

};

#endif /* CONTROLADOR_H_ */
