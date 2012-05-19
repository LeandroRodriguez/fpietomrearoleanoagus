#include <iostream>
#include <list>
#include "Nodo.h"
#include "Constantes.h"

class NodoHoja: public Nodo{

    //Atributos de clase madre Nodo, se heredan como privados

    private:
    List<int> listIdRegistros;
    List<int> listNroBloque;
    int proximaHoja;

    

    public:

    NodoHoja(Dimension dimension, int refBloque){
    //me pasan un numero de dimension. despues tendre que matchearlo con una de las dimensiones del accidente
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
	this->dimension = dimension;
	this->refBloque = refBloque;
	this->listIdRegistros = new List<int>();
	this->listNroBloque = new List<int>();
	
    }

    ~NodoHoja(){}
    
    unsigned long int getTamanioSerializado();
    Bytes serializarse();

}
