#include "Menu.h"


Menu::Menu(){
    Controlador* controlador = new Controlador();
    continuar = true;
    while (continuar){
        system("clear");
        ImprimirOpciones();
        cin >> opcion;
        switch(opcion){
            case 0:
                continuar = false;
            case 1:
                cout << "Ingrese la falla" << endl;
                cin >> falla;
                cout << "Ingrese Fecha Inicio" << endl;
                cin >> fechaInicio;
                cout << "Ingrese Fecha Fin" << endl;
                cin >> fechaFin;
                controlador->ListarTenesPorFalla(falla, fechaInicio, fechaFin);
                break;
            case 2:
                cout << "Ingrese el accidente" << endl;
                cin >> accidente;
                cout << "Ingrese Fecha Inicio" << endl;
                cin >> fechaInicio;
                cout << "Ingrese Fecha Fin" << endl;
                cin >> fechaFin;
                controlador->ListarTenesPorAccidente(accidente, fechaInicio, fechaFin);
                break;
            case 3:
                cout << "Ingrese la formación" << endl;
                cin >> formacion;
                cout << "Ingrese Fecha Inicio" << endl;
                cin >> fechaInicio;
                cout << "Ingrese Fecha Fin" << endl;
                cin >> fechaFin;
                controlador->ListarFallasPorFormacion(formacion, fechaInicio, fechaFin);
                break;
            case 4:
                cout << "Ingrese la formación" << endl;
                cin >> formacion;
                cout << "Ingrese Fecha Inicio" << endl;
                cin >> fechaInicio;
                cout << "Ingrese Fecha Fin" << endl;
                cin >> fechaFin;
                controlador->ListarAccidentesPorFormacion(formacion, fechaInicio, fechaFin);
                break;
            case 5:
                system("clear");
                controlador->ListarFallas();
                cout<<endl;
                cout <<("PRESS ENTER");
                while (cin.get() != '\n');
                break;
            case 6:
                system("clear");
                controlador->ListarFormaciones();
                cout<<endl;
                cout <<("PRESS ENTER");
                while (cin.get() != '\n');
                break;
            case 7:
                system("clear");
                controlador->ListarLineasFerroviarias();
                cout<<endl;
                cout <<("PRESS ENTER");
                while (cin.get() != '\n');
                break;
            case 8:
                system("clear");
                controlador->ListarAccidentes();
                cout<<endl;
                cout <<("PRESS ENTER");
                while (cin.get() != '\n');
                break;
            case 9:
//                controlador->InsertarDato();
                break;
            case 10:
//                controlador->InsertarDatosCargaInicial();
                break;
            case 11:
                //controlador->ListarAccidentes();
                break;
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
	cout << " 1)  Listado de todos los trenes que tengan una misma falla" << endl;
	cout << " 2)  Listado de todos los trenes que tengan un mismo accidente" << endl;
	cout << " 3)  Listado de todas las fallas de una formación determinada" << endl;
	cout << " 4)  Listado de todos los accidentes de una formación determinada" << endl;
	cout << " 5)  Listado de todas las fallas" << endl;
	cout << " 6)  Listado de todas las formaciones" << endl;
	cout << " 7)  Listado de todas las lineas ferroviarias" << endl;
	cout << " 8)  Listado de todos los accidentes" << endl;
    cout << " 9) Ingresar datos de prueba" << endl;
    cout << " 10) Ingresar dato" << endl;
    cout << " 11) Eliminar dato" << endl;
	cout << endl;
	cout << " 0)  Salir" << endl;
	cout << endl;
};

