#ifndef SUBCLAVEREF_H_INCLUDED
#define SUBCLAVEREF_H_INCLUDED

template<class T> class SubClaveRef{
    private:
        T subclave;
        int RefNodo;

    public:

    T getSubCLave(){
        return this->subclave;
    };

    int getRefNodo(){
        return this->RefNodo;

        };

    bool operator< (const SubClaveRef* otro ){

        return ( this->subclave < otro->getSubCLave() );

        };

    SubClaveRef(T sub,int ref){
        this->SubClaveRef=sub;
        this->RefNodo=ref;
    };

    ~SubClaveRef(){
    };

};

#endif // SUBCLAVEREF_H_INCLUDED
