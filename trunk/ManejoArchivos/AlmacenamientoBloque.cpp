#include "AlmacenamientoBloque.h"

/*abro o creo los archivos*/
AlmacenamientoBloque::AlmacenamientoBloque(const string &pathDato,const string &pathLibres) {
	/*seteo los stream de los archivos*/
	string auxDatos =  DIR_ARCHIVO_DATOS;
	string auxLibres = DIR_ARCHIVO_DATOS;

	auxDatos += pathDato;
	auxLibres += pathLibres;

	this->pathDatos = auxDatos;
	this->pathLibres = auxLibres;

	/*Primero intento crear los directorios por si no existen*/

	/*intento abrir el archivo de datos*/
	this->aDatos.open(auxDatos.c_str(), fstream::in | fstream::out
			| fstream::ate | ios:: binary);

	/*Agregado*/
	if (this->aDatos.fail())
	{
		/*si falle, lo creo*/
		this->aDatos.open(auxDatos.c_str(), ios::in | ios::out | ios::trunc
			| ios::binary);

		/*REARMAR el guardado de registros para lo que necesitamos*/
		/*seteo en 0 los params*/
		this->UID = 0;
		this->numeroBloque = 0;
		this->cantidadBloques = 0;


		/*Creo bloque 0 en donde, por ahora, guardare un registro conteniendo el ultimo UID*/
		Bloque bloqueUIDs(LONGITUD_BLOQUE_DATA);

		/*Creo un registro donde ira solo el ultimo UID*/
		Bytes bytesUID("0"); //deberia castear el inicialUID a string
		RegistroVariable rUID(bytesUID);
		rUID.setNRegistro(this->UID);


		/*Agrego el registro al bloque*/
		bloqueUIDs.agregarRegistro(&rUID);

		/*escribo el bloque en el archivo*/
		Bytes b = bloqueUIDs.serializarse();
		escribirBloque(b, 0);
	}
	else
	{
		/*si se abrio correctamente, obtengo el ultimo UIDy lo seteo*/
		this->UID = getUltimoUID();

	}
	//Hasta aca


	/*
	if (!this->aDatos.is_open()) {
		ofstream aux(pathDato.c_str());
		if (aux.is_open()) {
			aux.close();
		}
		this->aDatos.open(pathDato.c_str(), fstream::binary | fstream::out
				| fstream::in);
	}
	*/

	/*
	this->aLibres.open(pathLibres.c_str(), fstream::binary | fstream::out
				| fstream::in | ios::trunc);

	if (!this->aLibres.is_open()) {
		ofstream aux(pathLibres.c_str());
		if (aux.is_open()) {
			aux.close();
		}
		this->aLibres.open(pathLibres.c_str(), fstream::binary | fstream::out
				| fstream::in | ios::trunc);
	}
	*/

	/*intento abrir el archivo de libres*/
	this->aLibres.open(auxLibres.c_str(), fstream::in | fstream::out
			| fstream::ate | ios:: binary);

	/*Agregado*/
	if (this->aLibres.fail())
	{
		/*si falle, lo creo*/
		this->aLibres.open(auxLibres.c_str(), ios::in | ios::out | ios::trunc
			| ios::binary);
	}
	/*seteo los estados de los archivos, revisando sus flags de error*/
	this->validoDatos = this->aDatos.good();
	this->validoLibres = this->aLibres.good();

}

/*cierro ambos archivos, si estan abiertos*/
AlmacenamientoBloque::~AlmacenamientoBloque() {
	if (this->aLibres.is_open())
		this->aLibres.close();

	if (this->aDatos.is_open())
		this->aDatos.close();
}

/*agrego un registro de datos*/
void AlmacenamientoBloque::agregarRegistro(RegistroVariable* rv){
	/*Primero busco un bloque disponible y despues escribo serializado*/
	/*obtengo el tamanio necesario para guardar el reg nuevo*/
	cantBytes bytesNecesitados = rv->getTamanioSerializado();
	/*obtengo el ultimo UID, para crear mi nuevo registro (autincremental)*/
	uint32_t ultimo = getUltimoUID();/*cambiar funcion del reg VAr -> ahora es UID*/

	/*busco un bloque creado con el espacio disponible, si es que hay*/
	offset nBloqueDisponible = getNumeroBloqueDisponible(bytesNecesitados);
	/*seteo el nro de reg correcto*/
	rv->setNRegistro(ultimo+1);
	if (nBloqueDisponible == 0)
	{
		/*no hay bloque disponible para el tamanio solicitado, entonces creo uno nuevo*/
		/*creo el bloque nuevo*/
		Bloque bloqueTemporal(LONGITUD_BLOQUE_DATA);
		bloqueTemporal.agregarRegistro(rv);
		/*me fijo la cant de bloques que tengo y la multiplico por la long de los bloques, consiguiendo el offset de mi nuevo bloque. Lo escribo*/
		int bloque = this->getUltimoBloque();
		Bytes b = bloqueTemporal.serializarse();
		escribirBloque(b, bloque*LONGITUD_BLOQUE_DATA);
		/*actualizo en el bloque 0 el valor del UID del ultimo reg. (el 1 es porque solo cree 1 nuevo bloque)*/
		actualizarBloqueUIDs(1);

		/*obtengo el espacio libre que quedo en mi nuevo bloque y escribo en el archivo de espacios libres*/
		stringstream ssEspacioLibre;
		ssEspacioLibre << bloqueTemporal.getEspacioLibre();

		escribirEspacioLibre(ssEspacioLibre.str());

		ssEspacioLibre.str("");

		/*actualizo mis parametros*/
		this->UID = ultimo+1;
		this->numeroBloque = getUltimoBloque();
	}
	else
	{
		/*hay bloque disponible, entonces voy a guardar el reg nuevo ahi*/
		/*recupero el bloque segun el nro que obtuve antes. Obtengo su tira de bytes y lo hidrato*/
		Bytes bloqueBytes(recuperarBloque(nBloqueDisponible));
		Bloque bloqueTemporal(LONGITUD_BLOQUE_DATA);
		bloqueTemporal.hidratarse(bloqueBytes);
		/*agrego el nuevo registro al bloque*/
		bloqueTemporal.agregarRegistro(rv);

		/*sobreescribo en el archivo el bloque modificado, en la posicion correspondiente*/
		escribirBloque(bloqueTemporal.serializarse(), (nBloqueDisponible)*LONGITUD_BLOQUE_DATA);
		/*actualizo el ultimo UID guardado en el bloque 0*/
		actualizarBloqueUIDs(1);
		/*obtengo el espacio libre que quedo en mi bloque modificado y actualizo el archivo de espacios libres*/
		stringstream ssEspacioLibre;
		ssEspacioLibre.str("");
		ssEspacioLibre << bloqueTemporal.getEspacioLibre();

		actualizarEspacioLibre(nBloqueDisponible, atoi(ssEspacioLibre.str().c_str()));

		ssEspacioLibre.str("");
		/*actualizo mis parametros*/
		this->UID = ultimo+1;
		this->numeroBloque = nBloqueDisponible;
	}
}

/*escribo el dato pasado en la posicioon pasada*/
void AlmacenamientoBloque::escribirBloque(const Bytes& dato, offset offsetBloque){

	string buffer = dato.toString();
	fstream file;

	file.open(this->pathDatos.c_str());
	/*seteo la posicion del put pointer donde necesito*/
	file.seekp(offsetBloque, ios_base::beg);
	/*escribo y guardo*/
	file.write(buffer.c_str(), LONGITUD_BLOQUE_DATA);
	file.flush();
}

/*escribo los bytes libres*/
void AlmacenamientoBloque::escribirEspacioLibre(const Bytes& libres){
	string buffer = libres.toString();
	buffer.append("\r\n");
	/*escribo y guardo*/
	this->aLibres.write(buffer.c_str(), buffer.size());
	this->aLibres.flush();
}

/*levanto del archivo el bloque pedido*/
Bytes AlmacenamientoBloque::recuperarBloque(offset nBloque){
	Bloque bloqueTemporal(LONGITUD_BLOQUE_DATA);

	ifstream almacenamientoEntrada;

	almacenamientoEntrada.open(this->pathDatos.c_str());

	string stream;
	/* Valido que el offset y la cantidad de bytes sean validos */
	if (almacenamientoEntrada.is_open()) {
		/*seteo el get pointer en la posicion del bloque pedido*/
		almacenamientoEntrada.seekg(nBloque * LONGITUD_BLOQUE_DATA, ios_base::beg);
		char* buffer;
		buffer = new char[LONGITUD_BLOQUE_DATA];

		/*levanto el bloque*/
		almacenamientoEntrada.read(buffer, LONGITUD_BLOQUE_DATA);
		/*paso la lectura a stream y borro el buffer auxiliar*/
		stream.append(buffer, LONGITUD_BLOQUE_DATA);
		delete[] buffer;
	}
	/*creo Bytes con mi stream y lo devuelvo*/
	Bytes bTemporal(stream);
	return bTemporal;
}

/*levanto del archivo el registro pedido*/
Bytes AlmacenamientoBloque::recuperarRegistro(offset nBloque, uint32_t UID){
	Bloque bloqueTemporal(LONGITUD_BLOQUE_DATA);

	ifstream almacenamientoEntrada;

	//almacenamientoEntrada.open(this->pathDatos.c_str());
	almacenamientoEntrada.open(this->pathDatos.c_str());
	string stream;
	/* Valido que el offset y la cantidad de bytes sean validos */
	if (almacenamientoEntrada.is_open()) {
		/*seteo el get pointer en la posicion del bloque donde se encuentra el reg pedido*/
		almacenamientoEntrada.seekg(nBloque * LONGITUD_BLOQUE_DATA, ios_base::beg);
		char* buffer;
		buffer = new char[LONGITUD_BLOQUE_DATA];

		/*levanto el bloque*/
		almacenamientoEntrada.read(buffer, LONGITUD_BLOQUE_DATA);
		/*paso la lectura a stream y borro el buffer auxiliar*/
		stream.append(buffer, LONGITUD_BLOQUE_DATA);
		delete[] buffer;
	}
	/*creo Bytes con mi stream*/
	Bytes bloqueBytes(stream.c_str());
	/*hidrato el bloque recuperado*/
	bloqueTemporal.hidratarse(bloqueBytes);
	/*obtengo el registro que busco del bloque que acabo de levantar, lo armo y devuelvo su dato*/
	Bytes registroBuscado(bloqueTemporal.obtenerRegistro(UID).toString());
	RegistroVariable registroTemporal(registroBuscado);
	return registroTemporal.getDato();
}

/*obtengo el nro de bloque que tenga el espacio buscado*/
offset AlmacenamientoBloque::getNumeroBloqueDisponible(cantBytes necesitoLibre){
	ifstream almacenamientoEntrada;
	this->cantidadBloques = 0;//¿?
	offset bloque = 0;

	almacenamientoEntrada.open(this->pathLibres.c_str());
	/*mientras no haya llegado al fin de linea del archivo de libres busco un bloque que cumpla mis demandas*/
	while(!almacenamientoEntrada.eof())
	{
		char* aux = (char*) malloc (sizeof(char)*LONGITUD_CANT_BYTES);
		/*voy obteniendo de a un bloque y verificando*/
		almacenamientoEntrada.getline(aux,LONGITUD_CANT_BYTES);
		bloque++;
		this->cantidadBloques = this->cantidadBloques+ 1;
		/*me fijo si tiene el espacio, y si lo tiene lo devuelvo*/
		if (necesitoLibre<=(atoi(aux)))
			return bloque;
	}
	/*si no encontre ningun bloque que tenga el espacio buscado, develvo 0*/
	return 0;
}

/*devuelvo el nro del ultimo bloque*/
offset AlmacenamientoBloque::getUltimoBloque(){
	return this->cantidadBloques;
}

/*devuelvo el ultimo UID*/
offset AlmacenamientoBloque::getUltimoUID(){
	/*En el bloque 0 se guardo el ultimo UID*/
	offset offset = 0;
	Bloque bloqueTemporal(LONGITUD_BLOQUE_DATA);

	//ifstream almacenamientoEntrada;
	string stream;

	ifstream almacenamientoEntrada;
	almacenamientoEntrada.open(this->pathDatos.c_str());
	if (almacenamientoEntrada.is_open()) {
		/*posiciono el get pointer en el bloque 0*/
		almacenamientoEntrada.seekg(offset, ios_base::beg);
		char* buffer;
		buffer = new char[LONGITUD_BLOQUE_DATA];
		/*levanto el bloque y lo pongo en mi stream, y borro el buffer auxiliar*/
		almacenamientoEntrada.read(buffer, LONGITUD_BLOQUE_DATA);
		stream.append(buffer, LONGITUD_BLOQUE_DATA);
		delete[] buffer;

		/*paso mi el bloqe 0 serializado a Bytes*/
		Bytes bTemporal(stream);
		Bloque bloque0(LONGITUD_BLOQUE_DATA);
		bloque0.hidratarse(bTemporal);
		/*levanto el registro que contiene el ultimo UID y lo devuelvo(el UID)*/
		Bytes rTemporal(bloque0.obtenerRegistro(0));

		return atoi(rTemporal.toString().c_str());
	}
	/*no debiese llegar nunca aca*/
	return offset;
}

/*actualizo el bloque 0 (que guarda el ultimo UID). En valor me pasan la cantidad de UIDs nuevos desde la ultima actulaizacion(como casi siempre se actualiza en el acto, este valor va a ser 1)*/
void AlmacenamientoBloque::actualizarBloqueUIDs(int valor){
	/*obtengo el ultimo UID*/
	offset ultimoUID = getUltimoUID();
	/*calculo el nuevo ultimo UID*/
	offset nuevoUID = ultimoUID + valor;
	stringstream ssnuevoUID;
	ssnuevoUID << nuevoUID;
	/*Siempre va a ser registro con UID 0 el que guarda el ultimo UID*/
	int inicialUID = 0;

	Bloque bloqueUIDs(LONGITUD_BLOQUE_DATA);


	/*Creo el registro donde ira solo el ultimo UID*/
	Bytes bytesUID(ssnuevoUID.str());
	RegistroVariable rUID(bytesUID);
	rUID.setNRegistro(inicialUID);

	/*Agrego el registro al bloque 0*/
	bloqueUIDs.agregarRegistro(&rUID);

	/*sobreescribo el bloque*/
	escribirBloque(bloqueUIDs.serializarse(), 0);
}

/*actualizo el espacio libre en el bloque pasado*/
void AlmacenamientoBloque::actualizarEspacioLibre(offset nBloqueDisponible, cantBytes ssEspacioLibre){
    	/*ahora te cuento pa que esta*/
	int lineCount=1;
	fstream file;
	string line;
	vector<int> tamanios;
	stringstream ss;
	string buffer = "";

	file.open(this->pathLibres.c_str());
	if(file.good())
	{
		string t;
		/*voy obteniendo linea a linea los espacios libres en los bloques y pasandolos a mi vector de tamanios, excepto en el del que quiero modificar, en 			el cual meto mi nuevo valor*/
		while(getline(file, t, '\n'))
		{
			if (lineCount==nBloqueDisponible)
			{
				tamanios.push_back(ssEspacioLibre);
				lineCount++;
			}
			else
			{
				tamanios.push_back(atoi(t.c_str()));
				lineCount++;
			}
		}
	}
	/*limpio el flag de error de eof y cierro*/
	file.clear();
	file.close();

	this->aLibres.close();
	this->aLibres.open(pathLibres.c_str(), fstream::binary | fstream::out
			| fstream::in | ios::trunc);

	/*voy sobreescribiendo linea a linea el archivo de libres*/
	for (int i=0; i<(lineCount-1); i++)
	{
		ss << tamanios[i];
		buffer = ss.str();
		buffer.append("\r\n");
		this->aLibres.write(buffer.c_str(), buffer.size());
		this->aLibres.flush();
		ss.str("");
	}

	return;
}

