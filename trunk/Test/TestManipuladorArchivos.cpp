#include "TestManipuladorArchivos.h"

TestManipuladorArchivos::TestManipuladorArchivos(){}

void TestManipuladorArchivos::TestRecuperarArchivos(){
    bool borrar = false;
    ManipuladorArchivos* manipulador = new ManipuladorArchivos();
    cout << endl << "Archivos Borrados:" << endl;
    manipulador->borrarArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    manipulador->borrarArchivos(DIR_ARCHIVO_INDICES,"",".idx");
    vector<string> archivosDatos = manipulador->getArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    vector<string> archivosIndices = manipulador->getArchivos(DIR_ARCHIVO_INDICES,"",".idx");
    if (archivosDatos.size() == 0 && archivosIndices.size() == 0)
        borrar = true;
    AlmacenamientoBloque(ARCHIVO_DATOS, ARCHIVO_DATOS_LIBRES);
    Indice(ARCHIVO_ARBOL);
    archivosDatos = manipulador->getArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    archivosIndices = manipulador->getArchivos(DIR_ARCHIVO_INDICES,"",".idx");
    if (archivosDatos[0] == ARCHIVO_DATOS_LIBRES && archivosDatos[1] == ARCHIVO_DATOS && archivosIndices[0] == ARCHIVO_ARBOL && borrar)
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
    Indice(ARCHIVO_ARBOL);
    vector<string> archivosDatos = manipulador->getArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    vector<string> archivosIndices = manipulador->getArchivos(DIR_ARCHIVO_INDICES,"",".idx");
    if (archivosDatos.size() == 2 && archivosIndices.size() == 1)
        crear = true;
    cout << endl << "Archivos Borrados:" << endl;
    manipulador->borrarArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    manipulador->borrarArchivos(DIR_ARCHIVO_INDICES,"",".idx");
    archivosDatos = manipulador->getArchivos(DIR_ARCHIVO_DATOS,"",".fde");
    archivosIndices = manipulador->getArchivos(DIR_ARCHIVO_INDICES,"",".idx");
    if (archivosDatos.size() == 0 && archivosIndices.size() == 0)
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
