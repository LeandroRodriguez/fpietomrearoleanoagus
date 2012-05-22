#include "TestAlmacenamientoBloque.h"

TestAlmacenamientoBloque::TestAlmacenamientoBloque(){}

void TestAlmacenamientoBloque::TestCrearAlmacenamientoBloque(){
    AlmacenamientoBloque* almacen = new AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
}

void TestAlmacenamientoBloque::TestAgregarRegistroAAlmacenamiento(){
    AlmacenamientoBloque* almacen = new AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    Bytes* byte1 = new Bytes("millonarios");
    RegistroVariable* registro1 = new RegistroVariable(*byte1);
    almacen->agregarRegistro(registro1);
    Bytes* byte2 = new Bytes("alteBrown");
    RegistroVariable* registro2 = new RegistroVariable(*byte2);
    almacen->agregarRegistro(registro2);
}

