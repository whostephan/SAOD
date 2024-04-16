#include <iostream>
#include "complex.h"

int main()
{
    Complex* pc;

    pc = new Complex(1);
    std::cout << *pc << std::endl;
    delete pc;

    pc = new Complex(1, 2);
    std::cout << *pc << std::endl;
    delete pc;

    pc = new Complex(3, 4);
    std::cout << *pc << std::endl;

    std::cout << "Re: " << pc->Re << ", Im: " << pc->Im << std::endl;

    delete pc;

    Complex* arr = new Complex[3];
    arr[0] = Complex(1, 2);
    arr[1] = Complex(3, 4);
    arr[2] = Complex(5, 6);

    for (int i = 0; i < 3; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;

    // pc[1].Re - это действительная часть второго элемента массива, на который указывает указатель pc

    delete[] arr;

    return 0;
}

