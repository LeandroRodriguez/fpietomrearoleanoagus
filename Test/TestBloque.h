#ifndef TESTBLOQUE_H_
#define TESTBLOQUE_H_
#include "../ManejoArchivos/Bloque.h"
#include "../ManejoArchivos/RegistroVariable.h"
#include "../ManejoArchivos/Bytes.h"
#include "../Constantes.h"
using namespace std;

class TestBloque{

    public:
    TestBloque();
    void TestAgregarRegistros();
    void TestSerializarHidratarBloque();
    void TestCrearBloque();

};


#endif /* TESTBLOQUE_H_ */
