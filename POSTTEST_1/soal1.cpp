#include <iostream>
using namespace std;

int findMin(int arr[], int n) {
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    int n = 8;
    int fibonacci[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int min = fibonacci[0];
    int indeks = 0;
    for (int i = 1; i < n; i++) {
        if (fibonacci[i] < min) {
            min = fibonacci[i];
            indeks = i;
        }
    }
    cout << "Nilai Minimum       : " << min << endl;
    cout << "Indeks Nilai Minimum: " << indeks << endl;
    return 0;
}

// hitung manual Tmin(n), Tmax(n)
// ---------------------------------------------
// |Pseudocode        | Cost | (Tmin) | (Tmax) |
// -----------------  |------|--------|---------
// |min = A[0]        | c1   | 1      | 1      |
// |for i = 1 to n-1  | c2   | n      | n      |
// |if A[i] < min     | c3   | n-1    | n-1    |
// |min = A[i]        | c4   | 0      | n-1    |
// |return min        | c5   | 1      | 1      |
// ---------------------------------------------
// Tmin(n) = c1 + c2(n) + c3(n-1) + c5 = (c2+c3)n + (c1-c3+c5)
// Tmax(n) = c1 + c2(n) + c3(n-1) + c4(n-1) + c5 = (c2+c3+c4)n + (c1-c3-c4+c5)


// analisis Big-O
// Best Case (Tmin): terjadi jika nilai terkecil ada di indeks 0(ascending). 
// variabel min di dalam kode IF tidak akan dijalankan karena dia mengambil nilai 1 yang di
// indeks 0 yang dimana itu sudah memenuhi syarat pada kode if. kompleksitasnya O(n).
// Worst Case (Tmax): terjadi saat data diurutkan secara descending. variabel min 
// yang berada di dalam kode IF akan dijalankan sebanyak (n-1) kali. kompleksitasnya O(n)
