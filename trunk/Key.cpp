#include <iostream>

struct Horario {
        unsigned int hora;
        unsigned int minutos;
        unsigned int segundos;
        };

struct Fecha {
        unsigned int Dia;
        unsigned int Mes;
        unsigned int Anio;
        };

class FechaHora:public InterfazSerializar {

    private:

    Horario IzqHora;
    Horario DerHora;
    Fecha fecha;

    public:

    FechaHora(){
    }

    void Hidratar(Bytes* CodigoBinario){
        }

    bool Setear1erHora(unsigned int hora, unsigned int min,unsigned int sec){
        }

    bool Setear2daHora(unsigned int hora,unsigned int min, unsigned int sec){
        }

    bool SetearFecha(unsigned int Dia,unsigned int Mes,unsigned int Anio){
        }

    Fecha getFecha(){
        }

    Horario getIzqHorario(){
        }

    Horario getDerHorario(){
        }

    Bytes* Serializarse(){
    }

};

class Key:public InterfazSerializar{

    private:

    char* LineaFerroviaria;
    FechaHora* FranjaHorariaDelSiniestro;
    char* Falla;
    char* Accidente;
    int   Formacion;

    public:

    void* getSubClaveSegunDim( int dim )

    Bytes* Serializarse(){
        }

    void Hidratar(Bytes* CodigoBinario){
    }



};
