#include <iostream>
#include "NodoInterno.h"

Bytes* NodoInterno<T>::Nodo(Bytes CodigoBinario){



    };

Bytes* NodoInterno<T>::Nodo(Key subclave ,unsigned long int ref){



    };

unsigned long int NodoInterno<T>::~NodoInterno(){



    };

bool NodoInterno<T>::InsertarNuevaSubClaveRef ( T subclave,int refAbloqueArbol ){

        SubClaveRef* item = new SubClaveRef<T>;

        item->subclave = subcl;
        item->RefNodo = RefNod;

        mylist.push_back (myint)

        this->ListaSubClaveRef->push_back(item);
        this->ListaSubClaveRef->sort();


    };

void NodoInterno<T>::Inicializar( int ref1 ,T subclave ,int ref2 ){

        this->Ref1erNodo=ref1;

        SubClaveRef* NuevaDupla= new SubClaveRef();
        NuevaDupla.RefNodo=ref;
        NuevaDupla.SubClave= subclave;

        this->ListaSubClaveRef->push_back(NuevaDupla);

    }


/* sirve solo para tipos clasicos, int, double, word etc */
unsigned long int NodoInterno<T>::getTamanioSerializado(){

	unsigned long int tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
    tamanioSerializado += sizeof(this->Ref1erNodo);
    tamanioSerializado += sizeof(char) * strlen(typeid(T));

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
    tamanioSerializado += sizeof(char) * strlen(typeid(char*));

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
Bytes NodoInterno<T>::Serializarse(){
	unsigned long int  tamanioTotal = this->getTamanioSerializado();

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

	/*aca guardo el tipo*/
    memcpy(str + cur, &typeid(T).name , strlen (typeid(T).name));
	cur += strlen(typeid(T));

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

	return str;
}

/*sirve para char* */
template<> Bytes NodoInterno<char*>::Serializarse{
    	unsigned long int  tamanioTotal = this->getTamanioSerializado();

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

	/*aca guardo el tipo*/
    memcpy(str + cur, &typeid(char*).name , strlen (typeid(char*).name));
	cur += strlen(typeid(char*));

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

	return str;
}


/*para tipos comunes  */
void NodoInterno<T>::Hidratar(char* bytes){

	unsigned int cur = 0;/*cur = cursor*/

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



    while(cur < strlen(bytes) ){

        int longitud =0;

        memcpy(longitud, bytes + cur  , sizeof(int));
        cur += sizeof(int);
        }
    }
