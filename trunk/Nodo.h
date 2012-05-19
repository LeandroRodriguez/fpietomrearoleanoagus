#include <iostream>

class Nodo:public InterfazSerializar {

    protected: /*asi al heredar los puede cambiar, si lo pongo private kb */

    unsigned long int CantElem
    unsigned long int Altura
    Dimension         dimension
    unsigned long int  tamanioMaximoNodo;
    unsigned long int RefBloque;

    public:
    Nodo();
    virtual ~Nodo();


}
