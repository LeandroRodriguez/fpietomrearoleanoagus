#include <iostream>

class InterfazSerializar{
    public:
        virtual char* Serializarse() = 0;

        virtual      Hidratar(char* CodigoBinario ) =0;

        virtual unsigned long int getTamanioSerializado() = 0;

        virtual ~InterfazSerializar() {}
}
