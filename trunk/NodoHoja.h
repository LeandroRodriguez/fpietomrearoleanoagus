#ifndef NODOHOJA_H_INCLUDED
#define NODOHOJA_H_INCLUDED

#include <typeinfo>
#include <iostream>
#include <list>
#include "Nodo.h"
#include "ManejoArchivos/AlmacenamientoBloque.h"
#include <malloc.h>

class NodoHoja: public Nodo{

    //Atributos de clase madre Nodo, se heredan como privados

    private:
    list<int>* listIdRegistros;
    list<int>* listNroBloque;
    int proximaHoja;

    Key* cargarDato(offset idRegistro, offset nroBloque);

    void InsertarIdRegistro(int id){
        this->listIdRegistros->push_back(id);
        this->ActualizarCantElem();
    }
    void InsertarNroBloque(int Blo){
        this->listNroBloque->push_back(Blo);
        this->ActualizarCantElem();
    }
    void ActualizarCantElem(){
        bool Size = (this->listIdRegistros->size() == this->listNroBloque->size());
        if (Size) {
            this->CantElem= this->listIdRegistros->size();
            }
        }
    void inicializar(){
        this->tamanioMaximoNodo=LONGITUD_BLOQUE_NODO;
        this->CantElem=0;
        this->Altura = 0;
        this->dimension=-1;
        this->tamanioUsado=0;
        this->listIdRegistros = new list<int>();
        this->listNroBloque = new list<int>();
        this->proximaHoja=0;//ojo con esto
        }
    public:

    NodoHoja();
    NodoHoja(Arbol* arbol);
    NodoHoja(char* str);
    ~NodoHoja(){};

    bool BuscarDato(Key* datoBuscado);
    list<Key*>* BuscarSegunFecha(string subclave, int dim, string fechaInicio, string fechaFin);
    unsigned long int getTamanioSerializado();
    char* Serializarse();
    void Hidratar(char* bytes);
    int getTamanioConDatos();
    Resultado insertarElemento(offset idRegistro, offset nroBloque, Key* dato, double porcentaje);
    vector<int> getTamanios();
    void imprimir();
    void ordenarBloquesRegistros(int dim);

    NodoHoja* PartirEn2(Key* &key, int dimension);

    Resultado insertarElementoSimuladoCargaInicial(offset idRegistro, offset nroBloque, Key* dato, double porcentaje);
    bool Baja(Key* dato);
};

#endif
