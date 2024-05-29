#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>

size_t naive(const std::string& str, const std::string& sub) {
    size_t n = str.size(), m = sub.size(), j = 0;
    for (size_t i = 0; i < n - m + 1; i++) {
        for (j = 0; j < m; j++) {
            if (str[i + j] != sub[j])
                break;
        }
        if (j == m)
            return i;
    }
    return std::string::npos;
}

void computeLPSArray(const std::string& sub, std::vector<int>& lps) {
    int length = 0;
    lps[0] = 0;
    int i = 1;
    while (i < sub.size()) {
        if (sub[i] == sub[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if (length != 0) {
                length = lps[length - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

size_t kmp(const std::string& str, const std::string& sub) {
    int n = str.size();
    int m = sub.size();
    std::vector<int> lps(m);
    computeLPSArray(sub, lps);
    int i = 0;
    int j = 0;
    while (i < n) {
        if (sub[j] == str[i]) {
            i++;
            j++;
        }
        if (j == m) {
            return i - j;
        }
        else if (i < n && sub[j] != str[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
    return std::string::npos;
}

size_t bm(const std::string& str, const std::string& sub) {
    int n = str.size();
    int m = sub.size();
    if (m == 0) return 0;

    std::vector<int> badChar(256, -1);
    for (int i = 0; i < m; i++) {
        badChar[(int)sub[i]] = i;
    }

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && sub[j] == str[shift + j]) {
            j--;
        }
        if (j < 0) {
            return shift;
        }
        else {
            shift += std::max(1, j - badChar[str[shift + j]]);
        }
    }
    return std::string::npos;
}

int main() {
    using namespace std;

    string str, sub = "was born in a small town called Sceptre";
    ifstream fin("engwiki_ascii.txt", ios::binary);
    if (!fin.is_open()) {
        cout << "not open!" << endl;
        return 0;
    }
    str.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    size_t n = 10;
    std::vector<size_t> times(n), indx(n);

    cout << "\nstd::find\n";
    for (size_t i = 0; i < n; i++) {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = str.find(sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::nanoseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++) {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nnaive\n";
    for (size_t i = 0; i < n; i++) {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = naive(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::nanoseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++) {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nKMP\n";
    for (size_t i = 0; i < n; i++) {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = kmp(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::nanoseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++) {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nBM\n";
    for (size_t i = 0; i < n; i++) {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = bm(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::nanoseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++) {
        cout << indx[i] << '\t' << times[i] << endl;
    }
}
