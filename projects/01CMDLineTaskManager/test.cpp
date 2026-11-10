#include <fstream>
#include <iostream>
#include <string>


int main()
{

    std::string str {};

    std::cout << "Number: ";

    std::cin >> str;

    std::cout << "Your string: " << str << "\n";

    int val {-1};

    val = std::stoi(str);

    std::cout << "Your number: " << val << "\n";
    return 0;
}