#include <iostream>
#include <fstream>
#include "WF.h"

using namespace std;

int main() {
    ifstream prev("prev.txt");
    ifstream current("cur.txt");

    if (!prev.is_open() || !current.is_open()) {
        cerr << "Error opening files" << endl;
        return 1;
    }

    WF wf;
    wf.Compare(prev, current);

    cout << "Distance: " << wf.Distance() << endl;

    string prescription = wf.Prescription();
    cout << "Prescription: " << prescription << endl;

    int i = 0, j = 0;
    for (char c : prescription) {
        switch (c) {
        case '.':
            i++; j++;
            break;
        case 'r':
            cout << "rrr " << wf.PrevLine(i++) << " -> " << wf.CurLine(j++) << endl;
            break;
        case 'd':
            cout << "<<< " << wf.PrevLine(i++) << endl;
            break;
        case 'i':
            cout << ">>> " << wf.CurLine(j++) << endl;
            break;
        }
    }

    return 0;
}
