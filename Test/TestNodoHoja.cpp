#include "TestNodoHoja.h"

TestNodoHoja::TestNodoHoja(){}

void TestNodoHoja::TestCrearNodoHoja(){
    Key* dato1 = new Key();
	dato1->setLineaFerroviaria("Sarmiento");
	dato1->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
	dato1->setFalla("no cierra puerta");
	dato1->setAccidente("incendio");
	dato1->setFormacion(1);

	Key* dato2 = new Key();
	dato2->setLineaFerroviaria("Mitre");
	dato2->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
	dato2->setFalla("no frena");
	dato2->setAccidente("choque");
	dato2->setFormacion(1);

	NodoHoja* nodo = new NodoHoja();
	AlmacenamientoBloque almacena(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    string str1(dato1->Serializarse());
    string str2(dato2->Serializarse());
	Bytes bytes1(str1);
	Bytes bytes2(str2);
	RegistroVariable registro1(bytes1);
	RegistroVariable registro2(bytes2);

	almacena.agregarRegistro(&registro1);
	offset nBloque1 = almacena.getNumeroBloque();
	offset nReg1 = almacena.getNumeroUID();
	nodo->insertarElemento(nReg1, nBloque1, dato1, 1);

	almacena.agregarRegistro(&registro2);
	offset nBloque2 = almacena.getNumeroBloque();
	offset nReg2 = almacena.getNumeroUID();
	nodo->insertarElemento(nReg2, nBloque2, dato2, 1);

    nodo->imprimir();
    delete dato1;
    delete dato2;
    delete nodo;
}

void TestNodoHoja::TestSerializarHidtratar(){
    Key* dato = new Key();
	dato->setLineaFerroviaria("Sarmiento");
	dato->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
	dato->setFalla("no cierra puerta");
	dato->setAccidente("incendio");
	dato->setFormacion(1);

	AlmacenamientoBloque almacena(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    string str(dato->Serializarse());
	Bytes bytes(str);
	RegistroVariable registro(bytes);
	almacena.agregarRegistro(&registro);
	offset nBloque = almacena.getNumeroBloque();
	offset nReg = almacena.getNumeroUID();
	NodoHoja* nodo1 = new NodoHoja();
	nodo1->insertarElemento(nReg, nBloque, dato, 1);
	char* serializacion = nodo1->Serializarse();
	NodoHoja* nodo2 = new NodoHoja(serializacion);
    nodo2->imprimir();
    delete dato;
    delete nodo1;
    delete nodo2;
}

void TestNodoHoja::TestPartirHojaEn2(){
    Key* dato1 = new Key();
	dato1->setLineaFerroviaria("Sarmiento");
	dato1->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
	dato1->setFalla("no cierra puerta");
	dato1->setAccidente("incendio");
	dato1->setFormacion(1);

	Key* dato2 = new Key();
	dato2->setLineaFerroviaria("Mitre");
	dato2->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
	dato2->setFalla("no frena");
	dato2->setAccidente("choque");
	dato2->setFormacion(1);

	NodoHoja* nodo1 = new NodoHoja();
	AlmacenamientoBloque almacena(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    string str1(dato1->Serializarse());
    string str2(dato2->Serializarse());
	Bytes bytes1(str1);
	Bytes bytes2(str2);
	RegistroVariable registro1(bytes1);
	RegistroVariable registro2(bytes2);

	almacena.agregarRegistro(&registro1);
	offset nBloque1 = almacena.getNumeroBloque();
	offset nReg1 = almacena.getNumeroUID();
	nodo1->insertarElemento(nReg1, nBloque1, dato1, 1);

	almacena.agregarRegistro(&registro2);
	offset nBloque2 = almacena.getNumeroBloque();
	offset nReg2 = almacena.getNumeroUID();
	nodo1->insertarElemento(nReg2, nBloque2, dato2, 1);
	nodo1->imprimir();
	Nodo* nodo2 = nodo1->PartirEn2(dato2);
	nodo1->imprimir();
	nodo2->imprimir();
	delete dato1;
    delete dato2;
    delete nodo1;
}
