#include <iostream>
using namespace std;

struct mahasiswa{
    string nama;
    string nim;
    float ipk;
};

int main() {
    const int n = 5;
    mahasiswa data[n];

    for (int i = 0; i < n; i++) {
        cout << "Data mahasiswa " << i + 1 << endl;
        cout << "Nama: "; 
        getline(cin >> ws, data[i].nama);
        cout << "NIM : "; 
        cin >> data[i].nim;
        cout << "IPK : "; 
        cin >> data[i].ipk;
    }

    int tertinggi = 0;
    for (int i = 1; i < n; i++) {
        if (data[i].ipk > data[tertinggi].ipk) {
            tertinggi = i;
        }
    }
    cout << endl;
    cout << "Mahasiswa dengan IPK tertinggi:" << endl;
    cout << "Nama : " << data[tertinggi].nama << endl;
    cout << "NIM  : " << data[tertinggi].nim << endl;
    cout << "IPK  : " << data[tertinggi].ipk << endl;
    return 0;
}

