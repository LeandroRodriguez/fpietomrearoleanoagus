#include <iostream>
#include "ManejoArchivos/Bytes.h"

class InterfazSerializar{
    public:
        virtual Bytes* Serializarse() = 0;

        virtual void Hidratar(Bytes* CodigoBinario ) = 0;

        virtual unsigned long int getTamanioSerializado() = 0;

        virtual ~InterfazSerializar(){}
};
