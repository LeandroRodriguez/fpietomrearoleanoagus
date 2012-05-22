#ifndef TESTREGISTRO_H_
#define TESTREGISTRO_H_
#include "../ManejoArchivos/Bloque.h"
#include "../ManejoArchivos/RegistroVariable.h"
#include "../ManejoArchivos/Bytes.h"
#include "../Constantes.h"
using namespace std;

class TestRegistro{

    public:
    TestRegistro();
    void TestCrearRegistro();
    void TestSerializarHidratarRegistro();
};


#endif /* TESTREGISTRO_H_ */
