#include <iostream>

class InterfazSerializar{
    public:
        virtual void Serializarse() = 0;
        virtual      Hidratar(char* CodigoBinario ) =0;
        virtual ~InterfazSerializar() {}
}
