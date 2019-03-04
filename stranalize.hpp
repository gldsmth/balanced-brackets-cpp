#pragma once

#include "mystack.hpp"

class stranalize
{
public:
    static void checkstr(std::string const &str);

private:
    static int checkstack(Stack<char> &strstack);
};
