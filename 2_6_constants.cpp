#include <iostream>

void f1(const std::string& str) {
    std::cout << "Done f1" << std::endl;
}

void f2(std::string& str) {
    std::cout << "Done f2" << std::endl;
}

int main() {
    {
        int x = 3;
        int y = 5;

        const int* p1 = &x;  // Pointer to CONSTANT INT : Also cast  int* -> const int*
        // *p = 10;          // CE
        p1 = &y;

        int* const p2 = &x;  // CONSTANT POINTER to int 
        *p2 = 10;
        // p2 = &y         
    }

    {
        f1("abcde");    // We can get rvalue as const string&
        // f2("abcde")  // CE: We cant' get rvalue as string& 
    }

    {
        // Lifetime Expansion
        const std::string& str = "very long str in dynamic memory";  // it will be deleted when main reference str is deleted
    }

    {
        // Lifetime Expansion
        int x = 0;
        const long long& d = x;
        std::cout << ++x << ' ' << d << std::endl; // 1 0
    }

}