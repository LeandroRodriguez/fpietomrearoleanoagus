#include "TestRegistro.h"

TestRegistro::TestRegistro(){}

void TestRegistro::TestCrearRegistro(){
    Bytes* byte = new Bytes("linea tigre");
    RegistroVariable* registro = new RegistroVariable(*byte);
    Bytes dato = registro->getDato();
    if ((dato.toString() == "linea tigre")&&(registro->estaVivo()))
        cout << "TestCrearRegistros: OK " << endl;
    else
        cout << "TestCrearRegistros: FAIL " << endl;
    delete byte;
    delete registro;
}

void TestRegistro::TestSerializarHidratarRegistro(){
    Bytes* byte = new Bytes("linea tigre");
    RegistroVariable* registro1 = new RegistroVariable(*byte);
    Bytes serializacion = registro1->serializarse();
    RegistroVariable* registro2 = new RegistroVariable();
    registro2->hidratarse(serializacion);
    string dato1 = registro1->getDato().toString();
    string dato2 = registro2->getDato().toString();
    if((registro1->getDato().toString() == registro2->getDato().toString())&&(registro1->getTamanioSerializado() == registro2->getTamanioSerializado()))
       cout << "TestSerializarHidratarRegistro: OK " << endl;
    else
       cout << "TestSerializarHidratarRegistro: FAIL " << endl;
    delete byte;
    delete registro1;
    delete registro2;
}
