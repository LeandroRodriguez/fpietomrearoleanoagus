#ifndef MENU_H_
#define MENU_H_
#include <string>
#include "Controlador.h"

using namespace std;

class Menu{
    private:
    int opcion;
    int continuar;
    string falla;
    string accidente;
    int formacion;

    public:
    Menu();
    void ImprimirOpciones();
};
#endif
