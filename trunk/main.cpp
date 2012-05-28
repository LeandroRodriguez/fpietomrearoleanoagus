#include "Test/TestBloque.h"
#include "Test/TestRegistro.h"
#include "Test/TestAlmacenamientoBloque.h"
#include "Test/TestPersistenciaArbol.h"
#include "Test/TestManipuladorArchivos.h"
using namespace std;

int main(){
    TestBloque* testBloque = new TestBloque();
    testBloque->TestCrearBloque();
    testBloque->TestAgregarRegistros();
    testBloque->TestSerializarHidratarBloque();
    delete testBloque;

    TestRegistro* testRegistro = new TestRegistro();
    testRegistro->TestCrearRegistro();
    testRegistro->TestSerializarHidratarRegistro();
    delete testRegistro;

    TestAlmacenamientoBloque* testAlmacen = new TestAlmacenamientoBloque();
    testAlmacen->TestCrearArchivosDatos();
    testAlmacen->TestAgregarRecuperarRegistro();
    testAlmacen->TestRecuperarBloque();
    //testAlmacen->TestEscribirBloque();
    delete testAlmacen;

    TestPersistenciaArbol* testPersistencia = new TestPersistenciaArbol();
    testPersistencia->TestCrearArchivoArbol();
    delete testPersistencia;

    TestManipuladorArchivos* testManipualdor = new TestManipuladorArchivos();
    testManipualdor->TestRecuperarArchivos();
    testManipualdor->TestBorrarArchivos();
    testManipualdor->TestCrearCarpeta();
    delete testManipualdor;
};
