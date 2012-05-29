#include "TestArbol.h"
void TestArbol::Testear(){

		Controlador* c = new Controlador();

		Key* dato = new Key();
		dato->setLineaFerroviaria("Sarmiento");
		dato->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
		dato->setFalla("no cierra puerta");
		dato->setAccidente("incendio");
		dato->setFormacion(1);
		c->InsertarDato(dato);

		c->indicePrimario->imprimir();

		Key* dato2 = new Key();
		dato2->setLineaFerroviaria("Mitre");
		dato2->setFranjaHorariaDelSiniestro("2012/01/21 00:00 00:30");
		dato2->setFalla("asientos rotos");
		dato2->setAccidente("choco con estacion");
		dato2->setFormacion(2);
		c->InsertarDato(dato2);
		c->indicePrimario->imprimir();

		Key* dato3 = new Key();
		char linea3[] ="Roca";
		dato3->setLineaFerroviaria(linea3);
		char franja3[] = "2012/02/23 00:00 00:30";
		dato3->setFranjaHorariaDelSiniestro(franja3);
		char falla3[] = "no frena";
		dato3->setFalla(falla3);
		char acc3[] = "choco con otro tren";
		dato3->setAccidente(acc3);
		dato3->setFormacion(3);
		c->InsertarDato(dato3);
		c->indicePrimario->imprimir();

		Key* dato4 = new Key();
		char linea4[] ="San martin";
		dato4->setLineaFerroviaria(linea4);
		char franja4[] = "2012/02/25 00:00 00:30";
		dato4->setFranjaHorariaDelSiniestro(franja4);
		char falla4[] = "esta roto";
		dato4->setFalla(falla4);
		char acc4[] = "exploto";
		dato4->setAccidente(acc4);
		dato4->setFormacion(4);
		c->InsertarDato(dato4);
		c->indicePrimario->imprimir();

		Key* dato5 = new Key();
		char linea5[] ="Belgrano";
		dato5->setLineaFerroviaria(linea5);
		char franja5[] = "2011/02/21 00:00 00:30";
		dato5->setFranjaHorariaDelSiniestro(franja5);
		char falla5[] = "no arranca";
		dato5->setFalla(falla5);
		char acc5[] = "no prende";
		dato5->setAccidente(acc5);
		dato5->setFormacion(5);
		c->InsertarDato(dato5);
		c->indicePrimario->imprimir();

		Key* dato6 = new Key();
		char linea6[] ="Subte";
		dato6->setLineaFerroviaria(linea6);
		char franja6[] = "2012/02/18 00:00 00:30";
		dato6->setFranjaHorariaDelSiniestro(franja6);
		char falla6[] = "motor roto";
		dato6->setFalla(falla6);
		char acc6[] = "descarrilo";
		dato6->setAccidente(acc6);
		dato6->setFormacion(6);
		c->InsertarDato(dato6);
		c->indicePrimario->imprimir();



	}
