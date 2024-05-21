#include <iostream>
#include "Str.h"

int main() {
    try {
        Str s1("Hello");
        Str s2 = s1;
        Str s3(" World");

        s1 += s3;

        std::cout << s1 << std::endl;
        std::cout << s2 << std::endl;

        for (int i = 0; i < strlen(s1); ++i) {
            std::cout << s1[i];
        }
        std::cout << std::endl;

        std::cout << s1[1] << std::endl;

        s1[1] = 'a';
        std::cout << s1 << std::endl;
        std::cout << s2 << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
