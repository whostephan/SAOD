#pragma once
#include "_str.h"
#include <stdexcept>

class Str {
    _str* p;

public:
    Str(const char* s = "") : p(new _str(s)) {}

    ~Str() {
        p->release();
    }

    Str(const Str& other) : p(other.p) {
        p->add_ref();
    }

    Str& operator=(const Str& other) {
        if (this != &other) {
            other.p->add_ref();
            p->release();
            p = other.p;
        }
        return *this;
    }

    Str& operator+=(const Str& other) {
        size_t new_length = strlen(p->get_data()) + strlen(other.p->get_data()) + 1;
        char* new_data = new char[new_length];
        strcpy_s(new_data, new_length, p->get_data());
        strcat_s(new_data, new_length, other.p->get_data());
        p->release();
        p = new _str(new_data);
        delete[] new_data;
        return *this;
    }

    operator const char* () const {
        return p->get_data();
    }

    char operator[](int i) const {
        if (i < 0 || i >= strlen(p->get_data())) {
            throw std::out_of_range("Index out of range");
        }
        return p->get_data()[i];
    }

    char& operator[](int i) {
        if (i < 0 || i >= strlen(p->get_data())) {
            throw std::out_of_range("Index out of range");
        }
        if (p->get_ref_count() > 1) {
            p->release();
            p = new _str(p->get_data());
        }
        return p->get_data()[i];
    }
};
