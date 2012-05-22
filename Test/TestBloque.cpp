#include "TestBloque.h"

TestBloque::TestBloque(){}

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
    if(espacioLibre1<espacioLibre2)
        cout << "TestAgregarRegistros == OK " << endl;
    }


