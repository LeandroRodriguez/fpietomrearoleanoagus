#include "Test/TestBloque.h"
#include "Test/TestRegistro.h"
using namespace std;

int main(){
    TestBloque* testBloque = new TestBloque();
    testBloque->TestCrearBloque();
    testBloque->TestAgregarRegistros();
    testBloque->TestSerializarHidratarBloque();
    TestRegistro* testRegistro = new TestRegistro();
    testRegistro->TestCrearRegistro();
    testRegistro->TestSerializarHidratarRegistro();
    return 0;
    };

