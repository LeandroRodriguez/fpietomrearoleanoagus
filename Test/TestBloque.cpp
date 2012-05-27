#include "TestBloque.h"

TestBloque::TestBloque(){}

void TestBloque::TestCrearBloque(){
    Bloque* bloque = new Bloque(2048);
    if(bloque->getEspacioLibre() == bloque->tamanio)
    cout << "TestCrearBloque: OK " << endl;
    else
    cout << "TestCrearBloque: FAIL " << endl;
    delete bloque;
}

void TestBloque::TestAgregarRegistros(){
    Bloque* bloque = new Bloque(256);
    Bytes* byte1 = new Bytes("agustin");
    Bytes* byte2 = new Bytes("origone");
    RegistroVariable* registro1 = new RegistroVariable(*byte1);
    RegistroVariable* registro2 = new RegistroVariable(*byte2);
	if (bloque->tieneLugar(registro1))
        bloque->agregarRegistro(registro1);
    tamanioBloque espacioLibre1 = bloque->getEspacioLibre();//236
    cantBytes cantSerializada = bloque->getTamanioSerializado();//256
	if (bloque->tieneLugar(registro2))
        bloque->agregarRegistro(registro2);
    tamanioBloque espacioLibre2 = bloque->getEspacioLibre();//236
    if(espacioLibre1>espacioLibre2)
        cout << "TestAgregarRegistros: OK " << endl;
    else
        cout << "TestAgregarRegistros: FAIL " << endl;
    delete bloque;
    delete byte1;
    delete byte2;
    delete registro1;
    delete registro2;
}

void TestBloque::TestSerializarHidratarBloque(){
    Bloque* bloque1 = new Bloque(1024);
    Bytes* byte = new Bytes("agustin");
    RegistroVariable* registro = new RegistroVariable(*byte);
    if (bloque1->tieneLugar(registro))
        bloque1->agregarRegistro(registro);
    Bytes serializacion = bloque1->serializarse();
    Bloque* bloque2 = new Bloque();
    bloque2->hidratarse(serializacion);
    Bytes cadena1 = bloque1->obtenerRegistro(0);
    Bytes cadena2 = bloque2->obtenerRegistro(0);
    if(cadena1.toString() == cadena2.toString())
        cout << "TestSerializarHidratarBloque: OK " << endl;
    else
        cout << "TestSerializarHidratarBloque: FAIL " << endl;
    delete bloque1;
    delete bloque2;
    delete byte;
    delete registro;
}

