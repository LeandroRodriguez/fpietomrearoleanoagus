#include <iostream>
#include "NodoInterno.h"

Bytes* NodoInterno::Nodo(Bytes CodigoBinario){



    };

Bytes* NodoInterno::Nodo(Key subclave ,unsigned long int ref){



    };

unsigned long int NodoInterno::~NodoInterno(){



    };

bool InsertarNuevaSubClaveRef ( Key subclave,refAbloqueArbol ){



    };

void NodoInterno::Inicializar( Key subclave ,unsigned long int ref ){

        SubClaveRef NuevaDupla;
        NuevaDupla.RefNodo=ref;
        NuevaDupla.SubClave= subclave;

        this->ListaSubClaveRef->push_back(NuevaDupla);

    }

/*OK*/
unsigned long int NodoInterno::getTamanioSerializado(){

	unsigned long int tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
    tamanioSerializado += sizeof(this->Ref1erNodo);

    /* consigo el tamanio de los elementos contenidos en ListaSubClaveRef*/
    /*Segun el tipo de nodo de subclave que guarde el nodo, estos tamanios pueden variar */
    this->ListaSubClaveRef::iterator it;

    it= this->ListaSubClaveRef.begin();

    for(it;it!=this->ListaSubClaveRef.end();it++){
        tamanioSerializado += sizeof(  *it );
        }
	return tamanioSerializado;
}

/*OK*/
Bytes NodoInterno::Serializarse(){
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
	cur += sizeof(this->RefNodo);

    /*tengo que guardar todos los elementos de la lista */
    this->ListaSubClaveRef::iterator it;

    it= this->ListaSubClaveRef.begin();

    /*A continuacion, la muerte de la informatica =) */
    for(it;it!=this->ListaSubClaveRef.end();it++){

        T subC = it->subclave;
        int refNodo = it->RefNodo;

        if (typeid(T).name == typeid(char).name ){
            int longitud = strlen(subC);
            memcpy(str + cur, longitud ,sizeof(int));/*convencion , 4 bytes para longitud */
            cur += sizeof(int);

            memcpy(str + cur, subC , longitud);
            cur += longitud;
            }

        if (typeid(T).name == typeid(int).name ){

            memcpy(str + cur, subC , sizeof(T));
            cur += sizeof(subC);
            memcpy(str + cur, refNodo , sizeof(refNodo));
            cur += sizeof(refNodo);
        }
    }

	return str;
}

unsigned long int NodoInterno::Hidratar(char* bytes){

	unsigned int cur = 0;/*cur = cursor*/

	memcpy(&this->CantElem, bytes + cur, sizeof(this->CantElem));
	cur += sizeof(this->CantElem);


	memcpy(&this->Altura, bytes + cur, sizeof(this->Altura));
	cur += sizeof(this->Altura);

	memcpy(&this->dimension, bytes + cur, sizeof(this->dimension));
	cur += sizeof(this->dimension);

	/*  */

	return cur;
}
