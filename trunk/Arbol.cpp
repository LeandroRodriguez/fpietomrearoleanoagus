#include "Arbol.h"
#include <string.h>

Nodo* Arbol::DevolverNodoSegunID(int IdNodo){
    Nodo* aux = this->persistir->leerNodo(IdNodo);
	aux->setArbol(this);
	return aux;
}

void Arbol::actualizarNodo(Nodo* nodoAActualizar){
	this->persistir->ActualizarNodo( nodoAActualizar);
    }

Arbol::Arbol( PersistenciaArbol* persistencia) {
	this->persistir=persistencia;
	this->cantidadElem= 0;
	this->raiz = NULL;

	if (this->persistir->existeBloque( ID_RAIZ)){
		this->raiz = this->persistir->obtenerRaiz();
		//if (this->raiz!= NULL)
		//	this->raiz->setArbol(this);
		//por ahora esto no lo ponemos, es sucio
	}

}

Arbol::~Arbol() {
	if (this->raiz!=NULL)
		delete this->raiz;
}


Resultado Arbol::insertar(offset nroBloque, offset nroRegistro, Key* dato){
	Resultado res;
	if (!raiz) {//lazy initialization
		//Es el primerElemento
            Nodo* Riz = this->crearRaiz();
            this->raiz = (NodoHoja*) (Riz);
            this->raiz->setIdDelNodo(ID_RAIZ);
            res = this->raiz->insertarElemento(nroRegistro, nroBloque , dato, 1);
                if(res == RES_OK){
                    this->cantidadElem  ++;
                    this->actualizarNodo(this->raiz);
                    }else{cout << "Grave error.Dato no entra en nodo"<< endl;}
	} else {
		//debo insertar recursivamente
		res = raiz->insertarElemento(nroRegistro, nroBloque, dato, 1);
		if(res == RES_OK)this->cantidadElem  ++;
		if(res == RES_DESBORDADO && (this->raiz->getHojaOInterno()=='H')){
            //se desborda y solo habia 1 nodo hoja
		    NodoHoja* Nder = (NodoHoja*) this->crearNuevoNodo(0,' ');
		    NodoHoja* raizvieja = (NodoHoja*) this->raiz;
            Key* k=NULL;
		    Nder = raizvieja->PartirEn2(k);//parti mi raiz hoja en 2
            NodoInterno<string>* RAIZNUEVA = (NodoInterno<string>*) this->crearNuevoNodo(1,'s');
            //consigo la subclave que va a subir
		    string subclaveRaizNueva = *(string*)k->getSubClaveSegunDim(Key::getDimensionSegunAltura(1));
            //a continuacion, swapeo IDS, para dejar la raiz siempre en su ID_RAIZ
            int auxID = RAIZNUEVA->getIdDelNodo();
            RAIZNUEVA->setIdDelNodo(raizvieja->getIdDelNodo());
            raizvieja->setIdDelNodo(auxID);
            //en mi raiz nueva, coloco la subclave del medio,y referencias a mis 2 hijos.
            RAIZNUEVA->Inicializar(raizvieja->getIdDelNodo(),subclaveRaizNueva,Nder->getIdDelNodo());
            /*guardo todos los cambios*/
            this->actualizarNodo(RAIZNUEVA);
            this->actualizarNodo(raizvieja);
            this->actualizarNodo(Nder);
            this->cantidadElem+=2;
            res=RES_OK;//queda todo bien
            }
	}
    return res;
}


void Arbol::ultimosAdisco() {
	/* La raiz la guardo siempre*/
	this->persistir->guardarRaiz(this->raiz);
	//this->actualizarNodo(this->raiz);
	//raiz = this->getNodo(1);
	/*Guardo solo los bloques que se modificaron*/
	/*for (list<Nodo*>::iterator it = ultimosAccedidos.begin(); it
			!= ultimosAccedidos.end(); ++it) {
		if ((*it)->getModificado() && (*it)->getId() != this->raiz->getId()) {
			this->actualizarNodo((*it));
		}
		if((*it)->getId() != this->raiz->getId())
			delete(*it);

	}

	ultimosAccedidos.clear();*/
}

Nodo* Arbol::crearRaiz() {
	Nodo* nuevaRaiz = this->crearNuevoNodo('H',' ');
	return nuevaRaiz;
}

Nodo* Arbol::crearNuevoNodo(int nivel,char tipo ) {
	Nodo* nuevoNodo = NULL;
	if (nivel == 0) {
		nuevoNodo = new NodoHoja();
	} else {//aca puedo poner la inteligencia para setear la dimension
            if (tipo == 'i')nuevoNodo = new NodoInterno<int>();
            if (tipo == 's')nuevoNodo = new NodoInterno<string>();
      }

	this->persistir->agregarNodo( nuevoNodo);
	return nuevoNodo;

}

Nodo* Arbol::getRaiz(){
	return this->raiz;
}

void Arbol::imprimir(){
	if (raiz != NULL) {
		cout << "EL ARBOL: " << endl;
		this->raiz->imprimir();
	}
	else{
		cout << "EL ARBOL NO TIENE ELEMENTOS " << endl;
	}
}

