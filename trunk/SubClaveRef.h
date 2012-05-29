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
class SubClaveRef<string>{

    private:
    string subclave;
    int RefNodo;
    public:

    string getSubClave()const{
        return this->subclave;
    }

    void setRefNodo(int c){
     this->RefNodo=c;
    }

    int getRefNodo(){
        return this->RefNodo;

        }

    bool operator< (const SubClaveRef<string>* otro){
        int hola = this->subclave.compare(otro->getSubClave());
        if ( hola <0)return true;
        return false;
        //http://www.cplusplus.com/reference/string/string/compare/
        }

    bool operator< (const string subc){
        int hola = this->subclave.compare(subc);
        if ( hola ==0)return true;
        return false;
        }

    bool operator== (const SubClaveRef<string>* otro){
        int hola = this->subclave.compare(otro->getSubClave() );
        if ( hola ==0)return true;
        return false;
        }

    SubClaveRef(string sub,int ref){
           this->subclave=sub;
           this->RefNodo=ref;
       }

    ~SubClaveRef(){}
};


#endif // SUBCLAVEREF_H_INCLUDED
