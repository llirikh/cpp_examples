#pragma once

#include <algorithm>
#include <cstring>
#include <iostream>

class String {
  public:
    String() = default;
    String(char);
    String(const char*);
    String(size_t, char);
    String(const String&);
    ~String();

    String& operator=(String);

    char& operator[](int);
    const char& operator[](int) const;

    bool operator==(const String&) const;
    bool operator!=(const String&) const;
    bool operator>(const String&) const;
    bool operator<(const String&) const;
    bool operator>=(const String&) const;
    bool operator<=(const String&) const;

    void push_back(char);
    void pop_back();

    String& operator+=(char);
    String& operator+=(const String&);

    size_t length() const;
    size_t size() const;
    size_t capacity() const;

    char& front();
    const char& front() const;

    char& back();
    const char& back() const;

    char* data();
    const char* data() const;

    size_t find(const String&) const;
    size_t rfind(const String&) const;

    String substr(size_t, size_t) const;

    bool empty() const;

    void clear();
    void shrink_to_fit();

    void repr() const;
    
  private:
    size_t sz_ = 0;
    size_t cap_ = 0;
    char* arr_ = nullptr;

    static const size_t kNpos = static_cast<size_t>(-1);

    String(size_t);

    void swap(String&);
};

String operator+(String, const String&);

std::istream& operator>>(std::istream&, String&);
std::ostream& operator<<(std::ostream&, const String&);


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
String::String(char c): String(static_cast<size_t>(1)) {
    arr_[0] = c;
}

String::String(const char* other): String(strlen(other)) {
    std::copy(other, other + sz_, arr_);
}

String::String(size_t n, char c): String(n) {
    std::fill(arr_, arr_ + sz_, c);
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

char& String::operator[](int n) {
    return arr_[n];
}

const char& String::operator[](int n) const {
    return arr_[n];
}

bool String::operator==(const String& other) const {
    if (sz_ != other.sz_) {
        return false;
    }

    return std::strcmp(arr_, other.arr_) == 0;
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}

bool String::operator>(const String& other) const {
    return std::strcmp(arr_, other.arr_) > 0;
}

bool String::operator<(const String& other) const {
    return other > *this;
}

bool String::operator>=(const String& other) const {
    return !(other > *this);
}

bool String::operator<=(const String& other) const {
    return !(*this > other);
}

void String::push_back(char c) {
    if (sz_ + 1 >= cap_) {
        String res(sz_ * 2 + 1);
        std::copy(arr_, arr_ + sz_, res.arr_);

        res[sz_] = c;
        res.sz_ = sz_ + 1;
        res[sz_ + 1] = '\0';

        swap(res);

        return;
    }

    arr_[sz_] = c;
    sz_ += 1;
    arr_[sz_] = '\0';
}

void String::pop_back() {
    --sz_;
    arr_[sz_] = '\0';
}

String& String::operator+=(char c) {
    push_back(c);
    return *this;
}

String& String::operator+=(const String& other) {
    for (size_t i = 0; i != other.size(); ++i) {
        push_back(other[i]);
    }
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
}

void String::shrink_to_fit() {
    String res(sz_);
    std::copy(arr_, arr_ + sz_, res.arr_);
    swap(res);
}


String operator+(String lhs, const String& rhs) {
    lhs += rhs;
    return lhs;
}

std::istream& operator>>(std::istream& is, String& str) {
    char c = '\0';
    while (is.get(c)) {
        str.push_back(c);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    return os << str.data();
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