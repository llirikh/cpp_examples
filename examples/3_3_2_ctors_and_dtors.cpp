// 3.3.2. Contructors and destructors. String.

#include <iostream>

class String {
  public:
    // String();                               // Default Constructor
    String() = default;                        // Explicitly Declared Implicity Defined Default Constructor: more preferable than just Default Contructor
    String(size_t n, char c);
    String(std::initializer_list<char> list);  // Get it with value, but not with reference because of it's easy type
    String(const String& other);               // Copy Contructor

    ~String();
  
  private:
    char* arr = nullptr;
    size_t sz = 0;
    size_t cap = 0;

    String(size_t n): arr(new char[n + 1]), sz(n), cap(n + 1) {  // Delegated Contructor: we will use it in other constructors
        arr[sz] = '\0';

        std::cout << "Delegated constructor has been called! -> ";
    }
};

// String::String() {
//     std::cout << "Default constructor has been called!" << std::endl;
// }

String::String(size_t n, char c): String(n) {
    std::fill(arr, arr + n, c);

    std::cout << "Constructor  (size_t, char) -> String  has been called!" << std::endl;
}

String::String(std::initializer_list<char> list): String(list.size()) {
    std::copy(list.begin(), list.end(), arr);

    std::cout << "Initializer list constructor has been called!" << std::endl;
}

String::String(const String& other): String(other.sz) {
    std::copy(other.arr, other.arr + sz, arr);

    std::cout << "Copy constructor has been called!" << std::endl;
} 

String::~String() {
    delete[] arr;
}

int main() {
    std::cout << "1: ";
    String s1;
    std::cout << std::endl;

    std::cout << "2: ";
    String s2(5, 'e');

    std::cout << "3: ";
    String s3{5, 'e'};                 // :( Initializer List has been called, but not  (size_t, char) -> String

    std::cout << "4: ";
    String s4 = {'a', 'b', 'c', 'd'};

    // s4.~String();  // UB: double-free because desctrutor will be cakked automatically in the end of this scope

    // String s5 = s4; // UB: double-free, because of default copy constructor

    std::cout << "6: ";
    String s6 = s4;

    std::cout << "7: ";
    String s7 = s7; // UB: copy contructor will copy uninitialized fields of other string
}