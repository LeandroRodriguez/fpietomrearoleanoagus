#ifndef BLOQUE_H_
#define BLOQUE_H_

/*#include "../Constantes.h"*/
/*#include "Bytes.h"*/
#include "RegistroVariable.h"

#include <list>
using namespace std;

class Bloque {

protected:

	list<RegistroVariable*> registros; /*registros fisicos guardados en el bloque*/

public:

	cantBytes tamanio; /*tamanio limite del bloque, ningun reg puede pesar mas que esto*/
	cantBytes usados; /*tamanio en uso*/
	uint32 nBloque; /*nro del bloque(unsigned int)*/
	uint32_t IUC; /*nose*/

	Bloque(const cantBytes& tamanio); /*constructor*/
	Bloque();
	virtual ~Bloque();/*destructor*/

	/*se devuelve a si mismo, como cadena de clase Bytes */
	Bytes serializarse();

	/*se carga con los datos de una cadena de Bytes */
	void hidratarse(const Bytes& bytes);

	/*agrega un registro variable */
	bool agregarRegistro(RegistroVariable* registro);

	/*esta funcion DEVUELVE TRUE SIEMRE... aca hay un error  */
	/*bool agregarEspacioNulo();*/

	/*se fija si tiene lugar para agregar un registro.True si tiene, false sino*/
	bool tieneLugar(RegistroVariable* registro);

	/*En base al numero de registro, te devuelve el registro en cuestión.Devuelve un string vacio si no tiene nada en esa posicion relativa */
	Bytes obtenerRegistro(uint32_t nRegistro);

	/*NO se le pasa ningun parametro, y no esta implementada....HUMO */
	/*Solucion: dado el numero de registro, lo modifica y le setea un parametro en false, asi al serializar, no lo guarda*/
	bool eliminarRegistro();

	/*Devuelve el tamanio del bloque serializado.O sea, el tamanio de construccion, ya que los bloques son fijos*/
	cantBytes getTamanioSerializado();

	/*Devuelve el espacio que le queda libre*/
	cantBytes getEspacioLibre();
};

#endif /* BLOQUE_H_ */
