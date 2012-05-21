#include <iostream>
#include "NodoInterno.h"

Bytes* NodoInterno::Nodo(Bytes CodigoBinario){



    };

Bytes* NodoInterno::Nodo(Key subclave ,unsigned long int ref){



    };

unsigned long int NodoInterno::getTamanioSerializado(){



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

Bytes* NodoInterno::Hidratar(Bytes CodigoBinario){




    };

Bytes* NodoInterno:: Serializarse(){




    };

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
