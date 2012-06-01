#include "NodoHoja.h"
#include "Arbol.h"

using namespace std;

NodoHoja::NodoHoja(){
    //me pasan un numero de dimension. despues tendre que matchearlo con una de las dimensiones del accidente
    this->inicializar();
    }

NodoHoja::NodoHoja(Arbol* arbol){
    this->arbol=arbol;
    this->inicializar();
}

bool NodoHoja::BuscarDato(Key* datoBuscado){
    bool encontrado = false;
    list<int>::iterator itReg = this->listIdRegistros->begin();
    list<int>::iterator itBloq = this->listNroBloque->begin();
    while (!encontrado && itReg != listIdRegistros->end() && itBloq != listNroBloque->end()){
        Key* dato = this->cargarDato(*itReg,*itBloq);
        if(dato->esIgual(datoBuscado))
            encontrado = true;
        itReg++;
        itBloq++;
    }
    return encontrado;
}

list<Key*>* NodoHoja::BuscarSegunFecha(string subclave, int dim, string fechaInicio, string fechaFin){
    list<int>::iterator itReg = this->listIdRegistros->begin();
    list<int>::iterator itBloq = this->listNroBloque->begin();
    list<Key*>* datos = new list<Key*>();
    while (itReg != listIdRegistros->end() && itBloq != listNroBloque->end()){
        Key* dato = this->cargarDato(*itReg,*itBloq);
        if(dato->getSubClaveSegunDim(dim)==subclave && dato->getSubClaveSegunDim(4) >= fechaInicio && dato->getSubClaveSegunDim(4)<= fechaFin)
           datos->push_back(dato);
        itReg++;
        itBloq++;
    }
    return datos;
}

unsigned long int NodoHoja::getTamanioSerializado(){

	unsigned long int tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
	tamanioSerializado += sizeof(this->proximaHoja);
	tamanioSerializado += sizeof(int);

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
    this->inicializar();
    this->Hidratar(str);
    }

char* NodoHoja::Serializarse(){
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

	int tam = this->listIdRegistros->size();
	memcpy(str + cur, &tam , sizeof(int));
	cur += sizeof(int);

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

	int tam;
	memcpy(&tam, bytes + cur, sizeof(int));
	cur += sizeof(int);

	for (int i = 0; i < tam; i++) {
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

	dato -> Hidratar(str);
	return dato;
}

int NodoHoja::getTamanioConDatos(){
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
	return tamanio;

}

Resultado NodoHoja::insertarElemento(offset idRegistro, offset nroBloque, Key* dato, double porcentaje){
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

Resultado NodoHoja::insertarElementoSimuladoCargaInicial(offset idRegistro, offset nroBloque, Key* dato, double porcentaje){
	//chequeo overflow
	if(this->getTamanioConDatos() > LONGITUD_BLOQUE_NODO*porcentaje)
		return RES_DESBORDADO;

	this->listIdRegistros->push_back(idRegistro);
	this->listNroBloque->push_back(nroBloque);

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

void NodoHoja::ordenarBloquesRegistros(){
    list<int>* listOrdenadaIdReg = new list<int>();
    list<int>* listOrdenadaNroBloq = new list<int>();
    list<int>::iterator itRegi1 = this->listIdRegistros->begin();;
    list<int>::iterator itBloqi2 = this->listNroBloque->begin();;
    list<int>::iterator itRegj1 = this->listIdRegistros->begin();
    list<int>::iterator itBloqj2 = this->listNroBloque->begin();
    list<int>::iterator minItReg;
    list<int>::iterator minItBloq;
    int dim = Key::getDimensionSegunAltura(this->Altura+1);
    int i1,i2,j1,j2,minReg,minBloq;
    bool seguir = true;
    while (itRegi1 != this->listIdRegistros->end() && itBloqi2 != this->listNroBloque->end() && seguir){
        list<int>::iterator itRegi1 = this->listIdRegistros->begin();
        list<int>::iterator itBloqi2 = this->listNroBloque->begin();
        i1 = *itRegi1;
        i2 = *itBloqi2;
        Key* actual = this->cargarDato(i1, i2);
        minReg = i1;
        minBloq = i2;
        minItReg = itRegi1;
        minItBloq = itBloqi2;
        itRegj1 = ++itRegi1;
        itRegi1--;
        itBloqj2 = ++itBloqi2;
        itBloqi2--;
        while(itRegj1 != this->listIdRegistros->end() && itBloqj2 != this->listNroBloque->end()){
            j1=*itRegj1;
            j2=*itBloqj2;
           // dim = 0;
            Key* siguiente = this->cargarDato(j1, j2);
            if (siguiente->getSubClaveSegunDim(dim) < actual->getSubClaveSegunDim(dim)){
                minReg = j1;
                minBloq = j2;
                actual = siguiente;
                minItReg = itRegj1;
                minItBloq = itBloqj2;
            }
            itRegj1++;
            itBloqj2++;
        }
        listOrdenadaIdReg->push_back(minReg);
        listOrdenadaNroBloq->push_back(minBloq);
        listIdRegistros->erase(minItReg);
        listNroBloque->erase(minItBloq);
        if (listIdRegistros->size() == 0 || listNroBloque->size() == 0)
            seguir = false;
    }
    this->listIdRegistros = listOrdenadaIdReg;
    this->listNroBloque = listOrdenadaNroBloq;
    list<int>::iterator itR = this->listIdRegistros->begin();
    list<int>::iterator itB = this->listNroBloque->begin();
}

//Devuelve la mitad derecha, deja en el original la mitad izquierda
// obviamente divide segun tamanios
//Devuelve la clave perteneciente al dato del "medio" ponderado.
NodoHoja* NodoHoja::PartirEn2(Key* &kAsubir){
    this->ordenarBloquesRegistros();
    vector<int> S = this->getTamanios();

    //int TamMitad = ( this->getTamanioConDatos() )/2;
    int TamMitad = LONGITUD_BLOQUE_NODO /2;

    vector<int>::iterator itTam = S.begin();
    list<int>::iterator itReg = this->listIdRegistros->begin();
    list<int>::iterator itBloq = this->listNroBloque->begin();
    list<int>* nLR = new list<int>;
    list<int>* l2B = new list<int>;

    int SumaParcial=0;

    bool SeLlegoAlaMitad=false;
// optimizacion : hacer un promedio ponderado del peso de los datos y sus claves
        while(!SeLlegoAlaMitad){
        SumaParcial += *itTam;
        if (SumaParcial > TamMitad ){
            SeLlegoAlaMitad=true;//paso a la derecha desde el que me pasa la "mitad", en adelante.
            }else{
            nLR->push_back(*itReg);
            l2B->push_back(*itBloq);
            itTam++;
            itReg++;
            itBloq++;
            }
        }

        kAsubir=this->cargarDato(*itReg,*itBloq);
        //me quedan los iT, apuntando en la "mitad"
        NodoHoja* Nder = (NodoHoja*)(this->arbol->crearNuevoNodo(0));

        for( ;itBloq!=this->listNroBloque->end() ;itBloq++){
            Nder->InsertarNroBloque(*itBloq);
            }// todo esto es para copiar la mitad derecha al nuevo nodo
        for( ;itReg!=this->listIdRegistros->end() ;itReg++){
            Nder->InsertarIdRegistro(*itReg);
            }
        Nder->proximaHoja= this->proximaHoja;//ojo con esto !
        //********************************************
        //borro la mitad derecha de ESTE nodo, ya que los pase a otro nodo
        delete this->listIdRegistros;
        delete this->listNroBloque;
        this->listIdRegistros=nLR;
        this->listNroBloque=l2B;
        this->ActualizarCantElem();
        /*------------------------------------------------*/
        this->proximaHoja=Nder->getIdDelNodo();//ojo con esto!
        cout << "Se Partio el Nodo" << this->getIdDelNodo() << endl;
    return Nder;
    }

void NodoHoja::imprimir() {
	std::cout <<"idBloqueHoja:"<<this->idBloque << ", cantElem:"<< this->CantElem << ", altura:" << this->Altura
			<<	", dimension:" << this->dimension<< ", proximahoja:" << this->proximaHoja<< "Referencias: " << endl;

	list<int>::iterator itRegistros;
	itRegistros= this->listIdRegistros->begin();

	list<int>::iterator itBloques;
	itBloques= this->listNroBloque->begin();

	for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
		std::cout<< "idReg:"<< *itRegistros<<", idBloque:"<<*itBloques<<endl;
		std::cout<<"Dato: ";
		this->cargarDato(*itRegistros, *itBloques)->imprimir();

		itBloques++;
		}

}
