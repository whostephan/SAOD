#ifndef PF_H
#define PF_H

#include <iostream>
#include <stdexcept>
#include <cstring>

class PF {
private:
    int* pv; 
    int n; 
    int cmpCount; 

public:

    PF() : pv(nullptr), n(0), cmpCount(0) {}


    ~PF() {
        delete[] pv;
    }


    PF(const PF& other) : pv(new int[other.n]), n(other.n), cmpCount(other.cmpCount) {
        std::copy(other.pv, other.pv + n, pv);
    }


    PF& operator=(const PF& other) {
        if (this != &other) {
            delete[] pv;
            n = other.n;
            cmpCount = other.cmpCount;
            pv = new int[n];
            std::copy(other.pv, other.pv + n, pv);
        }
        return *this;
    }


    void Init(const char* s) {
        if (pv) {
            delete[] pv;
        }
        n = strlen(s);
        pv = new int[n];
        cmpCount = 0;


        pv[0] = 0;
        int k = 0;
        for (int i = 1; i < n; ++i) {
            while (k > 0 && s[k] != s[i]) {
                k = pv[k - 1];
                ++cmpCount;
            }
            if (s[k] == s[i]) {
                ++k;
                ++cmpCount;
            }
            pv[i] = k;
        }
    }


    operator int() const {
        return n;
    }


    int operator[](int i) const {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range");
        }
        return pv[i];
    }

    int CmpCount() const {
        return cmpCount;
    }
};

#endif
