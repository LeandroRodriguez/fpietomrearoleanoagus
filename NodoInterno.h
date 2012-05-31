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


template<class T>
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

    list< SubClaveRef<T>* >* ListaSubClaveRef;

    /*funciona para char*,y todos los demas tipos  */
    bool SeRepiteSubclave(SubClaveRef<T>* item){
        typename list< SubClaveRef<T>* >::iterator it;
        it = this->ListaSubClaveRef->begin();

        bool SeRepite=false;

        for(;it!=this->ListaSubClaveRef->end();it++){
                SubClaveRef<T>* cosa = *it;
                if( cosa == item ){
                    SeRepite=true;
                    break;
                    }
                }
        return SeRepite;
        }

    void inicialize(){
        this->tamanioMaximoNodo=LONGITUD_BLOQUE_NODO;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef<T>* >;
        }
    public:

    /*void Copiar(NodoInterno<T>* Nold){
        this->CantElem= Nold->CantElem;
        this->Altura= Nold->Altura;
        this->dimension=Nold->dimension;
        this->tamanioMaximoNodo=Nold->tamanioMaximoNodo;
        this->ListaSubClaveRef = new list< SubClaveRef<T>* >(Nold->ListaSubClaveRef);
        }*/

    NodoInterno(Bytes* CodigoBinario){
        this->inicialize();
        this->Hidratar(CodigoBinario->toString() );
        }

    NodoInterno(char* cadena){
        this->inicialize();
        this->Hidratar(cadena);
    }

    NodoInterno(Arbol* arbol):Nodo(arbol){
        this->inicialize();
        }

    NodoInterno(){
        this->inicialize();
        }

    NodoInterno(int ref1,T subclave ,int ref2){
        this->inicialize();
        this->Inicializar(ref1,subclave,ref2);
        }

    Resultado InsertarNuevaSubClaveRef ( T subclave,int refAbloqueArbol ){
        /*Busca en el nodo si hay algún registro con los mismos identificadores que IdentificadorDato.
        Si lo encuentra, devuelve como resultado RES_DUPLICADO.

        Si el nodo hoja desborda, Devuelve  RES_DESBORDADO
        sino, devuelve RES_OK*/

        SubClaveRef<T>* item = new SubClaveRef<T>(subclave,refAbloqueArbol);

        if( this->SeRepiteSubclave(item) )return RES_DUPLICADO;

        if( item < (this->ListaSubClaveRef->front() )){
            int aux = item->getRefNodo();
            item->setRefNodo(this->Ref1erNodo);
            this->Ref1erNodo=aux;/*tiene un grado mas de complejidad, debido a 1er ref nodo*/
            }
            this->ListaSubClaveRef->push_back(item);
            this->ListaSubClaveRef->sort();
            this->CantElem=(this->CantElem)+1;
        if ( this->getTamanioSerializado() > this->tamanioMaximoNodo ) return RES_DESBORDADO;
        return RES_OK;
    }

    void Inicializar( int ref1 ,T subclave ,int ref2 ){
        this->Ref1erNodo=ref1;
        this->InsertarNuevaSubClaveRef(subclave,ref2);
    }

        //esto hay que mejorarlo.
    T conseguirClaveQueDividaAlMedioPonderadoElNodo(){

        typename list< SubClaveRef<T> >::iterator it;
        it = this->ListaSubClaveRef->begin();
        if( this->CantElem == 0) return -1;

        unsigned int Value = 0;
        if ( this->CantElem % 2 != 0){
            Value = ( this->CantElem / 2 )+1;
            }else{
                Value=  this->CantElem/2 ;
                }

        for(int I=0;I<=Value;it++){
        }
        SubClaveRef<T>* cosa = *it;
        return cosa->getSubClave();
    }

    unsigned long int getTamanioSerializado(){

	size_t tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
    tamanioSerializado += sizeof(this->Ref1erNodo);
    tamanioSerializado += ESPACIO_TIPOS;              /*aca guardo el tipo*/

    /* consigo el tamanio de los elementos contenidos en ListaSubClaveRef*/

    typename list< SubClaveRef<T>* >::iterator it;

    it = this->ListaSubClaveRef->begin();

    for(;it!=this->ListaSubClaveRef->end();it++){
        tamanioSerializado += strlen( (*it)->Serializarse() );//la magia del polimorfismo
        }
	return tamanioSerializado;
}

/* */
    char* Serializarse(){
	unsigned long int  tamanioTotal = this->getTamanioSerializado();

    /*el string que voy a devolver*/
	char* str =(char*) malloc(tamanioTotal * sizeof(char));
	unsigned int cur = 0;/*cur = cursor*/

    /*PRIMERO GUARDO EL TIPO*/
    memcpy(str + cur, typeid(T).name(), ESPACIO_TIPOS);
	cur += ESPACIO_TIPOS;

    /*guardo la cantidad de elementos */
	memcpy(str + cur, &this->CantElem , sizeof(this->CantElem));
	cur += sizeof(this->CantElem);

    /*bis altura*/
	memcpy(str + cur, &this->Altura , sizeof(this->Altura));
	cur += sizeof(this->Altura);

    /*bis ref 1er hijo izq  */
	memcpy(str + cur, &this->dimension , sizeof(this->dimension));
	cur += sizeof(this->dimension);

    /*bis dimension  */
	memcpy(str + cur, &this->Ref1erNodo , sizeof(this->Ref1erNodo));
	cur += sizeof(this->Ref1erNodo);

    /*tengo que guardar todos los elementos de la lista */
    typename list< SubClaveRef<T>* >::iterator it;

    it= this->ListaSubClaveRef->begin();

    for(;it!=this->ListaSubClaveRef->end();it++){
        SubClaveRef<T>* cosa = *it;
        char* serializacion = cosa->Serializarse();
        memcpy(str+cur, serializacion, strlen(serializacion) );
        cur+=strlen(serializacion);
    }
	return str;
}

/*  */
    void Hidratar(char* bytes){

    unsigned int cur = 0;/*cur = cursor ,ya se sabe el tipo*/
	memcpy(&this->CantElem, bytes + cur, sizeof(this->CantElem));
	cur += sizeof(this->CantElem);

	memcpy(&this->Altura, bytes + cur, sizeof(this->Altura));
	cur += sizeof(this->Altura);

	memcpy(&this->dimension, bytes + cur, sizeof(this->dimension));
	cur += sizeof(this->dimension);

	memcpy(bytes + cur, &this->Ref1erNodo , sizeof(this->Ref1erNodo));
	cur += sizeof(this->Ref1erNodo);

    while(cur < strlen(bytes) ){
        SubClaveRef<T> scr(bytes,cur);
        this->InsertarNuevaSubClaveRef( scr.getSubClave(),scr.getRefNodo() );
        //el cur se va incrementando solo, adentro del constructor de SubClaveRef
        }
    }

    ~NodoInterno(){}

    int DevolverNodoHijoSegunSubclave(T subcReq ){
        typename list< SubClaveRef<T>* >::iterator it;
        it= this->ListaSubClaveRef->begin();

        SubClaveRef<T>* cosa = *it;

        bool SubIgual = (cosa->operator==(subcReq));
        bool SubMenorOigual = !(cosa->operator<(subcReq));

        if (SubMenorOigual && !(SubIgual)){
            return this->Ref1erNodo;
        }
        /*ya considere para el caso del extremo izquierdo  */

        for(;it!=this->ListaSubClaveRef->end();it++){
            cosa = *it;
            bool SubIgual = (cosa->operator==(subcReq));
            bool SubMenorOigual = !(cosa->operator<(subcReq));

            /*si es igual, devuelvo ref a la derecha la subK de la lista */
            if( SubIgual ) return cosa->getRefNodo();

            if (SubMenorOigual && !(SubIgual)){
            /*si la subK en la que estoy en la lista, es mas grande que subcReq, devuelvo ref anterior */
                it--;
                cosa = *it;
                return (  cosa->getRefNodo()   );
                }
            it++;/*si llegue aca, mi subcReq,es mayor que mi subK de la pos en la que estoy */
            }
        /*si llegue hasta aca, tengo que irme por el extremo derecho  */
        return cosa->getRefNodo();
    }

    void imprimir(){
        std::cout <<"idBloque:"<<this->idBloque << ", cantElem:"<< this->CantElem << ", altura:" << this->Altura
			<<	", dimension:" << this->dimension<< " refs: " << this->Ref1erNodo << " ";

        typename list< SubClaveRef<T>* >::iterator it;
        it= this->ListaSubClaveRef->begin();

        for(;it!=this->ListaSubClaveRef->end();it++){
            SubClaveRef<T>* cosa = *it;
            cosa->imprimir();
            }
        std::cout << endl;
        }

    Resultado insertarElemento(offset nroBloque, offset nroRegistro, Key* dato, double porcentaje){
        T* subclave = (T*)dato->getSubClaveSegunDim(this->dimension);
        int IDNodoAbajo = this->DevolverNodoHijoSegunSubclave(*subclave);
        Resultado Res;

        if (this->Altura > 1 ){/*He aqui la recursividad.Voy bajando por el arbol */
            //levantar un nodo interno, de la persistencia, con IDNodoAbajo
            Nodo* NodoLeido =this->arbol->DevolverNodoSegunID(IDNodoAbajo);
            Res = NodoLeido->insertarElemento(nroBloque,nroRegistro,dato,porcentaje);
        }else{/*estoy en un nodo interno de nivel 1*/
            NodoHoja* NodoHleido = (NodoHoja*)(this->arbol->DevolverNodoSegunID(IDNodoAbajo));
            Res = NodoHleido->insertarElemento(nroBloque,nroRegistro,dato, porcentaje);

            if (Res == RES_DESBORDADO ){/*Aca tengo que solucionar overflow Hojas  */
                //NodoHoja* NHder = (NodoHoja*)(this->arbol->crearNuevoNodo(0,' '));
                NodoHoja* NHder=NULL;
                Key* k=NULL;
                NHder = NodoHleido->PartirEn2(k);

            Res = this->InsertarNuevaSubClaveRef(*((T*)k->getSubClaveSegunDim(this->dimension)),NHder->getIdDelNodo());

                 if (Res==RES_OK || Res==RES_DESBORDADO){//actualizo todos los cambios
                    this->arbol->actualizarNodo(this);
                    this->arbol->actualizarNodo(NodoHleido);
                    this->arbol->actualizarNodo(NHder);
                    }else cout << "subclave repetida, error mortal" << endl;
                }
            }
    	return Res;
    }

    void setAltura(int h){
        this->Altura=h;
        this->dimension= Key::getDimensionSegunAltura(h);
        }
    void setDim(int h){
        this->dimension=h;
        }
    int getDim(){
        return this->dimension;
    }

    int getAltura(){
        return this->Altura;
    }

};



#endif
