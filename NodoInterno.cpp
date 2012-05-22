#include <iostream>
#include "NodoInterno.h"

Bytes* NodoInterno::Nodo(Bytes CodigoBinario){



    };

Bytes* NodoInterno::Nodo(Key subclave ,unsigned long int ref){



    };

unsigned long int NodoInterno::~NodoInterno(){



    };

bool NodoInterno::InsertarNuevaSubClaveRef ( T subclave,int refAbloqueArbol ){

        SubClaveRef* item = new SubClaveRef<T>;

        item->subclave = subcl;
        item->RefNodo = RefNod;

        mylist.push_back (myint)

        this->ListaSubClaveRef->push_back(item);
        this->ListaSubClaveRef->sort();


    };

void NodoInterno::Inicializar( int ref1 ,T subclave ,int ref2 ){

        this->Ref1erNodo=ref1;

        SubClaveRef* NuevaDupla= new SubClaveRef();
        NuevaDupla.RefNodo=ref;
        NuevaDupla.subClave= subclave;

        this->ListaSubClaveRef->push_back(NuevaDupla);

    }


/* sirve solo para tipos clasicos, int, double, word etc */
unsigned long int NodoInterno::getTamanioSerializado(){

	unsigned long int tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
    tamanioSerializado += sizeof(this->Ref1erNodo);
    tamanioSerializado += sizeof(int);/*aca guardo el tipo*/

    /* consigo el tamanio de los elementos contenidos en ListaSubClaveRef*/
    /*Segun el tipo de nodo de subclave que guarde el nodo, estos tamanios pueden variar */
    this->ListaSubClaveRef::iterator it;

    it= this->ListaSubClaveRef.begin();

    for(it;it!=this->ListaSubClaveRef.end();it++){

        T subC = it->subclave;
        int refNodo = it->RefNodo;

        tamanioSerializado +=  sizeof(subC);
        tamanioSerializado +=  sizeof(refNodo);

        }
	return tamanioSerializado;
}

/* para char* */
template<> unsigned long int NodoInterno<char*>::getTamanioSerializado(){

    unsigned long int tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
    tamanioSerializado += sizeof(this->Ref1erNodo);
    tamanioSerializado += sizeof(int);/*aca guardo el tipo*/

    /* consigo el tamanio de los elementos contenidos en ListaSubClaveRef*/
    /*Segun el tipo de nodo de subclave que guarde el nodo, estos tamanios pueden variar */
    this->ListaSubClaveRef::iterator it;

    it= this->ListaSubClaveRef.begin();

    for(it;it!=this->ListaSubClaveRef.end();it++){

        char* subC = it->subclave;
        int refNodo = it->RefNodo;

        tamanioSerializado +=  sizeof(int);/*convencion para guardar tamanio  */
        tamanioSerializado +=  strlen(subC); /*tamnio variable */
        tamanioSerializado +=  sizeof(refNodo);

        }
	return tamanioSerializado;


    }

/*sirve solo para tipos clasicos, int, double, word etc*/
Bytes* NodoInterno::Serializarse(){
	unsigned long int  tamanioTotal = this->getTamanioSerializado();

    /*PRIMERO GUARDO EL TIPO*/
    memcpy(str + cur, &typeid(T).name , strlen (typeid(T).name));
	cur += sizeof(int));

    /*el string que voy a devolver*/
	char* str =(char*) malloc(tamanioTotal * sizeof(char));
	unsigned int cur = 0;/*cur = cursor*/

    /*guardo la cantidad de elementos */
	memcpy(str + cur, &this->CantElem , sizeof(this->CantElem));
	cur += sizeof(this->CantElem);

    /*bis altura*/
	memcpy(str + cur, &this->Altura , sizeof(this->Altura));
	cur += sizeof(this->Altura);

    /*bis ref 1er hijo izq  */
	memcpy(str + cur, &this->dimension , sizeof(this->dimension));
	cur += sizeof(this->dimension);

    /*bis dimension  */
	memcpy(str + cur, &this->RefNodo , sizeof(this->RefNodo));
	cur += sizeof(this->RefNodo);

    /*tengo que guardar todos los elementos de la lista */
    this->ListaSubClaveRef::iterator it;

    it= this->ListaSubClaveRef.begin();

    for(it;it!=this->ListaSubClaveRef.end();it++){

        T subC = it->subclave;
        int refNodo = it->RefNodo;

            memcpy(str + cur, subC , sizeof(T));
            cur += sizeof(subC);
            memcpy(str + cur, refNodo , sizeof(refNodo));
            cur += sizeof(refNodo);
    }

	return new Bytes(str);
}

/*sirve para char* */
template<> Bytes* NodoInterno<char*>::Serializarse{
    	unsigned long int  tamanioTotal = this->getTamanioSerializado();

    /*el string que voy a devolver*/
	char* str =(char*) malloc(tamanioTotal * sizeof(char));
	unsigned int cur = 0;/*cur = cursor*/


    /*PRIMERO GUARDO EL TIPO*/
    memcpy(str + cur, &typeid(T).name , strlen (typeid(T).name));
	cur += sizeof(int);

    /*guardo la cantidad de elementos */
	memcpy(str + cur, &this->CantElem , sizeof(this->CantElem));
	cur += sizeof(this->CantElem);

    /*bis altura*/
	memcpy(str + cur, &this->Altura , sizeof(this->Altura));
	cur += sizeof(this->Altura);

    /*bis ref 1er hijo izq  */
	memcpy(str + cur, &this->dimension , sizeof(this->dimension));
	cur += sizeof(this->dimension);

    /*bis dimension  */
	memcpy(str + cur, &this->RefNodo , sizeof(this->RefNodo));
	cur += sizeof(this->RefNodo);

    /*tengo que guardar todos los elementos de la lista */
    this->ListaSubClaveRef::iterator it;

    it= this->ListaSubClaveRef.begin();

    for(it;it!=this->ListaSubClaveRef.end();it++){

        char* subC = it->subclave;
        int refNodo = it->RefNodo;

            memcpy(str + cur, strlen(subC) , sizeof(int) ); /*convencion 4 bytes para longitud */
            cur += sizeof(int);
            memcpy(str + cur, subC , strlen(subC) );
            cur += strlen(subC);
            memcpy(str + cur, refNodo , sizeof(refNodo));
            cur += sizeof(refNodo);
    }

	return new Bytes(str);
}


/*para tipos comunes  */
void NodoInterno::Hidratar(char* bytes){

	unsigned int cur = sizeof(int);/*cur = cursor , LOS PRIMEROS 4 fueron leidos para saber el TIPO*/

	memcpy(&this->CantElem, bytes + cur, sizeof(this->CantElem));
	cur += sizeof(this->CantElem);


	memcpy(&this->Altura, bytes + cur, sizeof(this->Altura));
	cur += sizeof(this->Altura);

	memcpy(&this->dimension, bytes + cur, sizeof(this->dimension));
	cur += sizeof(this->dimension);

	memcpy(str + cur, &this->RefNodo , sizeof(this->RefNodo));
	cur += sizeof(this->RefNodo);

    while(cur < strlen(bytes) ){

        T subcl;

        memcpy(&subcl, bytes + cur  , sizeof(T) );
        cur += sizeof(T);

        int RefNod;

        memcpy(&RefNod, bytes + cur  , sizeof(int) );
        cur += sizeof(int);

        this->InsertarNuevaSubClaveRef( subcl,RefNod);



    }
}

template<> void NodoInterno<char*>::Hidratar(char* bytes){



 	unsigned int cur = sizeof(int);/*cur = cursor primeros 4 para saber tipo*/

	memcpy(&this->CantElem, bytes + cur, sizeof(this->CantElem));
	cur += sizeof(this->CantElem);


	memcpy(&this->Altura, bytes + cur, sizeof(this->Altura));
	cur += sizeof(this->Altura);

	memcpy(&this->dimension, bytes + cur, sizeof(this->dimension));
	cur += sizeof(this->dimension);

	memcpy(str + cur, &this->RefNodo , sizeof(this->RefNodo));
	cur += sizeof(this->RefNodo);

    while(cur < strlen(bytes) ){

        int longitud=0;

        memcpy(&longitud, bytes + cur  , sizeof(int) );
        cur += sizeof(int);

        char* subclave = new char[longitud];

        memcpy(subclave,bytes+longitud,longitud);
        cur += longitud;


        int RefNod=0;

        memcpy(&RefNod, bytes + cur  , sizeof(int) );
        cur += sizeof(int);

        this->InsertarNuevaSubClaveRef( subclave, RefNod);



    }
}
