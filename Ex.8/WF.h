#ifndef WF_H
#define WF_H

#include <vector>
#include <string>
#include <stdexcept>
#include <istream>

using namespace std;

class WF {
    int* pm; // Pointer to the matrix
    int M, N; // Dimensions of the matrix
    vector<string> prevVersion, curVersion;

public:
    WF();
    ~WF();

    int Rows() const;
    int Columns() const;
    int Get(int i, int j) const;
    void Set(int i, int j, int val);
    int Distance() const;
    void Compare(istream& prev, istream& current);
    string Prescription() const;
    string PrevLine(int i) const;
    string CurLine(int i) const;
};

#endif // WF_H
