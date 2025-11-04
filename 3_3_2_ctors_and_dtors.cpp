// 3.3.2. Contructors and destructors. String.

#include <iostream>

class String {
  public:
    // String();                               // Default Constructor
    String() = default;                        // Explicitly Declared Implicity Defined Default Constructor: more preferable than just Default Contructor
    String(size_t n, char c);
    String(std::initializer_list<char> list);  // Get it with value, but not with reference because of it's easy type

    ~String();
  
  private:
    char* arr = nullptr;
    size_t sz = 0;
    size_t cap = 0;
};

// String::String() {
//     std::cout << "Default constructor has been called!" << std::endl;
// }

String::String(size_t n, char c): arr(new char[n + 1]), sz(n), cap(n + 1) {
    std::fill(arr, arr + n, c);
    arr[sz] = '\0';

    std::cout << "Constructor  (size_t, char) -> String  has been called!" << std::endl;
}

String::String(std::initializer_list<char> list)
        : arr(new char[list.size() + 1])
        , sz(list.size())
        , cap(sz + 1) {
    std::copy(list.begin(), list.end(), arr);
    arr[sz] = '\0';

    std::cout << "Initializer list constructor has been called!" << std::endl;
}

String::~String() {
    delete[] arr;
}

int main() {
    String s1;
    String s2(5, 'e');
    String s3{5, 'e'};                 // :( Initializer List has been called, but not  (size_t, char) -> String
    String s4 = {'a', 'b', 'c', 'd'};

    // s4.~String();  // UB: double-free because desctrutor will be cakked automatically in the end of this scope
}