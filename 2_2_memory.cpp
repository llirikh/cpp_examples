// 2.2 Stack, static and dynamic memory

#include <iostream>

void f(int x) {
    std::cout << ++x << std::endl;
    f(x);
}

int cnt = 0;                          // variable is in Static Memory
void new_f() {
    std::cout << ++cnt << std::endl;
    new_f();
}

void memory_leak() {
    int* p = new int(5);
    std::cout << p << ' ' << *p << std::endl;
    // delete p;
}

void static_f() {
    static int x = 0;             // local static variable
    std::cout << ++x << std::endl;
    static_f();
}

int main() {
    int var = 5; // variable is in Stack

    // Stack Overflow
    if (false) {
        f(0);     // after 261879 Segmentation Fault
    }
        
    // Stack Overflow
    if (false) {
        new_f();  // after 523690 Segmentation Fault because of Location Of Return of function
    }
    
    // Stack Overflow
    if (false) {
        static_f();  // after 523690 Segmentation Fault because of Location Of Return of function
    }

    int* a = new int(5);           // allocated in Dynamic Memory
    std::cout << *a << std::endl;
    delete a;                      // if not to delete -> Memory Leak
    std::cout << std::endl;

    int* ptr = new int;
    std::cout << *ptr << std::endl; // UB
    *ptr = 5;
    std::cout << *ptr << std::endl;
    delete ptr;
    std::cout << *ptr << std::endl; // UB
    std::cout << std::endl;

    int* ptr_arr = new int[10];
    delete[] ptr_arr;

    int* p = new int(1);
    int* pp = new int(0);
    delete p, pp;                                 // only p will be deleted because of ( , ) has the lowest prioruty while parsing
    std::cout << *p << ' ' << *pp << std::endl;
    std::cout << std::endl;

    int* p1 = new int(1);
    int* p2 = new int(2);
    delete (p1, p2);                              // only p2 will be deleted because of (p1, p2) returns p2
    std::cout << *p1 << ' ' << *p2 << std::endl;
    std::cout << std::endl;

    // Memory Leak
    while (false) {
        memory_leak();
    }
}