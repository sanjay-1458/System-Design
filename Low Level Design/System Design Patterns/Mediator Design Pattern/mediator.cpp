#include <iostream>
#include <string>

using std::endl;
using std::cout;
using std::string;

class BaseComponent;

class IMediator {

public:

    virtual void notify(BaseComponent* component, string event) = 0;
    virtual ~IMediator() {}
};

class BaseComponent {

protected:

    IMediator* mediator;

public:
    
    virtual void doAction() = 0;

    virtual void receive() = 0;

    virtual ~BaseComponent() {}

    BaseComponent(IMediator* mediator = nullptr) {

        this -> mediator = mediator;
    }

    void setMediator(IMediator* mediator) {

        this -> mediator = mediator;
    }
};

class ConcreteComponentA : public BaseComponent {

public:

    ConcreteComponentA(IMediator* mediator): BaseComponent(mediator) {

        
    }

    void doAction()  override {

        cout<<"Action performed by Component-A"<<endl;

        mediator -> notify(this, "EVENT_A");
    }

    void receive() {

        cout<<"Component-A received data"<<endl;
    }
};
class ConcreteComponentB : public BaseComponent {

public:

    ConcreteComponentB(IMediator* mediator): BaseComponent(mediator) {}

    void doAction()  override {

        cout<<"Action performed by Component-B"<<endl;

        mediator -> notify(this, "EVENT_B");
    }

    void receive() override {

        cout<<"Component-B received data"<<endl;
    }
};

class Mediator : public IMediator {

private:

    BaseComponent* ComponentA;
    BaseComponent* ComponentB;

public:

    void notify(BaseComponent* component, string event) override {

        if(component != nullptr) {

            if(event == "EVENT_A") {

                ComponentB -> receive();
            }
            else if(event == "EVENT_B") {

                ComponentA -> receive();
            }
        }
    }

    void setComponentA(BaseComponent* component) {

        ComponentA = component;
    }

    void setComponentB(BaseComponent* component) {

        ComponentB = component;
    }
};

int main() {

    Mediator* mediator = new Mediator();

    BaseComponent* componentA = new ConcreteComponentA(mediator);

    BaseComponent* componentB = new ConcreteComponentB(mediator);

    mediator -> setComponentA(componentA);
    mediator -> setComponentB(componentB);

    componentA -> doAction();
    componentB -> doAction();

    delete componentB;
    delete componentA;
    delete mediator;

    return 0;
}