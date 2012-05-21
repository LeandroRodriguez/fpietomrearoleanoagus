#ifndef MENU_H_
#define MENU_H_

using namespace std;

class Menu{
    private:
    int opcion;
    int continuar;
    string falla;
    string accidente;
    string formacion;

    public:
    Menu();
    ImprimirOpciones();
};
#endif
