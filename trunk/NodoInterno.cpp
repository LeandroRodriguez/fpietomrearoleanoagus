#include <iostream>
#include "NodoInterno.h"

Bytes* NodoInterno:: Serializarse(){



    };

Bytes* NodoInterno::Nodo(Bytes CodigoBinario){



    };

Bytes* NodoInterno::Hidratar(Bytes CodigoBinario){




    };

unsigned long int NodoInterno::getTamanioSerializado(){



    };

unsigned long int NodoInterno::~NodoInterno(){



    };

bool NodoInterno::InsertarSubClaveReferencia( SubClave subclave ,unsigned long int ref ){

        SubClaveRef NuevaDupla;
        NuevaDupla.RefNodo=ref;
        NuevaDupla.SubClave= subclave;

        this->ListaSubClaveRef->push_back(NuevaDupla);

    }

