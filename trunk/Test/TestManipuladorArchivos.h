#ifndef TESTMANIPULADORARCHIVO_H_
#define TESTMANIPULADORARCHIVO_H_
#include "../ManipuladorArchivos.h"
#include "../ManejoArchivos/AlmacenamientoBloque.h"
#include "../ManejoArchivos/PersistenciaArbol.h"
#include "../Indice.h"
#include "../Constantes.h"
using namespace std;

class TestManipuladorArchivos{
    public:
    TestManipuladorArchivos();
    void TestRecuperarArchivos();
    void TestBorrarArchivos();
    void TestCrearCarpeta();
};

#endif /* TESTMANIPULADORARCHIVO_H_ */
