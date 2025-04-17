```cpp []
// Online C++ compiler to run C++ program online
#include <iostream>

class PaymentProcessor{
  public:
  virtual void processPayment(double amount)=0;
};

class CreditCard:public PaymentProcessor{
  public:
  void processPayment(double amount) override{
      std::cout<<"Amount is deducted from credit card: "<<amount<<std::endl;
  }
};

class PayPal:public PaymentProcessor{
  public:
  void processPayment(double amount) override{
      std::cout<<"Amount is deducted from pay pal: "<<amount<<std::endl;
  }
};

void deductUsing(PaymentProcessor* methodOfPayment,double amount){
    methodOfPayment->processPayment(amount);
}

int main() {
    CreditCard crediCardPayment;
    PayPal payPalPayment;
    deductUsing(&crediCardPayment,100.00);
    deductUsing(&payPalPayment,200.00);
    return 0;
}
```
