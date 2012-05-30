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


Resultado Arbol::insertar(offset nroBloque, offset nroRegistro, Key* dato){
	Resultado res;
	if (!raiz) {//lazy initialization
		//Es el primerElemento
            this->crearRaiz();
            res = this->raiz->insertarElemento(nroRegistro, nroBloque , dato, 1);
                if(res == RES_OK){
                    this->cantidadElem+=1;
                    this->actualizarNodo(this->raiz);
                    }else{cout << "Grave error."<< endl;}
	} else {
                    if(!this->raiz->tieneArbol())this->raiz->setArbol(this);
		//debo insertar recursivamente
		res = raiz->insertarElemento(nroRegistro, nroBloque, dato, 1);
		if(res == RES_OK){
			this->cantidadElem  ++;
			this->actualizarNodo(this->raiz);
			}
		if(res == RES_DESBORDADO && (this->raiz->getHojaOInterno()=='H')){
            //se desborda y solo habia 1 nodo hoja
		    NodoHoja* Nder = (NodoHoja*) this->crearNuevoNodo(0,' ');
		    NodoHoja* raizvieja = (NodoHoja*) this->raiz;
            Key* k=NULL;
		    Nder = raizvieja->PartirEn2(k);//parti mi raiz hoja en 2
            NodoInterno<string>* RAIZNUEVA = (NodoInterno<string>*) this->crearNuevoNodo(1,'s');
            //consigo la subclave que va a subir
		    string subclaveRaizNueva = *((string*)k->getSubClaveSegunDim(Key::getDimensionSegunAltura(1)));
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

NodoHoja* Arbol::crearRaiz() {
	NodoHoja* nuevaRaiz = new NodoHoja(this);
	this->persistir->guardarRaiz(nuevaRaiz);
    this->raiz=nuevaRaiz;
	return nuevaRaiz;
	}

Nodo* Arbol::crearNuevoNodo(int nivel,char tipo ) {
	Nodo* nuevoNodo = NULL;
	if (nivel == 0) {
		nuevoNodo = new NodoHoja(this);
	} else {//aca puedo poner la inteligencia para setear la dimension
            if (tipo == 'i'){
                nuevoNodo = new NodoInterno<int>(this);
                ((NodoInterno<int>*) nuevoNodo)->setAltura(nivel);
                }
            if (tipo == 's'){
                nuevoNodo = new NodoInterno<string>(this);
                ((NodoInterno<string>*) nuevoNodo)->setAltura(nivel);
                }
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

/*funcion de arranque para la carga inicial. Aca seteo los datos iniciales para arrancar con la recursividad*/
void Arbol::cargaInicial(list<Dato*>* listaDeDatos){
    /*seteo la dimension con la que comienzo a ordenar(sin ninguna razon en particular elijo una sobre las otras)*/
	int dimension = 1;
	/*creo la raiz vacia, dps la voy a modificar*/
	if(Key::EsIntEstaDimension(dimension)){
        NodoInterno<int>* raiz = new NodoInterno<int>();
	}
	else{
	    NodoInterno<string>* raiz = new NodoInterno<string>();
	}
	offset nroNodo = this->persistir->agregarRaiz(raiz);
	/*creo una sublista donde solo voy a tener la lista con los datos iniciales*/
	list<list<Dato*>*>* subListasDatos = new list<list<Dato*>*>();
	subListasDatos->push_back(listaDeDatos);
	list<list<list<Dato*>*>*>* listaDeSubListasDatos = new list<list<list<Dato*>*>*>();
	listaDeSubListasDatos->push_back(subListasDatos);
	/*elijo un porcentaje de empaquetamineto inicial del 75%*/
	double porcentajeDeEmpaquetamiento = 0.75;
	/*funcion recursiva*/
	list<offset>* listaRefs = cargaInicialArmarNodos(listaDeSubListasDatos, dimension, porcentajeDeEmpaquetamiento);
	/*me tiene que devolver una sola referencia*/
	list<offset>::iterator itListaRefs;
	itListaRefs = listaRefs->begin();
	offset referencia;
	for(;itListaRefs!=listaRefs->end();itListaRefs++){
		referencia = (*itListaRefs);
	}
	/*levanto el nodo del archivo*/
	if(Key::EsIntEstaDimension(dimension)){
        nodoInterno<int>* raiz = leerNodo(referencia);
	}
	else{
        nodoInterno<string>* raiz = leerNodo(referencia);
	}
	/*le seteo el idRaiz y lo persisto*/
	this->persistir->guardarRaiz(raiz);
	/*modifico el nro nodo de referencia y lo pongo vacio*/
	nodoHoja* nodoVacio = new nodoHoja();
	setIdDelNodo(referencia);
	ActualizarNodo(nodoVacio);
}
/*desde aca, la recu me va a devolver una lista con un solo nodo, que va a ser el raiz*/

/*devuelvo list de punteros de nodos del nivel anterior, y referencio los nuevos nodos con eso*/
/*en el ultimo la list tiene un solo elemento que debiese ser el puntero de la raiz, esto lo meto en el arbol, pero igual lo manejo en la func no recursiva*/


list<Dato*>* obtenerListaOrdenadaPorDimension(list<Dato*>* lista, int dimension){
	list<Dato*>* listaOrdenadaDatosSubArboles = new list<Dato*>();
	bool swapped;
	do{
	     swapped = false;
	     int i;
	     for (i = 1; i <= lista->size() - 1; i++) {
	    	 if((Key->EsIntEstaDimension(dimension) && (*(int*)this->getElemento(lista, i-1)->getClave()->getSubClaveSegunDim(dimension)) >
				 (*(int*)this->getElemento(lista, i-1)->getClave()->getSubClaveSegunDim(dimension))) || (!(Key->EsIntEstaDimension(dimension)) &&
				 (*(string*)this->getElemento(lista, i-1)->getClave()->getSubClaveSegunDim(dimension)) >
				 (*(string*)this->getElemento(lista, i-1)->getClave()->getSubClaveSegunDim(dimension))))
	    	 {
	    		 Dato* aux = this->getElemento(lista, i-1);
	    		 Dato* elem = this->getElemento(lista, i);
	    		 this->setElemento(lista, i - 1,elem);
	    		 this->setElemento(lista, i,aux);
	    		 swapped = true;
	    	 }
	     }
	}
	while (swapped);
	return listaOrdenadaDatosSubArboles;
}

Dato* getElemento (list<Dato*>* lista, int index){
	list<Dato*>::iterator it;
	it=lista->begin();

	int i = 0;
	for(;it!=lista->end();it++){
		if(i == index)
			return *it;
		i++;
	}
	return Null;
}

void setElemento (list<Dato*>* lista, int index, Dato* dato){
	list<Dato*>::iterator it;
	it=lista->begin();

	int i = 0;
	for(;it!=lista->end();it++){
		if(i == index){
			list->insert(it, dato);
			return;
		}
		i++;
	}
	return Null;
}

int cargaInicialConseguirParticionConNivel(list<Dato*>* subListaOrdenada, list<SubClaveRef<int>*>* listaClaves, list<list<Dato*>*>* listaListasDatosSubArboles, int  porcentajeDeEmpaquetamiento){
	/*si la subListaOrdenada tiene un solo elemento, devuelvo en la sublista, ese elemento y uno vacio. y en la de clave tomo la clave del unico elemento
	(total, ante igualdad hay que ir para las 2 ramas)*/

	//TO DO
	/*ACA PARTE DE CODEO COMPLICADO. aca dps voy a tener que hacer el codigo groso*/
	return 2;
}

/*SOBRECARGA del metodo de arriba*/
int cargaInicialConseguirParticionConNivel(list<Dato*>* subListaOrdenada, list<SubClaveRef<string>*>* listaClaves, list<list<Dato*>*>* listaListasDatosSubArboles, int  porcentajeDeEmpaquetamiento){
	/*si la subListaOrdenada tiene un solo elemento, devuelvo en la sublista, ese elemento y uno vacio. y en la de clave tomo la clave del unico elemento
	(total, ante igualdad hay que ir para las 2 ramas)*/

	//TO DO
	/*ACA PARTE DE CODEO COMPLICADO. aca dps voy a tener que hacer el codigo groso*/
	return 2;
}

int conseguirNivelMayor(list<int>* listaMaestraNiveles){
	//TO DO
	return 2;
}

/*obtengo la lista de subClaves de la pos j de la lista de listas de claves*/
void* obtenerClavesSegunPos(list<list<SubClaveRef<int>*>*>* listaMaestraClaves, int j, int dimension){
	int i = 0;
	if(Key::EsIntEstaDimension(dimension)){
		list<SubClaveRef<int>*>* listaClavesSubarboles;
	}
	else{
		list<SubClaveRef<string>*>* listaClavesSubarboles;
	}
	list<int>::iterator itListaClaves;
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

/*SOBRECARGO el metodo de arriba*/
void* obtenerClavesSegunPos(list<list<SubClaveRef<string>*>*>* listaMaestraClaves, int j, int dimension){
	int i = 0;
	if(Key::EsIntEstaDimension(dimension)){
		list<SubClaveRef<int>*>* listaClavesSubarboles;
	}
	else{
		list<SubClaveRef<string>*>* listaClavesSubarboles;
	}
	list<int>::iterator itListaClaves;
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
list<list<Dato*>*>* obtenerListasSegunPos(list<list<list<Dato*>*>*>* listaMaestraDatosSubArboles, int j){
	int i = 0;
	list<list<Dato*>*>* listaDatosSubarboles;
	list<int>::iterator itListaClaves;
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
offset obtenerReferenciaNodosSegunPos(list<offset>* listaReferenciasNodosHios, int j){
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
void* partirSubarbol(list<list*>* listaDatosSubArbol, int dimension, list<list*>* listasDatosSubArbolesNuevos){
	//TO DO
	/*de mi lista de listas de datos vieja las voy metiendo en una sola lista de datos, agregando en orden al final*/

	/*busco la clave del medio de mi lista de datos*/
	/*guardo en listasDatosSubArbolesNuevos mis dos subarboles y la clave la meto en una lista y la devuelvo*/
	if(Key::EsIntEstaDimension(dimension)){
		list<SubClaveRef<int>*>* listaClavesSubarboles;
	}
	else{
		list<SubClaveRef<string>*>* listaClavesSubarboles
	}
	return listaClavesSubarboles;
}

/*reemplazo la lista de lista de datos en la lista maestra de listas de listas de datos(en la pos j)*/
void reemplazarDatoListaDatos(list<list*>* listaMaestraDatosSubArboles, list<list*>* listasDatosSubArbolesNuevos, int j){
	int i = 0;
	list<list*>* listaMaestraDatosSubarbolesNueva;
	list<int>::iterator itListaClaves;
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

/*reemplazo la lista de claves en la lista maestra de listas de claves(en la pos j)*/
void reemplazarDatoListaClaves(list<list*>* listaMaestraClaves, list<SubClaveRef<int>*>* claveMediana, j){
	int i = 0;
	/*si esta lista la malloqueo, tendria que deletear la vieja al final, antes de asignarle la nueva referencia*/
	list<list*>* listaMaestraClavesNueva;
	list<int>::iterator itListaClaves;
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

/*SOBRECARGO el metodo de arriba*/
void reemplazarDatoListaClaves(list<list*>* listaMaestraClaves, list<SubClaveRef<string>*>* claveMediana, j){
	int i = 0;
	/*si esta lista la malloqueo, tendria que deletear la vieja al final, antes de asignarle la nueva referencia*/
	list<list*>* listaMaestraClavesNueva;
	list<int>::iterator itListaClaves;
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
offset insertarDatosEnNodoHoja(list<Dato*>* listaSubSubArboles, double porcentaje)){
	/*instancio un nodoHoja*/
	NodoHoja* nodoHoja = new NodoHoja();

	list<Dato*>::iterator itSubListaDatos;
	itSubListaDatos= listaSubSubArboles->begin();

	for(;itSubListaDatos!=listaSubSubArboles->end();itSubListaDatos++){
		/*obtengo de mi dato los 3 datos que necesito para insertar en el nodo*/
		offset idRegistro = (*itSubListaDatos)->getIdRegistro();
		offset nroBloque = (*itSubListaDatos)->getNroBoque();
		Key clave = (*itSubListaDatos)->getClave();
		if(idRegistro == -1){
			/*el nodo queda vacio*/
			/*si esto pasa este tuviese que ser el unico dato*/
		}
		else{
			/*para cada elemento de la lista voy insertandolo en mi nodo hoja*/
			Resultado res = nodoHoja->insertarElemento(idRegistro, nroBloque, &clave, porcentaje)
			/*por como lo arme, no hay chance de que tire overflow. Y verifique antes que no se repitiesen los datos*/
			if(res = RES_OK){
				this->CantElem++;
			}
		}
	}
	/*llamo a persistencia para que guarde el nodo*/
	offset nroNodo = this->persistir->agregarNodo(nodoHoja);
	/*me devuelve el nro de nodo, yo retorno ese numero de nodo*/
	return nroNodo;
}

/*creo un nodo interno y meto todos las refs de la lista pasada. Luego lo persisto y retorno el nro de nodo*/
offset insertarDatosEnNodoInterno(list<list*>* listaMaestraClaves, list<offset>* listaReferenciasNodosHios, int i, int dimension){
	/*para la clave de la posicion it de la lista de listas de claves*/
	if(Key::EsIntEstaDimension(dimension)){
		list<SubClaveRef<int>*>* listaClaves = (list<SubClaveRef<int>*>*)this->obtenerClavesSegunPos(listaMaestraClaves, i, dimension);
	}
	else{
		list<SubClaveRef<string>*>* listaClaves = (list<SubClaveRef<string>*>*)this->obtenerClavesSegunPos(listaMaestraClaves, i, dimension);
	}
	list<int>::iterator itListaClaves;
	itListaClaves= listaClaves->begin();
	/*construyo mi NodoI*/
	if(Key::EsIntEstaDimension(dimension)){
        NodoInterno<int>* nodoInterno = new NodoInterno<int>();
	}
	else{
	    NodoInterno<string>* nodoInterno = new NodoInterno<string>();
	}
	int k = 0;
	offset primerReferencia = this->obtenerReferenciaNodosSegunPos(listaReferenciasNodosHios, k);
	for(;itListaClaves!=listaClaves->end();itListaClaves++){
		k++;
		/*recupero la subClaveRef*/
		if(Key::EsIntEstaDimension(dimension)){
			SubClaveRef<int>* subClave = (*itListaClaves);
		}
		else{
			SubClaveRef<string>* subClave = (*itListaClaves);
		}
		/*asigno una referencia*/
		offset referenciaSiguiente = this->obtenerReferenciaNodosSegunPos(listaReferenciasNodosHios, k);
		if(k==1){
			/*la primera vez tengo que agregar tambien la primer referencia*/
			Inicializar(primerReferencia, subClave->getSubClave(), referenciaSiguiente);
		}
		else{
			/*despues solo agrego conjuntos de clave - referencia*/
			InsertarNuevaSubClaveRef(subClave->getSubClave(), referenciaSiguiente);
		}
	}
	/*persisto el nodo*/
	offset nroNodo = this->persistir->agregarNodo(nodoInterno);
	/*me devuelve el nro de nodo, yo retorno ese numero de nodo*/
	return nroNodo;
}

/*voy creando nodos internos por cada lisa de claves y meto las refs necesarias segun la cant de claves. Los persisto y retorno una lista de nros de nodos*/
list<offset>* insertarHijosEnNodoPadre(list<list*>* listaMaestraClaves, list<offset>* listaRefsNodosArmados, int dimension){
	/*construyo mis NodoI*/
	int d = 0;
	list<offset>* listaRefsNodosInternos;

	list<int>::iterator itListaMaestraClaves;
	itListaMaestraClaves= listaMaestraClaves->begin();
	int k = 0;
	/*construyo un nodo por cada lista de listas de claves*/
	for(;itListaMaestraClaves!=listaMaestraClaves->end();itListaMaestraClaves++){
		/*instancio un nodo interno por cada lista de claves*/
		/*voy a iterar sobre mis listas de claves para ir armando el nodo interno*/
		if(Key::EsIntEstaDimension(dimension)){
		    NodoInterno<int>* nodoInterno = new NodoInterno<int>();
			list<SubClaveRef<int>*>::iterator itListaClaves;
		}
		else{
		    NodoInterno<string>* nodoInterno = new NodoInterno<string>();
			list<SubClaveRef<string>*>::iterator itListaClaves;
		}
		itListaClaves = (*itListaMaestraClaves)->begin();
		/*consigo la primer referencia*/
		offset primerReferencia = this->obtenerReferenciaNodosSegunPos(listaReferenciasNodosHios, k);
		/*meto tantas refs como necesite junto con la clave(1 + qe la cant de claves)*/
		for(;itListaClaves!=(*itListaMaestraClaves)->end();itListaClaves++){
			k++;
			/*recupero la subClaveRef*/
			if(Key::EsIntEstaDimension(dimension)){
				SubClaveRef<int>* subClave = (*itListaClaves);
			}
			else{
				SubClaveRef<string>* subClave = (*itListaClaves);
			}
			/*asigno una referencia*/
			offset referenciaSiguiente = this->obtenerReferenciaNodosSegunPos(listaReferenciasNodosHios, k);
			if(k==1){
				/*la primera vez tengo que agregar tambien la primer referencia*/
				Inicializar(primerReferencia, subClave->getSubClave(), referenciaSiguiente);
			}
			else{
				/*despues solo agrego conjuntos de clave - referencia*/
				InsertarNuevaSubClaveRef(subClave->getSubClave(), referenciaSiguiente);
			}
		}
		k++;
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
list<offset>* cargaInicialArmarNodos(list<list*>* subListasDatos, int dimension, double porcentajeDeEmpaquetamiento){
	/*Creo 3 listas que voy a ir usando a lo largo de la funcion*/
	list<int>* listaMaestraNiveles = new list<int>();
	list<list*>* listaMaestraClaves = new list<list*>();
	list<list*>* listaMaestraDatosSubArboles = new list<list*>();

	/*para cada una de mis sublistas:*/
	list<list*>::iterator itSubListas;
	itSubListas= subListasDatos->begin();

	for(;itSubListas!=subListasDatos->end();itSubListas++){
		list<list*>::iterator itSubSubListas;
		itSubSubListas= (*subListasDatos)->begin();

		for(;itSubSubListas!=(*subListasDatos)->end();itSubSubListas++){
			/*ordeno datos por mi dimension*/
			list<Dato*>* subListaOrdenada = this->obtenerListaOrdenadaPorDimension(&(*itSubSubListas),dimension);//TO DO
			/*una vez que tengo mi lista ordenada, comienzo con la insercion en nodos como si fuese una carga inicial comun(mmm, mas bien una 				simulacion)*/
			/*instancio dos listas vacias para que me devuelva resultados el metodo que simula la carga inicial del subarbol*/
			if(Key::EsIntEstaDimension(dimension)){
				list<SubClaveRef<int>*>* listaClaves;//lista de claves
			}
			else{
				list<SubClaveRef<string>*>* listaClaves;//lista de claves
			}
			list<list*>* listaListasDatosSubArboles;//lista de listas de datos
			int nivel = cargaInicialConseguirParticionConNivel(subListaOrdenada, listaClaves, listaListasDatosSubArboles, 					porcentajeDeEmpaquetamiento); //TO DO
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
		list<offset>* listaNodosInternos;
		/*agarro los nodos de algun lado y armo mi arbol resultante*/
		list<list*>::iterator itListaSubArboles;
		itListaSubArboles= listaMaestraDatosSubArboles->begin();
		/*para cada SubArb de la lista de SubArbs*/
		int i = 0;
		for(;itListaSubArboles!=listaMaestraDatosSubArboles->end();itListaSubArboles++){
			list<offset>* listaReferenciasNodosHoja;
			/*para cada SubSubArb de la lista de SubArb*/
			list<list*>::iterator itSubSubListas;
			itSubSubListas= (*itListaSubArboles).begin();

			for(;itSubSubListas!=(*itListaSubArboles).end();itSubSubListas++){
				/*inserto el SubSubArbol de datos en un nodoHoja*/
				offset nroNodoHoja = this->insertarDatosEnNodoHoja(&(*itSubSubListas), porcentajeDeEmpaquetamiento);//TO DO
				/*inserto la ref al nodo hoja en una nueva lista*/
				listaReferenciasNodosHoja->push_back(nroNodoHoja);
			}

			offset nroNodoInterno = this->insertarDatosEnNodoInterno(listaMaestraClaves, listaReferenciasNodosHoja, i, dimension);

			/*meto el nodo interno en una lista de resultados, con las refs de los nodos internos*/
			listaNodosInternos->push_back(nroNodoInterno);
			i++;
		}
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
		if((*listaMaestraNiveles) < nivelMayor){
			/*si nivel es menor que el mayor, voy a tener que reacomodar*/
			/*agarro la subList de ese subArbol(sigo teniendo acceso a ella?)(ponela que la sigo teniendo de arriba) y consigo la clave del 			medio para(dimension+1)*/
			/*mi lista de datos de subarboles, las tendria que juntar en una sola lista*/
			list<list*>* listaDatosSubArbol = this->obtenerListasSegunPos(listaMaestraDatosSubArboles, j);
			list<list*>* listasDatosSubArbolesNuevos;//para que me devueve los nuevos subarboles
			if(Key::EsIntEstaDimension(dimension)){
				list<SubClaveRef<int>*>* claveMediana = (list<SubClaveRef<int>*>*)this->partirSubarbol(listaDatosSubArbol, dimension, 										listasDatosSubArbolesNuevos);
			}
			else{
				list<SubClaveRef<string>*>* claveMediana = (list<SubClaveRef<string>*>*)this->partirSubarbol(listaDatosSubArbol, dimension, 										listasDatosSubArbolesNuevos);
			}
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
	list<offset>* listaRefsNodosArmados = cargaInicialArmarNodos(listaMaestraDatosSubArboles, Key::getSiguienteDimension(dimension), 				porcentajeDeEmpaquetamiento);

	/*con los nodos recibidos, reconstruyo mis nodos de nivel superior*/
	/*para cada SubArb de la lista de SubArbs*/
	list<offset>* listaNodosInternos = this->insertarHijosEnNodoPadre(listaMaestraClaves, listaRefsNodosArmados, dimension);

	delete listaMaestraNiveles;
	delete listaMaestraClaves;
	delete listaMaestraDatosSubArboles;
	/*retorno ahora las refs de estos nodos,(que ya referencian a los inferiores), para que se agreguen en el siguiente nivel*/
	return listaNodosInternos;
}
