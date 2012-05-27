#include "TestAlmacenamientoBloque.h"

TestAlmacenamientoBloque::TestAlmacenamientoBloque(){}

void TestAlmacenamientoBloque::TestCrearAlmacenamientoBloque(){
    AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
}

void TestAlmacenamientoBloque::TestAgregarRecuperarRegistro(){
    AlmacenamientoBloque* almacen = new AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    Bytes* byte1 = new Bytes("millonarios");
    RegistroVariable* registro1 = new RegistroVariable(*byte1);
    almacen->agregarRegistro(registro1);
    offset id1 = almacen->getNumeroUID();

    Bytes* byte2 = new Bytes("alteBrown");
    RegistroVariable* registro2 = new RegistroVariable(*byte2);
    almacen->agregarRegistro(registro2);
    offset id2 = almacen->getNumeroUID();

    offset bloque =almacen->getNumeroBloque();
    RegistroVariable reg1 = almacen->recuperarRegistro(bloque,id1);
    RegistroVariable reg2 = almacen->recuperarRegistro(bloque,id2);
    if (reg1.getDato().toString() == "millonarios" && reg2.getDato().toString() == "alteBrown")
        cout << "TestAlmacenamientoBloque: OK " << endl;
    else
        cout << "TestAlmacenamientoBloque: FAIL " << endl;
    delete byte1;
    delete registro1;
    delete almacen;
    delete byte2;
    delete registro2;
}
