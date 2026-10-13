#include "io.h"
#include <iostream>

int readNumber()
{

  std::cout << "Enter a number: ";
  int num{0};
  std::cin >> num;
  return num;
}

void writeAnswer(unsigned int answer)
{
  std::cout << "The sum of the two numbers is: " << answer << "\n";
}
