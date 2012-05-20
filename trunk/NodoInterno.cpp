#include <iostream>
#include "NodoInterno.h"

Bytes* NodoInterno:: Serializarse(){




    };

Bytes* NodoInterno::Nodo(Bytes CodigoBinario){



    };

Bytes* NodoInterno::Nodo(Key subclave ,unsigned long int ref){



    };

Bytes* NodoInterno::Hidratar(Bytes CodigoBinario){




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

unsigned long int NodoInterno::getTamanioSerializado(){

	unsigned long int tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
    tamanioSerializado += sizeof(this->Ref1erNodo);

	/*for (unsigned int i = 0;i < this->listIdRegistros.size(); i++){
		tamanioSerializado += sizeof(this->listIdRegistros[i]);
		tamanioSerializado += sizeof(this->listNroBloque[i]);
	}

    list< SubClaveRef<T>  >* ListaSubClaveRef;*/

	return tamanioSerializado;
}
