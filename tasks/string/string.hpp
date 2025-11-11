#pragma once

#include <algorithm>
#include <compare>
#include <cstring>
#include <iostream>

class String {
  public:
    String() = default;
    String(char symbol);
    String(const char* other);
    String(size_t n, char symbol);
    String(const String& other);
    ~String();

    String& operator=(String other);

    bool operator==(const String& other) const;
    std::weak_ordering operator<=>(const String& other) const;

    char& operator[](int n);
    const char& operator[](int n) const;

    void push_back(char symbol);
    void pop_back();

    String& operator+=(char symbol);
    String& operator+=(const String& other);

    size_t length() const;
    size_t size() const;
    size_t capacity() const;

    char& front();
    const char& front() const;

    char& back();
    const char& back() const;

    char* data();
    const char* data() const;

    size_t find(const String& substr) const;
    size_t rfind(const String& substr) const;

    String substr(size_t start, size_t count) const;

    bool empty() const;

    void clear();
    void shrink_to_fit();

    void repr() const;
    
  private:
    size_t sz_ = 0;
    size_t cap_ = 0;
    char* arr_ = nullptr;

    static const size_t kNpos = static_cast<size_t>(-1);

    String(size_t n);

    void swap(String& other);
};

String operator+(const String& lhs, const String& rhs);

std::istream& operator>>(std::istream& istream, String& str);
std::ostream& operator<<(std::ostream& ostream, const String& str);


/////////////////////////////////////////////////
// Private Definitions
/////////////////////////////////////////////////
String::String(size_t n): sz_(n), cap_(sz_ == 0 ? 0 : sz_ + 1), arr_(sz_ == 0 ? nullptr : new char[cap_]) {
    if (sz_ != 0) {
        arr_[sz_] = '\0';
    }
}

void String::swap(String& other) {
    std::swap(sz_, other.sz_);
    std::swap(cap_, other.cap_);
    std::swap(arr_, other.arr_);
}

/////////////////////////////////////////////////
// Public Definitions
/////////////////////////////////////////////////
String::String(char symbol): String(static_cast<size_t>(1)) {
    arr_[0] = symbol;
}

String::String(const char* other): String(strlen(other)) {
    std::copy(other, other + sz_, arr_);
}

String::String(size_t n, char symbol): String(n) {
    std::fill(arr_, arr_ + sz_, symbol);
}

String::String(const String& other): String(other.sz_) {
    std::copy(other.arr_, other.arr_ + sz_, arr_);
}

String::~String() {
    delete[] arr_;
}

String& String::operator=(String other) {
    swap(other);
    return *this;
}

bool String::operator==(const String& other) const {
    if (sz_ != other.sz_) {
        return false;
    }

    if (arr_ == nullptr && other.arr_ == nullptr) {
        return true;
    }
    if (arr_ == nullptr || other.arr_ == nullptr) {
        return false;
    }

    return std::strcmp(arr_, other.arr_) == 0;
}

std::weak_ordering String::operator<=>(const String& other) const {
    int cmp = std::strcmp(arr_, other.arr_);
    if (cmp < 0) {
        return std::weak_ordering::less;
    }
    if (cmp > 0) {
        return std::weak_ordering::greater;
    }
    return std::weak_ordering::equivalent;
}

char& String::operator[](int n) {
    return arr_[n];
}

const char& String::operator[](int n) const {
    return arr_[n];
}

void String::push_back(char symbol) {
    *this += symbol;
}

void String::pop_back() {
    --sz_;
    arr_[sz_] = '\0';
}

String& String::operator+=(char symbol) {
    if (sz_ + 2 > cap_) {
        size_t new_cap = (sz_ == 0 ? 1 : sz_ * 2);
        String new_str(new_cap);

        std::copy(arr_, arr_ + sz_, new_str.arr_);
        new_str.sz_ = sz_;

        swap(new_str);
    }

    arr_[sz_] = symbol;
    sz_ += 1;
    arr_[sz_] = '\0';

    return *this;
}

String& String::operator+=(const String& other) {
    if (sz_ + other.sz_ + 1 > cap_) {
        size_t new_cap = std::max(sz_ * 2, sz_ + other.sz_);
        String new_str(new_cap);

        std::copy(arr_, arr_ + sz_, new_str.arr_);
        new_str.sz_ = sz_;

        swap(new_str);
    }

    std::copy(other.arr_, other.arr_ + other.sz_, arr_ + sz_);
    sz_ += other.sz_;

    return *this;
}

size_t String::length() const {
    return sz_;
}

size_t String::size() const {
    return sz_;
}

size_t String::capacity() const {
    return cap_;
}

char& String::front() {
    return arr_[0];
}

const char& String::front() const {
    return arr_[0];
}

char& String::back() {
    return arr_[sz_ - 1];
}

const char& String::back() const {
    return arr_[sz_ - 1];
}

char* String::data() {
    return arr_;
}

const char* String::data() const {
    return arr_;
}

size_t String::find(const String& substr) const {
    if (substr.sz_ > sz_) {
        return sz_;
    }

    const char* pos = std::strstr(arr_, substr.arr_);
    if (pos == nullptr) {
        return sz_;
    }

    return pos - arr_;
}

size_t String::rfind(const String& substr) const {
    if (substr.sz_ > sz_) {
        return sz_;
    }

    size_t ptr = sz_ - 1;
    size_t ptr_substr = substr.sz_ - 1;
    while (ptr != kNpos && ptr_substr != kNpos) {
        if (arr_[ptr] == substr.arr_[ptr_substr]) {
            --ptr_substr;
        } else {
            ptr_substr = substr.sz_ - 1;
        }
        --ptr;
    }

    if (ptr_substr == kNpos) {
        return ptr + 1;
    }

    return sz_;
}

String String::substr(size_t start, size_t count) const {
    String res(count);
    std::copy(arr_ + start, arr_ + start + count, res.arr_);
    return res;
}

bool String::empty() const {
    return sz_ == 0;
}

void String::clear() {
    sz_ = 0;
    if (arr_ != nullptr) {
        arr_[sz_] = '\0';
    }
}

void String::shrink_to_fit() {
    String res(sz_);
    std::copy(arr_, arr_ + sz_, res.arr_);
    swap(res);
}

/////////////////////////////////////////////////
// External Definitions
/////////////////////////////////////////////////

String operator+(const String& lhs, const String& rhs) {
    String copy = lhs;
    copy += rhs;
    return copy;
}

std::istream& operator>>(std::istream& istream, String& str) {
    str.clear();
    char symbol = '\0';
    while (istream.get(symbol) && std::isspace(symbol) == 0) {
        str += symbol;
    }

    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const String& str) {
    return ostream << str.data();
}


void String::repr() const {

    std::cout << "sz_: " << sz_ << std::endl;
    std::cout << "cap_: " << cap_ << std::endl;

    std::cout << "arr_: ";

    if (arr_ == nullptr) {
        std::cout << "nullptr";
        std::cout << std::endl << std::endl;
        return;
    }

    for (size_t i = 0; i != sz_; ++i) {
        std::cout << arr_[i];
    }
    if (arr_[sz_] == '\0') {
        std::cout << "\\0";
    }

    std::cout << std::endl << std::endl;
}