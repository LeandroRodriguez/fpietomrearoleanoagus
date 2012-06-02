#include "Controlador.h"

Controlador::Controlador() {
	 /*creo las carpetas donde guardo los archivos*/
	 ManipuladorArchivos* manipulo = new ManipuladorArchivos();
	 manipulo->creoCarpeta("./Indices");
	 manipulo->creoCarpeta("./Archivos");
	 /*recupero todos los archivos *.idx de la carpeta de indices*/
	 vector<string> aux = manipulo->getArchivos(DIR_ARCHIVO_INDICES,"",".idx");

	 if (aux.size()>0){
		 archivoArbol = aux[0];
	 }else{
		 archivoArbol = ARCHIVO_ARBOL;
     }

	 /*creo el indice para guardar las referencias al dato en mi arbol*/
	 this->indice = new Indice(this->archivoArbol);

	 delete manipulo;
}

Controlador::~Controlador(){
	// TODO Auto-generated destructor stub
}

void Controlador::ArmarDatoEInsertar(){
    system("clear");
    string linea,accidente,falla,formacion,horario;
    cout << "Ingrese Linea Ferroviaria" << endl;
    cin.ignore(256,'\n');
    getline(cin,linea);
    cout << linea << endl;
    cout << "Ingrese Accidente Ferroviaria" << endl;
    getline(cin,accidente);
    cout << accidente << endl;
    cout << "Ingrese Falla Ferroviaria" << endl;
    getline(cin,falla);
    cout << falla << endl;
    cout << "Ingrese Formacion Ferroviaria" << endl;
    getline(cin,formacion);
    cout << formacion << endl;
    cout << "Ingrese Franja Horaria Del Siniestro" << endl;
    getline(cin,horario);
    cout << horario << endl;
    Key* key = new Key();
    key->setLineaFerroviaria(linea);
    key->setAccidente(accidente);
    key->setFalla(falla);
    key->setFormacion(formacion);
    key->setFranjaHorariaDelSiniestro(horario);
    this->InsertarDato(key);
}

/*Inserto el dato pasado por parametro tanto en el archivo de data, como sus referencias en el arbol*/
void Controlador::InsertarDato(Key* dato){
	/*creo un objeto que se encargara de almacenar el dato en el archivo correspondiente*/
	AlmacenamientoBloque almacena(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);

	/*si el dato no es null, lo guardo*/
	if (dato ) {
		/*obtengo los bytes del dato serializado*/
		string str(dato->Serializarse());
		Bytes bytes(str);

		/*creo un registro donde guardo los bytes del dato, y lo guardo en el archivo de data*/
		RegistroVariable registro(bytes);
		almacena.agregarRegistro(&registro);
		/*le paso al arbol el numero de bloque y el UID del reg en donde guarde el dato*/
		Resultado res = indice->agregarDato(almacena.getNumeroBloque(), almacena.getNumeroUID(), dato);
		if(res == RES_DESBORDADO)
		{
			string aux = DIR_ARCHIVO_INDICES;
			aux += this->archivoArbol;
			remove(aux.c_str());
			this->indice = new Indice(this->archivoArbol);

			string pathDatos = DIR_ARCHIVO_DATOS;
			pathDatos += ARCHIVO_DATOS;
			string pathLibres = DIR_ARCHIVO_DATOS;
			pathLibres += ARCHIVO_DATOS_LIBRES;
			remove(pathLibres.c_str());

			string pathNuevosDatos = DIR_ARCHIVO_DATOS;
			pathNuevosDatos += "a";
			pathNuevosDatos += ARCHIVO_DATOS;
			rename(pathDatos.c_str(), pathNuevosDatos.c_str());
			this->CargaInicial(pathNuevosDatos);
			remove(pathNuevosDatos.c_str());
		}
	}
};


list<Key*>* Controlador::getListaKey(string path){
	list<Key*>* lista = new list<Key*>();
	ifstream almacenamientoEntrada;

	almacenamientoEntrada.open(path.c_str());

	long begin, end;
	begin = almacenamientoEntrada.tellg();
	almacenamientoEntrada.seekg (0, ios::end);
	end = almacenamientoEntrada.tellg();
	long size = (end-begin);

	int i = 1;
	int cursor = i*LONGITUD_BLOQUE_DATA;
	almacenamientoEntrada.seekg(LONGITUD_BLOQUE_DATA, ios_base::beg);//me paro en el bloque 1
	while(cursor < size)
	{
		string stream;
		char* aux = (char*) malloc (sizeof(char)*LONGITUD_BLOQUE_DATA);
		almacenamientoEntrada.read(aux,LONGITUD_BLOQUE_DATA);
		stream.append(aux, LONGITUD_BLOQUE_DATA);
		delete[] aux;
		Bytes bloqueBytes(stream.c_str());
		/*hidrato el bloque recuperado*/
		Bloque bloqueTemporal(LONGITUD_BLOQUE_DATA);
		bloqueTemporal.hidratarse(bloqueBytes);
		list<RegistroVariable*>* registros = bloqueTemporal.getRegistros();
		list<RegistroVariable*>::iterator itRegistros;
		itRegistros= registros->begin();
		for(;itRegistros!=registros->end();itRegistros++)
		{
			Key* dato = new Key();
			dato -> Hidratar((*itRegistros)->getDato().toString());
			lista->push_back(dato);
		}
		i++;
		cursor = i*LONGITUD_BLOQUE_DATA;
		almacenamientoEntrada.seekg(cursor, ios_base::beg);//me paro en el bloque 1
	}
	almacenamientoEntrada.close();
	return lista;
}

void Controlador::ListarTenesPorFalla(string falla, string fechaInicio, string fechaFin){
    list<Key*>* datos = new list<Key*>();
	datos = this->BuscarTrenesConFallaSegunFecha(falla, fechaInicio, fechaFin);
    //LineaFerroviaria dim = 0
	list<string>* subclaves = this->GenerarListaDeSubclaveSegunDim(0, datos);
    cout << "LISTADO TRENES CON FALLA: "<< falla << endl;
    cout << "Cantidad Elementos: " << subclaves->size() <<endl;
    list<string>::iterator itDato = subclaves->begin();
    for(;itDato != subclaves->end();itDato++){
            cout << "- "<<(*itDato) <<endl;

    }
    cin.get();
}

void Controlador::ListarTenesPorAccidente(string accidente, string fechaInicio, string fechaFin){
    list<Key*>* datos = new list<Key*>();
	datos = this->BuscarTrenesConAccidenteSegunFecha(accidente, fechaInicio, fechaFin);
    //LineaFerroviaria dim = 0
	list<string>* subclaves = this->GenerarListaDeSubclaveSegunDim(0, datos);
    cout << "LISTADO TRENES CON ACCIDENTES "<< accidente << endl;
    cout << "Cantidad Elementos: " << subclaves->size() <<endl;
    list<string>::iterator itDato = subclaves->begin();
    for(;itDato != subclaves->end();itDato++){
            cout << "- " <<(*itDato) <<endl;

    }
    cin.get();
}

void Controlador::ListarFallasPorFormacion(string formacion, string fechaInicio, string fechaFin){
    list<Key*>* datos = new list<Key*>();
	datos = this->BuscarTrenesConFormacionSegunFecha(formacion, fechaInicio, fechaFin);
    //Fallas dim = 3
	list<string>* subclaves = this->GenerarListaDeSubclaveSegunDim(3, datos);
    cout << "LISTADO FALLAS DE FORMACION "<< formacion << endl;
    cout << "Cantidad Elementos: " << subclaves->size() <<endl;
    list<string>::iterator itDato = subclaves->begin();
    for(;itDato != subclaves->end();itDato++){
            cout << (*itDato) <<endl;

    }
    cin.get();
}

void Controlador::ListarAccidentesPorFormacion(string formacion, string fechaInicio, string fechaFin){
    list<Key*>* datos = new list<Key*>();
	datos = this->BuscarTrenesConFormacionSegunFecha(formacion, fechaInicio, fechaFin);
    //Accidentes dim = 2
	list<string>* subclaves = this->GenerarListaDeSubclaveSegunDim(2, datos);
    cout << "LISTADO ACCIDENTES DE FORMACION "<< formacion << endl;
    cout << "Cantidad Elementos: " << subclaves->size() <<endl;
    list<string>::iterator itDato = subclaves->begin();
    for(;itDato != subclaves->end();itDato++){
            cout << "- "<< (*itDato) <<endl;

    }
    cin.get();
}

void Controlador::ListarFallas(){
    string path = DIR_ARCHIVO_DATOS;
    path += ARCHIVO_DATOS;
    list<Key*>* datos = this->getListaKey(path);
	//Fallas dim = 3
	list<string>* subclaves = this->GenerarListaDeSubclaveSegunDim(3, datos);
	cout << "LISTADO FALLAS" << endl;
	cout << "Cantidad Elementos: " << subclaves->size() <<endl;
    list<string>::iterator itDato = subclaves->begin();
    for(;itDato != subclaves->end();itDato++){
            cout << "- " << (*itDato) <<endl;
    }
    cin.get();
}

void Controlador::ListarFormaciones(){
    string path = DIR_ARCHIVO_DATOS;
    path += ARCHIVO_DATOS;
    list<Key*>* datos = this->getListaKey(path);
	//Formacion dim = 1
	list<string>* subclaves = this->GenerarListaDeSubclaveSegunDim(1, datos);
	cout << "LISTADO FORMACIONES" << endl;
	cout << "Cantidad Elementos: " << subclaves->size() <<endl;
    list<string>::iterator itDato = subclaves->begin();
    for(;itDato != subclaves->end();itDato++){
            cout << "- "<<(*itDato) <<endl;

    }
    cin.get();
}

void Controlador::ListarLineasFerroviarias(){
    string path = DIR_ARCHIVO_DATOS;
    path += ARCHIVO_DATOS;
    list<Key*>* datos = this->getListaKey(path);
	//Linea Ferroviaria dim = 0
	list<string>* subclaves = this->GenerarListaDeSubclaveSegunDim(0, datos);
	cout << "LISTADO LINEAS FERROVIARIAS" << endl;
	cout << "Cantidad Elementos: " << subclaves->size() <<endl;
    list<string>::iterator itDato = subclaves->begin();
    for(;itDato != subclaves->end();itDato++){
            cout << "- "<<(*itDato) <<endl;

    }
    cin.get();
}

void Controlador::ListarAccidentes(){
    string path = DIR_ARCHIVO_DATOS;
    path += ARCHIVO_DATOS;
    list<Key*>* datos = this->getListaKey(path);
	//Accidentes dim = 2
	list<string>* subclaves = this->GenerarListaDeSubclaveSegunDim(2, datos);
	cout << "LISTADO ACCIDENTES" << endl;
	cout << "Cantidad Elementos : " << subclaves->size() <<endl;
	list<string>::iterator itDato = subclaves->begin();
    for(;itDato != subclaves->end();itDato++){
            cout << "- " << (*itDato) <<endl;

    }
    cin.get();
}

/*Inserto el dato pasado por parametro tanto en el archivo de data, como sus referencias en el arbol*/
void Controlador::InsertarDatosCargaInicial(list<Key*>* listaKey){
	/*creo un objeto que se encargara de almacenar el dato en el archivo correspondiente*/
	AlmacenamientoBloque almacena(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
	/*creo una lista de DATOs que le voy a pasar a la carga incial*/
	list<Dato*>* listaDatosCargaInicial = new list<Dato*>();
	/*voy a iterar sobre mi lista de datos para ir insertandolas en el archivo. Y tmb armar el DATO que le voy a pasar ala carga inicial (nroBloq,idReg,clave)*/
	list<Key*>::iterator itListaKey = listaKey->begin();

	for(;itListaKey!=listaKey->end();itListaKey++){
		/*booleano para controlar repeticiones*/
		bool estaRepetido = false;
		/*si el dato no es null, lo guardo*/
		Key* key = (*itListaKey);
		if (key) {

			/*checkeo si ya existe el dato en mi listas de Datos para evitar guardarlo y pasarselo al arbol*/
			list<Dato*>::iterator itListaDatosCargaInicial;
			itListaDatosCargaInicial= listaDatosCargaInicial->begin();
			for(;itListaDatosCargaInicial!=listaDatosCargaInicial->end();itListaDatosCargaInicial++){
				Dato* k2 = (*itListaDatosCargaInicial);
				if(key->esIgual(( k2->getClave() ))){
					estaRepetido = true;
					break;
				}
			}
			if(!estaRepetido){
				/*obtengo los bytes del dato serializado*/
				string str(key->Serializarse());
				Bytes bytes(str);

				/*creo un registro donde guardo los bytes del dato, y lo guardo en el archivo de data*/
				RegistroVariable registro(bytes);
				almacena.agregarRegistro(&registro);
				/*armo el DATO y lo meto en mi lista*/
				Dato* datoCargaInicial = new Dato();
				datoCargaInicial->setIdRegistro(almacena.getNumeroUID());
				datoCargaInicial->setNroBoque(almacena.getNumeroBloque());
				datoCargaInicial->setClave(key);
				listaDatosCargaInicial->push_back(datoCargaInicial);
			}
		}
	}
	/*llamo al indice, que a su vez mediara con el arbol, para ejecutar la carga inicial*/
	this->indice->agregarDatosCargaInicial(listaDatosCargaInicial);//AGREGAR ESTA FUNCION MEDIADORA A INDICE
}

bool Controlador::BuscarDato(Key* dato){
    return this->indice->BuscarDato(dato);
}

list<Key*>* Controlador::BuscarTrenesConFallaSegunFecha(string falla, string fechaInicio, string fechaFin){
    //falla dim=3
    return this->BuscarSegunFecha(falla, 3, fechaInicio, fechaFin);
}

list<Key*>* Controlador::BuscarTrenesConAccidenteSegunFecha(string accidente, string fechaInicio, string fechaFin){
    //accidente dim=2
    return this->BuscarSegunFecha(accidente, 2, fechaInicio, fechaFin);
}

list<Key*>* Controlador::BuscarTrenesConFormacionSegunFecha(string formacion, string fechaInicio, string fechaFin){
    //formacion dim=1
    return this->BuscarSegunFecha(formacion, 1, fechaInicio, fechaFin);
}

list<Key*>* Controlador::BuscarSegunFecha(string subclave, int dim , string fechaInicio, string fechaFin){
    return this->indice->BuscarSegunFecha(subclave, dim, fechaInicio, fechaFin);
}

list<string>* Controlador::GenerarListaDeSubclaveSegunDim(int dim, list<Key*>* lista){
    list<string>* subclaves= new list<string>();
    list<Key*>::iterator it = lista->begin();
    for(;it != lista->end();it++){
        string subclave = (*it)->getSubClaveSegunDim(dim);
        subclaves->push_back(subclave);
    }
    subclaves->sort();
    subclaves->unique();
    return subclaves;
}

void Controlador::CargarDatosPrueba(){
    string path = DIR_ARCHIVO_DATOS;
	path += "a";
	path += ARCHIVO_DATOS;
	list<Key*>* lista = this->getListaKey(path);
	this->InsertarDatosCargaInicial(lista);
	system("clear");
	cout << "DATOS DE PRUEBA CARGADOS" << endl;
	cin.get();
}


void Controlador::CargaInicial(string path){
	string aux = DIR_ARCHIVO_INDICES;
	aux += this->archivoArbol;
	remove(aux.c_str());
	this->indice = new Indice(this->archivoArbol);

	string pathDatos = DIR_ARCHIVO_DATOS;
	pathDatos += ARCHIVO_DATOS;
	string pathLibres = DIR_ARCHIVO_DATOS;
	pathLibres += ARCHIVO_DATOS_LIBRES;
	remove(pathLibres.c_str());
	remove(pathDatos.c_str());

	list<Key*>* lista = this->getListaKey(path);
	this->InsertarDatosCargaInicial(lista);
}


void Controlador::ImprimirArbol(){
    this->indice->imprimir();
    cin.get();
}


/*
void Controlador::cargarArchivos(){

	 ManipuladorArchivos* manipulo = new ManipuladorArchivos();

	 archivosClasificacion
		 = manipulo->getArchivos(DIR_ARCHIVO_INDICES_CLASIFICACION,"",".idx");

	 archivosSeleccion
		 = manipulo->getArchivos(DIR_ARCHIVO_INDICES_SELECCION,"",".idx");

	 archivoPrimario
		 = manipulo->getArchivos(DIR_ARCHIVO_INDICES,"",".idx")[0];

	 delete manipulo;
}*/


/*Controlador::Controlador(){
    //not implemented
    }


*/


