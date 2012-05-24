#include "PersistenciaArbol.h"

/*creo o abro el archivo al final, para editarlo*/
PersistenciaArbol::PersistenciaArbol(string nombreArchivo) {
	// en caso de que exista lo abro al final
	archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::ate | ios::binary);

	if (archivo.fail()) {
		// Si no existe lo crea.
		archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::trunc
			| ios::binary);
	}

}

/*cierro el archivo, si esta abierto*/
PersistenciaArbol::~PersistenciaArbol() {
	if (archivo.is_open())
		archivo.close();
}

/*si el archivo fue abierto, me fijo si esta vacio*/
bool PersistenciaArbol::isVacio(){
	/*primero me fijo que este abierto y que no tenga seteado ningun flag de error(badbit, eofbit o failbit)*/
	if (archivo.is_open() && archivo.good()) {
		/*apunto el get pointer al final del archivo. (0, end) -> offset 0 desde el final*/
		this->archivo.seekg(0, ios::end);
		/*si la posicion del get pointer es 0 (estoy al comienzo, o sea fin = comienzo => vacio) el archivo esta vacio*/
		if (this->archivo.tellg() ==0 )
			return true;

	}

	return false;
}
/*me fijo si esta el nro de bloque buscado*/
bool PersistenciaArbol::existeBloque(offset nro){
	/*no estoy comprobando que el archivo este abierto ni revisando los flags*/
	/*apunto el get pointer al final del archivo*/
	this->archivo.seekg(0, ios::end);
	/*me fijo si el get pointer esta posicionado mas alla del numero de bloque pasado, sino no hay tal bloque*/
	if (nro  * LONGITUD_BLOQUE_NODO > archivo.tellg()){
		return false;
	}else
		return true;
}

/*devuelvo el nro de nodo correspondiente para un nuevo nodo (autoincremental)=>(ultimoNroNodo+1). devuelvo -1 si el archivo no esta abierto o no es good()*/
offset PersistenciaArbol::NroNodoNuevo(){
	/*primero me fijo que este abierto y que no tenga seteado ningun flag de error(badbit, eofbit o failbit)*/
	if (archivo.is_open() && archivo.good()) {
		/*me posiciono al final*/
		this->archivo.seekg(0, ios::end);
		/*mi posicion final/longBloqNodo me va a decir cual es el nro nodo correpondiente*/
		offset nro= ((this->archivo.tellg() / LONGITUD_BLOQUE_NODO))  ;

		return nro;
	}else
		return -1;

}

/*devuelvo true si pude actualizar, false si no*/
bool PersistenciaArbol::ActualizarNodo(Nodo* nodo){

		/*hago un par de chequeos*/
		if (!archivo.is_open()){
			cerr<< "Problemas al intentar abrir el archivo"<< endl;
			return false;
		}

		if (! this->existeBloque( nodo->getId())){
			cerr<< "Metodo: Actualizar. Nro de bloque inexistente. Nro: "<< nodo->getId();
			return false;
		}

		if (nodo->getId() == ID_RAIZ){
			cerr<< "Metodo: ActualizarNodo. Se quiere guardar la raiz con el metodo inorrecto." << endl;
			return NULL;
		}



		/*creo un string auxliar para guardar la cadena total que dps voy a guardar en el archivo*/
		char auxiliar[LONGITUD_BLOQUE_NODO ];
		/*serializo el nodo*/
		char* serial = nodo->Serializar();

		/*consigo el tamanio serializado y verifico que enre en un bloque*/
		unsigned long int tam= nodo->getTamanioSerializado();
		if (tam + 1 > LONGITUD_BLOQUE_NODO ){
			cerr<<"Dato Mayor al tamaño de bloque."<<endl;
			return false;
		}
		/*en la pos 0 guardo si es hoja o interno*/
		auxiliar[0] = nodo->getHojaOInterno();
		/*y en los restantes copio el serial del nodo*/
		for (unsigned int i = 1; i < tam +1; i++) {
			auxiliar[i] = serial[i - 1];
		}

		/*posiciono el get pointer en el principio + Long*nroBloque (al ppio del bloque a actualizar)*/
		archivo.seekg((nodo->getId()) * LONGITUD_BLOQUE_NODO , ios::beg);
		/*escribo en el archivo y guardo*/
		archivo.write(auxiliar, LONGITUD_BLOQUE_NODO);
		archivo.flush();
		/*libero el serial auxiliar que use*/
		free(serial);
		return true;
}

/*devuelvo puntero al nodo raiz del archivo*/
Nodo* PersistenciaArbol::obtenerRaiz(){
	/*valido apertura del archivo y que exista el bloque raiz (1)*/
	if (!archivo.is_open()){
		cerr<< "Problemas al intentar abrir el archivo"<< endl;
		return NULL;
	}

	if (! this->existeBloque( ID_RAIZ )){
		cerr<< "Metodo: LeerNodo. Nro de bloque inexistente, Nro: " << ID_RAIZ;
		return NULL;
	}

	/*Posiciono el get pointer en el principio + (longBloque*1) */
	archivo.seekg((ID_RAIZ ) * LONGITUD_BLOQUE_NODO , ios::beg);

	/*pido memoria para levantar la raiz*/
	char* lectura = (char*) malloc (sizeof(char) * LONGITUD_BLOQUE_NODO);

	unsigned char lectura2[LONGITUD_BLOQUE_NODO];
	archivo.read(reinterpret_cast<char*> (lectura2), LONGITUD_BLOQUE_NODO);
	/*copio la lectura 1 caracter corrido para no levantar el flag si es hoja o interno*/
	for (unsigned int i = 0; i < (LONGITUD_BLOQUE_NODO) -1 ; i++) {
		lectura[i] = lectura2[i+1];
	}

	Nodo* auxiliar = NULL;
	/*aca evaluo el flag de tipo de nodo y creo el objeto correspondiente*/
	if  ( lectura2[0] == 'H' ){
		auxiliar = new NodoHoja(lectura);
	}else if  (lectura2[0] == 'I' ){
		auxiliar = new NodoInterno(lectura );
	}


	/*libero la memoria de la lectura y retorno el puntero a la raiz*/
	free(lectura);
	archivo.flush();

	return auxiliar;

}

/*devuelvo true si pude actualizar, false si no*/
bool PersistenciaArbol::guardarRaiz(Nodo* nodo){
	/*Si no existe el archivo, se crea¿?*/
	if (!archivo.is_open()){
		cerr<< "Problemas al intentar abrir el archivo"<< endl;
		return 0;
	}

	/*seteo el id raiz (1)*/
	offset 	rta = ID_RAIZ;
	nodo->setId(rta);
	/*levanto el raiz viejo*/
	char auxiliar[LONGITUD_BLOQUE_NODO];
	char* serial = nodo->serializar();
	/*me fijo el tamanio serializado del candidato a insertar*/
	unsigned long int tam= nodo->getTamanioSerializado();
	if (tam + 1> LONGITUD_BLOQUE_NODO){
		cerr<<"Dato Mayor al tamaño de bloque."<<endl;
		return false;
	}
	/*consigo el flag de Hoja o Interno y lo guardo en la pos 0*/
	auxiliar[0] = nodo->getHojaOInterno();

	/*y en los restantes copio el serial del nodo*/
	for (unsigned int i = 1; i < tam +1; i++) {
		auxiliar[i] = serial[i - 1];
	}

	/*me posiciono*/
	archivo.seekg((rta ) * LONGITUD_BLOQUE_NODO, ios::beg);
	/*escribo y guardo*/
	archivo.write(auxiliar, LONGITUD_BLOQUE_NODO);
	archivo.flush();
	/*libero el serial auxiliar que use y retono*/
	free(serial);
	return true;
}

/*guardo un nodo nuevo. Si pudo insertar retorno el nro de nodo*/
 offset PersistenciaArbol::agregarNodo(Nodo* nodo){
	/*Si no existe el archivo, se crea¿?*/
	if (!archivo.is_open()){
		cerr<< "Problemas al intentar abrir el archivo"<< endl;
		return 0;
	}

	if (  nodo->getId() == ID_RAIZ){
		/*aca lo podria mandar al metodo guardar raiz, nose :(*/
		cerr<< "Metodo: AgregarNodo. Se quiere guardar la raiz con el metodo inorrecto." << endl;
		return NULL;
	}

	/* busco nodo libre*/
	offset 	rta = this->NroNodoNuevo();
	nodo->setId(rta);

	/*borrar
	if (nodo->getId() == 9){
		cerr<< "aca" << endl;
	}*/

	/*pido el serial y me fijo que entre*/
	char auxiliar[LONGITUD_BLOQUE_NODO ];
	char* serial = nodo->serializar();

	unsigned long int tam= nodo->getTamanioSerializado();
	if (tam + 1 > LONGITUD_BLOQUE_NODO ){
		cerr<<"Dato Mayor al tamaño de bloque."<<endl;
		return false;
	}

	/*pongo el flag en la pos 0 y copio el serial*/
	auxiliar[0] = nodo->getHojaOInterno();

	for (unsigned int i = 1; i < tam +1; i++) {
		auxiliar[i] = serial[i - 1];
	}

	/*me posiciono, escribo y guardo*/
	archivo.seekg((rta ) * LONGITUD_BLOQUE_NODO , ios::beg);

	archivo.write(auxiliar, LONGITUD_BLOQUE_NODO);
	archivo.flush();
	/*libero el serial y retorno el nro de nodo*/
	free(serial);
	return rta;
}

/*me pasan un nro de nodo y devuelvo un puntero a ese nodo si existe. si hay algun error devuelvo null*/
 Nodo* PersistenciaArbol::leerNodo( offset nroNodo) {
		/*chequeo estado del archivo y que el nro nodo sea correcto*/
		if (!archivo.is_open()){
			cerr<< "Problemas al intentar abrir el archivo"<< endl;
			return NULL;
		}

		if ( nroNodo == ID_RAIZ ){
			cerr<< "Metodo: LeerNodo. Se quiere leer la raiz con el metodo inorrecto." << endl;
			return NULL;
		}

		if (! this->existeBloque( nroNodo )){
			cerr<< "Metodo: LeerNodo. Nro de bloque inexistente, Nro: " << nroNodo << endl;
			return NULL;
		}


		/*Posiciono en el registro a leer*/
		archivo.seekg((nroNodo ) * LONGITUD_BLOQUE_NODO , ios::beg);

		char* lectura = (char*) malloc (sizeof(char) * LONGITUD_BLOQUE_NODO);
		/*levanto la cadena de bytes*/
		unsigned char lectura2[LONGITUD_BLOQUE_NODO];
		archivo.read(reinterpret_cast<char*> (lectura2), LONGITUD_BLOQUE_NODO);

		for (unsigned int i = 0; i < LONGITUD_BLOQUE_NODO -1 ; i++) {
			lectura[i] = lectura2[i+1];
		}
		/*creo el nodo correspondiente*/
		Nodo* auxiliar;

		if  ( lectura2[0] == 'H' ){
			auxiliar = new NodoHoja(lectura);
		}else if  (lectura2[0] == 'I' ){
			auxiliar = new NodoInterno(lectura );
		}


		/*libero la lectura que use para levantar la tira de bytes*/
		free(lectura);
		/*guardo el archivo y retorno el puntero al nodo*/
		archivo.flush();

		return auxiliar;
}

/*devuelve un string de metadatos(bloque 0)*/
char* PersistenciaArbol::leerMetaDatos(){
	/*me fijo que el archivo este abierto y no este vacio*/
	if (!archivo.is_open()){
		cerr<< "Problemas al intentar abrir el archivo"<< endl;
		return NULL;
	}

	if (this->isVacio()){
		cerr<<"Archivo vacio"<<endl;
		return NULL;
	}

	/*posiciono el get pointer al ppio del archivo*/
	archivo.seekg(0, ios::beg);
	/*levanto el primer bloque*/
	char* lectura = (char*) malloc (sizeof(char) * LONGITUD_BLOQUE_NODO);

	unsigned char lectura2[LONGITUD_BLOQUE_NODO];
	archivo.read(reinterpret_cast<char*> (lectura2), LONGITUD_BLOQUE_NODO);
	/*lo copio a mi variable mallocada y la devuelvo*/
	for (unsigned int i = 0; i < LONGITUD_BLOQUE_NODO  ; i++) {
		lectura[i] = lectura2[i];
	}

	return lectura;
}

/*guardo los metadatos del arbol. Devuelve true si se pudo guardar, false si no*/
bool PersistenciaArbol::cargarMetaDatos(char* metadatos, long int tamanio){
	/*me fijo que el archivo este abierto, y que el tamaño no exceda el de bloque*/
	if (!archivo.is_open()){
		cerr<< "Problemas al intentar abrir el archivo"<< endl;
		return false;
	}

	if (tamanio > LONGITUD_BLOQUE_NODO ){
		cerr<< "La informacion a guardar es demasiado grande"<< endl;
		return false;
	}


	/*Metadatos en el bloque 0*/
	offset 	rta = 0;
	char auxiliar[LONGITUD_BLOQUE_NODO];

	for (unsigned int i = 0; i < tamanio; i++) {
		auxiliar[i] = metadatos[i];
	}

	/*me posiciono al ppio del archivo, escribo y guardo*/
	archivo.seekg(0 , ios::beg);

	archivo.write(auxiliar, LONGITUD_BLOQUE_NODO);
	archivo.flush();

	return true;
}
