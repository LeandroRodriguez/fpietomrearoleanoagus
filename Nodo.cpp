#include "Nodo.h"

void Nodo::setIdDelNodo(int ref){
     this->idBloque= ref;
    }

char Nodo::getHojaOInterno(){
        if (this->Altura>0)return 'I';
        return 'H';
        }

