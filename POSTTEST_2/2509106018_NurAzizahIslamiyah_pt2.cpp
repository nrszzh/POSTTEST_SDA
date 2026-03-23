#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct kereta {
    int no_kereta;
    string nama_kereta;
    string asal;
    string tujuan;
    int harga;
};

kereta daftar_kereta[100] = {
    {101, "Thomas Rail", "Jakarta", "Surabaya", 500000},
    {112, "Emily Emerald", "Malang", "Solo", 600000},
    {110, "Titipo Little", "Yogyakarta", "Jakarta", 450000},
    {104, "Gordon Big", "Bandung", "Solo", 480000},
    {106, "Percy GreenLoco", "Surabaya", "Bogor", 250000}
};
int jml_kereta = 5;

void header() {
    cout << "================================================================================" << endl;
    cout << "| " << setw(5) << left << "ID" 
        << "| " << setw(18) << left << "Nama kereta" 
        << "| " << setw(15) << left << "Asal" 
        << "| " << setw(15) << left << "Tujuan" 
        << "| " << setw(15) << left << "Harga" << " |" << endl;
    cout << "================================================================================" << endl;
}

void jadwal(kereta* arr, int n, string judul) {
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

void swap(kereta* a, kereta* b) {
    kereta temp = *a;
    *a = *b;
    *b = temp;
}

void sort_no(kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->no_kereta < (arr + idx)->no_kereta)
            idx = j;
        }
        swap((arr + idx), (arr + i));
    }
}

void jump_search(kereta* arr, int n) {
    int pil_searchno;
    do {
        system("cls");
        jadwal(arr, n, "PENCARIAN NOMOR KERETA");
        bool terurut = true;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i].no_kereta > arr[i+1].no_kereta) { terurut = false; break; }
        }
        cout << endl;
        cout << "Status Nomor kereta: " << (terurut ? "[TERURUT]" : "[ACAK]") << endl;
        cout << "1. Cari Nomor kereta" << endl;
        cout << "2. Urutkan Nomor kereta " << endl;
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
                cout << "Nomor kereta yang dicari: ";
                cin >> target;

                int step = sqrt(n);
                int iterasi = 0;
                cout << "--- PROSES ITERASI ---" << endl;
                while (arr[min(step, n) - 1].no_kereta < target) {
                    cout << "[ JUMP ] Indeks " << min(step, n)-1 << " : " << arr[min(step, n)-1].no_kereta << " -> JUMP!" << endl;
                    iterasi = step;
                    step += sqrt(n);
                    if (iterasi >= n)
                    break;
                }

                