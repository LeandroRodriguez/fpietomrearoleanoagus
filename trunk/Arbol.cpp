#include "Arbol.h"
#include <string.h>

Nodo* Arbol::DevolverNodoSegunID(int IdNodo){
    Nodo* aux = this->persistir->leerNodo(IdNodo);
	aux->setArbol(this);
	return aux;
}

bool Arbol::BuscarDato(Key* datoBuscado){
    //if (this->raiz->getHojaOInterno()=='H')
      return raiz->BuscarDato(datoBuscado);
}

void Arbol::actualizarNodo(Nodo* nodoAActualizar){
	this->persistir->ActualizarNodo( nodoAActualizar);
    }

Arbol::Arbol( PersistenciaArbol* persistencia) {
	this->persistir=persistencia;
	this->cantidadElem= 0;
	this->raiz = NULL;

	if (this->persistir->existeBloque(ID_RAIZ)){
		this->raiz = this->persistir->obtenerRaiz();
		cout << "El ARBOL cargo raiz existente" << endl;
		cout << "*****************************" << endl;
		}else{
	cout << "No existia raiz previa" << endl;
	cout << "**********************" << endl;
		}
}

Arbol::~Arbol() {
	if (this->raiz!=NULL)
		delete this->raiz;
}


Resultado Arbol::LazyInicialization(offset nroBloque,offset nroRegistro,Key* dato){
//Es el primerElemento
    this->crearRaiz();
    Resultado res = this->raiz->insertarElemento(nroRegistro, nroBloque , dato, 1);
    if(res == RES_OK){
        this->cantidadElem+=1;
        this->actualizarNodo(this->raiz);
        }else{cout << "Grave error."<< endl;}
        return res;
    }

Resultado Arbol::insertar(offset nroBloque, offset nroRegistro, Key* dato){
	Resultado res;
	if (!raiz) {res = this->LazyInicialization(nroBloque,nroRegistro,dato);
	}else{
	    if(!this->raiz->tieneArbol())this->raiz->setArbol(this);
	    //inserto recursivamente
		res = raiz->insertarElemento(nroRegistro, nroBloque, dato, 1);
		if(res == RES_OK){
			this->cantidadElem  ++;
			this->actualizarNodo(this->raiz);
			}
		if(res == RES_DESBORDADO && (this->raiz->getHojaOInterno()=='H')){
            //se desborda y solo habia 1 nodo hoja
		    NodoHoja* Nder=NULL;
		    NodoHoja* raizvieja = (NodoHoja*) this->raiz;
            Key* k=NULL;
		    Nder = raizvieja->PartirEn2(k);//parti mi raiz hoja en 2
            NodoInterno* RAIZNUEVA = (NodoInterno*) this->crearNuevoNodo(1);
            //consigo la subclave que va a subir
		    string subclaveRaizNueva = k->getSubClaveSegunDim(Key::getDimensionSegunAltura(1));

            //a continuacion, swapeo IDS, para dejar la raiz siempre en su ID_RAIZ
            int auxID = RAIZNUEVA->getIdDelNodo();
            RAIZNUEVA->setIdDelNodo(raizvieja->getIdDelNodo());
            raizvieja->setIdDelNodo(auxID);
            //en mi raiz nueva, coloco la subclave del medio,y referencias a mis 2 hijos.
            RAIZNUEVA->Inicializar(raizvieja->getIdDelNodo(),subclaveRaizNueva,Nder->getIdDelNodo());
            this->raiz=RAIZNUEVA;
            /*guardo todos los cambios*/
            this->actualizarNodo(RAIZNUEVA);
            this->actualizarNodo(raizvieja);
            this->actualizarNodo(Nder);
            this->cantidadElem+=2;
            res=RES_OK;//queda todo bien
            }
            //if(res==RES_DESBORDADO && this->raiz-getHojaOinterno()=='i'){}
	}
    return res;
}

NodoHoja* Arbol::crearRaiz() {
	NodoHoja* nuevaRaiz = new NodoHoja(this);
	this->persistir->guardarRaiz(nuevaRaiz);
    this->raiz=nuevaRaiz;
	return nuevaRaiz;
	}

Nodo* Arbol::crearNuevoNodo(unsigned int nivel) {
	Nodo* nuevoNodo = NULL;
	if (nivel == 0) {
		nuevoNodo = new NodoHoja(this);
	} else {
             nuevoNodo = new NodoInterno(this);
            ((NodoInterno*) nuevoNodo)->setAltura(nivel);
            }
	this->persistir->agregarNodo( nuevoNodo);
	return nuevoNodo;
}

Nodo* Arbol::getRaiz(){
	return this->raiz;
}

void Arbol::imprimir(){
	if (raiz != NULL) {
		cout << "Raiz Del Arbol: " << endl;
		if(!this->raiz->tieneArbol())this->raiz->setArbol(this);
		this->raiz->imprimir();
	}
	else{
		cout << "EL ARBOL NO TIENE ELEMENTOS " << endl;
	}
}

/*funcion de arranque para la carga inicial. Aca seteo los datos iniciales para arrancar con la recursividad*/
void Arbol::cargaInicial(list<Dato*>* listaDeDatos){
    /*seteo la dimension con la que comienzo a ordenar(sin ninguna razon en particular elijo una sobre las otras)*/
        int dimension = 1;
        /*creo la raiz vacia, dps la voy a modificar*/
        NodoInterno* raiz = new NodoInterno();
        offset nroNodo = this->persistir->guardarRaiz(raiz);
        /*creo una sublista donde solo voy a tener la lista con los datos iniciales*/
        list<list<Dato*>*>* subListasDatos = new list<list<Dato*>*>();
        subListasDatos->push_back(listaDeDatos);
        list<list<list<Dato*>*>*>* listaDeSubListasDatos = new list<list<list<Dato*>*>*>();
        listaDeSubListasDatos->push_back(subListasDatos);
        /*elijo un porcentaje de empaquetamineto inicial del 75%*/
        double porcentajeDeEmpaquetamiento = 0.75;
        /**/
        int alturaInicial = 0;
        /*funcion recursiva*/
        list<offset>* listaRefs = cargaInicialArmarNodos(listaDeSubListasDatos, dimension, porcentajeDeEmpaquetamiento, &alturaInicial);
        /*me tiene que devolver una sola referencia*/
        list<offset>::iterator itListaRefs;
        itListaRefs = listaRefs->begin();
        offset referencia;
        for(;itListaRefs!=listaRefs->end();itListaRefs++){
                referencia = (*itListaRefs);
        }
        /*levanto el nodo del archivo*/
        NodoInterno* ra = (NodoInterno*)this->persistir->leerNodo(referencia);;
        /*le seteo el idRaiz y lo persisto*/
        this->persistir->guardarRaiz(ra);
        /*modifico el nro nodo de referencia y lo pongo vacio*/
        NodoHoja* nodoVacio = new NodoHoja();
        nodoVacio->setIdDelNodo(referencia);
        this->persistir->ActualizarNodo(nodoVacio);
}
/*desde aca, la recu me va a devolver una lista con un solo nodo, que va a ser el raiz*/

/*devuelvo list de punteros de nodos del nivel anterior, y referencio los nuevos nodos con eso*/
/*en el ultimo la list tiene un solo elemento que debiese ser el puntero de la raiz, esto lo meto en el arbol, pero igual lo manejo en la func no recursiva*/


Dato* Arbol::getElemento (list<Dato*>* lista, int index){
        list<Dato*>::iterator it;
        it=lista->begin();

        int i = 0;
        for(;it!=lista->end();it++){
                if(i == index)
                        return *it;
                i++;
        }
        return NULL;
}

void Arbol::setElemento (list<Dato*>* lista, int index, Dato* dato){
        list<Dato*>::iterator it;
        it=lista->begin();

        int i = 0;
        for(;it!=lista->end();it++){
                if(i == index){
                        lista->insert(it, dato);
                        it++;
                        lista->remove(*it);
                        return;
                }
                i++;
        }
        return;
}

list<Dato*>* Arbol::obtenerListaOrdenadaPorDimension(list<Dato*>* lista, int dimension){
        list<Dato*>* listaOrdenadaDatosSubArboles = new list<Dato*>();
        bool swapped;
        do{
             swapped = false;
             int i;
             for (i = 1; i <= lista->size() - 1; i++)
             {
            	 if(this->getElemento(lista, i-1)->getClave()->getSubClaveSegunDim(dimension) >
					 this->getElemento(lista, i)->getClave()->getSubClaveSegunDim(dimension))
                 {
                         Dato aux = *this->getElemento(lista, i-1);
                         Dato elem = *this->getElemento(lista, i);
                         this->setElemento(lista, i - 1,&elem);
                         this->setElemento(lista, i,&aux);
                         swapped = true;
                 }
             }
        }
        while (swapped);
        return lista;
}

int Arbol::conseguirParticionRecursiva(int nivel, int dimension, list<list<Dato*>*>* listaListasResultados, list<SubClaveRef*>* listaSubClaves, list<list<Dato*>*>** listaListasResultadosDevolucion, list<SubClaveRef*>** listaClavesDevolucion){
	nivel++;
	if(listaSubClaves->size()>1){
	    /*flag para ver si se uso mas de un nodo interno, en cuyo caso la recursividad debe volver a llamarse*/
	    bool usoMasDeUnNodo = false;
		/*aca guardo los resultados de este nivel*/
		list<list<Dato*>*>* listaListasResultadosNueva = new list<list<Dato*>*>();
		list<SubClaveRef*>* listaClavesNueva = new list<SubClaveRef*>();

		list<list<Dato*>*>::iterator itListaDatos;
		itListaDatos = listaListasResultados->begin();
		int paso = 1;
		list<SubClaveRef*>::iterator itClave;
		itClave = listaSubClaves->begin();
		list<Dato*>* listaDatosAux = new list<Dato*>();
		NodoInterno* nodoInterno = new NodoInterno();
		for(;itClave!=listaSubClaves->end();itClave++){
			Resultado res;
			list<Dato*>::iterator itDato;
			itDato = (*itListaDatos)->begin();
			for(;itDato!=(*itListaDatos)->end();itDato++){
				listaDatosAux->push_back(*itDato);
			}
			/*meto clave en el nodo Interno*/
			if(paso == 1){
				nodoInterno->Inicializar(0, (*itClave)->getSubClave(), 0);
				res = RES_OK;
			}
			else{
				res = nodoInterno->InsertarNuevaSubClaveRef((*itClave)->getSubClave(), 0);
			}
			if(res == RES_DESBORDADO){
			    /*si el nodo se desbordo, voy a tener que usar otro nivel mas*/
			    usoMasDeUnNodo = true;
				/*meto lista datos en lista listas datos*/
				listaListasResultadosNueva->push_back(listaDatosAux);
				/*meto clave en lista claves*/
				listaClavesNueva->push_back((*itClave));
				/*instancio nodointerno nuevo*/
				nodoInterno = new NodoInterno();
				/*le inserto el dato(con inicializar)*/
				nodoInterno->Inicializar(0, (*itClave)->getSubClave(), 0);
				/*instancio una nueva lista datos aux*/
				listaDatosAux = new list<Dato*>();
			}
			paso++;

			itListaDatos++;
		}
		/*meto los datos (n+1) en mi lista*/
		list<Dato*>::iterator itDato;
		itDato = (*itListaDatos)->begin();
		for(;itDato!=(*itListaDatos)->end();itDato++){
			listaDatosAux->push_back(*itDato);
		}
		listaListasResultadosNueva->push_back(listaDatosAux);

		if(usoMasDeUnNodo){
            /*llamado recursivo*/
            return conseguirParticionRecursiva(nivel, dimension, listaListasResultadosNueva, listaClavesNueva, listaListasResultadosDevolucion, listaClavesDevolucion);
		}
	}
	/*listas nuevas igual a las que me llegaron*/
	/*deletear la referencia vieja de listas Devolucion???*/
	*listaListasResultadosDevolucion = listaListasResultados;
	*listaClavesDevolucion = listaSubClaves;
    return nivel;
}

int Arbol::cargaInicialConseguirParticionConNivel(list<Dato*>* subListaOrdenada, list<SubClaveRef*>** listaClaves, list<list<Dato*>*>** listaListasDatosSubArboles, double  porcentajeDeEmpaquetamiento, int dimension){
        /*si la subListaOrdenada tiene un solo elemento, devuelvo en la sublista, ese elemento y uno vacio. y en la de clave tomo la clave del unico elemento
        (total, ante igualdad hay que ir para las 2 ramas)*/
	list<Dato*>::iterator itDato;
    itDato = subListaOrdenada->begin();
        //int i = 0;
	/*primer recorrida*/
	list<list<Dato*>*>* listaListasResultados = new list<list<Dato*>*>();
	list<SubClaveRef*>* listaSubClaves = new list<SubClaveRef*>();
	list<Dato*>* listaAux = new list<Dato*>();
	Key* clave;
	NodoHoja* nodoHoja = new NodoHoja();
	for(;itDato!=subListaOrdenada->end();itDato++){
		/*guardo el dato en un nodo(solo en RAM)*/
		Dato* dato = (*itDato);
		offset idRegistro = dato->getIdRegistro();
        offset nroBloque = dato->getNroBoque();
        clave = dato->getClave();
		Resultado res = nodoHoja->insertarElementoSimuladoCargaInicial(idRegistro, nroBloque, clave, porcentajeDeEmpaquetamiento);
		/*veo si desbordo el nodo*/
		if(res==RES_DESBORDADO){
			listaListasResultados->push_back(listaAux);
			nodoHoja = new NodoHoja();
			/*no checkeo el res pq el primero tiene que entrar bien siempre*/
			Resultado res = nodoHoja->insertarElementoSimuladoCargaInicial(idRegistro, nroBloque, clave, porcentajeDeEmpaquetamiento);
			listaAux = new list<Dato*>();
			/*creo y guardo la subClave*/
			SubClaveRef* subClave = new SubClaveRef(clave->getSubClaveSegunDim(dimension),0);
			listaSubClaves->push_back(subClave);
		}
		listaAux->push_back(dato);
	}
	itDato--;
	listaListasResultados->push_back(listaAux);
	/*entonces, tengo una lista de listas de datos, y una lista de subclaves*/
	/*acabo de pasar el nivel 1*/
	int nivel = 1;
	/*tendria que verificar el caso que lista de claves el size sea 0(aca tendria que crear nodo vacio)*/
	/*tambien si claves->size <= listaDatos->size*/
	if(listaSubClaves->size()==0){
		/*setear un nodo vacio o algo*/
		/*agarro la clave del ultimo elemento y la meto en la lista*/
        SubClaveRef* subClave = new SubClaveRef(clave->getSubClaveSegunDim(dimension),0);
        listaSubClaves->push_back(subClave);
        /*meto un dato vacio a la lista*/
        Dato* dato = (*itDato);
		dato->setIdRegistro(0);
        dato->setNroBoque(0);
        dato->setClave(NULL);

        list<Dato*>* listaAux = new list<Dato*>();
        listaAux->push_back(dato);
        /*meto la lista, a mi lista de listas*/
        listaListasResultados->push_back(listaAux);
        nivel++;
	}
	else{
        if((listaSubClaves->size() == listaListasResultados->size())){
            /*meto un dato vacio a la lista para balancear*/
            Dato* dato = (*itDato);
            dato->setIdRegistro(0);
            dato->setNroBoque(0);
            dato->setClave(NULL);

            list<Dato*>* listaAux = new list<Dato*>();
            listaAux->push_back(dato);
            /*meto la lista, a mi lista de listas*/
            listaListasResultados->push_back(listaAux);
        }
        /*le paso las listas a ordenar, y las 2 donde quiero que me devuelva los resultados*/
        nivel = this->conseguirParticionRecursiva(nivel, dimension, listaListasResultados, listaSubClaves, listaListasDatosSubArboles, listaClaves);
	}

    return nivel;
}

int Arbol::conseguirNivelMayor(list<int>* listaMaestraNiveles){
        listaMaestraNiveles->sort();
        return listaMaestraNiveles->back();
}

list<SubClaveRef*>* Arbol::obtenerClavesSegunPos(list<list<SubClaveRef*>*>* listaMaestraClaves, int j, int dimension){
        int i = 0;
        list<SubClaveRef*>* listaClavesSubarboles = new list<SubClaveRef*>();
        list<list<SubClaveRef*>*>::iterator itListaClaves;
        itListaClaves= listaMaestraClaves->begin();
        for(;itListaClaves!=listaMaestraClaves->end();itListaClaves++){
                if(j==i){
                        listaClavesSubarboles = (*itListaClaves);
                        break;
                }
                i++;
        }
        return listaClavesSubarboles;
}

/*obtengo la lista de listas de datos de la pos j de la lista de listas de listas de datos*/
list<list<Dato*>*>* Arbol::obtenerListasSegunPos(list<list<list<Dato*>*>*>* listaMaestraDatosSubArboles, int j){
        int i = 0;
        list<list<Dato*>*>* listaDatosSubarboles;
        list<list<list<Dato*>*>*>::iterator itListaClaves;
        itListaClaves = listaMaestraDatosSubArboles->begin();
        for(;itListaClaves!=listaMaestraDatosSubArboles->end();itListaClaves++){
                if(j==i){
                        listaDatosSubarboles = (*itListaClaves);
                        break;
                }
                i++;
        }
        return listaDatosSubarboles;
}

/*obtengo la referencia de la posicion j de mi lista de referencias*/
offset Arbol::obtenerReferenciaNodosSegunPos(list<offset>* listaReferenciasNodosHios, int j){
        int i = 0;
        offset referenciaNodoHijo;
        list<offset>::iterator itListaRefs;
        itListaRefs = listaReferenciasNodosHios->begin();
        for(;itListaRefs!=listaReferenciasNodosHios->end();itListaRefs++){
                if(j==i){
                        referenciaNodoHijo = (*itListaRefs);
                        break;
                }
                i++;
        }
        return referenciaNodoHijo;
}

/*consigo la clave media(segun tamanio) y las dos sublistas que se parten a partir de esa clave*/
list<SubClaveRef*>* Arbol::partirSubarbol(list<list<Dato*>*>* listaDatosSubArbol, int dimension, list<list<Dato*>*>* listasDatosSubArbolesNuevos){
	/*de mi lista de listas de datos vieja las voy metiendo en una sola lista de datos, agregando en orden al final*/

	/*busco la clave del medio de mi lista de datos*/
	/*guardo en listasDatosSubArbolesNuevos mis dos subarboles y la clave la meto en una lista y la devuelvo*/
	int tamanio = 0;
	list<Dato*>* listaTotal = new list<Dato*>();
	list<list<Dato*>*>::iterator itListaDatos;
	itListaDatos= listaDatosSubArbol->begin();
	for(;itListaDatos!=listaDatosSubArbol->end();itListaDatos++){
		list<Dato*>::iterator itSubListaDatos;
		itSubListaDatos = (*itListaDatos)->begin();
		for(;itSubListaDatos!=(*itListaDatos)->end();itSubListaDatos++){
			listaTotal->push_back(*itSubListaDatos);
			tamanio += (*itSubListaDatos)->getClave()->getTamanioSerializado();
		}
	}

	list<SubClaveRef*>* listaClavesSubarboles = new list<SubClaveRef*>();

	list<Dato*>* listDatosIzq = new list<Dato*>();
	list<Dato*>* listDatosDer = new list<Dato*>();

	list<Dato*>::iterator itlistaTotal;
	itlistaTotal= listaTotal->begin();
	int cursor = 0;
	bool seleccionoClaveMitad = false;
	for(;itlistaTotal!=listaTotal->end();itlistaTotal++){
		Key* c = (*itlistaTotal)->getClave();
		if(cursor >= (tamanio/2))
		{
			if(!seleccionoClaveMitad){
				string clave = c->getSubClaveSegunDim(dimension);
				SubClaveRef* subClave = new SubClaveRef(clave, 0);
				listaClavesSubarboles->push_back(subClave);
				seleccionoClaveMitad = true;
			}
			listDatosDer->push_back(*itlistaTotal);
		}
		else
			listDatosIzq->push_back(*itlistaTotal);

		cursor += c->getTamanioSerializado();
	}

	if(!seleccionoClaveMitad)
	{
		Dato* d = listaTotal->back();
		string clave = d->getClave()->getSubClaveSegunDim(dimension);
		SubClaveRef* subClave = new SubClaveRef(clave, 0);
		listaClavesSubarboles->push_back(subClave);
		if(listaTotal->size() == 1)
		{
			Dato* d = new Dato();
			d->setIdRegistro(0);
			d->setNroBoque(0);
			d->setClave(NULL);
			listDatosDer->push_back(d);
		}
	}

	return listaClavesSubarboles;
}

/*reemplazo la lista de lista de datos en la lista maestra de listas de listas de datos(en la pos j)*/
void Arbol::reemplazarDatoListaDatos(list<list<list<Dato*>*>*>* listaMaestraDatosSubArboles, list<list<Dato*>*>* listasDatosSubArbolesNuevos, int j){
        int i = 0;
        list<list<list<Dato*>*>*>* listaMaestraDatosSubarbolesNueva = new list<list<list<Dato*>*>*>();
        list<list<list<Dato*>*>*>::iterator itListaClaves;
        itListaClaves= listaMaestraDatosSubArboles->begin();
        for(;itListaClaves!=listaMaestraDatosSubArboles->end();itListaClaves++){
                if(j==i){
                        listaMaestraDatosSubarbolesNueva->push_back(listasDatosSubArbolesNuevos);
                }
                else{
                        listaMaestraDatosSubarbolesNueva->push_back(*itListaClaves);
                }
                i++;
        }
        listaMaestraDatosSubArboles = listaMaestraDatosSubarbolesNueva;
}

void Arbol::reemplazarDatoListaClaves(list<list<SubClaveRef*>*>* listaMaestraClaves, list<SubClaveRef*>* claveMediana, int j){
        int i = 0;
        /*si esta lista la malloqueo, tendria que deletear la vieja al final, antes de asignarle la nueva referencia*/
        list<list<SubClaveRef*>*>* listaMaestraClavesNueva = new list<list<SubClaveRef*>*>();
        list<list<SubClaveRef*>*>::iterator itListaClaves;
        itListaClaves= listaMaestraClaves->begin();
        for(;itListaClaves!=listaMaestraClaves->end();itListaClaves++){
                if(j==i){
                        listaMaestraClavesNueva->push_back(claveMediana);
                }
                else{
                        listaMaestraClavesNueva->push_back(*itListaClaves);
                }
                i++;
        }
        listaMaestraClaves = listaMaestraClavesNueva;
}

/*creo un nodo hoja y meto todos los datos de la lista pasada. Luego lo persisto y retorno el nro de nodo*/
offset Arbol::insertarDatosEnNodoHoja(list<Dato*>* listaSubSubArboles, double porcentaje){
        /*instancio un nodoHoja*/
        NodoHoja* nodoHoja = new NodoHoja();
        nodoHoja->setIdDelNodo(10);

        list<Dato*>::iterator itSubListaDatos;
        itSubListaDatos= listaSubSubArboles->begin();

        for(;itSubListaDatos!=listaSubSubArboles->end();itSubListaDatos++){
                /*obtengo de mi dato los 3 datos que necesito para insertar en el nodo*/
                offset idRegistro = (*itSubListaDatos)->getIdRegistro();
                offset nroBloque = (*itSubListaDatos)->getNroBoque();
                Key* clave = (*itSubListaDatos)->getClave();
                offset va = VACIO;
                if(idRegistro == va){
                        /*el nodo queda vacio*/
                        /*si esto pasa este tuviese que ser el unico dato*/
                }
                else{
                        /*para cada elemento de la lista voy insertandolo en mi nodo hoja*/
                        Resultado res = nodoHoja->insertarElemento(idRegistro, nroBloque, clave, porcentaje);
                        /*por como lo arme, no hay chance de que tire overflow. Y verifique antes que no se repitiesen los datos*/
                        if(res == RES_OK){
                                this->cantidadElem++;
                        }
                }
        }
        /*llamo a persistencia para que guarde el nodo*/
        offset nroNodo = this->persistir->agregarNodo(nodoHoja);
        /*me devuelve el nro de nodo, yo retorno ese numero de nodo*/
        return nroNodo;
}

/*SOBRECARGO el metodo de arriba*/
offset Arbol::insertarDatosEnNodoInterno(list<list<SubClaveRef*>*>* listaMaestraClaves, list<offset>* listaReferenciasNodosHios, int i, int dimension){
        /*para la clave de la posicion it de la lista de listas de claves*/
	list<SubClaveRef*>* listaClaves = (list<SubClaveRef*>*)this->obtenerClavesSegunPos(listaMaestraClaves, i, dimension);
	list<SubClaveRef*>::iterator itListaClaves;
	itListaClaves= listaClaves->begin();
	/*construyo mi NodoI*/
	NodoInterno* nodoInterno = new NodoInterno();
	int k = 0;
	offset primerReferencia = this->obtenerReferenciaNodosSegunPos(listaReferenciasNodosHios, k);
	for(;itListaClaves!=listaClaves->end();itListaClaves++){
			k++;
			/*recupero la subClaveRef*/
			SubClaveRef* subClave = (*itListaClaves);
			/*asigno una referencia*/
			offset referenciaSiguiente = this->obtenerReferenciaNodosSegunPos(listaReferenciasNodosHios, k);
			if(k==1){
				/*la primera vez tengo que agregar tambien la primer referencia*/
				nodoInterno->Inicializar(primerReferencia, subClave->getSubClave(), referenciaSiguiente);
			}
			else{
					/*despues solo agrego conjuntos de clave - referencia*/
				nodoInterno->InsertarNuevaSubClaveRef(subClave->getSubClave(), referenciaSiguiente);
			}
	}
    /*tengo que setear la altura, que para este metodo es 1*/
    nodoInterno->setAltura(1);
	/*le agrego la dimension al nodo*/
    nodoInterno->setDim(dimension);
	/*persisto el nodo*/
	offset nroNodo = this->persistir->agregarNodo(nodoInterno);
	/*me devuelve el nro de nodo, yo retorno ese numero de nodo*/
	return nroNodo;
}

list<offset>* Arbol::insertarHijosEnNodoPadre(list<list<SubClaveRef*>*>* listaMaestraClaves, list<offset>* listaRefsNodosArmados, int dimension, int alturaVuelta){
        /*construyo mis NodoI*/
        int d = 0;
        list<offset>* listaRefsNodosInternos = new list<offset>();

        list<list<SubClaveRef*>*>::iterator itListaMaestraClaves;
        itListaMaestraClaves= listaMaestraClaves->begin();
        int k = 0;
        NodoInterno* nodoInterno;
        /*construyo un nodo por cada lista de listas de claves*/
        for(;itListaMaestraClaves!=listaMaestraClaves->end();itListaMaestraClaves++){
			/*instancio un nodo interno por cada lista de claves*/
			/*voy a iterar sobre mis listas de claves para ir armando el nodo interno*/

			nodoInterno = new NodoInterno();
			list<SubClaveRef*>::iterator itListaClaves;

			itListaClaves = (*itListaMaestraClaves)->begin();
			/*consigo la primer referencia*/
			offset primerReferencia = this->obtenerReferenciaNodosSegunPos(listaRefsNodosInternos, k);
			/*meto tantas refs como necesite junto con la clave(1 + qe la cant de claves)*/
			for(;itListaClaves!=(*itListaMaestraClaves)->end();itListaClaves++){
					k++;
					/*recupero la subClaveRef*/
					SubClaveRef* subClave = (*itListaClaves);

					/*asigno una referencia*/
					offset referenciaSiguiente = this->obtenerReferenciaNodosSegunPos(listaRefsNodosInternos, k);
					if(k==1){
							/*la primera vez tengo que agregar tambien la primer referencia*/
						nodoInterno->Inicializar(primerReferencia, subClave->getSubClave(), referenciaSiguiente);
					}
					else{
							/*despues solo agrego conjuntos de clave - referencia*/
						nodoInterno->InsertarNuevaSubClaveRef(subClave->getSubClave(), referenciaSiguiente);
					}
			}
			k++;
			/*le agrego la altura*/
            nodoInterno->setAltura(alturaVuelta);
			/*le agrego la dimension al nodo*/
            nodoInterno->setDim(dimension);
			/*persisto el nodo*/
			offset nroNodo = this->persistir->agregarNodo(nodoInterno);
			/*meto las refs en mi lista*/
			listaRefsNodosInternos->push_back(nroNodo);
        }
        /*retorno la lista de refs*/
        return listaRefsNodosInternos;
}


/*EN TODOS LOS LADOS DONDE METI PUNTEROS A NODOS, HAY QUE CAMBIARLO POR LOS IDS DE LOS NODOS*/
/*TOMAR POSIBLES ACCIONES ANTE EL CASO QUE UN SUBARBOL SOLO TENGA UN DATO (la clave que tendria??)*/
/*VER COMO VOY HACIENDO SUBSISTIR LOS NODOS A LO LARGO DE LA RECURSIVIDAD*/
/*una opcion, devolver los nodos de abajo para arriba a medida que fui terminando, y usar algun flag que me indique cuando llego al nivel de la raiz(la veo muy viable)(repensarlo maniana)*/

/*funcion recursiva encargada de hacer la coordinacion de la magia de la carga inicial*/
list<offset>* Arbol::cargaInicialArmarNodos(list<list<list<Dato*>*>*>* subListasDatos, int dimension, double porcentajeDeEmpaquetamiento, int* alturaVuelta){
        /*Creo 3 listas que voy a ir usando a lo largo de la funcion*/
        list<int>* listaMaestraNiveles = new list<int>();
        list<list<SubClaveRef*>*>* listaMaestraClaves = new list<list<SubClaveRef*>*>();

        list<list<list<Dato*>*>*>* listaMaestraDatosSubArboles = new list<list<list<Dato*>*>*>();

        /*para cada una de mis sublistas:*/
        list<list<list<Dato*>*>*>::iterator itSubListas;
        itSubListas= subListasDatos->begin();

        list<Dato*>* subListaOrdenada;
        list<SubClaveRef*>* listaClaves;
        list<list<Dato*>*>* listaListasDatosSubArboles;
        for(;itSubListas!=subListasDatos->end();itSubListas++){
                list<list<Dato*>*>::iterator itSubSubListas;
                itSubSubListas= (*itSubListas)->begin();

                for(;itSubSubListas!=(*itSubListas)->end();itSubSubListas++){
                        /*ordeno datos por mi dimension*/
                        subListaOrdenada = this->obtenerListaOrdenadaPorDimension((*itSubSubListas),dimension);
                        /*una vez que tengo mi lista ordenada, comienzo con la insercion en nodos como si fuese una carga inicial comun(mmm, mas bien una                               simulacion)*/
                        /*instancio dos listas vacias para que me devuelva resultados el metodo que simula la carga inicial del subarbol*/
                        listaClaves = new list<SubClaveRef*>();//lista de claves

                        listaListasDatosSubArboles = new list<list<Dato*>*>();//lista de listas de datos
                        int nivel = cargaInicialConseguirParticionConNivel(subListaOrdenada, &listaClaves, &listaListasDatosSubArboles, porcentajeDeEmpaquetamiento, dimension); //TO DO
                        /*recupero el nivel del arbol, las claves del nodo raiz y una lista de subarboles*/

                        /*estos datos los tengo que guardar en algun lado o los voy a perder en la siguiente iteracion(ponele que los voy metiendo en 3 listas)*/
                        listaMaestraNiveles->push_back(nivel);
                        listaMaestraClaves->push_back(listaClaves);
                        listaMaestraDatosSubArboles->push_back(listaListasDatosSubArboles);
                }
        }
        /*una vez que sali del primer ciclo compararia los niveles de los distintos subarboles(sublistas)*/
        /*obtengo el mayor nivel*/
        int nivelMayor = this->conseguirNivelMayor(listaMaestraNiveles); //TO DO

        /*si el mayor nivel era 2, ya podria recuperar el nodo hoja entero, auque esto lo puedo verificar mas abajo*/
        if(nivelMayor == 2){
                list<offset>* listaNodosInternos = new list<offset>();
                /*agarro los nodos de algun lado y armo mi arbol resultante*/
                list<list<list<Dato*>*>*>::iterator itListaSubArboles;
                itListaSubArboles= listaMaestraDatosSubArboles->begin();
                /*para cada SubArb de la lista de SubArbs*/
                int i = 0;
                offset nroNodoHoja;
                offset nroNodoInterno;
                list<Dato*>* listaDatosAuxiliar;
                list<list<Dato*>*>::iterator itSubSubListas;
                for(;itListaSubArboles!=listaMaestraDatosSubArboles->end();itListaSubArboles++){
                        list<offset>* listaReferenciasNodosHoja = new list<offset>();
                        /*para cada SubSubArb de la lista de SubArb*/
                        itSubSubListas= (*itListaSubArboles)->begin();

                        for(;itSubSubListas!=(*itListaSubArboles)->end();itSubSubListas++){
                                listaDatosAuxiliar = (*itSubSubListas);
                                /*inserto el SubSubArbol de datos en un nodoHoja*/
                                nroNodoHoja = this->insertarDatosEnNodoHoja(listaDatosAuxiliar, porcentajeDeEmpaquetamiento);//TO DO
                                /*inserto la ref al nodo hoja en una nueva lista*/
                                listaReferenciasNodosHoja->push_back(nroNodoHoja);
                        }

                        nroNodoInterno = this->insertarDatosEnNodoInterno(listaMaestraClaves, listaReferenciasNodosHoja, i, dimension);

                        /*meto el nodo interno en una lista de resultados, con las refs de los nodos internos*/
                        listaNodosInternos->push_back(nroNodoInterno);
                        i++;
                }
                /*luego de este cilco la altura del siguiente es 2*/
                (*alturaVuelta)++;
                /*libero memoria*/
                delete listaMaestraNiveles;
                delete listaMaestraClaves;
                delete listaMaestraDatosSubArboles;
                /*retorno la lista de refs de nodos internos*/
                return listaNodosInternos;
        }
        if(nivelMayor == 1){
                //RAJEMOS VIEJO
                //KATRINA DE CHANES
        }

        list<int>::iterator itListaNiveles;
        itListaNiveles= listaMaestraNiveles->begin();
        int j=0;
        for(;itListaNiveles!=listaMaestraNiveles->end();itListaNiveles++){
                /*para cada nivel resultante comparo*/
                if((*itListaNiveles) < nivelMayor){
                        /*si nivel es menor que el mayor, voy a tener que reacomodar*/
                        /*agarro la subList de ese subArbol(sigo teniendo acceso a ella?)(ponela que la sigo teniendo de arriba) y consigo la clave del                         medio para(dimension+1)*/
                        /*mi lista de datos de subarboles, las tendria que juntar en una sola lista*/
                        list<list<Dato*>*>* listaDatosSubArbol = this->obtenerListasSegunPos(listaMaestraDatosSubArboles, j);
                        list<list<Dato*>*>* listasDatosSubArbolesNuevos = new list<list<Dato*>*>();//para que me devueve los nuevos subarboles
                        list<SubClaveRef*>* claveMediana = this->partirSubarbol(listaDatosSubArbol, dimension, listasDatosSubArbolesNuevos);

                        /*remplazo la nueva lista de listas de subarboles por la vieja*/
                        this->reemplazarDatoListaDatos(listaMaestraDatosSubArboles, listasDatosSubArbolesNuevos, j);
                        this->reemplazarDatoListaClaves(listaMaestraClaves, claveMediana, j);
                }
                /*sino*/
                        /*(las demas tenian 2 subarboles minimo)los traslado a mi nueva lista de sublistas(subarboles)*/
                        /*creo que en realidad no hago nada*/
                /**/
                j++;
        }
        /*para cada una de estas sublistas tendria que recomenzar*/
        /*Arme una lista de sublistas =0*/
        /*quizas en su momento podria recalcular el porcentajeDeEmpaquetamiento*/
        list<offset>* listaRefsNodosArmados = cargaInicialArmarNodos(listaMaestraDatosSubArboles, Key::getSiguienteDimension(dimension), porcentajeDeEmpaquetamiento, alturaVuelta);
        /*con los nodos recibidos, reconstruyo mis nodos de nivel superior*/
        /*para cada SubArb de la lista de SubArbs*/
        list<offset>* listaNodosInternos = this->insertarHijosEnNodoPadre(listaMaestraClaves, listaRefsNodosArmados, dimension, *alturaVuelta);

        /*aumento la altura*/
        (*alturaVuelta)++;

        delete listaMaestraNiveles;
        delete listaMaestraClaves;
        delete listaMaestraDatosSubArboles;
        /*retorno ahora las refs de estos nodos,(que ya referencian a los inferiores), para que se agreguen en el siguiente nivel*/
        return listaNodosInternos;
}

