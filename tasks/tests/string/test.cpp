#include <iostream>
#include <cassert>
#include <cstring>
#include <sstream>
#include "string.hpp"

// --- Конструкторы и базовые операции ---
void test_constructors() {
    String s1; // default
    assert(s1.empty());
    assert(s1.length() == 0);

    String s2(5, 'x');
    assert(s2.length() == 5);
    for (size_t i = 0; i < 5; ++i)
        assert(s2[i] == 'x');

    String s3("hello");
    assert(s3.length() == 5);
    assert(std::strcmp(s3.data(), "hello") == 0);

    String s4 = s3; // copy ctor
    assert(s4 == s3);

    String s5;
    s5 = s3; // assignment
    assert(s5 == s3);

    s5 = s5; // self-assignment
    assert(s5 == s3);
}

// --- Сравнение ---
void test_comparison() {
    String a("abc"), b("abc"), c("abd"), d("ab");

    assert(a == b);
    assert(!(a != b));
    assert(a < c);
    assert(c > a);
    assert(d < a);
    assert(a >= b);
    assert(a <= b);
}

// --- Индексация и front/back ---
void test_index_and_accessors() {
    String s("world");
    assert(s.front() == 'w');
    assert(s.back() == 'd');
    s.front() = 'W';
    s.back() = 'D';
    assert(std::strcmp(s.data(), "WorlD") == 0);

    const String cs("check");
    // проверка const front/back/operator[]
    const char& cf = cs.front();
    const char& cb = cs.back();
    const char& ci = cs[2];
    assert(cf == 'c');
    assert(cb == 'k');
    assert(ci == 'e');
    // проверка const data()
    const char* ptr = cs.data();
    assert(std::strcmp(ptr, "check") == 0);
}

// --- push_back / pop_back ---
void test_push_pop() {
    String s;

    for (int i = 0; i < 100; ++i) {
        s.push_back('a');
        assert(s.back() == 'a');
        assert(s.length() == static_cast<size_t>(i + 1));
        assert(s.data()[s.length()] == '\0');
    }

    size_t cap_after_push = s.capacity();
    assert(cap_after_push >= s.size());

    for (int i = 0; i < 50; ++i) {
        s.pop_back();
        assert(s.length() == static_cast<size_t>(100 - i - 1));
    }
    assert(s.length() == 50);
    assert(s.data()[s.length()] == '\0');
}

// --- Операторы + и += ---
void test_plus_and_plus_equal() {
    String s1("abc");
    String s2("def");
    String s3 = s1 + s2;
    assert(std::strcmp(s3.data(), "abcdef") == 0);

    String s4("x");
    s4 += s1;
    assert(std::strcmp(s4.data(), "xabc") == 0);

    s4 += 'z';
    assert(s4.back() == 'z');

    String s5 = 'Q' + s1;
    assert(s5 == "Qabc");

    String s6 = s1 + 'Z';
    assert(s6 == "abcZ");
}

// --- find и rfind ---
void test_find_and_rfind() {
    String s("abracadabra");
    assert(s.find("abra") == 0);
    assert(s.find("bra") == 1);
    assert(s.find("cad") == 4);
    assert(s.find("xyz") == s.length());
    assert(s.rfind("abra") == 7);
    assert(s.rfind("a") == 10);

    const String cs("aaaaa");
    assert(cs.find("aa") == 0);
    assert(cs.rfind("aa") == 3);
}

// --- substr ---
void test_substr() {
    String s("hello world");
    String sub = s.substr(6, 5);
    assert(sub == "world");
}

// --- clear, empty, shrink_to_fit ---
void test_clear_and_shrink() {
    String s("example");
    size_t old_cap = s.capacity();
    s.clear();
    assert(s.empty());
    assert(s.capacity() == old_cap); // память не освобождается

    s.shrink_to_fit();
    assert(s.capacity() == 0 || s.capacity() == s.length());
}

// --- Потоковый ввод/вывод ---
void test_io() {
    String s("input");
    std::cout << "Testing output: " << s << std::endl;
    // Проверим ввод через stringstream
    std::istringstream iss("streamtest");
    String t;
    iss >> t;
    assert(t == "streamtest");
}

// --- Проверка const-методов на длину и доступ ---
void test_const_methods() {
    const String s("constant");
    assert(s.size() == 8);
    assert(s.length() == 8);
    assert(!s.empty());
    const char* data = s.data();
    assert(std::strcmp(data, "constant") == 0);
    assert(s.front() == 'c');
    assert(s.back() == 't');
    assert(s[3] == 's');
}

// --- Проверка эффективности перевыделения ---
void test_memory_efficiency() {
    String s;
    size_t reallocs = 0;
    size_t prev_capacity = s.capacity();
    for (int i = 0; i < 10000; ++i) {
        s.push_back('x');
        if (s.capacity() != prev_capacity) {
            ++reallocs;
            prev_capacity = s.capacity();
        }
    }
    // амортизированное O(1) → мало перевыделений
    assert(reallocs < 50);
}

int main() {
    test_constructors();
    test_comparison();
    test_index_and_accessors();
    test_push_pop();
    test_plus_and_plus_equal();
    test_find_and_rfind();
    test_substr();
    test_clear_and_shrink();
    test_io();
    test_const_methods();
    test_memory_efficiency();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}