
#include <iostream>


int main() {

    int x = 0;
    int y = ++x * x++;
    std::cout << y << "\n";
}