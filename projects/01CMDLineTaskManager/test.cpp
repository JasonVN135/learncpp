#include <fstream>
#include <iostream>
#include <string>


int main()
{

    std::cout << "Enter some text\n";

    std::string stuff {};

    std::getline(std::cin, stuff);

    std::cout << "Here is the output: " << stuff << "\n";

    return 0;
}