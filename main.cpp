#include "stranalize.hpp"
#include <iostream>

int main()
{
    std::string str;

    std::cout << "Enter string to check:\n";

    std::getline(std::cin,str);

    stranalize::checkstr(str);
}
