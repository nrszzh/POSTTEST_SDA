#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Kereta {
    int no_kereta;
    string nama_kereta;
    string asal;
    string tujuan;
    int harga;
};

Kereta daftar_kereta[100] = {
    {101, "Thomas Rail", "Jakarta", "Surabaya", 500000},
    {112, "Emily Emerald", "Malang", "Solo", 600000},
    {110, "Titipo Little", "Yogyakarta", "Jakarta", 450000},
    {104, "Gordon Big", "Bandung", "Solo", 480000},
    {106, "Percy GreenLoco", "Surabaya", "Bogor", 250000}
};
int jml_kereta = 5;

void swap(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void header() {
    cout << "================================================================================\n";
    cout << "| " << setw(5) << left << "ID" 
        << "| " << setw(18) << left << "Nama Kereta" 
        << "| " << setw(15) << left << "Asal" 
        << "| " << setw(15) << left << "Tujuan" 
        << "| " << setw(15) << left << "Harga" << " |" << endl;
    cout << "================================================================================\n";
}

void jadwal(Kereta* arr, int n, string judul) {
    system("cls");
    cout << ">>> " << judul << " <<<" << endl;
    if (n == 0) {
        cout << "Data masih kosong.\n";
    } else {
        header();
        for (int i = 0; i < n; i++) {
            cout << "| " << setw(5) << left << (arr + i)->no_kereta 
                << "| " << setw(18) << left << (arr + i)->nama_kereta 
                << "| " << setw(15) << left << (arr + i)->asal 
                << "| " << setw(15) << left << (arr + i)->tujuan 
                << "| Rp" << setw(13) << left << (arr + i)->harga << " |" << endl;
        }
        cout << "================================================================================\n";
    }
}

void sort_no(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->no_kereta < (arr + idx)->no_kereta)
            idx = j;
        }
        swap((arr + idx), (arr + i));
    }
}

void jump_search(Kereta* arr, int n) {
    int pil_searchno;
    do {
        system("cls");
        jadwal(arr, n, "PENCARIAN NOMOR KERETA");
        bool terurut = true;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i].no_kereta > arr[i+1].no_kereta) { terurut = false; break; }
        }
        cout << endl;
        cout << "Status Nomor Kereta: " << (terurut ? "[TERURUT]" : "[ACAK]") << endl;
        cout << "1. Cari Nomor Kereta" << endl;
        cout << "2. Urutkan Nomor Kereta " << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pil_searchno;

        if (pil_searchno == 1) {
            if (!terurut) {
                cout << endl;
                cout << "Pencarian Gagal, Data belum terurut.";
                getch();
            } else {
                int target;
                cout << "Nomor Kereta yang dicari: ";
                cin >> target;

                int step = sqrt(n);
                int prev = 0;
                cout << "--- PROSES ITERASI ---" << endl;
                while (arr[min(step, n) - 1].no_kereta < target) {
                    cout << "[ JUMP ] Indeks " << min(step, n)-1 << " : " << arr[min(step, n)-1].no_kereta << " -> JUMP!" << endl;
                    prev = step;
                    step += sqrt(n);
                    if (prev >= n) break;
                }