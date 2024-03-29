#ifndef SUBCLAVEREF_H_INCLUDED
#define SUBCLAVEREF_H_INCLUDED

using namespace std;
class SubClaveRef{

    private:
    string subclave;
    int RefNodo;
    public:

    void imprimir(){
        std::cout<< "subclave:"<< this->subclave <<", idNodo:"<<this->RefNodo<<endl;
        }

    unsigned int getTamanioSerializado(){
        unsigned int tam = strlen( this->subclave.c_str() )+1+sizeof(int)+sizeof(this->RefNodo);
        return tam ;
    }
    char* Serializarse(){// haciendo strlen() la cadena que me devuelve, se cuanto mover cursor exterior
        int cur=0;
        char* str = new char[this->getTamanioSerializado() ];

        int pInt = strlen( this->subclave.c_str())+1;//artilugio para usar memcopy

        //cout << "longitud de la subclave a serializar "<< pInt << endl;

        memcpy(str + cur,&pInt,sizeof(int) );

        cur += sizeof(int);//guarde longitud de la subclave en un int

        memcpy(str + cur, this->subclave.c_str() ,strlen( this->subclave.c_str() )+1);
        cur += strlen( this->subclave.c_str() )+1;//guarde la subclave

        memcpy(str + cur, &this->RefNodo , sizeof(RefNodo));
        cur += sizeof(RefNodo);//guarde el nodo
        return str;
        }

    void Hidratar(char* bytes,unsigned int &cur){//devuelvo el tamanio que use de la cadena
        int longitud=0;
        memcpy(&longitud, bytes + cur  , sizeof(int) );
        cur += sizeof(int);
       // cout << "long subclave " << longitud << endl;

        char* cadena = new char[longitud];
        memcpy(cadena, bytes + cur  , longitud );
        cur += longitud;

        int RefNod=0;

        memcpy(&RefNod, bytes + cur  , sizeof(this->RefNodo) );
        cur += sizeof(this->RefNodo);
        //cout << "refnod " << RefNod << endl;

        this->setRefNodo(RefNod);
        this->subclave= string(cadena) ;
        //cout <<"subclave " <<this->subclave << endl;
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

    bool esMenorEstrictoQue(const SubClaveRef* otro){
        int hola = this->subclave.compare(otro->getSubClave());
        if ( hola <0){
            //cout << this->subclave << " es menor que " << otro->getSubClave() << endl;
            return true;
            }
            //cout << this->subclave << " es mayor o igual que " << otro->getSubClave() << endl;
            return false;
        //http://www.cplusplus.com/reference/string/string/compare/
        }

    bool esMenorEstrictoQue(const string& sub){
        int hola = this->subclave.compare(sub);
        if ( hola <0){
            //cout << this->subclave << " es menor que " << sub << endl;
            return true;
            }
            //cout << this->subclave << " es mayor o igual que " << sub << endl;
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

    bool esMayorEstrictoQue(const string& sub){
        int hola = this->subclave.compare(sub);
        if ( hola >0){
            //cout << this->subclave << " es mayor que " << sub << endl;
            return true;
            }
            //cout << this->subclave << " es menor o igual que " << sub << endl;
            return false;
        }

    bool esMayorEstrictoQue(const SubClaveRef* otro){
        int hola = this->subclave.compare(otro->getSubClave());
        if ( hola >0){
            //cout << this->subclave << " es mayor que " << otro->getSubClave() << endl;
            return true;
            }
          //  cout << this->subclave << " es menor o igual que " << otro->getSubClave() << endl;
            return false;
        //http://www.cplusplus.com/reference/string/string/compare/
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
