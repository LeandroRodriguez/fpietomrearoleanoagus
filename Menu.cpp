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
                break;
            case 1:
                system("clear");
                cout << "Ingrese la falla" << endl;
                cin.ignore(256,'\n');
                getline(cin, falla);
                cout << "Ingrese Fecha Inicio" << endl;
                cin.ignore(256,'\n');
                getline(cin, fechaInicio);
                cout << "Ingrese Fecha Fin" << endl;
                cin.ignore(256,'\n');
                getline(cin, fechaFin);
                system("clear");
                controlador->ListarTenesPorFalla(falla, fechaInicio, fechaFin);
                cout<<endl;
                cout <<("PRESS ENTER");
                while (cin.get() != '\n');
                break;
            case 2:
                system("clear");
                cout << "Ingrese el accidente" << endl;
                cin.ignore(256,'\n');
                getline(cin, accidente);
                cout << "Ingrese Fecha Inicio" << endl;
                cin.ignore(256,'\n');
                getline(cin, fechaInicio);
                cout << "Ingrese Fecha Fin" << endl;
                cin.ignore(256,'\n');
                getline(cin, fechaFin);
                system("clear");
                controlador->ListarTenesPorAccidente(accidente, fechaInicio, fechaFin);
                cout<<endl;
                cout <<("PRESS ENTER");
                while (cin.get() != '\n');
                break;
            case 3:
                system("clear");
                cout << "Ingrese la formación" << endl;
                cin.ignore(256,'\n');
                getline(cin,formacion);
                cout << "Ingrese Fecha Inicio" << endl;
                cin.ignore(256,'\n');
                getline(cin, fechaInicio);
                cout << "Ingrese Fecha Fin" << endl;
                cin.ignore(256,'\n');
                getline(cin, fechaFin);
                controlador->ListarFallasPorFormacion(formacion, fechaInicio, fechaFin);
                cout<<endl;
                cout <<("PRESS ENTER");
                while (cin.get() != '\n');
                break;
            case 4:
                system("clear");
                cout << "Ingrese la formación" << endl;
                cin.ignore(256,'\n');
                getline(cin, formacion);
                cout << "Ingrese Fecha Inicio" << endl;
                cin.ignore(256,'\n');
                getline(cin, fechaInicio);
                cout << "Ingrese Fecha Fin" << endl;
                cin.ignore(256,'\n');
                getline(cin, fechaFin);
                system("clear");
                controlador->ListarAccidentesPorFormacion(formacion, fechaInicio, fechaFin);
                cout<<endl;
                cout <<("PRESS ENTER");
                while (cin.get() != '\n');
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
                system("clear");
                controlador->CargarDatosPrueba();
                cout<<endl;
                cout <<("PRESS ENTER");
                while (cin.get() != '\n');
                break;
            case 10:
                system("clear");
                controlador->ImprimirArbol();
                cout<<endl;
                cout <<("PRESS ENTER");
                while (cin.get() != '\n');
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
    cout << " 9)  Cargar datos de prueba" << endl;
    cout << " 10) Imprimir arbol" << endl;
    cout << " 11) Ingresar dato" << endl;
    cout << " 11) Eliminar dato" << endl;
	cout << endl;
	cout << " 0)  Salir" << endl;
	cout << endl;
};

