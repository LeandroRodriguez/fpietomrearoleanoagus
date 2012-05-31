#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

//#include "ManejoArchivos/Almacenamiento.h"
//#include "Datos/Registro.h"
//#include "Key.h"

//#include "Datos/ClaveNumero.h"
//#include "Datos/Clave.h"
#include "Indice.h"
//#include "ManejoArchivos/Bytes.h"
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

	void ListarTenesPorFalla(string falla);
	void ListarTenesPorAccidente(string accidente);
	void ListarFallasPorFormacion(int formacion);
	void ListarAccidentesPorFormacion(int formacion);
	void ListarFallas();
	void ListarForcaciones();
	void ListarLineas();
	void ListarAccidentes();

    void InsertarDatosCargaInicial(list<Key*>* listaDatos);
};

#endif /* CONTROLADOR_H_ */
