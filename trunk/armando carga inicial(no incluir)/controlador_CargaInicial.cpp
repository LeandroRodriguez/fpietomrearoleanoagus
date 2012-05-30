//Agregar a controlador.cpp para manejar la carga incial

/*Inserto el dato pasado por parametro tanto en el archivo de data, como sus referencias en el arbol*/
void Controlador::InsertarDatosCargaInicial(list<Key>* listaDatos){
	/*creo un objeto que se encargara de almacenar el dato en el archivo correspondiente*/
	AlmacenamientoBloque almacena(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
	/*creo una lista de DATOs que le voy a pasar a la carga incial*/
	list<Dato*>* listaDatosCargaInicial = new list<Dato*>*();
	/*voy a iterar sobre mi lista de datos para ir insertandolas en el archivo. Y tmb armar el DATO que le voy a pasar ala carga inicial (nroBloq,idReg,clave)*/
	list<int>::iterator itListaDatos;
	itListaDatos= listaDatos->begin();	
	for(;itListaDatos!=listaDatos->end();itListaDatos++){
		/*booleano para controlar repeticiones*/
		bool estaRepetido = false;
		/*si el dato no es null, lo guardo*/
		Key* dato = (*itListaDatos);
		if (dato) {

			/*checkeo si ya existe el dato en mi listas de Datos para evitar guardarlo y pasarselo al arbol*/
			list<int>::iterator itListaDatosCargaInicial;
			itListaDatosCargaInicial= listaDatosCargaInicial->begin();	
			for(;itListaDatosCargaInicial!=listaDatosCargaInicial->end();itListaDatosCargaInicial++){	
				if(dato->esIgual(*itListaDatosCargaInicial)){
					estaRepetido = true;
					break;
				}
			}		
			if(!estaRepetido){
				/*obtengo los bytes del dato serializado*/
				string str(dato->Serializarse());
				Bytes bytes(str);

				/*creo un registro donde guardo los bytes del dato, y lo guardo en el archivo de data*/
				RegistroVariable registro(bytes);
				almacena.agregarRegistro(&registro);
				/*armo el DATO y lo meto en mi lista*/	
				Dato* datoCargaInicial = new Dato();			
				dato->setIdRegistro(almacena.getNumeroUID());
				dato->setNroBoque(almacena.getNumeroBloque());
				dato->setClave(dato);			
				listaDatosCargaInicial->push_back(dato);
			}	
		}
	}
	/*llamo al indice, que a su vez mediara con el arbol, para ejecutar la carga inicial*/
	indicePrimario->agregarDatosCargaInicial(listaDatosCargaInicial);//AGREGAR ESTA FUNCION MEDIADORA A INDICE
}
