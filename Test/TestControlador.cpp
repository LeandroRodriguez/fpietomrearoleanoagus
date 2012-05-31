#include "TestControlador.h"

TestControlador::TestControlador(){}

void TestControlador::TestInsertarDato(){
    Controlador* controlador = new Controlador();
    Key* dato = new Key();
    dato->setLineaFerroviaria("Sarmiento");
	dato->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
	dato->setFalla("no cierra puerta");
	dato->setAccidente("incendio");
	dato->setFormacion("1");
	controlador->InsertarDato(dato);

	Key* dato2 = new Key();
	dato2->setLineaFerroviaria("Mitre");
	dato2->setFranjaHorariaDelSiniestro("2012/01/21 00:00 00:30");
	dato2->setFalla("asientos rotos");
	dato2->setAccidente("choco con estacion");
	dato2->setFormacion("2");
	controlador->InsertarDato(dato2);

	Key* dato3 = new Key();
	char linea3[] ="Roca";
	dato3->setLineaFerroviaria(linea3);
	char franja3[] = "2012/02/23 00:00 00:30";
	dato3->setFranjaHorariaDelSiniestro(franja3);
	char falla3[] = "no frena";
	dato3->setFalla(falla3);
	char acc3[] = "choco con otro tren";
	dato3->setAccidente(acc3);
	dato3->setFormacion("3");
	controlador->InsertarDato(dato3);

	Key* dato4 = new Key();
	char linea4[] ="San martin";
	dato4->setLineaFerroviaria(linea4);
	char franja4[] = "2012/02/25 00:00 00:30";
	dato4->setFranjaHorariaDelSiniestro(franja4);
	char falla4[] = "esta roto";
	dato4->setFalla(falla4);
	char acc4[] = "exploto";
	dato4->setAccidente(acc4);
	dato4->setFormacion("4");
	controlador->InsertarDato(dato4);
    /*
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
	controlador->InsertarDato(dato5);

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
	controlador->InsertarDato(dato6);

	Key* dato7 = new Key();
	dato7->setLineaFerroviaria("Junin");
	dato7->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
	dato7->setFalla("no cierra puerta");
	dato7->setAccidente("incendio");
	dato7->setFormacion(5);
	controlador->InsertarDato(dato7);

	Key* dato8 = new Key();
	dato8->setLineaFerroviaria("Ledesma");
	dato8->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
	dato8->setFalla("no tiene puerta");
	dato8->setAccidente("incendio");
	dato8->setFormacion(4);
	controlador->InsertarDato(dato8);

	Key* dato9 = new Key();
	dato9->setLineaFerroviaria("Rivadavia");
	dato9->setFranjaHorariaDelSiniestro("2012/02/29 00:00 00:30");
	dato9->setFalla("no cierra");
	dato9->setAccidente("quemado");
	dato9->setFormacion(4);
	controlador->InsertarDato(dato9);

	Key* dato10 = new Key();
	dato10->setLineaFerroviaria("TorCuato");
	dato10->setFranjaHorariaDelSiniestro("2012/02/29 00:00 00:00");
	dato10->setFalla("no cierra");
	dato10->setAccidente("roto");
	dato10->setFormacion(4);
	controlador->InsertarDato(dato10);

	Key* dato11 = new Key();
	dato11->setLineaFerroviaria("LaBoca");
	dato11->setFranjaHorariaDelSiniestro("2012/02/29 00:00 00:00");
	dato11->setFalla("no abre ventanas");
	dato11->setAccidente("descarrilamiento");
	dato11->setFormacion(6);
	controlador->InsertarDato(dato11);*/

    controlador->indice->imprimir();
	delete controlador;
	delete dato;
	delete dato2;
	delete dato3;
	delete dato4;
	/*delete dato5;
	delete dato6;
	delete dato7;
	delete dato8;
	delete dato9;
	delete dato10;
	delete dato11;*/

}
