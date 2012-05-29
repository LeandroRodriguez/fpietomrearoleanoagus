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
    bool VerSiSeRepiteSubclave(SubClaveRef<T>* item){
        typename list< SubClaveRef<T>* >::iterator it;
        it = this->ListaSubClaveRef->begin();

        bool NoSeRepite=true;

        for(;it!=this->ListaSubClaveRef->end();it++){
                SubClaveRef<T>* cosa = *it;
                if( cosa == item ){
                    NoSeRepite=false;
                    break;
                    }
                }
        return NoSeRepite;
    }

    public:

    NodoInterno(Bytes* CodigoBinario){
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef<T>* >;
        this->Hidratar(CodigoBinario->toString() );
        }

    NodoInterno(char* cadena){

        this->tamanioMaximoNodo=0;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef<T>* >;
        this->Hidratar(cadena);
    }

    NodoInterno(Arbol* arbol):Nodo(arbol){
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef<T>* >;
        }

    NodoInterno(){
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef<T>* >;
        }

    NodoInterno(int ref1,T subclave ,int ref2){

        this->ListaSubClaveRef= new list<SubClaveRef<T>* >;

        this->Inicializar(ref1,subclave,ref2);

    }

    Resultado InsertarNuevaSubClaveRef ( T subclave,int refAbloqueArbol ){
        /*Busca en el nodo si hay algún registro con los mismos identificadores que IdentificadorDato.
        Si lo encuentra, devuelve como resultado RES_DUPLICADO.

        Si el nodo hoja desborda, Devuelve  RES_DESBORDADO
        sino, devuelve RES_OK*/

        SubClaveRef<T>* item = new SubClaveRef<T>(subclave,refAbloqueArbol);

        if( this->VerSiSeRepiteSubclave(item) )return RES_DUPLICADO;

        this->ListaSubClaveRef->push_back(item);
        this->ListaSubClaveRef->sort();/*tiene un grado mas de complejidad, debido a 1er ref nodo   */
        this->CantElem=(this->CantElem)+1;

        if ( this->getTamanioSerializado() > this->tamanioMaximoNodo ) return RES_DESBORDADO;

        return RES_OK;
    }

    void Inicializar( int ref1 ,T subclave ,int ref2 ){

        this->Ref1erNodo=ref1;

        this->CantElem=1;

        SubClaveRef<T>* NuevaDupla= new SubClaveRef<T>(subclave,ref2);

        this->InsertarNuevaSubClaveRef(subclave,ref2);

    }

    /* sirve solo para tipos clasicos, int, double, word etc */
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

    /* sirve solo para tipos clasicos, int, double, word etc */
    unsigned long int getTamanioSerializado(){

	size_t tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
    tamanioSerializado += sizeof(this->Ref1erNodo);
    tamanioSerializado += sizeof(int)+1;              /*aca guardo el tipo*/

    /* consigo el tamanio de los elementos contenidos en ListaSubClaveRef*/

    typename list< SubClaveRef<T>* >::iterator it;

    it = this->ListaSubClaveRef->begin();

    for(;it!=this->ListaSubClaveRef->end();it++){

        tamanioSerializado +=  sizeof(T);/*para cada tipo, un tamanio fijo */
        tamanioSerializado +=  sizeof(int);/*ref a nodo   */

        }
	return tamanioSerializado;
}

/*sirve solo para tipos clasicos, int, double, word etc*/
    char* Serializarse(){
	unsigned long int  tamanioTotal = this->getTamanioSerializado();


    /*el string que voy a devolver*/
	char* str =(char*) malloc(tamanioTotal * sizeof(char));
	unsigned int cur = 0;/*cur = cursor*/

    /*PRIMERO GUARDO EL TIPO*/
    memcpy(str + cur, typeid(T).name(), sizeof(int)+1);
	cur += sizeof(int)+1;

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

         T subC = cosa->getSubClave();
         int RefNodo = cosa->getRefNodo();

            memcpy(str + cur, &subC , sizeof(subC));
            cur += sizeof(subC);
            memcpy(str + cur, &RefNodo , sizeof(RefNodo));
            cur += sizeof(RefNodo);
    }
	return str;
}

/*para tipos comunes  */
    void Hidratar(char* bytes){

	unsigned int cur = 0;/*cur = cursor , LOS PRIMEROS 5 fueron leidos para saber el TIPO*/
	memcpy(&this->CantElem, bytes + cur, sizeof(this->CantElem));
	cur += sizeof(this->CantElem);


	memcpy(&this->Altura, bytes + cur, sizeof(this->Altura));
	cur += sizeof(this->Altura);

	memcpy(&this->dimension, bytes + cur, sizeof(this->dimension));
	cur += sizeof(this->dimension);

	memcpy(bytes + cur, &this->Ref1erNodo , sizeof(this->Ref1erNodo));
	cur += sizeof(this->Ref1erNodo);

    while(cur < strlen(bytes) ){

        T subcl;

        memcpy(&subcl, bytes + cur  , sizeof(T) );
        cur += sizeof(T);

        int RefNod;

        memcpy(&RefNod, bytes + cur  , sizeof(int) );
        cur += sizeof(int);

        this->InsertarNuevaSubClaveRef( subcl,RefNod);
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

    void imprimir(){}

    Resultado insertarElemento(offset nroBloque, offset nroRegistro, Key* dato, double porcentaje){
        T subclave = (T) dato->getSubClaveSegunDim(this->dimension);
        int IDNodoAbajo = this->DevolverNodoHijoSegunSubclave(subclave);
        Resultado Res;

        if (this->Altura > 1 ){/*He aqui la recursividad.Voy bajando por el arbol */
            //levantar un nodo interno, de la persistencia, con IDNodoAbajo
            Nodo* NodoLeido =this->arbol->DevolverNodoSegunID(IDNodoAbajo);
            Res = NodoLeido->insertarElemento(nroBloque,nroRegistro,dato,porcentaje);
        }else{/*estoy en un nodo interno de nivel 1*/
            NodoHoja* NodoHleido = (NodoHoja*)(this->arbol->DevolverNodoSegunID(IDNodoAbajo));
            Res = NodoHleido->insertarElemento(nroBloque,nroRegistro,dato, porcentaje);

            if (Res == RES_DESBORDADO ){/*Aca tengo que solucionar overflow Hojas  */
                NodoHoja* NHder = (NodoHoja*)(this->arbol->crearNuevoNodo('H',' '));
                NHder = NodoHleido->PartirEn2();

                this->arbol->actualizarNodo(NodoHleido);
                this->arbol->actualizarNodo(NHder);


                }
            }
    	return Res;
    }

};

template <>
class NodoInterno<char*>:public Nodo{

    private:

    int Ref1erNodo;

    list< SubClaveRef<char*>* >* ListaSubClaveRef;

    public:

    NodoInterno(Arbol* arbol):Nodo(arbol){
        this->tamanioMaximoNodo=0;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef<char*>* >;
        }

    NodoInterno(Bytes* CodigoBinario){
        char* asd = new char[ CodigoBinario->toString().length() ];
        memcpy(asd ,&CodigoBinario->toString() ,CodigoBinario->toString().length() );
        this->Hidratar( asd );
        delete asd;
        }

    NodoInterno(char* cadena){

        this->tamanioMaximoNodo=0;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef<char*>* >;
        this->Hidratar(cadena);
    }

    NodoInterno(){}

    NodoInterno(int ref1,char* subclave ,int ref2){

        this->ListaSubClaveRef= new list<SubClaveRef<char*>* >;

        this->Inicializar(ref1,subclave,ref2);

    }

    void Inicializar( int ref1 ,char* subclave ,int ref2 ){

        this->Ref1erNodo=ref1;

        this->InsertarNuevaSubClaveRef(subclave,ref2);

    }

    Resultado InsertarNuevaSubClaveRef ( char* subclave,int refAbloqueArbol ){
        /*Busca en el nodo si hay algún registro con los mismos identificadores que IdentificadorDato.
        Si lo encuentra, devuelve como resultado RES_DUPLICADO.

        Si el nodo hoja desborda, Devuelve  RES_DESBORDADO
        sino, devuelve RES_OK*/

        SubClaveRef<char*>* item = new SubClaveRef<char*>(subclave,refAbloqueArbol);

        if( this->VerSiSeRepiteSubclave(item) )return RES_DUPLICADO;

        this->ListaSubClaveRef->push_back(item);
        this->ListaSubClaveRef->sort();
        this->CantElem=(this->CantElem)+1;

        if ( this->getTamanioSerializado() > this->tamanioMaximoNodo ) return RES_DESBORDADO;

        return RES_OK;
    }

    bool VerSiSeRepiteSubclave(SubClaveRef<char*>* item){
        list< SubClaveRef<char*>* >::iterator it;
        it = this->ListaSubClaveRef->begin();

        bool NoSeRepite=true;

        for(;it!=this->ListaSubClaveRef->end();it++){
                SubClaveRef<char*>* cosa = *it;
                if( cosa == item ){
                    NoSeRepite=false;
                    break;
                    }
                }
        return NoSeRepite;
    }

    unsigned long int getTamanioSerializado(){

        size_t tamanioSerializado = 0;

    	tamanioSerializado += sizeof(this->CantElem);
    	tamanioSerializado += sizeof(this->Altura);
    	tamanioSerializado += sizeof(this->dimension);
        tamanioSerializado += sizeof(this->Ref1erNodo);
        tamanioSerializado += sizeof(int)+1;/*aca guardo el tipo*/

        /* consigo el tamanio de los elementos contenidos en ListaSubClaveRef*/
        /*Segun el tipo de nodo de subclave que guarde el nodo, estos tamanios pueden variar */


        list< SubClaveRef<char*>* >::iterator it = this->ListaSubClaveRef->begin();

        for(;it!=this->ListaSubClaveRef->end();it++){

            SubClaveRef<char*>* cosa = *it;

            char* subC = cosa->getSubClave();
            int refNodo = cosa->getRefNodo();

            tamanioSerializado +=  sizeof(int);/*convencion para guardar tamanio  */
            tamanioSerializado +=  strlen(subC); /*tamanio variable */
            tamanioSerializado +=  sizeof(refNodo);

            }
    	return tamanioSerializado;


        }

    char* Serializarse(){

        size_t  tamanioTotal = this->getTamanioSerializado();
        /*el string que voy a devolver*/
    	char* str =(char*) malloc(tamanioTotal * sizeof(char));
    	size_t cur = 0;/*cur = cursor*/


        /*PRIMERO GUARDO EL TIPO*/
        memcpy(str + cur, typeid(char*).name() , sizeof(int)+1);
    	cur += sizeof(int)+1;

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
        list< SubClaveRef<char*>* >::iterator it;

        it= this->ListaSubClaveRef->begin();

        int* pTempInt = new int;/* work around para poder usar memcopy, nada mas*/

        for(;it!=this->ListaSubClaveRef->end();it++){

            SubClaveRef<char*>* cosa = *it;

            char* subC = cosa->getSubClave();
            int refNodo = cosa->getRefNodo();

                *pTempInt = strlen(subC);

                memcpy(str + cur, pTempInt , sizeof(int) ); /*convencion 4 bytes para longitud */
                cur += sizeof(int);
                memcpy(str + cur, subC , strlen(subC) );
                cur += strlen(subC);

                *pTempInt = refNodo;

                memcpy(str + cur, pTempInt , sizeof(refNodo));
                cur += sizeof(refNodo);
        }
        delete pTempInt;

    	return str;
    }

    void Hidratar(char* bytes){

     	unsigned int cur = 0;/*cur = cursor */

    	memcpy(&this->CantElem, bytes + cur, sizeof(this->CantElem));
    	cur += sizeof(this->CantElem);


    	memcpy(&this->Altura, bytes + cur, sizeof(this->Altura));
    	cur += sizeof(this->Altura);

    	memcpy(&this->dimension, bytes + cur, sizeof(this->dimension));
    	cur += sizeof(this->dimension);

    	memcpy(bytes + cur, &this->Ref1erNodo , sizeof(this->Ref1erNodo));
    	cur += sizeof(this->Ref1erNodo);

        while(cur < strlen(bytes) ){

            int longitud=0;

            memcpy(&longitud, bytes + cur  , sizeof(int) );
            cur += sizeof(int);

            char* subclave = new char[longitud];

            memcpy(subclave,bytes+longitud,longitud);
            cur += longitud;


            int RefNod=0;

            memcpy(&RefNod, bytes + cur  , sizeof(int) );
            cur += sizeof(int);

            this->InsertarNuevaSubClaveRef( subclave, RefNod);
            }
        }

    char* conseguirClaveQueDividaAlMedioPonderadoElNodo(){

            list< SubClaveRef<char*>* >::iterator it;

            it = this->ListaSubClaveRef->begin();

             unsigned int LongitudTotal=0;

            while(it!= this->ListaSubClaveRef->end()){
                SubClaveRef<char*>* cosa = *it;
                LongitudTotal = LongitudTotal + strlen( cosa->getSubClave() );
                it++;
                }/*consegui longitud total de los datos */

            it = this->ListaSubClaveRef->begin();

            bool NoSeHallaSuperadoLaMitad = true;

            unsigned int LongMitad = (int) LongitudTotal / (int) 2 ;
            unsigned int LongParcial = 0;


            while(NoSeHallaSuperadoLaMitad){
                 SubClaveRef<char*>* cosa = *it;

                 LongParcial = LongParcial + strlen(cosa->getSubClave());

                 if ( LongParcial > LongMitad ){
                     NoSeHallaSuperadoLaMitad = false;
                     }else{
                         it++;
                     }
            }

            return (*it)->getSubClave();
        }

    ~NodoInterno(){}

    Resultado insertarElemento(offset nroBloque, offset nroRegistro, Key* dato, double porcentaje){
    	return RES_OK;
    }

    void imprimir(){}

};





#endif
