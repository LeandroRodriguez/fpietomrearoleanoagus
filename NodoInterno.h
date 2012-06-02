#ifndef NODOINTERNO_H_
#define NODOINTERNO_H_

#include <typeinfo>
#include <iostream>
#include <list>
#include <string.h>
#include <cstring>
#include "SubClaveRef.h"
#include "Nodo.h"
#include "Arbol.h"
#include "NodoHoja.h"

using namespace std;

class NodoInterno: public Nodo{

    /*Atributos de clase madre Nodo, se heredan como privados
        unsigned long int CantElem
        unsigned long int Altura
        Dimension         dimension
        unsigned long int  tamanioMaximoNodo;
        unsigned int idBloque;
    */

    private:

    int Ref1erNodo;

    list< SubClaveRef* >* ListaSubClaveRef;

    /*funciona para char*,y todos los demas tipos  */
    bool SeRepiteSubclave(SubClaveRef* item);

    void inicialize();
    public:

    /*void Copiar(NodoInterno<T>* Nold){
        this->CantElem= Nold->CantElem;
        this->Altura= Nold->Altura;
        this->dimension=Nold->dimension;
        this->tamanioMaximoNodo=Nold->tamanioMaximoNodo;
        this->ListaSubClaveRef = new list< SubClaveRef<T>* >(Nold->ListaSubClaveRef);
        }*/

    NodoInterno(Bytes* CodigoBinario);

    NodoInterno(char* cadena);

    NodoInterno(Arbol* arbol):Nodo(arbol){
        this->inicialize();
        }

    NodoInterno();
    NodoInterno(int ref1,string subclave ,int ref2);

    Resultado InsertarNuevaSubClaveRef ( string subclave,int refAbloqueArbol );

    bool BuscarDato(Key* datoBuscado);
    list<Key*>* BuscarSegunFecha(string subclave, int dim, string fechaInicio, string fechaFin);

    void Inicializar( int ref1 ,string subclave ,int ref2 );

    string conseguirClaveQueDividaAlMedioPonderadoElNodo();

    unsigned long int getTamanioSerializado();


    char* Serializarse();

    void Hidratar(char* bytes);
    ~NodoInterno(){}

    int DevolverNodoHijoSegunSubclave(string subcReq ,int& OtraIdNodoSiSubclaveIgual);
    list<int>* DevolverTodosSusIdHijosEnOrden();
    list<Nodo*>* DevolverNodosDadasIds(list<int>* ListaIdsNodos);
    void imprimir();

    Resultado insertarElemento(offset nroBloque, offset nroRegistro, Key* dato, double porcentaje);

    void setAltura(int h);
    void setDim(int h);
    int getDim();
    int getAltura();

};



#endif
