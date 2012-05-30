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
    bool EliminarIdRegistro(int id){
        bool found = false;
        list<int>::iterator itRegistros;
        itRegistros= this->listIdRegistros->begin();

        for(;itRegistros!=this->listIdRegistros->end();itRegistros++){
            int regId = *itRegistros;
            if( regId == id ){
                this->listIdRegistros->erase(itRegistros);
                found = true;
                break;
                }
        }
        this->ActualizarCantElem();
        return found;
    }
    bool EliminarNroBloque(int Blo){
        bool found = false;
        list<int>::iterator itBloq;
        itBloq= this->listNroBloque->begin();

        for(;itBloq!=this->listNroBloque->end();itBloq++){
            int nodoId = *itBloq;
            if( nodoId == Blo ){
                this->listIdRegistros->erase(itBloq);
                found = true;
                break;
                }
        }
        this->ActualizarCantElem();
        return found;
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

    unsigned long int getTamanioSerializado();
    char* Serializarse();
    void Hidratar(char* bytes);
    int getTamanioConDatos();
    Resultado insertarElemento(offset idRegistro, offset nroBloque, Key* dato, double porcentaje);
    vector<int> getTamanios();
    void imprimir();

    NodoHoja* PartirEn2(Key* &key);

};

#endif
