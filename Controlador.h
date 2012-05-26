#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

/*#include "Constantes.h"*/
/*#include "ManejoArchivos/Bytes.h"*/
//#include "ManejoArchivos/Almacenamiento.h"
#include "ManejoArchivos/AlmacenamientoBloque.h"
/*#include "ManejoArchivos/Bloque.h"*/
//#include "Datos/Registro.h"
/*#include "ManejoArchivos/RegistroVariable.h"*/
//#include "Key.h"

//#include "Datos/ClaveNumero.h"
//#include "Datos/Clave.h"
#include "Indice.h"

#include "exception"
#include "string"
#include "iostream"
#include <iostream>
#include "ManipuladorArchivos.h"

using namespace std;

class Controlador {
	string archivoPrimario;/*nombre del archivo con el indice(mi arbol)*/

public:

	// Crea el controlador y levanta todos los indices en /Archivos/Indices/
	Controlador();
	virtual ~Controlador();

	/*Inserto el dato pasado por parametro tanto en el archivo de data, como sus referencias en el arbol*/
	void InsertarDato(Key* dato);

	/*ListarTenesPorFalla(falla);
	ListarTenesPorAccidente(accidente);
	ListarFallasPorFormacion(formacion);
	ListarAccidentesPorFormacion(formacion);
	ListarFallas();
	ListarForcaciones();
	ListarLineas();
	ListarAccidentes();*/
};

#endif /* CONTROLADOR_H_ */
