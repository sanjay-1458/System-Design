Type-1
```cpp []
// Online C++ compiler to run C++ program online
#include <iostream>


// Product

// Abstract Product
class Shape{
   public:
   virtual void show()=0;
   virtual ~Shape(){}
};

// Concrete product class
class Square:public Shape{
    public:
    void show() override{
        std::cout<<"Square"<<std::endl;
    }
};
class Circle:public Shape{
    public:
    void show() override{
        std::cout<<"Circle"<<std::endl;
    }
};

// Factory

// Abstract factory/ creator

class ShapeFactory{
    public:
    virtual Shape* createShape()=0;
    virtual ~ShapeFactory(){}
};

// Concrete factory

class SquareFactory:public ShapeFactory{
    public:
    Shape* createShape() override{
        return new Square();
    }
};
class CircleFactory:public ShapeFactory{
    public:
    Shape* createShape() override{
        return new Circle();
    }
};
int main() {
    ShapeFactory* createShape=new SquareFactory();
    Shape* square=createShape->createShape();
    square->show();
    delete square;
    delete createShape;

    return 0;
}
```
Type - 2
```cpp []
// Online C++ compiler to run C++ program online
#include <iostream>


// Product

// Abstract Product
class Shape{
   public:
   virtual void show()=0;
   virtual ~Shape(){}
};

// Concrete product class
class Square:public Shape{
    public:
    void show() override{
        std::cout<<"Square"<<std::endl;
    }
};
class Circle:public Shape{
    public:
    void show() override{
        std::cout<<"Circle"<<std::endl;
    }
};

// Creator / Factory
class ShapeFactory{
    public:
    static Shape* createShape(const std::string&type){
        if(type=="Circle"){
            return new Circle;
        }
        else if(type=="Square"){
            return new Square;
        }
        else{
            return nullptr;
        }
    }
};

int main() {
    Shape* circle=ShapeFactory::createShape("Circle");
    circle->show();
    delete circle;
    return 0;
}
```
