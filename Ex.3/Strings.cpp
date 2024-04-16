#include <iostream>
#include <string>
#include "Str.h"
using namespace std;

void Test(const Str& s) {}

int main()
{
    Str s1("Hello, ");
    Str s2("world!");
    Str s3 = s1 + s2.getText();
    std::cout << s3.getText() << std::endl;
    return 0;
}

