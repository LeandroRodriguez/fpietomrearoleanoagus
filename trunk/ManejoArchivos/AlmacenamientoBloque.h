#ifndef ALMACENAMIENTOBLOQUE_H_
#define ALMACENAMIENTOBLOQUE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Constantes.h"
//#include "Almacenamiento.h"
#include "Bytes.h"
#include "RegistroVariable.h"
#include "Bloque.h"

using namespace std;

class AlmacenamientoBloque {

private:
	fstream aDatos;
	fstream aLibres;

	string pathDatos;
	string pathLibres;

	bool validoDatos;
	bool validoLibres;

	uint32_t UID; //id autoincremental de los reg variables
	offset numeroBloque; //aca siempre debo dejar el ultimo bloque donde se escribio
	offset cantidadBloques;

public:

	/*abro o creo los archivos*/
	AlmacenamientoBloque(const string &pathDato,const string &pathLibres);
	/*cierro ambos archivos*/
	virtual ~AlmacenamientoBloque();

	void escribirBloque(const Bytes& dato, offset offsetBloque);
	void escribirEspacioLibre(const Bytes& dato);

	void agregarRegistro(RegistroVariable* rv);

	Bytes recuperarBloque(offset nBloque);
	Bytes recuperarRegistro(offset nBloque, uint32_t IUC);

	offset getNumeroBloque(){return this->numeroBloque;}
	offset getNumeroUID(){return this->UID;}
	offset getNumeroBloqueDisponible(cantBytes necesitoLibre);

	offset getUltimoUID();
	offset getUltimoBloque();
	void actualizarBloqueUIDs(int valor);
	void actualizarEspacioLibre(offset nBloqueDisponible, cantBytes ssEspacioLibre);
};


#endif /* ALMACENAMIENTOBLOQUE_H_ */
