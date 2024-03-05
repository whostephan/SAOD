#include <iostream>
using namespace std;


void Swap(int* pa, int* pb) {
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

int main()
{
    /*int x = 3;
    int* p = &x;
    cout << x << ' ' << *p << ' ' << p << endl;
    p++;
    cout << p << endl;
    cout << p - &x << endl;

    typedef unsigned char byte;
    byte* pb = (byte*)--p;
    for (byte* pt = pb; pt - pb < sizeof(int); pt++)
        cout << (int)*pt << ' ';
    cout << endl;
    */

    int a = 3, b = 5;

    cout << "Before swap: a = " << a << ", b = " << b << endl;

    Swap(&a, &b);

    cout << "After swap: a = " << a << ", b = " << b << endl;

    return 0;
}


