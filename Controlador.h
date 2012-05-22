#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include "Constantes.h"
#include "Datos/Bytes.h"
#include "Almacenamiento/Almacenamiento.h"
#include "Almacenamiento/AlmacenamientoBloque.h"
#include "Datos/Bloque.h"
#include "Datos/Registro.h"
#include "Datos/RegistroVariable.h"

//#include "Datos/ClaveNumero.h"
//#include "Datos/Clave.h"
#include "AccesoAMails/AccesoAEmails.h"
#include "Indices/Indice.h"
#include "Indices/IndiceSeleccion.h"
#include "Indices/IndiceClasificacion.h"

#include "Controlador.h"
#include "exception"
#include "string"
#include "iostream"
#include <iostream>
#include "ManipuladorArchivos.h"

using namespace std;

class Controlador {

	vector<string> archivosClasificacion;
	vector<string> archivosSeleccion;
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


protected:


	//REUTILIZABLE? -> void cargarArchivos();

	// Obsoletos?...
	/*
	void DescargoMailsCreoIndice(TipoClasificacion tipo,string palabra);
	void DescargoMailsCreoIndiceFrom(string from);
	void DescargoMailsCreoIndiceTo(string to);
	void DescargoMailsCreoIndiceSubject(string subject);
	void DescargoMailsCreoIndiceClasificacion(TipoClasificacion tipo);
	void DescargoMailsCreoIndice();
	void MailsCreoIndice(string palabra);
	*/
	// ...Fin Obsoletos?
};

#endif /* CONTROLADOR_H_ */
