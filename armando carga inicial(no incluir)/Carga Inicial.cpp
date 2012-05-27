
//**mi funcion, de movida, tiene que recibir una lista con los datos a insertar**//
/*desde esta llamaria a la recursiva, ponele*/
/*desde aca, la recu me va a devolver una lista con un solo nodo, que va a ser el raiz*/

/*devuelvo list de punteros de nodos del nivel anterior, y referencio los nuevos nodos con eso*/
/*en el ultimo la list tiene un solo elemento que debiese ser el puntero de la raiz, esto lo meto en el arbol, pero igual lo manejo en la func no recursiva*/



NodoInterno* insertarDatosEnNodoInterno(list<list*>* listaMaestraClaves, list<int>* listaReferenciasNodosHios, int i){
	/*para la clave de la posicion it de la lista de listas de claves*/
	List* listaClaves = this->obtenerClavesSegunPos(listaMaestraClaves, i);

	list<int>::iterator itListaClaves;
	itListaClaves= listaClaves->begin();
	/*construyo mi NodoI*/			
	for(;itListaClaves!=listaClaves->end();itListaClaves++){
		/*asigno una referencia*/
		/*asigno una clave*/			
	}
	/*asigno ultima referencia, si es que hay, sino, ref null o algo para identificar (vacio)*/
	
}

list<NodoInterno*>* insertarHijosEnNodoPadre(list<list*>* listaMaestraClaves, list<NodoInterno*>* listaRefsNodosArmados){
	/*construyo mis NodoI*/
	int d = 0;
	list<NodoInterno*>* listaNodosInternos;
	for(int k = 0,k<listaMaestraClaves.size(),k){	
		List* listaClaves = this->obtenerClavesSegunPos(listaMaestraClaves, k);		
		list<int>::iterator itListaClaves;
		itListaClaves= listaClaves->begin();
		/*construyo un nodo*/		
		for(;itListaClaves!=listaClaves->end();itListaClaves++){					
			/*asigno una referencia(obtengo la ref de la pos d)*/
			/*asigno una clave*/			
			d++;
		}
		/*asigno una referencia al ultimo nodo(obtengo la ref de la pos d)*/		
		d++;		
		/*meto el nodo interno en una lista de resultados, con las refs de los nodos internos*/
		listaNodosInternos->push_back(nodoInterno);
				
	}
	return listaNodosInternos;
}


/*EN TODOS LOS LADOS DONDE METI PUNTEROS A NODOS, HAY QUE CAMBIARLO POR LOS IDS DE LOS NODOS*/
/*TOMAR POSIBLES ACCIONES ANTE EL CASO QUE UN SUBARBOL SOLO TENGA UN DATO (la clave que tendria??)*/
/*VER COMO VOY HACIENDO SUBSISTIR LOS NODOS A LO LARGO DE LA RECURSIVIDAD*/
/*una opcion, devolver los nodos de abajo para arriba a medida que fui terminando, y usar algun flag que me indique cuando llego al nivel de la raiz(la veo muy viable)(repensarlo maniana)*/

//**la recursiva recibe (list* subListasDatos, int dimension, int porcentajeDeEmpaquetamiento)**//
list<NodoInterno*>* cargaInicialArmarNodos(list<list*>* subListasDatos, int dimension, int porcentajeDeEmpaquetamiento){
	/*Creo 3 listas que voy a ir usando a lo largo de la funcion*/
	list<int>* listaMaestraNiveles = new list<int>();	
	list<list*>* listaMaestraClaves = new list<list*>();
	list<list*>* listaMaestraDatosSubArboles = new list<list*>();
	
	/*para cada una de mis sublistas:*/
	list<list*>::iterator itSubListas;
	itSubListas= subListasDatos->begin();

	for(;itSubListas!=subListasDatos->end();itSubListas++){
		/*ordeno datos por mi dimension*/
		list<list*>* subListaOrdenada = this->obtenerListaOrdenadaPorDimension(&(*itSubListas),dimension);//TO DO
		/*una vez que tengo mi lista ordenada, comienzo con la insercion en nodos como si fuese una carga inicial comun(mmm, mas bien una simulacion)*/
		/*instancio dos listas vacias para que me devuelva resultados el metodo que simula la carga inicial del subarbol*/
		list<Key>* listaClaves;//lista de claves
		list<list*>* listaListasDatosSubArboles;//lista de listas de datos		
		int nivel = cargaInicialConseguirParticionConNivel(subListaOrdenada, listaClaves, listaListasDatosSubArboles, porcentajeDeEmpaquetamiento);//TO DO
		/*ACA PARTE DE CODEO COMPLICADO. aca dps voy a tener que hacer el codigo groso*/
		/*recupero el nivel del arbol, las claves del nodo raiz y una lista de subarboles*/
	
		/*estos datos los tengo que guardar en algun lado o los voy a perder en la siguiente iteracion(ponele que los voy metiendo en 3 listas)*/
		listaMaestraNiveles->push_back(nivel);
		listaMaestraClaves->push_back(listaClaves);
		listaMaestraDatosSubArboles->push_back(listaListasDatosSubArboles);
	}
	/*una vez que sali del primer ciclo compararia los niveles de los distintos subarboles(sublistas)*/
	/*obtengo el mayor nivel*/	
	int nivelMayor = this->conseguirNivelMayor(listaMaestraNiveles); //TO DO	
		
	/*si el mayor nivel era 2, ya podria recuperar el nodo hoja entero, auque esto lo puedo verificar mas abajo*/
	if(nivelMayor == 2){
		list<NodoInterno*>* listaNodosInternos;
		/*agarro los nodos de algun lado y armo mi arbol resultante*/		
		list<list*>::iterator itListaSubArboles;
		itListaSubArboles= listaMaestraDatosSubArboles->begin();
		/*para cada SubArb de la lista de SubArbs*/
		int i = 0;		
		for(;itListaSubArboles!=listaMaestraDatosSubArboles->end();itListaSubArboles++){
			list<int>* listaReferenciasNodosHoja;		
			/*para cada SubSubArb de la lista de SubArb*/
			for(;itListaSubSubArboles!=itListaSubArboles->end();itListaSubSubArboles++){	
				/*inserto el SubSubArbol en un nodoHoja*/
				NodoHoja* nodoHoja = this->insertarDatosEnNodoHoja(&(*itListaSubSubArboles));//TO DO
				/*inserto la ref al nodo hoja en una nueva lista*/
				listaReferenciasNodosHoja->push_back(nodoHoja);
			}
			
			NodoInterno* nodoInterno = this->insertarDatosEnNodoInterno(listaMaestraClaves, listaReferenciasNodosHoja, i);			
			
			/*meto el nodo interno en una lista de resultados, con las refs de los nodos internos*/
			listaNodosInternos->push_back(nodoInterno);
			i++;
		}

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
			List<list*>* listaDatosSubArbol = this->obtenerListasSegunPos(listaMaestraDatosSubArboles, j);
			list<list*>* listasDatosSubArbolesNuevos;//para que me devueve los nuevos subarboles
			list<Key>* claveMediana = this->partirSubarbol(listaDatosSubArbol, dimension, listasDatosSubArbolesNuevos);
			/*remplazo la nueva lista de listas de subarboles por la vieja*/
			this->reemplazarDatoLista(listaMaestraDatosSubArboles, listasDatosSubArbolesNuevos, j);
			this->reemplazarDatoLista(listaMaestraClaves, claveMediana, j);						
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
	list<NodoInterno*>* listaRefsNodosArmados = cargaInicialArmarNodos(listaMaestraDatosSubArboles, Key::getSiguienteDimmension(dimension), 			porcentajeDeEmpaquetamiento);

	/*con los nodos recibidos, reconstruyo mis nodos de nivel superior*/
	/*para cada SubArb de la lista de SubArbs*/
	list<NodoInterno*>* listaNodosInternos = this->insertarHijosEnNodoPadre(listaMaestraClaves, listaRefsNodosArmados);
	
	delete listaMaestraNiveles;
	delete listaMaestraClaves;
	delete listaMaestraDatosSubArboles;
	/*retorno ahora las refs de estos nodos,(que ya referencian a los inferiores), para que se agreguen en el siguiente nivel*/
	return listaNodosInternos;
}




/*agarro los nodos de algun lado y armo mi arbol resultante*/		
		
		
