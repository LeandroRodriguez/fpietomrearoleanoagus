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







}
