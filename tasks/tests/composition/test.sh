#! /usr/bin/env bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

echo " "
echo "########## Begin testing $1 ##########"
echo " "

echo "########## Clang-tidy check ##########"
clang-tidy -extra-arg=-std=c++17 -quiet composition.cpp
if [[ ! $? -eq 0 ]]
then
  echo " "
  echo -e "${RED}Clang-tidy verification failed${NC}"
  exit 1
fi
echo -e "${GREEN}Clang-tidy achieved${NC}"
echo " "

echo "########## Сlang-format check ##########"
clang-format -i -style='{BasedOnStyle: Google, DerivePointerAlignment: false, PointerAlignment: Left, AlignOperands: true}' composition.cpp &&
git diff --ignore-submodules --color composition.cpp > diff &&
cat diff
if [[ -s diff ]]
then
  echo " "
  echo -e "${RED}Clang-format verification failed${NC}"
  exit 1
fi
echo -e "${GREEN}Clang-format achieved${NC}"
echo " "

echo "########## Build with clang ##########"
clang++ -std=c++20 -pedantic -Werror -Wextra -fsanitize=address -fsanitize=undefined composition.cpp -o main.out
if [[ ! -s main.out ]]
then
  echo " "
  echo -e "${RED}Couldn't be built with clang${NC}"
  exit 1
fi
echo -e "${GREEN}Build with clang achieved${NC}"
echo " "

echo "########## Running clang tests ##########"
./main.out 5 12 8 5 3 7 6 4 6 2>stderr.log 1>/dev/null < test.txt 
if [[ -s stderr.log ]]
then 
  echo " "
  echo -e "${RED}Test are not passed${NC}"
  echo "stderr:"
  cat stderr.log
  exit 1
fi
rm main.out
rm stderr.log
echo -e "${GREEN}Clang tests achieved${NC}"
echo " "


echo "########## Build with g++ ##########"
g++ -std=c++20 -pedantic -Werror -Wextra -fsanitize=address -fsanitize=undefined composition.cpp -o main.out
if [[ ! -s main.out ]]
then
  echo " "
  echo -e "${RED}Couldn't be built with g++${NC}"
  exit 1
fi
echo -e "${GREEN}Build with g++ achieved${NC}"
echo " "


echo "########## Running g++ tests ##########"
./main.out 5 12 8 5 3 7 6 4 6 2>stderr.log 1>/dev/null < test.txt 
if [[ -s stderr.log ]]
then 
  echo " "
  echo -e "${RED}Test are not passed${NC}"
  echo "stderr:"
  cat stderr.log
  exit 1
fi
rm stderr.log
echo -e "${GREEN}g++ tests achieved${NC}"
echo " "


echo "########## Valgrind check ##########"
valgrind --leak-check=yes --log-file=log.txt ./main.out 5 12 8 5 3 7 6 4 6 < test.txt 
echo "Valgrind log:"
cat log.txt
python3 valgrind_parser.py
if [[ ! $? -eq 0 ]]
then 
  echo " "
  echo -e "${RED}Who has stoled free?${NC}"
  exit 1
fi
echo -e "${GREEN}Valgrind achieved${NC}"
echo " "

echo " "
echo -e "${GREEN}All tests passed${NC}"
echo " "