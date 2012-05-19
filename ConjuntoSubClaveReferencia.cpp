#include <iostream>
#include <list>

/*include SubClave      */

struct SubClaveRef{
        SubClave subclave;
        unsigned long int RefNodo;
    }

class ConjuntoSubClaveReferencia:public InterfazSerializar {

    private:

    unsigned long int Ref1erNodo;

    list<SubClaveRef>* ListaSubClaveRef;

    public:

    ConjuntoSubClaveReferencia(){
        };

    ConjuntoSubClaveReferencia(unsigned long int RefIzq, SubClave subc, unsigned long int RefDer){
        this->Ref1erNodo=RefIzq;
        this->ListaSubClaveRef=new list<SubClaveRef>;
        this->InsertarSubClaveReferencia(subc,ref);
        };


    ~ConjuntoSubClaveReferencia(){
        };

    bool InsertarSubClaveReferencia( SubClave subclave ,unsigned long int ref ){

        SubClaveRef NuevaDupla;
        NuevaDupla.RefNodo=ref;
        NuevaDupla.SubClae= subclave;

        this->ListaSubClaveRef->push_back(NuevaDupla);

    }





}
