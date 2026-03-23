#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <conio.h>
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

                bool found = false;
                for (int i = iterasi; i < min(step, n); i++) {
                    cout << "[Linear] Indeks " << i << " : " << arr[i].no_kereta;
                    if (arr[i].no_kereta == target) {
                        cout << "Kereta Ditemukan" << endl;
                        swap((arr + i), (arr + 0));
                        found = true;
                        break;
                    }
                    cout << "Salah" << endl;
                }

                if (found) {
                    cout << endl;
                    cout << "Data ditemukan dan di-swap ke urutan pertama.";
                } else {
                    cout << endl;
                    cout << "Data tidak ditemukan.";
                }
                getch();
            }
        } else if (pil_searchno == 2) {
            sort_no(arr, n);
            cout << endl;
            cout << "Nomor kereta Berhasil Diurutkan";
            getch();
        }
    } while (pil_searchno != 0);
}

void merge(kereta arr[], int kiri, int mid, int kanan) {
    int n1 = mid - kiri + 1;
    int n2 = kanan - mid;
    kereta left[n1], right[n2];
    for (int i = 0; i < n1; i++) left[i] = arr[kiri + i];
    for (int j = 0; j < n2; j++) right[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = kiri;
    while (i < n1 && j < n2) {
        if (left[i].nama_kereta <= right[j].nama_kereta) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
}

void merge_nama(kereta* arr, int kiri, int kanan) {
    if (kiri < kanan) {
        int mid = kiri + (kanan - kiri) / 2;
        merge_nama(arr, kiri, mid);
        merge_nama(arr, mid + 1, kanan);
        merge(arr, kiri, mid, kanan);
    }
}


void selectionsort_harga(kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + idx)->harga)
            idx = j;
        }
        swap((arr + idx), (arr + i));
    }
}