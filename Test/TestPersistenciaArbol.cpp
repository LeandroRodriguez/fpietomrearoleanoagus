#include "TestPersistenciaArbol.h"

TestPersistenciaArbol::TestPersistenciaArbol(){}

void TestPersistenciaArbol::TestCrearPersistenciaArbol(){
    PersistenciaArbol* persistencia = new PersistenciaArbol(ARCHIVO_ARBOL);
    delete persistencia;
}
