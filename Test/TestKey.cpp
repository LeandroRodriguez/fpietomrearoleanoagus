#include "TestKey.h"

TestKey::TestKey(){}

void TestKey::TestSerializarHidratarKey(){
    Key* dato1 = new Key();
    dato1->setLineaFerroviaria("Sarmiento");
	dato1->setFranjaHorariaDelSiniestro("2012/02/21 00:00 00:30");
	dato1->setFalla("no cierra puerta");
	dato1->setAccidente("incendio");
	dato1->setFormacion(1);
	string serializacion = dato1->Serializarse();

	Key* dato2 = new Key(serializacion);
	dato1->imprimir();
	dato2->imprimir();
	if (dato1->esIgual(dato2))
        cout << "TestSerializarHidratarKey: OK" << endl;
    else
        cout << "TestSerializarHidratarKey: FAIL" <<endl;
}
