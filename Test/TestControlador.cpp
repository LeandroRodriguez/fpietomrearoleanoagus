#include "TestControlador.h"

TestControlador::TestControlador(){}

void TestControlador::TestInsertarDato(){
    Key* dato = new Key();
    dato->setLineaFerroviaria("Sarmiento");
	dato->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
	dato->setFalla("no cierra puerta");
	dato->setAccidente("incendio");
	dato->setFormacion(1);
	Controlador* controlador = new Controlador();
    controlador->InsertarDato(dato);
}
