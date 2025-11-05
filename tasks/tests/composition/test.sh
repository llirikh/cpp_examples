#! /usr/bin/env bash

echo "begin testing $1"

echo "clang-tidy check"
clang-tidy -extra-arg=-std=c++17 -quiet composition.cpp
if [[ ! $? -eq 0 ]]
then 
  echo "Проверка clang-tidy не пройдена"
  exit 1
fi

echo "clang-format check"
clang-format -i -style='{BasedOnStyle: Google, DerivePointerAlignment: false, PointerAlignment: Left, AlignOperands: true}' composition.cpp &&
git diff --ignore-submodules --color composition.cpp > diff &&
cat diff
if [[ -s diff ]]
then 
  echo "Проверка clang-format не пройдена"
  exit 1
fi
echo "clang-format achieved"


echo "Начинаем билдить"

echo "Build with clang"
clang++-13 -std=c++20 -pedantic -Werror -Wextra -fsanitize=address -fsanitize=undefined composition.cpp -o main.out
if [[ ! -s main.out ]]
then 
  echo "Пранк clang'ом не пройден"
  exit 1
fi
echo "Build with clang achieved"

echo "Running clang tests"
./main.out 5 12 8 5 3 7 6 4 6 2>stderr.log 1>/dev/null < test.txt 
if [[ -s stderr.log ]]
then 
  echo "Тесты не пройдены. stderr:"
  cat stderr.log
  exit 1
fi
rm main.out
rm stderr.log
echo "Clang tests achieved"


echo "Build with g++"
g++-11 -std=c++20 -pedantic -Werror -Wextra -fsanitize=address -fsanitize=undefined composition.cpp -o main.out
if [[ ! -s main.out ]]
then 
  echo "Пранк g++ не пройден"
  exit 1
fi
echo "Build with g++ achieved"


echo "Running g++ tests"
./main.out 5 12 8 5 3 7 6 4 6 2>stderr.log 1>/dev/null < test.txt 
if [[ -s stderr.log ]]
then 
  echo "Тесты не пройдены. stderr:"
  cat stderr.log
  exit 1
fi
rm stderr.log
echo "g++ tests achieved"


echo "Попробуем valgrind!"
valgrind --leak-check=yes --log-file=log.txt ./main.out 5 12 8 5 3 7 6 4 6 < test.txt 
echo "Valgrind log:"
cat log.txt
python3 valgrind_parser.py
if [[ ! $? -eq 0 ]]
then 
  echo "А кто украл free?"
  exit 1
fi
echo "Valgrind achieved"

echo "Вы потрясающие! ^)"