#include <iostream>
#include "string.hpp"

int main() {
  String str0; // конструктор по умолчанию
  String str01 = str0; // еще одна проверка на него
  String str1(10, 'c'); // конструктор от двух параметров
  String str2("23124121312312312312312"); // конструктор от сишной строки
  String str3 = str2; // конструктор копирования
  str3 = str1; // оператор присваивания
  str2.push_back('a'); // push_back
  str2.pop_back(); // pop_back
  str2 += "test"; // operator +=
  String plus_str = str2 + str3; // operator +
  auto test = str2.find("test"); // find
  std::cout << test;
  test = str2.rfind("test"); // rfind
  std::cout << test;
}