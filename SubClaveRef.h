#ifndef SUBCLAVEREF_H_INCLUDED
#define SUBCLAVEREF_H_INCLUDED

using namespace std;

template<class T> class SubClaveRef{
    private:
        T subclave;
        int RefNodo;

    public:

     T getSubClave()const{
        return this->subclave;
    }

    int getRefNodo(){
        return this->RefNodo;

        }
    void setRefNodo(int num){
        this->RefNodo=num;
    }

    SubClaveRef(T sub,int ref){
           this->subclave=sub;
           this->RefNodo=ref;
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
};


template<>
class SubClaveRef<char*>{

    private:
    char* subclave;
    int RefNodo;
    public:

    char* getSubClave()const{
        return this->subclave;
    }

    void setRefNodo(int c){
     this->RefNodo=c;
    }

    int getRefNodo(){
        return this->RefNodo;

        }

    bool operator< (const SubClaveRef<char*>* otro){
        int hola = strcmp ( this->subclave , otro->getSubClave() );
        if ( hola <0)return true;
        return false;
        // http://www.cplusplus.com/reference/clibrary/cstring/strcmp/
        }

    bool operator< (const char* subc){
        int hola = strcmp ( this->subclave , subc );
        if ( hola ==0)return true;
        return false;
        }

    bool operator== (const SubClaveRef<char*>* otro){
        int hola = strcmp ( this->subclave , otro->getSubClave() );
        if ( hola ==0)return true;
        return false;
        }

    SubClaveRef(char* sub,int ref){
           this->subclave=sub;
           this->RefNodo=ref;
       }

    ~SubClaveRef(){}
};


#endif // SUBCLAVEREF_H_INCLUDED
