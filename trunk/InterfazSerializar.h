#ifndef INTERFAZSERIALIZAR_H_INCLUDED
#define INTERFAZSERIALIZAR_H_INCLUDED

class InterfazSerializar{
    public:
        virtual char* Serializarse() = 0;

        virtual void Hidratar(char* CodigoBinario ) =0;

        virtual unsigned long int getTamanioSerializado() = 0;

        virtual ~InterfazSerializar(){};
};



#endif // INTERFAZSERIALIZAR_H_INCLUDED
