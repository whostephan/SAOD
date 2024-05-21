#include "WF.h"
#include <algorithm>

WF::WF() : pm(nullptr), M(0), N(0) {}

WF::~WF() {
    delete[] pm;
}

int WF::Rows() const {
    return M;
}

int WF::Columns() const {
    return N;
}

int WF::Get(int i, int j) const {
    if (i < 0 || i >= M || j < 0 || j >= N) {
        throw out_of_range("Get: Index out of range");
    }
    return pm[i * N + j];
}

void WF::Set(int i, int j, int val) {
    if (i < 0 || i >= M || j < 0 || j >= N) {
        throw out_of_range("Set: Index out of range");
    }
    pm[i * N + j] = val;
}

int WF::Distance() const {
    return Get(M - 1, N - 1);
}

void WF::Compare(istream& prev, istream& current) {
    char buf[512];

    while (prev.good()) {
        prev.getline(buf, sizeof(buf));
        prevVersion.push_back(buf);
    }
    while (current.good()) {
        current.getline(buf, sizeof(buf));
        curVersion.push_back(buf);
    }

    M = static_cast<int>(prevVersion.size()) + 1;
    N = static_cast<int>(curVersion.size()) + 1;

    pm = new int[M * N];

    for (int i = 0; i < M; ++i) {
        Set(i, 0, i);
    }

    for (int j = 0; j < N; ++j) {
        Set(0, j, j);
    }

    for (int i = 1; i < M; ++i) {
        for (int j = 1; j < N; ++j) {
            int cost = (prevVersion[i - 1] == curVersion[j - 1]) ? 0 : 1;
            Set(i, j, min({ Get(i - 1, j) + 1, Get(i, j - 1) + 1, Get(i - 1, j - 1) + cost }));
        }
    }
}

string WF::Prescription() const {
    int i = M - 1, j = N - 1;
    string prescription;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && Get(i, j) == Get(i - 1, j - 1) + ((prevVersion[i - 1] == curVersion[j - 1]) ? 0 : 1)) {
            if (prevVersion[i - 1] != curVersion[j - 1]) {
                prescription = "r" + prescription;
            }
            else {
                prescription = "." + prescription;
            }
            i--; j--;
        }
        else if (i > 0 && Get(i, j) == Get(i - 1, j) + 1) {
            prescription = "d" + prescription;
            i--;
        }
        else {
            prescription = "i" + prescription;
            j--;
        }
    }

    return prescription;
}

string WF::PrevLine(int i) const {
    if (i < 0 || i >= static_cast<int>(prevVersion.size())) {
        throw out_of_range("PrevLine: Index out of range");
    }
    return prevVersion[i];
}

string WF::CurLine(int i) const {
    if (i < 0 || i >= static_cast<int>(curVersion.size())) {
        throw out_of_range("CurLine: Index out of range");
    }
    return curVersion[i];
}
