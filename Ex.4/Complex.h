#pragma once
#include <iostream>
#include <cmath>


class Complex
{
public:
    double Re;
    double Im;

    Complex(double re = 0, double im = 0) : Re(re), Im(im) {}

    Complex operator+(const Complex& c) const {
        return Complex(Re + c.Re, Im + c.Im);
    }

    Complex operator-(const Complex& c) const {
        return Complex(Re - c.Re, Im - c.Im);
    }

    Complex operator*(const Complex& c) const {
        return Complex(Re * c.Re - Im * c.Im, Re * c.Im + Im * c.Re);
    }

    Complex operator/(const Complex& c) const {
        double denominator = c.Re * c.Re + c.Im * c.Im;
        return Complex((Re * c.Re + Im * c.Im) / denominator, (Im * c.Re - Re * c.Im) / denominator);
    }

    Complex Conjugate() const {
        return Complex(Re, -Im);
    }

    double Mod() const {
        return std::sqrt(Re * Re + Im * Im);
    }

    double Arg() const {
        if (Re == 0 && Im == 0) {
            return 0;
        }
        if (Re > 0) {
            return std::atan(Im / Re);
        }
        if (Re < 0 && Im >= 0) {
            return std::atan(Im / Re) + std::atan(1) * 2;
        }
        if (Re < 0 && Im < 0) {
            return std::atan(Im / Re) - std::atan(1) * 2;
        }
        if (Re == 0 && Im > 0) {
            return std::atan(1) * 2;
        }
        if (Re == 0 && Im < 0) {
            return -std::atan(1) * 2;
        }
    }

};

inline std::ostream& operator << (std::ostream& o, const Complex& c) {
    return o << '(' << c.Re << ", " << c.Im << ')';
}


