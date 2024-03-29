#ifndef REGISTROVARIABLE_H_
#define REGISTROVARIABLE_H_

#include <stdlib.h>
#include "Bytes.h"
#include <string>
#include <string.h>

class Utils;

class RegistroVariable {

protected:
	Bytes dato;
	bool vivo;
	uint32 nRegistro;

public:
	RegistroVariable(const Bytes& dato);
	RegistroVariable();
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
	void setVivo(bool vivo){this->vivo = vivo;}
};

#endif /* REGISTROVARIABLE_H_ */
