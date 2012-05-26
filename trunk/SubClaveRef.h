#ifndef SUBCLAVEREF_H_INCLUDED
#define SUBCLAVEREF_H_INCLUDED

template<class T> class SubClaveRef{
    private:
        T subclave;
        int RefNodo;

    public:

     T getSubClave()const{
        return this->subclave;
    };

    int getRefNodo(){
        return this->RefNodo;

        };

    bool operator< (const SubClaveRef<T>* otro ){

        return ( this->subclave < otro->getSubCLave() );

        };

    bool operator == (const SubClaveRef<T>* otro ){

        return ( this->subclave == otro->getSubCLave() );

        };

    SubClaveRef(T sub,int ref){
        this->subclave=sub;
        this->RefNodo=ref;
    };

    ~SubClaveRef(){
    };

};
/*para ordenar char*  */
template<> bool SubClaveRef<char*>::operator< (const SubClaveRef<char*>* otro){
    int hola = strcmp ( this->subclave , otro->getSubClave() );
    if ( hola <0)return true;
    return false;
    /* http://www.cplusplus.com/reference/clibrary/cstring/strcmp/ */
};

template<> bool SubClaveRef<char*>::operator== (const SubClaveRef<char*>* otro){
    int hola = strcmp ( this->subclave , otro->getSubClave() );
    if ( hola ==0)return true;
    return false;

};

#endif // SUBCLAVEREF_H_INCLUDED