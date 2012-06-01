#include "TestCargaInicial.h"
void TestCargaInicial::Testear(){
	Controlador* c = new Controlador();
	string path = DIR_ARCHIVO_DATOS;
	path += "a";
	path += ARCHIVO_DATOS;
	list<Key*>* lista = c->getListaKey(path);

	c->InsertarDatosCargaInicial(lista);

}
