#include "NodoHoja.h"

NodoHoja::NodoHoja(){
    //me pasan un numero de dimension. despues tendre que matchearlo con una de las dimensiones del accidente
    this->tamanioMaximoNodo=0;
    this->CantElem=0;
    this->Altura = 0;
	this->listIdRegistros = new list<int>();
	this->listNroBloque = new list<int>();

    }
/*
NodoHoja::NodoHoja(Arbol* arbol):Nodo(arbol){

}*/
unsigned long int NodoHoja::getTamanioSerializado(){

	unsigned long int tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
	tamanioSerializado += sizeof(this->proximaHoja);

	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		tamanioSerializado += sizeof(  *itRegistros );
        }


	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itBloques!=this->listNroBloque->end();itBloques++){
		tamanioSerializado += sizeof(  *itBloques );
        }

	return tamanioSerializado;
}

    NodoHoja::NodoHoja(char* str){
    this->tamanioMaximoNodo=0;
    this->CantElem=0;
    this->listIdRegistros = new list<int>();
	this->listNroBloque = new list<int>();
    this->Hidratar(str);
    }

char* NodoHoja::Serializarse()
{
	unsigned long int  tamanioTotal = this->getTamanioSerializado();

	char* str =(char*) malloc(tamanioTotal * sizeof(char));
	unsigned int cur = 0;/*cur = cursor*/

	memcpy(str + cur, &this->CantElem , sizeof(this->CantElem));
	cur += sizeof(this->CantElem);

	memcpy(str + cur, &this->Altura , sizeof(this->Altura));
	cur += sizeof(this->Altura);

	memcpy(str + cur, &this->dimension , sizeof(this->dimension));
	cur += sizeof(this->dimension);

	memcpy(str + cur, &this->proximaHoja , sizeof(this->proximaHoja));
	cur += sizeof(this->proximaHoja);

	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		memcpy(str + cur, &(*itRegistros) , sizeof(*itRegistros) );
		cur += sizeof(*itRegistros);

		memcpy(str + cur, &(*itBloques) , sizeof(*itBloques));
		cur += sizeof(*itBloques);

		itBloques++;
        }

	return str;
}

void NodoHoja::Hidratar(char* bytes){

	unsigned int cur = 0;/*cur = cursor*/

	memcpy(&this->CantElem, bytes + cur, sizeof(this->CantElem));
	cur += sizeof(this->CantElem);

	memcpy(&this->Altura, bytes + cur, sizeof(this->Altura));
	cur += sizeof(this->Altura);

	memcpy(&this->dimension, bytes + cur, sizeof(this->dimension));
	cur += sizeof(this->dimension);

	memcpy(&this->proximaHoja, bytes + cur, sizeof(this->proximaHoja));
	cur += sizeof(this->proximaHoja);

	while(cur < strlen(bytes) )
	{
		int idRegistro;
		memcpy(&idRegistro, bytes + cur  , sizeof(int) );
		cur += sizeof(int);
		this->listIdRegistros->push_back(idRegistro);

		int nroBloque;
		memcpy(&nroBloque, bytes + cur  , sizeof(int) );
		cur += sizeof(int);
		this->listNroBloque->push_back(nroBloque);
	}
}



Key* NodoHoja::cargarDato(offset idRegistro, offset nroBloque){
	Key* dato = new Key();
	AlmacenamientoBloque almacena(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);

	string str= almacena.recuperarRegistro(nroBloque, idRegistro).toString();

	int a = str.length();
	char* bla = new char[str.length() ];

	memcpy(bla,&str,str.length());

	dato -> Hidratar(bla);
	return dato;
}

int NodoHoja::getTamanioConDatos()
{
	int tamanio = 0;
	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		offset idReg = *itRegistros;
		offset nroBlo = *itBloques;
		Key* dato = this->cargarDato(idReg, nroBlo);

		tamanio += dato->getTamanioSerializado();
		itBloques++;
        }
	tamanio += sizeof(this->proximaHoja);
	return tamanio;

}


Resultado NodoHoja::insertarElemento(offset idRegistro, offset nroBloque, Key* dato, double porcentaje)
{
	/*Busca en el nodo si hay algún registro con los mismos identificadores que IdentificadorDato.
	Si lo encuentra, devuelve como resultado RES_DUPLICADO.

	Si el nodo hoja desborda, Devuelve  RES_DESBORDADO
	sino, devuelve RES_OK
	*/

	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		offset idReg = *itRegistros;
		offset nroBlo = *itBloques;
		Key* d = this->cargarDato(idReg, nroBlo);
		if(dato->esIgual(d))
			return RES_DUPLICADO;
		itBloques++;
        }


	//chequeo overflow
	int tamanio = this->getTamanioConDatos();
	if((tamanio + dato->getTamanioSerializado()) > LONGITUD_BLOQUE_NODO*porcentaje){
		this->listIdRegistros->push_back(idRegistro);
		this->listNroBloque->push_back(nroBloque);
		this->CantElem++;
		return RES_DESBORDADO;
	}

	this->listIdRegistros->push_back(idRegistro);
	this->listNroBloque->push_back(nroBloque);
	this->CantElem++;

	return RES_OK;

}

vector<int> NodoHoja::getTamanios(){
	vector<int> tamanios;
	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		offset idReg = *itRegistros;
		offset nroBlo = *itBloques;
		Key* dato = this->cargarDato(idReg, nroBlo);

		int tamanio = dato->getTamanioSerializado();
		tamanios.push_back(tamanio);
		itBloques++;
	}
	return tamanios;

}

void NodoHoja::imprimir() {
	//Bytes b;
	//b.agregar((void*)this->Serializarse(), getTamanioSerializado(), 0);
	//string a = b.toString();
/*
	std::cout <<"idBloque:"<<this->idBloque << ", serializacion:";
	int i;
	char* serial = this->Serializarse();
	string str = "";
	int tamanio = this->getTamanioSerializado();
	for (i = 0; i < tamanio; i++) {
		//char aux[1];
		//memcpy(aux,serial + i,1);
		//cout<<aux;
		str += serial+i;
	}
	cout<<str<<endl;

	string str;
	char aux[getTamanioSerializado()];
	memcpy(aux,this->Serializarse(),getTamanioSerializado());
	str.append(aux,getTamanioSerializado());

	std::cout <<"idBloque:"<<this->idBloque << ", serializacion:" << str<<endl;*/
	std::cout <<"idBloque:"<<this->idBloque << ", cantElem:"<< this->CantElem << ", altura:" << this->Altura
			<<	", dimension:" << this->dimension<< ", proximahoja:" << this->proximaHoja<< "refs: " << endl;

	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		std::cout<< "idReg:"<< *itRegistros<<", idBloque:"<<*itBloques<<endl;
		std::cout<<"Dato: "<<this->cargarDato(*itRegistros, *itBloques)->Serializarse()<<endl;

		itBloques++;
		}

}


