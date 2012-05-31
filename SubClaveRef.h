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
        return strlen( this->Serializarse() );
    }
    char* Serializarse(){// haciendo strlen() la cadena que me devuelve, se cuanto mover cursor exterior
        int cur=0;
        char* str = new char[(this->subclave.length()+sizeof(int)+sizeof(this->RefNodo)) ];
        int* pInt = new int;
        *pInt = this->subclave.length();//artilugio para usar memcopy
        memcpy(str + cur,pInt,sizeof(int) );
        cur += sizeof(int);//guarde longitud de la subclave en un int
        memcpy(str + cur, &this->subclave , this->subclave.length());
        cur += this->subclave.length();//guarde la subclave
        memcpy(str + cur, &this->RefNodo , sizeof(RefNodo));
        cur += sizeof(RefNodo);//guarde el nodo
        delete pInt;
        return str;
        }

    void Hidratar(char* bytes,unsigned int &cur){//devuelvo el tamanio que use de la cadena
        int longitud=0;
        memcpy(&longitud, bytes + cur  , sizeof(int) );
        cur += sizeof(int);

        string subcl;
        memcpy(&subcl, bytes + cur  , longitud );
        cur += longitud;

        int RefNod;

        memcpy(&RefNod, bytes + cur  , sizeof(this->RefNodo) );
        cur += sizeof(this->RefNodo);

        this->setRefNodo(RefNod);
        this->subclave=subcl;
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

    bool operator< (const SubClaveRef* otro){
        int hola = this->subclave.compare(otro->getSubClave());
        if ( hola <0){
            cout << this->subclave << " es menor que " << otro->getSubClave() << endl;
            return true;
            }
            cout << this->subclave << " es mayor o igual que " << otro->getSubClave() << endl;
            return false;
        //http://www.cplusplus.com/reference/string/string/compare/
        }

    bool operator< (const string subc){
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
    bool operator== (const string otro){
        int hola = this->subclave.compare(otro );
        if ( hola ==0)return true;
        return false;
        }

    bool operator> (const string otro){
       int hola = this->subclave.compare(otro);
       if(hola>0)return true;
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
