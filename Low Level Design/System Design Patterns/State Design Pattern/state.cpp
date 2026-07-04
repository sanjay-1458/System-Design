#include <iostream>

using namespace std;

class Context;

class State{
    
public:
    
    virtual void operation1(Context* context) = 0;
    virtual void operation2(Context* context) = 0;
    
    virtual ~State() {}
};

class Context {
    
    State* currentState;
    
public:

    Context(State* state) {
        
        if(state) {
            
            currentState = state;
        }
        else {
            
            currentState = nullptr;
        }
    }
    
    void setState(State* state) {
        
        delete currentState;
        currentState = state;
    }
    
    void operation1() {
        
        currentState -> operation1(this);
    }
    
    void operation2() {
        
        currentState -> operation2(this);
    }
    
    ~Context() {
        
        delete currentState;
    }
};



class StateB;

class StateA : public State {
    
public:

    void operation1(Context* context);
    void operation2(Context* context) {
        
        cout << "Invalid Operation2 by StateA" << endl;
    }
};


class StateB : public State {
    
public:

    void operation1(Context* context) {
        
        cout << "Invalid Operation1 by StateB" << endl;
    }
    void operation2(Context* context) {
        
        cout << "Operation2 performed by StateB" << endl;
    }
};

void StateA::operation1(Context* context) {
        
        cout << "Operation1 performed by StateA" << endl;
        
        context -> setState(new StateB());
    }


int main() {
    
    Context* context = new Context(nullptr);
    State* stateA = new StateA();
    
    context -> setState(stateA);
    
    context -> operation1();
    context -> operation2();

    delete context;
    
    return 0;
}