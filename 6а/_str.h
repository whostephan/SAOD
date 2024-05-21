#pragma once
#include <string.h>
#include <stdexcept>

class _str {
    char* data;
    int ref_count;

public:
    _str(const char* s) : data(new char[strlen(s) + 1]), ref_count(1) {
        strcpy_s(data, strlen(s) + 1, s);
    }

    ~_str() {
        delete[] data;
    }

    void add_ref() {
        ++ref_count;
    }

    void release() {
        if (--ref_count == 0) {
            delete this;
        }
    }

    char* get_data() {
        return data;
    }

    const char* get_data() const {
        return data;
    }

    int get_ref_count() const {
        return ref_count;
    }
};
