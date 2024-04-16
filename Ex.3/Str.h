#pragma once
#include <string.h>

class Str
{
    char* m_pszText;

public:
    Str() //Конструктор “по умолчанию” (default)
    {
        m_pszText = new char[1] { 0 };
    }

    Str(const char* p) //Конструктор инициализации z-строкой
    {
        if (p) {
            m_pszText = new char[strlen(p) + 1];
            strcpy_s(m_pszText, strlen(p) + 1, p);
        }
        else
            m_pszText = new char[1] { 0 };
    }

    Str(const Str& s) {
        m_pszText = new char[strlen(s.m_pszText) + 1];
        strcpy_s(m_pszText, strlen(s.m_pszText) + 1, s.m_pszText);
    }

    const Str& operator=(const Str& s) {
        if (&s == this) return *this;
        delete[] m_pszText;
        m_pszText = new char[strlen(s.m_pszText) + 1];
        strcpy_s(m_pszText, strlen(s.m_pszText) + 1, s.m_pszText);
        return *this;
    }

    Str& operator+=(const char* sz) {
        int len1 = strlen(m_pszText);
        int len2 = strlen(sz);
        char* newText = new char[len1 + len2 + 1];
        strcpy_s(newText, len1 + len2 + 1, m_pszText);
        strcat_s(newText, len1 + len2 + 1, sz);
        delete[] m_pszText;
        m_pszText = newText;
        return *this;
    }

    Str operator+(const char* sz) const {
        Str newStr(*this);
        newStr += sz;
        return newStr;
    }

    const char* getText() const {
        return m_pszText;
    }


    ~Str()
    {
        delete[] m_pszText;
    }
    operator const char* () const { return m_pszText; }
};
