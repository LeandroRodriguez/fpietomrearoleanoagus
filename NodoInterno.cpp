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

