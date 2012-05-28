#include "TestPersistenciaArbol.h"

TestPersistenciaArbol::TestPersistenciaArbol(){}

void TestPersistenciaArbol::TestCrearArchivoArbol(){
    PersistenciaArbol* persistencia = new PersistenciaArbol(ARCHIVO_ARBOL);
    if (persistencia->isVacio())
        cout << "TestCrearArchivoArbol: OK" <<endl;
    else
        cout << "TestCrearArchivoArbol: FAIL" <<endl;
    delete persistencia;
}

void TestPersistenciaArbol::TestObtenerRaiz(){
    PersistenciaArbol* persistencia = new PersistenciaArbol(ARCHIVO_ARBOL);
    Nodo* nodo = persistencia->obtenerRaiz();
}
