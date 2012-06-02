#include "Nodo.h"

void Nodo::setIdDelNodo(int ref){
     this->idBloque= ref;
    }

char Nodo::getHojaOInterno(){
        if (this->Altura>0)return 'I';
        return 'H';
        }

Nodo::Nodo(){}
Nodo::Nodo(Arbol* arb){
    this->arbol=arb;
    }

void Nodo::setArbol(Arbol* arb){
    if(arb!=NULL)this->arbol=arb;
}
