#include "Indice.h"

Indice::Indice(){
	this->persistencia = NULL;
	this->arbol = NULL;
}

Indice::Indice(string nombreArchivo) {
	string aux = DIR_ARCHIVO_INDICES;
	aux += nombreArchivo;

	this->persistencia = new PersistenciaArbol(aux);

	this->arbol = new Arbol(this->persistencia);

	//la metadata es la cantidad de elementos del arbol
	if (!this->persistencia->isVacio()){
		//si no esta vacio, leo la metadata, sino la escribo con la cantidad de elementos del arbol
		this->hidratarMetada( this->persistencia->leerMetaDatos());
		cout << "Leyo metadata del bloque 0" << endl;
	}else{
	    cout << "Escribio metadata en bloque 0"<< endl;
		char* ser = this->serializarMetadata();
		this->persistencia->cargarMetaDatos(ser,this->getTamanioSerializado());
		free (ser);
	}
    cout << "++++++++++++++++++++++++++" << endl;
}

Indice::~Indice() {
	delete (this->arbol);
	delete (this->persistencia);
}

/*
offset Indice::buscar(Key* dato){
	Resultado resul = RES_OK;
	//return this->arbol->buscar(dato, resul);
	return 0;
}*/


Resultado Indice::agregarDato(offset nroBloque, offset nroRegistro, Key* dato){
	//agrego al arbol
	Resultado res = this->arbol->insertar(nroBloque,  nroRegistro, dato);

	//actualizo metadata
	char* ser = this->serializarMetadata();
	this->persistencia->cargarMetaDatos(ser,this->getTamanioSerializado());
	free (ser);
    return res;
}

void Indice::imprimir(){
	this->arbol->imprimir();
}

char* Indice::serializarMetadata(){
	int tam = this->getTamanioSerializado();
	char* str = (char*) malloc (tam );

	memcpy(str,&(this->arbol->cantidadElem), sizeof(this->arbol->cantidadElem));
	return str;

}

long int Indice::getTamanioSerializado(){
	return sizeof(this->arbol->cantidadElem);
}

void Indice::agregarDatosCargaInicial(list<Dato*>* listaDatosCargaInicial){
    this->arbol->cargaInicial(listaDatosCargaInicial);
}

bool Indice::hidratarMetada(char* metadata){
	memcpy(&(this->arbol->cantidadElem) ,metadata,sizeof(this->arbol->cantidadElem));
	return true;
}

bool Indice::BuscarDato(Key* dato){
    return this->arbol->BuscarDato(dato);
}

list<Key*>* Indice::BuscarSegunFecha(string subclave, int dim, string fechaInicio, string fechaFin){
    if(this->arbol->getCantElemen() )
    return this->arbol->BuscarSegunFecha(subclave, dim, fechaInicio, fechaFin);
    return NULL;
}

void Indice::Baja(Key* dato){
	this->arbol->Baja(dato);
}

