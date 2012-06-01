#ifndef SUBCLAVEREF_H_INCLUDED
#define SUBCLAVEREF_H_INCLUDED

using namespace std;
/*
template<class T> class SubClaveRef{
    private:
        T subclave;
        int RefNodo;

    public:

    SubClaveRef(){}

     T getSubClave()const{
        return this->subclave;
    }

    int getRefNodo(){
        return this->RefNodo;

        }
    void setRefNodo(int num){
        this->RefNodo=num;
    }

    SubClaveRef(T sub, int ref){
           this->subclave=sub;
           this->RefNodo=ref;
        }

    SubClaveRef(char* bytes,unsigned int& cur){
        this->Hidratar(bytes,cur);
    }
    bool operator< (const T subc){
        return ( this->subclave < subc );
        }

    bool operator< (const SubClaveRef<T>* otro ){
        return ( this->subclave < otro->getSubCLave() );
    }

    bool operator==(const T otro){
        return (this->subclave == otro );
        }
    ~SubClaveRef(){}

    void imprimir(){
        std::cout<< "subclave:"<< this->subclave <<", idNodo:"<<this->RefNodo<<endl;
        }

    char* Serializarse(){
            char* str = new char[(sizeof(this->subclave)+sizeof(this->RefNodo))];
            int cur=0;
            memcpy(str + cur,&this->subclave, sizeof(this->subclave));
            cur += sizeof(this->subclave);
            memcpy(str + cur, &this->RefNodo , sizeof(RefNodo));
            cur += sizeof(RefNodo);
            return str;
        }
    void Hidratar(char* bytes,unsigned int& cur){//cursos,voy moviendo un cursor que me pasan de afuera
        T subcl;
        memcpy(&subcl, bytes + cur  , sizeof(T) );
        cur += sizeof(T);

        int RefNod;

        memcpy(&RefNod, bytes + cur  , sizeof(int) );
        cur += sizeof(int);

        this->setRefNodo(RefNod);
        this->subclave=subcl;
        }

    unsigned int getTamanioSerializado(){
        return strlen( this->Serializarse() );
    }
};
*/

class SubClaveRef{

    private:
    string subclave;
    int RefNodo;
    public:

    void imprimir(){
        std::cout<< "subclave:"<< this->subclave <<", idNodo:"<<this->RefNodo<<endl;
        }

    unsigned int getTamanioSerializado(){
        unsigned int tam = this->subclave.length()+sizeof(int)+sizeof(this->RefNodo);
        return tam ;
    }
    char* Serializarse(){// haciendo strlen() la cadena que me devuelve, se cuanto mover cursor exterior
        int cur=0;
        char* str = new char[(strlen( this->subclave.c_str() )+sizeof(int)+sizeof(this->RefNodo)) ];

        int pInt = strlen( this->subclave.c_str());//artilugio para usar memcopy

        cout << pInt << endl;

        memcpy(str + cur,&pInt,sizeof(int) );

        cur += sizeof(int);//guarde longitud de la subclave en un int

        memcpy(str + cur, this->subclave.c_str() ,strlen( this->subclave.c_str() ));
        cur += strlen( this->subclave.c_str() );//guarde la subclave

        memcpy(str + cur, &this->RefNodo , sizeof(RefNodo));
        cur += sizeof(RefNodo);//guarde el nodo
        return str;
        }

    void Hidratar(char* bytes,unsigned int &cur){//devuelvo el tamanio que use de la cadena
        int longitud=0;
        memcpy(&longitud, bytes + cur  , sizeof(int) );
        cur += sizeof(int);
        cout << "long subclave " << longitud << endl;

        char* cadena = new char[longitud];
        memcpy(cadena, bytes + cur  , longitud );
        cur += longitud+1;

        int RefNod=0;

        memcpy(&RefNod, bytes + cur  , sizeof(this->RefNodo) );
        cur += sizeof(this->RefNodo);
        cout << "refnod " << RefNod << endl;

        this->setRefNodo(RefNod);
        this->subclave= string(cadena) ;
        cout <<"subclave " <<this->subclave << endl;
        }

    string getSubClave()const{
        return this->subclave;
    }

    void setSubClave(string h){
        this->subclave=h;
    }

    void setRefNodo(int c){
     this->RefNodo=c;
    }

    int getRefNodo(){
        return this->RefNodo;
        }

/*
    bool operator< (const SubClaveRef *otro){
        int hola = this->subclave.compare(otro->getSubClave());
        if ( hola <0){
            cout << this->subclave << " es menor que " << otro->getSubClave() << endl;
            return true;
            }
            cout << this->subclave << " es mayor o igual que " << otro->getSubClave() << endl;
            return false;
        //http://www.cplusplus.com/reference/string/string/compare/
        }

    bool operator< (const string &subc){
        int hola = this->subclave.compare(subc);
        if ( hola <0){
            cout << this->subclave << " es menor que " << subc << endl;
            return true;
            }
            cout << this->subclave << " es mayor o igual que " << subc << endl;
            return false;
        //http://www.cplusplus.com/reference/string/string/compare/
        }

    bool operator== (const SubClaveRef* otro){
        int hola = this->subclave.compare(otro->getSubClave() );
        if ( hola ==0)return true;
        return false;
        }
    bool operator== (const string &otro){
        int hola = this->subclave.compare(otro );
        if ( hola ==0)return true;
        return false;
        }

    bool operator> (const string &otro){
       int hola = this->subclave.compare(otro);
       if(hola>0)return true;
       return false;
    }
*/
    bool esMenorEstrictoQue(const SubClaveRef* otro){
        int hola = this->subclave.compare(otro->getSubClave());
        if ( hola <0){
            cout << this->subclave << " es menor que " << otro->getSubClave() << endl;
            return true;
            }
            cout << this->subclave << " es mayor o igual que " << otro->getSubClave() << endl;
            return false;
        //http://www.cplusplus.com/reference/string/string/compare/
        }

    bool esMenorEstrictoQue(const string& sub){
        int hola = this->subclave.compare(sub);
        if ( hola <0){
            cout << this->subclave << " es menor que " << sub << endl;
            return true;
            }
            cout << this->subclave << " es mayor o igual que " << sub << endl;
            return false;
        //http://www.cplusplus.com/reference/string/string/compare/
        }

    bool esIgualQue(const SubClaveRef* otro){
        int hola = this->subclave.compare(otro->getSubClave() );
        if ( hola == 0 )return true;
        return false;
        }

    bool esIgualQue(const string& sub){
        int hola = this->subclave.compare(sub );
        if ( hola == 0 )return true;
        return false;
        }

    SubClaveRef(char* bytes,unsigned int& cur){
        this->Hidratar(bytes,cur);
    }
    SubClaveRef(string sub,int ref){
           this->subclave=sub;
           this->RefNodo=ref;
       }

    SubClaveRef(){};
    ~SubClaveRef(){}
};
#endif // SUBCLAVEREF_H_INCLUDED
