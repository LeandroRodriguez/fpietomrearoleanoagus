#ifndef REGISTROVARIABLE_H_
#define REGISTROVARIABLE_H_

#include <stdlib.h>
#include "Bytes.h"
#include "../Constantes.h"
#include <string>
#include <string.h>

class Utils;

class RegistroVariable {

protected:
	Bytes dato;
	bool vivo;
	uint32 nRegistro;
	cantBytes tamanioDato;

public:
	RegistroVariable(const Bytes& dato);
	virtual ~RegistroVariable();

	void setDato(const Bytes& dato);
	Bytes getDato() const;
	bool estaVivo() const;
	void matar();
	Bytes serializarse();
	void hidratarse(const Bytes& cadena);
	cantBytes getTamanioSerializado();
	uint32 getNRegistro(){return this->nRegistro;}
	void setNRegistro(const uint32& UID){this->nRegistro = UID;}
};

#endif /* REGISTROVARIABLE_H_ */
