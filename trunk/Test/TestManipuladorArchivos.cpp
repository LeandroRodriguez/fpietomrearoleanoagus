#include "TestManipuladorArchivos.h"

TestManipuladorArchivos::TestManipuladorArchivos(){}

void TestManipuladorArchivos::TestRecuperarArchivos(){
    bool borrar = false;
    ManipuladorArchivos* manipulador = new ManipuladorArchivos();
    cout << endl << "Archivos Borrados:" << endl;
    manipulador->borrarArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    vector<string> archivos = manipulador->getArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    if (archivos.size() == 0)
        borrar = true;
    AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    PersistenciaArbol(ARCHIVO_ARBOL);
    archivos = manipulador->getArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    if (archivos[0] == ARCHIVO_DATOS_LIBRES && archivos[1] == ARCHIVO_DATOS && archivos[2] == ARCHIVO_ARBOL && borrar)
       cout << "TestRecuperarArchivos: OK " << endl;
    else
       cout << "TestRecuperarArchivos: FAIL " << endl;
    delete manipulador;
}

void TestManipuladorArchivos::TestBorrarArchivos(){
    bool crear = false;
    bool borrar = false;
    ManipuladorArchivos* manipulador = new ManipuladorArchivos();
    AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    PersistenciaArbol(ARCHIVO_ARBOL);
    vector<string> archivos = manipulador->getArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    if (archivos.size() == 3)
        crear = true;
    cout << endl << "Archivos Borrados:" << endl;
    manipulador->borrarArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    archivos = manipulador->getArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    if (archivos.size() == 0)
        borrar = true;
    if (crear && borrar)
       cout << "TestBorrarArchivos: OK " << endl;
    else
       cout << "TestBorrarArchivos: FAIL " << endl;
    delete manipulador;
}

void TestManipuladorArchivos::TestCrearCarpeta(){
    ManipuladorArchivos* manipulador = new ManipuladorArchivos();
    manipulador->creoCarpeta(DIR_ARCHIVO_DATOS);
}
