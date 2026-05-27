#include <iostream>

using std::cout;
using std::endl;

class ConcreteElementA;
class ConcreteElementB;

class Visitor {

public:

    virtual void visit(ConcreteElementA* element) = 0;
    virtual void visit(ConcreteElementB* element) = 0;

    virtual ~Visitor() {}
};


class Element {

public:

    virtual void accept(Visitor* visitor) = 0;

    virtual ~Element() {}
};

class ConcreteElementA : public Element{

public:

    void accept(Visitor* visitor) {

        visitor -> visit(this);
    }

    void operation() {

        cout << "Operation on A" << endl;
    }
};

class ConcreteElementB : public Element{

public:

    void accept(Visitor* visitor) {

        visitor -> visit(this);
    }

    void operation() {

        cout << "Operation on B" << endl;
    }
};

class ConcreteVisitor : public Visitor {

public:

    void visit(ConcreteElementA* element) {

        cout << "Visitor processing Element A" <<endl;
        element -> operation();
    }
    void visit(ConcreteElementB* element) {

        cout << "Visitor processing Element B" <<endl;
        element -> operation();
    }
};

int main() {

    Element* elementA = new ConcreteElementA();
    Element* elementB = new ConcreteElementB();

    Visitor* visitor = new ConcreteVisitor();

    elementA -> accept(visitor);
    elementB -> accept(visitor);

    delete elementB;
    delete elementA;
    delete visitor;

    return 0;
}