
//**mi funcion, de movida, tiene que recibir una lista con los datos a insertar**//
/*desde esta llamaria a la recursiva, ponele*/
/*desde aca, la recu me va a devolver una lista con un solo nodo, que va a ser el raiz*/

/*devuelvo list de punteros de nodos del nivel anterior, y referencio los nuevos nodos con eso*/
/*en el ultimo la list tiene un solo elemento que debiese ser el puntero de la raiz, esto lo meto en el arbol, pero igual lo manejo en la func no recursiva*/

/*TOMAR POSIBLES ACCIONES ANTE EL CASO QUE UN SUBARBOL SOLO TENGA UN DATO (la clave que tendria??)*/
/*VER COMO VOY HACIENDO SUBSISTIR LOS NODOS A LO LARGO DE LA RECURSIVIDAD*/
/*una opcion, devolver los nodos de abajo para arriba a medida que fui terminando, y usar algun flag que me indique cuando llego al nivel de la raiz(la veo muy viable)(repensarlo maniana)*/

//**la recursiva recibe (list* subListasDatos, int dimension, int porcentajeDeEmpaquetamiento)**//
list* cargaInicialArmarNodos(list* subListasDatos, int dimension, int porcentajeDeEmpaquetamiento){
	/*para cada una de mis sublistas:*/
	list<int>::iterator itSubListas;
	itSubListas= subListasDatos->begin();

	for(;itSubListas!=subListasDatos->end();itSubListas++){
		/*ordeno datos por mi dimension*/
		list* subListaOrdenada = this->obtenerListaOrdenadaPorDimension(&(*itSubListas),dimension);//TO DO
		/*una vez que tengo mi lista ordenada, comienzo con la insercion en nodos como si fuese una carga inicial comun(mmm, mas bien una simulacion)*/
		/*instancio dos listas vacias para que me devuelva resultados*/
		list listaClaves, listasDatosSubArboles;		
		int nivel = cargaInicialConseguirParticionConNivel(subListaOrdenada, &listaClaves, &listasDatosSubArboles);//TO DO
		/*ACA PARTE DE CODEO COMPLICADO. aca dps voy a tener que hacer el codigo groso*/
		/*recupero el nivel del arbol, las claves del nodo raiz y una lista de subarboles*/
	
		/*estos datos los tengo que guardar en algun lado o los voy a perder en la siguiente iteracion(ponele que los voy metiendo en 3 listas)*/
	
		/*guardo en un nodo temporal el "nodo" superior(es necesario decirle nivel?)(ver como hacer para lograr esto, nose si se puede asi nomas)(las 			refes a los hijos, que todavia no cree?)*//*esto nodo vendria a ser hijo del del paso anterior*/
	
	/*ListalistaClaves.size() == subListasDatos.size()// n=(listaClaves.size()+1) listasDAtos por iteracion// un nivel por iteracion*/
	/**/
	}
	/*una vez que sali del primer ciclo compararia los niveles de los distintos subarboles(sublistas)*/
	/*obtengo el mayor nivel*/	
	int nivelMayor = this->conseguirNivelMayor(listaNiveles); //TO DO	
		
	/*si el mayor nivel era 2, ya podria recuperar el nodo hoja entero, auque esto lo puedo verificar mas abajo*/
	if(nivelMayor == 2){
		/*agarro los nodos de algun lado y armo mi arbol resultante*/		
		list<int>::iterator itListaSubArboles;
		itListaSubArboles= listaSubArboles->begin();
		/*para cada SubArb de la lista de SubArbs*/
		int i = 0;		
		for(;itListaSubArboles!=listaSubArboles->end();itListaSubArboles++){		
			(*itListaSubArboles)
			/*para cada SubSubArb de la lista de SubArb*/
			for(;itListaSubSubArboles!=itListaSubArboles->end();itListaSubSubArboles++){	
				/*inserto el SubSubArbol en un nodoHoja*/
				NodoHoja* nodoHoja = this->insertarDatosEnNodoHoja(&(*itListaSubSubArboles));//TO DO
				/*inserto la ref al nodo hoja en una nueva lista*/
			}
			
			/*para la clave de la posicion it de la lista de listas de claves*/
			List* listaClaves = this->obtenerClavesSegunPos(listaClaves, i);

			list<int>::iterator itListaClaves;
			itListaClaves= listaClaves->begin();
			/*construyo mi NodoI*/			
			for(;itListaClaves!=listaClaves->end();itListaClaves++){
				/*asigno una referencia*/
				/*asigno una clave*/			
			}
			/*asigno ultima referencia, si es que hay, sino, ref null o algo para identificar (vacio)*/
			
			/*meto el nodo interno en una lista de resultados, con las refs de los nodos internos*/
			i++;
		}
		/*retorno la lista de refs de nodos internos*/
	/*y aca si ya podria hacer un return del arbol que corte con la recursividad*/
	/**/
	}
	if(nivelMayor == 1){
		//RAJEMOS VIEJO
		//KATRINA DE CHANES
	}

	list<int>::iterator itListaNiveles;
	itListaNiveles= listaNiveles->begin();
	int j=0;
	for(;itListaNiveles!=listaNiveles->end();itListaNiveles++){
		/*para cada nivel resultante comparo*/
		if((*itListaNiveles) < nivelMayor){
			/*si nivel es menor que el mayor, voy a tener que reacomodar*/
			/*agarro la subList de ese subArbol(sigo teniendo acceso a ella?)(ponela que la sigo teniendo de arriba) y consigo la clave del 			medio para(dimension+1)*/
			List* listaListasSubArboles = this->obtenerListasSegunPos(listaSubArboles, j);
			list listasDatosSubArboles;//para que me devueve los nuevos subarboles
			list*<Clave> claveMediana = this->partirSubarbol(listaListasSubArboles, dimension, &listasDatosSubArboles);
			/*remplazo la nueva lista de listas de subarboles por la vieja*/
			this->reemplazarDatoLista(listaSubArboles, &listasDatosSubArboles);
			this->reemplazarDatoLista(listaClaves, claveMediana);						
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
	list*<Nodo*> listaRefsNodosArmados = cargaInicialArmarNodos(listaSubArboles, Clave::getSiguienteDimmension(dimension), porcentajeDeEmpaquetamiento)

	/*con los nodos recibidos, reconstruyo mis nodos de nivel superior*/
	list<int>::iterator itListaRefNodosHijos;
	itListaRefNodosHijos= listaRefsNodosArmados->begin();
	/*para cada SubArb de la lista de SubArbs*/
	int i = 0;		
	/*podria iterar sobre la lista de claves y las ref las consigo por pos*/
	for(;itListaRefNodosHijos!=listaRefsNodosArmados->end();itListaRefNodosHijos++){		
		/*asigno una referencia (*itListaRefNodosHijos)*/
		//cuando llego a la ultima ref no agrego claves(ver como verifico esto)			
		/*asigno una clave (la consigo de mi listaClaves)*/			
	}
	/*retorno ahora las refs de estos nodos,(que ya referencian a los inferiores), para que se agreguen en el siguiente nivel*/
}

 list<int>* listIdRegistros = new list<int>();




/*agarro los nodos de algun lado y armo mi arbol resultante*/		
		
		
