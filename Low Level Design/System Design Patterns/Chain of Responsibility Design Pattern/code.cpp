#include <bits/stdc++.h>
using namespace std;

class Request {
    
public:
    
    bool valid = true;
    bool authenticate = true;
};

class Handler {
    
protected:
    
    Handler* next;
    
public:

    Handler(): next(nullptr) {}
    
    virtual void handle(Request& request) = 0;
    
    void setHandler(Handler* handler) {
        
        next = handler;
    }
    
    virtual ~Handler() {}
};

class ValidationHandler : public Handler {
    
public:
    
    void handle(Request& request) override {
        
        cout << "Performing Validation \n";
        
        if(!(request.valid)) {
            
            return;
        }
    
        if(next) {
            
            next -> handle(request);
        }
    }
};


class AuthorizationHandler : public Handler {
    
public:
    
    void handle(Request& request) override {
        
        cout << "Checking Authorization \n";
        
        if(!(request.authenticate)) {
            
            return;
        }
    
        if(next) {
            
            next -> handle(request);
        }
    }
};

class ProcessingHandler : public Handler {
    
public:
    
    void handle(Request& request) override {
        
        cout << "Performing Computation \n";
    
    
        if(next) {
            
            next -> handle(request);
        }
    }
};



int main() {
    
    Request request;
    Handler* validationHandler = new ValidationHandler();
    Handler* authorizationHandler = new AuthorizationHandler();
    Handler* processingHandler = new ProcessingHandler();
    
    validationHandler -> setHandler(authorizationHandler);
    authorizationHandler -> setHandler(processingHandler);
    
    validationHandler -> handle(request);
    
    delete validationHandler;
    delete authorizationHandler;
    delete processingHandler;
    
    return 0;
}
