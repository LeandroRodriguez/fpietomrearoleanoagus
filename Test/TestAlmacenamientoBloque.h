#ifndef TESTALMACENAMIENTOBLOQUE_H_
#define TESTALMACENAMIENTOBLOQUE_H_
#include "../ManejoArchivos/AlmacenamientoBloque.h"
#include "../Constantes.h"
using namespace std;

class TestAlmacenamientoBloque{

    public:
    TestAlmacenamientoBloque();
    void TestCrearArchivosDatos();
    void TestAgregarRecuperarRegistro();
    void TestRecuperarBloque();
    void TestEscribirBloque();
};


#endif /* TESTALMACENAMIENTOBLOQUE_H_ */


