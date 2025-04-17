```cpp []
// Online C++ compiler to run C++ program online
#include <iostream>

class Shape{
    public:
    virtual Shape* clone()=0;
    virtual ~Shape(){}
};

// Create and return new copy object
class Circle: public Shape{
    public:
    Circle(){
        std::cout<<"Circle is created"<<std::endl;
    }
    Circle(const Circle&circle){
        std::cout<<"Copy is created"<<std::endl;
    }
    Shape* clone() override{
        return new Circle(*this);
    }
    
};
int main() {
    Shape* circle=new Circle;
    Shape* copyCircle=circle->clone();
    delete circle;
    delete copyCircle;
    return 0;
}
```
