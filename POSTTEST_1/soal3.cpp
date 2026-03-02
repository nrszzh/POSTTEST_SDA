#include <iostream>
using namespace std;

int bil_prima[7] = {2, 3, 5, 7, 11, 13, 17};
int n = 7;

void reverseArray(int* arr, int n) {
    int* ptr_awal = arr;
    int* ptr_akhir = arr + n - 1;

    while (ptr_awal < ptr_akhir) {
        int temp = *ptr_awal;
        *ptr_awal = *ptr_akhir;
        *ptr_akhir = temp;
        ptr_awal++;
        ptr_akhir--;
    }
}

int main() {
    cout << "Array sebelum dibalik: ";
    for (int i = 0; i < n; i++) cout << bil_prima[i] << " "; 
    reverseArray(bil_prima, n);
    cout << endl;
    cout << "Array sesudah dibalik: ";
    for (int i = 0; i < n; i++) cout << bil_prima[i] << " ";
    cout << endl;
    cout << "Alamat memori elemen:" << endl;
    for (int i = 0; i < n; i++) {
        cout << bil_prima[i] 
            << " -> " << &bil_prima[i] << endl;
    }
    return 0;
}
