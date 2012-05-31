#include "Controlador.h"

/*REVISAR Y ARREGLAR*/
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

/*Inserto el dato pasado por parametro tanto en el archivo de data, como sus referencias en el arbol*/
void Controlador::InsertarDato(Key* dato){
	/*creo un objeto que se encargara de almacenar el dato en el archivo correspondiente*/
	AlmacenamientoBloque almacena(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);

	/*si el dato no es null, lo guardo*/
	if (dato) {
		/*obtengo los bytes del dato serializado*/
		string str(dato->Serializarse());
		Bytes bytes(str);

		/*creo un registro donde guardo los bytes del dato, y lo guardo en el archivo de data*/
		RegistroVariable registro(bytes);
		almacena.agregarRegistro(&registro);
		/*le paso al arbol el numero de bloque y el UID del reg en donde guarde el dato*/
		Resultado res = indice->agregarDato(almacena.getNumeroBloque(), almacena.getNumeroUID(), dato);
        cout << res << endl;
	}
}

void Controlador::ListarTenesPorFalla(string falla){
    //not implemented
    }

void Controlador::ListarTenesPorAccidente(string accidente){
    //not implemented
    }

void Controlador::ListarFallasPorFormacion(int formacion){
    //not implemented
    }

void Controlador::ListarAccidentesPorFormacion(int formacion){
    //not implemented
    }

void Controlador::ListarFallas(){
    //not implemented
    }

void Controlador::ListarForcaciones(){
    //not implemented
    }

void Controlador::ListarLineas(){
    //not implemented
    }

void Controlador::ListarAccidentes(){
    //not implemented
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
