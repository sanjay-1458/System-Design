#include <iostream>

using std::cout;
using std::endl;

class Prototype {

public:

    virtual Prototype* clone() = 0;

    virtual void print() = 0;

    virtual ~Prototype() {}
};

class ConcretePrototype : public Prototype{

    int *data;

public:
     
    ConcretePrototype(int value) {

        data = new int(value);
    }

    ConcretePrototype(const ConcretePrototype& other) {

        data = new int(*(other.data));
    }

    ConcretePrototype& operator=(const ConcretePrototype& other) {

        if(this != &other) {
   
            delete data;
            
            data = new int(*(other.data));
        }

        return *this;
    }

    Prototype* clone() override {

        return new ConcretePrototype(*this);
    }

    void print() {

        cout << *data << endl;
    }

    ~ConcretePrototype() {

        delete data;
    }
};

int main() {

    Prototype* original = new ConcretePrototype(10);

    Prototype* copied = original -> clone();

    original -> print();
    copied -> print();


    delete copied;
    delete original;

    return 0;
}