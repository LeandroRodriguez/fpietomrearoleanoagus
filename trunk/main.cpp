#include "Test/TestBloque.h"
#include "Test/TestRegistro.h"
#include "Test/TestAlmacenamientoBloque.h"
#include "Test/TestPersistenciaArbol.h"
#include "Test/TestManipuladorArchivos.h"
#include "Test/TestArbol.h"
#include "Test/TestControlador.h"
#include "Test/TestKey.h"
#include "Test/TestArbol.h"
#include "Test/TestNodoHoja.h"
#include "Test/TestNodoInterno.h"

using namespace std;

int main(){
    /*TestRegistro* testRegistro = new TestRegistro();
    testRegistro->TestCrearRegistro();
    testRegistro->TestSerializarHidratarRegistro();
    delete testRegistro;

    TestBloque* testBloque = new TestBloque();
    testBloque->TestCrearBloque();
    testBloque->TestAgregarRegistros();
    testBloque->TestSerializarHidratarBloque();
    delete testBloque;

    TestAlmacenamientoBloque* testAlmacen = new TestAlmacenamientoBloque();
    testAlmacen->TestCrearArchivosDatos();
    testAlmacen->TestAgregarRecuperarRegistro();
    testAlmacen->TestRecuperarBloque();
    //testAlmacen->TestEscribirBloque();
    delete testAlmacen;

    TestManipuladorArchivos* testManipualdor = new TestManipuladorArchivos();
    testManipualdor->TestRecuperarArchivos();
    testManipualdor->TestBorrarArchivos();
    testManipualdor->TestCrearCarpeta();
    delete testManipualdor;

    TestPersistenciaArbol* testPersistencia = new TestPersistenciaArbol();
    testPersistencia->TestCrearArchivoArbol();
    delete testPersistencia;*/

    /*TestArbol* testArbol = new TestArbol();
	testArbol->Testear();
	//testArbol->UnDatoMas();
    delete testArbol;*/

    TestControlador* testControlador = new TestControlador();
    //testControlador->TestInsertarDato();
    testControlador->TestControladorBuscarDato();
    delete testControlador;

    /*TestKey* testKey = new TestKey();
    testKey->TestSerializarHidratarKey();
    delete testKey;*/

    /*TestNodoHoja* testNodoHoja = new TestNodoHoja();
    testNodoHoja->TestCrearNodoHoja();
    testNodoHoja->TestSerializarHidtratar();
    //ESTE NO ANDA POR AHORA
    //testNodoHoja->TestPartirHojaEn2();
    testNodoHoja->TestBuscarDato();*/

    /*TestNodoInterno* testNodoInterno = new TestNodoInterno();
    //testNodoInterno->TestCrearNodoInterno();
    testNodoInterno->TestSerializarHidratar();*/
};


