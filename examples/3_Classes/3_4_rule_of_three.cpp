// 3.4. Assignment operator. Rule of three.

#include <iostream>

class String {
  public:
    // String();                               // Default Constructor
    String() = default;                        // Explicitly Declared Implicity Defined Default Constructor: more preferable than just Default Contructor
    String(size_t n, char c);
    String(std::initializer_list<char> list);  // Get it with value, but not with reference because of it's easy type
    String(const String& other);               // Copy Contructor

    String& operator=(String other);    // Assignment operator

    ~String();
  
  private:
    char* arr = nullptr;
    size_t sz = 0;
    size_t cap = 0;

    String(size_t n): arr(new char[n + 1]), sz(n), cap(n + 1) {  // Delegated Contructor: we will use it in other constructors
        arr[sz] = '\0';

        std::cout << "Delegated constructor has been called! -> ";
    }

    void swap(String& other);
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


// String& String::operator=(const String& other) {  // Too complex: it's better to use Copy and Swap Idiom
//     if (this == &other) return *this;             // to make this ability: str = str

//     delete[] arr;

//     sz = other.sz;
//     cap = other.cap;
//     arr = new char[other.cap];
//     std::copy(other.arr, other.arr + sz, arr);

//     return *this;
// }

// String& String::operator=(const String& other) {  // It can be shortened
//     String copy = other;
//     swap(copy);
//     return *this;
// }

String& String::operator=(String other) {  // Copy and Swap: it's good)
    swap(other);

    std::cout << "String has been copied!" << std::endl;

    return *this;
}

void String::swap(String& other) {         // Swap method for Copy and Swap
    std::swap(arr, other.arr);
    std::swap(sz, other.sz);
    std::swap(cap, other.cap);

    std::cout << "Swap method has been called!" << std::endl;
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

    // s4.~String();                  // UB: double-free because desctrutor will be cakked automatically in the end of this scope

    std::cout << "5: ";
    // String s5 = s4;                // UB: double-free, because of default copy constructor
    std::cout << std::endl;

    std::cout << "6: ";
    String s6 = s4;

    std::cout << "7: ";
    // String s7 = s7;               // UB: copy contructor will copy uninitialized fields of other string
    std::cout << std::endl;
    
    std::cout << "8: ";
    // s6 = s3;                      // UB: double-free, because of default assignment constructor
    std::cout << std::endl;

    std::cout << "9: ";
    s6 = s3;

}