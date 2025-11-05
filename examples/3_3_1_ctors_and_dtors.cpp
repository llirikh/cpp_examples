// 3.3.1. Constructors and destructors. Base.

#include <iostream>

class Complex {
  public:
    Complex(double re);             // It's better to define method out of class because of it can be redifintion
    Complex(double re, double im);
  
  private:
    double re = 0.0;
    double im = 0.0;
};

Complex::Complex(double re): re(re) {                    // Member Initializer List
    // this->re = real;                                  // Bad style beacause of extra-copy
    std::cout << "Ctor1 has been called!" << std::endl;
}

Complex::Complex(double re, double im): re(re), im(im) {
    std::cout << "Ctor2 has been called!" << std::endl;
}


class Simple {
  int a = 0;
  int b = 0;
};

int main() {
    Complex c1(5.0);
    Complex c2 = 12.4;     // Value-Initialization
    Complex c3{3.4};
    Complex c4 = {323.6};
    
    Simple s;  // Implicitly Declared Default Constuctor: default contructor has been generated automatically
}