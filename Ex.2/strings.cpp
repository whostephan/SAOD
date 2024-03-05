#include <iostream>
using namespace std;

int string_copy(char* d, const char* s) {
    while (*s != '\0') {
        *d = *s;
        d++;
        s++;
    }
    *d = '\0';
    return 0;
}

int len(const char* s) {
    int length = 0;
    while (*s != '\0') {
        length++;
        s++;
    }
    return length;
}

int compare(const char* s, const char* t) {
    while (*s && *t && *s == *t) {
        s++;
        t++;
    }
    return *s - *t;
}

int main()
{
    char str[] = "Hello!";
    char t[32];

    std::cout << "String length: " << strlen(str) << ", Array size: " << sizeof(str) << std::endl;

    char* pd = t;
    const char* ps = str;
    while (*pd++ = *ps++);

    std::cout << "Copied string: " << t << std::endl;

    char t2[32];
    string_copy(t2, str);
    std::cout << "Copied string using function: " << t2 << std::endl;

    const char* s1 = "banana";
    const char* s2 = "apple";

    std::cout << "Length of string s1: " << len(s1) << std::endl;
    std::cout << "Comparison result: " << compare(s1, s2) << std::endl;

    return 0;
}

