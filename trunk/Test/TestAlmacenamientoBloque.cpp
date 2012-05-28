#include "TestAlmacenamientoBloque.h"

TestAlmacenamientoBloque::TestAlmacenamientoBloque(){}

void TestAlmacenamientoBloque::TestCrearArchivosDatos(){
    AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    cout << "TestCrearArchivosDatos: OK " << endl;
}

void TestAlmacenamientoBloque::TestAgregarRecuperarRegistro(){
    AlmacenamientoBloque* almacen = new AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    Bytes byte1("millonarios");
    RegistroVariable* registro1 = new RegistroVariable(byte1);
    almacen->agregarRegistro(registro1);
    offset id1 = almacen->getNumeroUID();

    Bytes byte2("alteBrown");
    RegistroVariable* registro2 = new RegistroVariable(byte2);
    almacen->agregarRegistro(registro2);
    offset id2 = almacen->getNumeroUID();

    offset nBloque =almacen->getNumeroBloque();
    RegistroVariable reg1 = almacen->recuperarRegistro(nBloque,id1);
    RegistroVariable reg2 = almacen->recuperarRegistro(nBloque,id2);
    Bytes serializacion = almacen->recuperarBloque(nBloque);
    Bloque* bloque = new Bloque();
    bloque->hidratarse(serializacion);
    if (reg1.getDato().toString() == "millonarios" && reg2.getDato().toString() == "alteBrown")
        cout << "TestAgregarRecuperarRegistro: OK " << endl;
    else
        cout << "TestAgregarRecuperarRegistro: FAIL " << endl;
    delete registro1;
    delete almacen;
    delete registro2;
}

void TestAlmacenamientoBloque::TestRecuperarBloque(){
    AlmacenamientoBloque* almacen = new AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    Bytes byte1("tatengue");
    RegistroVariable* registro1 = new RegistroVariable(byte1);
    almacen->agregarRegistro(registro1);
    offset id1 = almacen->getNumeroUID();

    Bytes byte2("bicho");
    RegistroVariable* registro2 = new RegistroVariable(byte2);
    almacen->agregarRegistro(registro2);
    offset id2 = almacen->getNumeroUID();
    offset nBloque =almacen->getNumeroBloque();
    Bytes serializacion = almacen->recuperarBloque(nBloque);
    Bloque* bloque = new Bloque();
    bloque->hidratarse(serializacion);
    if (bloque->obtenerRegistro(id1).toString() == "tatengue" && bloque->obtenerRegistro(id2).toString() == "bicho")
        cout << "TestRecuperarBloque: OK " << endl;
    else
        cout << "TestRecuperarBloque: FAIL " << endl;
    delete registro1;
    delete almacen;
    delete registro2;
    delete bloque;
}

void TestAlmacenamientoBloque::TestEscribirBloque(){
    AlmacenamientoBloque* almacen = new AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    Bytes byte1("pirata");
    Bytes byte2("cordobes");
    RegistroVariable* registro1 = new RegistroVariable(byte1);
    almacen->agregarRegistro(registro1);
    offset nBloque = almacen->getNumeroBloque();
    almacen->escribirBloque(byte2,15);
    Bytes serializacion = almacen->recuperarBloque(nBloque);
    Bloque* bloque = new Bloque();
    bloque->hidratarse(serializacion);
    Bytes ser = bloque->serializarse();
    cout << ser.toString() << endl;
    delete almacen;
    delete registro1;
    delete bloque;
}
