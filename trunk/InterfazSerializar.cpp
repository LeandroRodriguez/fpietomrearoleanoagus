#include <iostream>

/* include Bytes */

class InterfazSerializar{
    public:
        virtual Bytes* Serializarse() = 0;

        virtual      Hidratar(char* CodigoBinario ) =0;

        virtual unsigned long int getTamanioSerializado() = 0;

        virtual ~InterfazSerializar() {}
}
