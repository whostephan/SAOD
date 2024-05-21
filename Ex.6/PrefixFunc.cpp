#include <iostream>
#include <cstdlib>
#include <ctime>
#include "PF.h"

// Функция для генерации случайной строки
void generateRandomString(char* s, int length, int alphabetSize) {
    for (int i = 0; i < length; ++i) {
        s[i] = 'a' + rand() % alphabetSize;
    }
    s[length] = '\0';
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    PF pf;
    pf.Init("rakaratrakarakarakatakarakara");

    for (int i = 0; i < (int)pf; ++i) {
        std::cout << pf[i];
    }
    std::cout << std::endl;

    const int lengths[] = { 100, 200, 400, 800, 1600 };
    const int alphabetSizes[] = { 2, 4, 8, 16, 32 };

    for (int alphabetSize : alphabetSizes) {
        for (int length : lengths) {
            char* s = new char[length + 1];
            generateRandomString(s, length, alphabetSize);

            pf.Init(s);

            std::cout << "Length: " << length
                << ", Alphabet Size: " << alphabetSize
                << ", Comparisons: " << pf.CmpCount()
                << std::endl;

            delete[] s;
        }
    }

    return 0;
}
