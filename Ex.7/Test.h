#ifndef TEST_H
#define TEST_H

#include <iostream>

class Test {
public:
    int Val;
    Test() : Val(0) { std::cout << "Test created\n"; }
    ~Test() { std::cout << "Test destroyed\n"; }
};

#endif // TEST_H
