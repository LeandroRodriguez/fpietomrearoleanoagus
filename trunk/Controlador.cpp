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
		indice->agregarDato(almacena.getNumeroBloque(), almacena.getNumeroUID(), dato);
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
