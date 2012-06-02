#include "NodoInterno.h"

bool compare (SubClaveRef* s1, SubClaveRef* s2){
    bool resultado = s1->esMenorEstrictoQue(s2);
    return resultado;
};


bool NodoInterno::SeRepiteSubclave(SubClaveRef* item){
        list< SubClaveRef* >::iterator it;
        it = this->ListaSubClaveRef->begin();

        bool SeRepite=false;

        for(;it!=this->ListaSubClaveRef->end();it++){
                SubClaveRef* cosa = *it;
                if( cosa->esIgualQue(item)){
                    SeRepite=true;
                    break;
                    }
                }
        return SeRepite;
        }

void NodoInterno::inicialize(){
        this->tamanioMaximoNodo=LONGITUD_BLOQUE_NODO;
        this->CantElem=0;
        this->ListaSubClaveRef= new list<SubClaveRef* >;
        }

    NodoInterno::NodoInterno(Bytes* CodigoBinario){
        this->inicialize();
        char* cod = new char[CodigoBinario->toString().length()];
        strcpy(cod,CodigoBinario->toString().c_str());
        this->Hidratar(cod);
        }

    NodoInterno::NodoInterno(char* cadena){
        this->inicialize();
        this->Hidratar(cadena);
    }

    NodoInterno::NodoInterno(){
        this->inicialize();
        }

    NodoInterno::NodoInterno(int ref1,string subclave ,int ref2){
        this->inicialize();
        this->Inicializar(ref1,subclave,ref2);
        }

Resultado NodoInterno::InsertarNuevaSubClaveRef ( string subclave,int refAbloqueArbol ){
        /*Busca en el nodo si hay algún registro con los mismos identificadores que IdentificadorDato.
        Si lo encuentra, devuelve como resultado RES_DUPLICADO.

        Si el nodo hoja desborda, Devuelve  RES_DESBORDADO
        sino, devuelve RES_OK*/
        if(this->ListaSubClaveRef->empty()){
            this->ListaSubClaveRef->push_front(new SubClaveRef(subclave,refAbloqueArbol));
            this->CantElem=this->CantElem+1;
            return RES_OK;
            }

        SubClaveRef* itemNuevo = new SubClaveRef(subclave,refAbloqueArbol);

        if( this->SeRepiteSubclave(itemNuevo) )return RES_DUPLICADO;

       // SubClaveRef* primeritem = this->ListaSubClaveRef->front();

      //  if( itemNuevo->esMenorEstrictoQue(primeritem) ) {
        //    int aux = itemNuevo->getRefNodo();
          //  itemNuevo->setRefNodo(this->Ref1erNodo);
        //    this->Ref1erNodo=aux;/*tiene un grado mas de complejidad, debido a 1er ref nodo*/
       //     this->ListaSubClaveRef->push_front(itemNuevo);
       //     this->CantElem=this->CantElem+1;
      //      }else{
            this->ListaSubClaveRef->push_back(itemNuevo);
            this->ListaSubClaveRef->sort(compare);
            this->CantElem=this->CantElem+1;
      //      }
        if ( this->getTamanioSerializado() > this->tamanioMaximoNodo ) return RES_DESBORDADO;
        return RES_OK;
    }

void NodoInterno::Inicializar( int ref1 ,string subclave ,int ref2 ){
        this->Ref1erNodo=ref1;
        this->InsertarNuevaSubClaveRef(subclave,ref2);
    }

unsigned long int NodoInterno::getTamanioSerializado(){

	size_t tamanioSerializado = 0;

	tamanioSerializado += sizeof(this->CantElem);
	tamanioSerializado += sizeof(this->Altura);
	tamanioSerializado += sizeof(this->dimension);
    tamanioSerializado += sizeof(this->Ref1erNodo);
    /* consigo el tamanio de los elementos contenidos en ListaSubClaveRef*/
    list< SubClaveRef* >::iterator it;

    it = this->ListaSubClaveRef->begin();

    for(;it!=this->ListaSubClaveRef->end();it++){
        tamanioSerializado += (*it)->getTamanioSerializado();
        }
	return tamanioSerializado;
}

char* NodoInterno::Serializarse(){
	unsigned long int  tamanioTotal = this->getTamanioSerializado();

    /*el string que voy a devolver*/
	char* str =(char*) malloc(tamanioTotal * sizeof(char));
	unsigned int cur = 0;/*cur = cursor*/

    /*guardo la cantidad de elementos */
	memcpy(str + cur, &this->CantElem , sizeof(this->CantElem));
	cur += sizeof(this->CantElem);


	memcpy(str + cur,&this->Altura, sizeof(this->Altura));
	cur += sizeof(this->Altura);

	memcpy(str + cur,&this->dimension , sizeof(this->dimension));
	cur += sizeof(this->dimension);

	memcpy(str + cur,&this->Ref1erNodo, sizeof(this->Ref1erNodo));
	cur += sizeof(this->Ref1erNodo);

    /*tengo que guardar todos los elementos de la lista */
    list< SubClaveRef* >::iterator it;

    it= this->ListaSubClaveRef->begin();

    for(;it!=this->ListaSubClaveRef->end();it++){
        SubClaveRef* cosa = *it;
        char* serializacion = cosa->Serializarse();
        memcpy(str+cur, serializacion, cosa->getTamanioSerializado() );
        cur+=cosa->getTamanioSerializado();
    }
     //cout << "linea" << string(str) << endl;

	return str;
}

void NodoInterno::Hidratar(char* bytes){

    unsigned int cur = 0;/*cur = cursor ,ya se sabe el tipo*/
    int AUXMAXCANT =0;//OJO, cant de elementos crece naturalmente al ingresar datos
	memcpy(&AUXMAXCANT, bytes + cur, sizeof(this->CantElem));
	cur += sizeof(this->CantElem);

	memcpy(&this->Altura, bytes + cur, sizeof(this->Altura));
	cur += sizeof(this->Altura);
    	cout << "Altura: " << this->Altura << endl;

	memcpy(&this->dimension, bytes + cur, sizeof(this->dimension));
	cur += sizeof(this->dimension);
    	cout << "Dimension: " << this->dimension << endl;

	memcpy(&this->Ref1erNodo, bytes+ cur, sizeof(this->Ref1erNodo));
	cur += sizeof(this->Ref1erNodo);
    	cout << "Ref1erNodo: " << this->Ref1erNodo << endl;
    //int hastaaca = cur;
    int i=0;
    while( i < AUXMAXCANT ){
        SubClaveRef scr(bytes,cur);
        this->InsertarNuevaSubClaveRef( scr.getSubClave(),scr.getRefNodo() );
        //el cur se va incrementando solo, adentro del constructor de SubClaveRef
        //cout << "cursor: " << (cur-hastaaca) << endl;
        i=i+1;
        }
    }

int NodoInterno::DevolverNodoHijoSegunSubclave(string subcReq,int& OtroIdNodoEnCasoDeSubClaveIgual){
        OtroIdNodoEnCasoDeSubClaveIgual= IDNODOINVALIDO;//DEFAULT
        list< SubClaveRef* >::iterator it;
        it= this->ListaSubClaveRef->begin();
        SubClaveRef* cosa = *it;
        //CasoParticularExtremoIzquierdo
/***********************************************************************/
        bool FirstSubIgualaSubReq = (cosa->esIgualQue(subcReq));
        if(FirstSubIgualaSubReq){
            OtroIdNodoEnCasoDeSubClaveIgual = this->Ref1erNodo;
            return cosa->getRefNodo();
            }

        bool FirstSubMayorEstrictoAsubReq = (cosa->esMayorEstrictoQue(subcReq));
        if (FirstSubMayorEstrictoAsubReq){
            return this->Ref1erNodo;
            }
/***********************************************************************/
        /*ya considere para el caso del extremo izquierdo  */
        for(;it!=this->ListaSubClaveRef->end();it++){
            cosa = *it;
            bool SubIgual = (cosa->esIgualQue(subcReq));
            bool SubMayorEstricto = (cosa->esMayorEstrictoQue(subcReq));

            /*si es igual, devuelvo ref a la derecha la subK de la lista,y el anterior */
            if( SubIgual ) {
                OtroIdNodoEnCasoDeSubClaveIgual =  (*(it--))->getRefNodo();
                return cosa->getRefNodo();
                }

            if (SubMayorEstricto){
            /*si la subK en la que estoy en la lista, es mas grande que subcReq, devuelvo ref anterior */
                it--;
                cosa = *it;
                return (  cosa->getRefNodo()   );
                }
            /*si llegue aca, mi subcReq,es mayor que mi subK de la pos en la que estoy */
            }
        /*si llegue hasta aca, tengo que irme por el extremo derecho  */
        return cosa->getRefNodo();
    }

list<int>* NodoInterno::DevolverTodosSusIdHijosEnOrden(){
    list<int>* listIdHijos = new list<int>();
    list< SubClaveRef* >::iterator it;
    it= this->ListaSubClaveRef->begin();

    listIdHijos->push_back(this->Ref1erNodo);
    for( ; it != this->ListaSubClaveRef->end() ; it++ ){
       SubClaveRef* item = *it;
       listIdHijos->push_back(item->getRefNodo() );
       }
       return listIdHijos;
    }
void NodoInterno::imprimir(){
        std::cout <<"idBloque:"<<this->idBloque << ", cantElem:"<< this->CantElem << ", altura:" << this->Altura
			<<	", dimension:" << this->dimension<< ", Referencias:"<<endl;
		std::cout<<	"idNodo: " << this->Ref1erNodo << endl;

        list< SubClaveRef* >::iterator it;
        it= this->ListaSubClaveRef->begin();

        for(;it!=this->ListaSubClaveRef->end();it++){
            SubClaveRef* cosa = *it;
            cosa->imprimir();
            }
        std::cout <<"***************+++***************" << endl;
        list< SubClaveRef* >::iterator it2;
        it2= this->ListaSubClaveRef->begin();

        Nodo* nodito = this->arbol->DevolverNodoSegunID(this->Ref1erNodo);

        if(!nodito->tieneArbol())nodito->setArbol(this->arbol);
        nodito->imprimir();

        for(;it2!=this->ListaSubClaveRef->end();it2++){
            SubClaveRef* sc = *it2;
            Nodo* cosa = this->arbol->DevolverNodoSegunID(sc->getRefNodo());
            if(!cosa->tieneArbol())cosa->setArbol(this->arbol);
            cosa->imprimir();
        }
    }

bool NodoInterno::BuscarDato(Key* datoBuscado){
    bool encontrado = false;
    string subclave = datoBuscado->getSubClaveSegunDim(this->dimension);
    int otroNodoPorSiDaIgualSub = IDNODOINVALIDO;
    int id = this->DevolverNodoHijoSegunSubclave(subclave,otroNodoPorSiDaIgualSub);
    Nodo* nodoHijo = arbol->DevolverNodoSegunID(id);

    if( otroNodoPorSiDaIgualSub != IDNODOINVALIDO ){
    Nodo* otroHijo = arbol->DevolverNodoSegunID(otroNodoPorSiDaIgualSub);
    encontrado = ( nodoHijo->BuscarDato(datoBuscado) || otroHijo->BuscarDato(datoBuscado));
    }else{
        encontrado = nodoHijo->BuscarDato(datoBuscado);
        }
    return encontrado;
}

list<Key*>* NodoInterno::BuscarSegunFecha(string subclave, int dim, string fechaInicio, string fechaFin){
    list<Key*>* datos1 = new list<Key*>();
    list<Key*>* datos2 = new list<Key*>();
    int otroNodoPorSiDaIgualSub = IDNODOINVALIDO;
    if (this->getDim() == dim)
        //caso feliz en q la dim coindice
        int id = this->DevolverNodoHijoSegunSubclave(subclave,otroNodoPorSiDaIgualSub);
        Nodo* nodoHijo = arbol->DevolverNodoSegunID(id);
        if( otroNodoPorSiDaIgualSub != IDNODOINVALIDO ){
            Nodo* otroHijo = arbol->DevolverNodoSegunID(otroNodoPorSiDaIgualSub);
            datos1 = nodoHijo->BuscarSegunFecha(subclave, dim, fechaInicio, fechaFin);
            datos2 = otroHijo->BuscarSegunFecha(subclave, dim, fechaInicio, fechaFin);
        }else{
            datos1 = nodoHijo->BuscarSegunFecha(subclave, dim, fechaInicio, fechaFin);
        }
    else
        //caso no feliz en q la dim no coincide
        list<int>* ids = this->DevolverTodosSusIdHijosEnOrden();
        list<Nodo*>* nodos= this->DevolverNodosSegunIds();
        list<int>::iterator itNodo = nodos->begin();
        datos1->itNodo->BuscarSegun(subclave, dim, fechaInicio, fechaFin);
        //primer dato lo hagarro afuera
        while (itNodo != nodos->end()){
            //incremento
            itNodo++:
            //segundo dato
            datos2->itNodo->BuscarSegunFecha(subclave, dim, fechaInicio, fechaFin);
            datos1->merge(*datos2);
        }
    return datos1;
}

Resultado NodoInterno::insertarElemento(offset nroBloque, offset nroRegistro, Key* dato, double porcentaje){
        string subclave = dato->getSubClaveSegunDim(this->dimension);
        int dummy =0;
        int IDNodoAbajo = this->DevolverNodoHijoSegunSubclave(subclave,dummy);
        Resultado Res;

        if (this->Altura > 1 ){/*He aqui la recursividad.Voy bajando por el arbol */
            //levantar un nodo interno, de la persistencia, con IDNodoAbajo
            Nodo* NodoLeido =this->arbol->DevolverNodoSegunID(IDNodoAbajo);
            Res = NodoLeido->insertarElemento(nroBloque,nroRegistro,dato,porcentaje);
        }else{/*estoy en un nodo interno de nivel 1*/
            NodoHoja* NodoHleido = (NodoHoja*)(this->arbol->DevolverNodoSegunID(IDNodoAbajo));
            Res = NodoHleido->insertarElemento(nroBloque,nroRegistro,dato, porcentaje);

            if (Res == RES_DESBORDADO ){/*Aca tengo que solucionar overflow Hojas  */
                NodoHoja* NHder=NULL;
                Key* k=NULL;
                NHder = NodoHleido->PartirEn2(k);

            Res = this->InsertarNuevaSubClaveRef((k->getSubClaveSegunDim(this->dimension)),NHder->getIdDelNodo());

                 if (Res==RES_OK || Res==RES_DESBORDADO){//actualizo todos los cambios
                    this->arbol->actualizarNodo(this);
                    this->arbol->actualizarNodo(NodoHleido);
                    this->arbol->actualizarNodo(NHder);
                    }else cout << "subclave repetida, error mortal" << endl;
                }else{
                    this->arbol->actualizarNodo(NodoHleido);
                    }
            }
    	return Res;
    }

void NodoInterno::setAltura(int h){
        this->Altura=h;
        this->dimension= Key::getDimensionSegunAltura(h);
        }
void NodoInterno::setDim(int h){
        this->dimension=h;
        }
int NodoInterno::getDim(){
        return this->dimension;
    }

int NodoInterno::getAltura(){
        return this->Altura;
    }
