#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

class Key : public InterfazSerializar{

    private:
	char* LineaFerroviaria;

	int   Formacion;

	char* Falla;

	char* Accidente;

	char* FranjaHorariaDelSiniestro;

    public:

	//ESTE METODO ES VOID NO PUEDE DEVOLVER INTS, CHARS*, ETC
	void* getSubClaveSegunDim( int dim );


	Bytes* Serializarse();

	void Hidratar(Bytes* bytes);


	unsigned long int getTamanioSerializado();
};

#endif // KEY_H_INCLUDED
