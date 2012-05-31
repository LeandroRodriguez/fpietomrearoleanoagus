/*
 * Bloque.cpp
 *
 *	¿Commenting?: Leo
 */

#include "Bloque.h"

/*constructor*/
Bloque::Bloque(const cantBytes& tamanio) {
	this->tamanio = tamanio;
	this->usados = 0;
	this->registros = new list<RegistroVariable*>();
	/*el nroBloque se lo setean desde afuera*/
	/*IUC sigo sin saber que es, pero tmp se inicializa*/
}

    Bloque::Bloque(){}

/*destructor*/
Bloque::~Bloque() {

}

/*devuelve true si el registro se pudo insertar, false si no se pudo*/
bool Bloque::agregarRegistro(RegistroVariable* registro) {
	/*obtengo el tamanio que ocupa serializado*/
	cantBytes tamanioSerializado = registro->getTamanioSerializado();
	/*me tendria que fijar con ese tamanio, si entra en el bloque*/

	//uint32 ultimoIUC = this->IUC;

	/* esto se debise descomentar para mi
	if (!tieneLugar(registro)) {
		cerr << "Error: No hay lugar para el registro que desea ingresar." << endl;
		return false;
	}
	 */

	/*verifico que el registro no sea nulo, e inserto*/
	if (registro != NULL) {
		this->registros->push_back(registro);
    	} else {
    		cerr << "Error: Se intento agregar un registro nulo.";
    	}
	/*aumento la cant de tam usado, segun al tamanio serializado del registro que quiero ingresar*/
	this->usados += tamanioSerializado;

	//guardar en un archivo el nuevo espacio que queda en el bloque

	return true;
}

/*nose que carajo sear esta cosa hardcodeada fea ni pa que sirve*/
/*bool Bloque::agregarEspacioNulo() {
	return true;
}*/

/*devuelve la tira de bytes del objeto serializado*/
Bytes Bloque::serializarse() {
	int espacioLibre;

	//Bytes serializacion;
	/*defino un iterador para recorrer mi lista de registros*/
	string serializacion = "";
	list<RegistroVariable*>::iterator it = this->registros->begin();

	//Serializar cada uno de los registros y los voy metiendo todos juntos en una cadena
	for ( ; it != this->registros->end(); it++) {
		//le pido al reg que se serialize
		Bytes registroSerializado = (*it)->serializarse();
		serializacion += (registroSerializado.toString());
	}

	//lleno el espacio libre con 0's
	espacioLibre = this->tamanio - this->usados;

	string stringNulo;

	for (int i = 0; i < (espacioLibre); i++) {
		stringNulo += "0";
	}

	Bytes bytesNulos(stringNulo);
	serializacion+=(bytesNulos.toString());
	//creo un string con tantos 0 como espacio libre tenga,
	//y lo agrego al final de mi serializacion

	Bytes b;
	b.agregar(serializacion, 0);

	return b;
}

/*recupero mi objeto a partir de una tira de bytes*/
void Bloque::hidratarse(const Bytes& bytesBloque) {

	cantBytes tamanio = bytesBloque.getTamanio();/*consigo la cant de bytes pasados*/
	cantBytes tamanioDato = 0;
	cantBytes tamanioUsado = 0;

	int i = 0;
	/*cantBytes es un tipo definido en ctes como un long int*/
	if (tamanio < LONGITUD_CANT_BYTES) {
		cerr << "El tamanio del bloque es muy chico (" << tamanio << ")"<< endl;
		return;
	}

	bool seguir = true;
	bool pasoCero = false;

	while (seguir) {
		/*int = atoi(string)*//*mas info http://www.cplusplus.com/reference/clibrary/cstdlib/atoi/ */
		/*obtengo los bytes del bloque pasado desde (tamanioUsado + i * LONGITUD_CANT_BYTES * 2) hasta (LONGITUD_CANT_BYTES)
		 *eso lo paso a string y le agrego el caracter de fin de linea
		 *este string es el que convierto en un int con atoi

		Como tamanioUsado=0 y i=0 en la primera levanto los primeros 8 bytes.*/
		cantBytes datoUID = atoi(bytesBloque.getSubBytes(tamanioUsado + i * LONGITUD_CANT_BYTES * 2 + i, LONGITUD_CANT_BYTES).toString().c_str());
		/*si pasoCero(o sea, ya paso el bloque con UID=0) y no levante bytes, corto*/
		if ((datoUID == 0)&&(pasoCero))
		{
			i--; /* vuelvo 8 bytes atras*/
			break;
		}
		/*levanto los siguientes 8 bytes (primer ciclo)*/
		tamanioDato = atoi(bytesBloque.getSubBytes(tamanioUsado + i * LONGITUD_CANT_BYTES * 2 + LONGITUD_CANT_BYTES + i, LONGITUD_CANT_BYTES).toString().c_str());
		/*si no levante bytes corto*/
		if (tamanioDato == 0) {
			//cerr << "salame" << endl;
			i--;
			break;
		}

		string a = bytesBloque.getSubBytes(tamanioUsado + i * LONGITUD_CANT_BYTES * 2 + LONGITUD_CANT_BYTES*2 + i,1).toString();
		bool vivo = (a=="1");


		/*levanto a partir de los bytes del paso anterior (primer ciclo) segun tamanioDato, y ahora no lo convierto en int*/
		Bytes dato = bytesBloque.getSubBytes(LONGITUD_CANT_BYTES * 2 + i * LONGITUD_CANT_BYTES * 2 + tamanioUsado + i + 1,tamanioDato);
		/*Aca es donde recupero el dato en formato de Bytes*/

		/*aumento i para desplazarme sobre la tira de BytesBloques*/
		i++;

		/*Hidrato mi registro variable con la cadena de bytes del dato*/
		RegistroVariable* registro = new RegistroVariable(dato);
		registro->setNRegistro(datoUID);
		registro->setVivo(vivo);
		agregarRegistro(registro);
		/*Seteo todos sus atributos y lo agrego al bloque*/

		tamanioUsado = tamanioUsado + tamanioDato;
		/*Voy aumentando el tamanio usado del bloque*/

		/*si paso el dato UniqueId de valor 0 seteo esta variable en true*/
		if (datoUID == 0) pasoCero=true;
	}
	/*finalmente seteo tamanios*/
	this->tamanio = tamanio;
	this->usados = tamanioUsado + i * LONGITUD_CANT_BYTES * 2 + LONGITUD_CANT_BYTES * 2;

}

/*true si tiene lugar para insertar el registro pasado, false si no*/
bool Bloque::tieneLugar(RegistroVariable* registro) {

	cantBytes tamanioDelNuevo = registro->getTamanioSerializado();

	if (this->tamanio >= tamanioDelNuevo + this->usados) {
		return true;
	} else {
		return false;
	}
}

/*Los bloques son de tamanio fijo*/
cantBytes Bloque::getTamanioSerializado() {
	return this->tamanio;
}

/*devuelve espacio libre*/
cantBytes Bloque::getEspacioLibre() {
	return (this->tamanio - this->usados);
}

/*devuelvo tira de bytes de un registro segun su UID*/
Bytes Bloque::obtenerRegistro(uint32_t nRegistro){
	Bytes registroBuscado;

	list<RegistroVariable*>::iterator it = this->registros->begin();
	/*busco en la lista si encuentro el UID dado. Si lo encuentro devuelvo el dato, sino un string vacio*/
	while (it != this->registros->end()) {
		RegistroVariable* registro = (RegistroVariable*)*it;
		Bytes dato = registro->getDato();
		uint32 UID = registro->getNRegistro();
		if  (UID == nRegistro) {
			return dato;
		}
		it++;
	}

	return Bytes("");

}
