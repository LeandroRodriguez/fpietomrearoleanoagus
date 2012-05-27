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
    TestRegistro* testRegistro = new TestRegistro();
    testRegistro->TestCrearRegistro();
    testRegistro->TestSerializarHidratarRegistro();
    TestAlmacenamientoBloque* testAlmacen = new TestAlmacenamientoBloque();
    testAlmacen->TestCrearAlmacenamientoBloque();
    testAlmacen->TestAgregarRecuperarRegistro();
    TestPersistenciaArbol* testPersistencia = new TestPersistenciaArbol();
    testPersistencia->TestCrearPersistenciaArbol();
    TestManipuladorArchivos* testManipualdor = new TestManipuladorArchivos();
    testManipualdor->TestRecuperarArchivos();
    testManipualdor->TestBorrarArchivos();
    testManipualdor->TestCrearCarpeta();
    delete testBloque;
    delete testRegistro;
    delete testAlmacen;
    delete testPersistencia;
    delete testManipualdor;
    };
