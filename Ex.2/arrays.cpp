#include <iostream>
using namespace std;

void rotate(int a[], int n, bool clockwise = false) {
    if (clockwise) {
        int x = a[n - 1];
        for (int i = n - 1; i > 0; i--)
            a[i] = a[i - 1];
        a[0] = x;
    }
    else {
        int x = a[0];
        for (int i = 1; i < n; i++)
            a[i - 1] = a[i];
        a[n - 1] = x;
    }
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Before rotation: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl;

    rotate(arr, n, true);
    cout << "After clockwise rotation: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl;

    rotate(arr, n);
    cout << "After counter-clockwise rotation: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl;

    return 0;
}






