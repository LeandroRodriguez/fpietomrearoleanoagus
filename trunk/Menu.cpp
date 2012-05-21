#include "Menu.h"

//HICE ESTAS CLASES XQ DE LO OTRO MUCHO NO ESTOY CASANDO Y QUERIA EMEPZAR CON ALGO


Menu::Menu(){
    Controlador controlador = new Controlador();
    continuar = 1;
    while (continuar){
        system("clear");
        ImprimirOpciones();
        cin >> opcion;
        switch(opcion){
            case 0:
                continuar = 0;
            case 1:
                cout << "Ingrese la falla" << endl;
                cin >> falla;
                controlador->ListarTenesPorFalla(falla);
                break;
            case 2:
                cout << "Ingrese el accidente" << endl;
                cin >> accidente;
                controlador->ListarTenesPorAccidente(accidente);
                break;
            case 3:
                cout << "Ingrese la formación" << endl;
                cin >> formacion;
                controlador->ListarFallasPorFormacion(formacion);
                break;
            case 4:
                cout << "Ingrese la formación" << endl;
                cin >> formacion;
                controlador->ListarAccidentesPorFormacion(formacion);
                break;
            case 5:
                controlador->ListarFallas();
                break;
            case 6:
                controlador->ListarForcaciones();
                break;
            case 7:
                controlador->ListarLineas();
                break;
            case 9:
                controlador->ListarAccidentes();
            default:
                cout << "Ingrese una opción valida" << endl;
                break;
            }
        }
    }

void Menu::ImprimirOpciones(){
	cout << "Menu Principal" << endl;
	cout << endl;
	cout << "Ingrese la opción que desee:" << endl;
	cout << endl;
	cout << " 1) Listado de todos los trenes que tengan una misma falla" << endl;
	cout << " 2) Listado de todos los trenes que tengan un mismo accidente" << endl;
	cout << " 3) Listado de todas las fallas de una formación determinada" << endl;
	cout << " 4) Listado de todos los accidentes de una formación determinada" << endl;
	cout << " 5) Listado de todas las fallas" << endl;
	cout << " 7) Listado de todas las formaciones" << endl;
	cout << " 8) Listado de todas las lineas" << endl;
	cout << " 9) Listado de todos los accidentes" << endl;
	cout << endl;
	cout << " 0)  Salir" << endl;
	cout << endl;
}

