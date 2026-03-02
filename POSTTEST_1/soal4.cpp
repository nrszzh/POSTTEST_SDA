#include <iostream>
using namespace std;

void tukar(int* a, int* b) {
    int tempe = *a;
    *a = *b;
    *b = tempe;
}

int main() {
    int x, y;
    
    cout << "Masukkan nilai x: ";
    cin >> x;
    cout << "Masukkan nilai y: ";
    cin >> y;
    cout << "Sebelum ditukar: " << endl;
    cout << "x = " << x << ", y = " << y << endl;
    tukar(&x, &y);
    cout << "----------------" << endl;
    cout << "Setelah ditukar:" << endl;
    cout << "x = " << x << ", y = " << y << endl;
    return 0;
}


