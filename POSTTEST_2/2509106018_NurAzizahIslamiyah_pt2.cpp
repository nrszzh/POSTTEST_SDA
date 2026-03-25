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
    {102, "Thomas Rail", "Jakarta", "Surabaya", 500000},
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
        cout << "Data masih kosong" << endl;
    } else {
        header();
        for (int i = 0; i < n; i++) {
            cout << "| " << setw(5) << left << (arr + i)->no_kereta 
                << "| " << setw(18) << left << (arr + i)->nama_kereta 
                << "| " << setw(15) << left << (arr + i)->asal 
                << "| " << setw(15) << left << (arr + i)->tujuan 
                << "| Rp" << setw(13) << left << (arr + i)->harga << " |" << endl;
        }
        cout << "================================================================================" << endl;
    }
}

void swap(kereta* a, kereta* b) {
    kereta temp = *a;
    *a = *b;
    *b = temp;
}

void linear_rute(kereta* arr, int n) {
    system("cls");
    if (n == 0) {
        cout << "Data kosong";
        getch();
        return;
    }
    jadwal(arr, n, "PENCARIAN RUTE");
    string asal, tujuan;
    cin.ignore();
    cout << endl;
    cout << "Asal     : ";
    getline(cin, asal);
    cout << "Tujuan   : ";
    getline(cin, tujuan);
    cout << endl;
    cout << "---- PROSES ITERASI ----" << endl;
    bool ketemu = false;
    for (int i = 0; i < n; i++) {
        cout << "Indeks " << i << ": ";
        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "Rute ditemukan" << endl;
            swap((arr + i), (arr + 0));
            ketemu = true;
            break;
        }
        cout << "Belum ketemu" << endl;
    }
    cout << "Rute tidak ditemukan" << endl;
    cout << "--- Pencarian Selesai ---";
    getch();
}

void jump_search(kereta* arr, int n) {
    int pil_searchno;
    do {
        system("cls");
        jadwal(arr, n, "PENCARIAN NOMOR KERETA");
        bool terurut = true;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i].no_kereta > arr[i+1].no_kereta) {
                terurut = false; break;
            }
        }

        cout << "Status Nomor kereta: " << (terurut ? "[TERURUT]" : "[ACAK]") << endl;
        cout << "1. Cari Nomor kereta" << endl;
        cout << "2. Urutkan Nomor kereta" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pil_searchno;

        if (pil_searchno == 1) {
            if (!terurut) {
                cout << "Pencarian Gagal, Data belum terurut.";
                getch();
            } else {
                int target;
                cout << "Nomor kereta yang dicari: ";
                cin >> target;

                int step = (int)sqrt((double)n); 
                int prev = 0; 
                cout << "--- FASE LOMPAT ---" << endl;
                while (arr[min(step, n) - 1].no_kereta < target) {
                    cout << "Indeks : " << min(step, n)-1 << " , No.Kereta : " << arr[min(step, n)-1].no_kereta << " -> LOMPAT" << endl;
                    prev = step;
                    step += (int)sqrt((double)n);
                    if (prev >= n)
                    break; 
                }

                cout << "--- FASE LINEAR ---";
                int batas = step;
                if (batas > n) batas = n; 
                bool ketemu = false;
                int idx_ketemu = -1;
                while (prev < batas) {
                    cout << "Indeks : " << prev << " , No.Kereta : " << arr[prev].no_kereta << endl;
                    if (arr[prev].no_kereta == target) {
                        cout << " Kereta ditemukan" << endl;
                        idx_ketemu = prev;
                        ketemu = true;
                        break;
                    }
                    cout << " Belum ketemu" << endl;
                    prev++;
                }

                if (ketemu) {
                    swap((arr + idx_ketemu), (arr + 0));
                    cout << "Kereta ditemukan pada indeks ke - " << idx_ketemu << "dan di swap ke urutan pertama";
                } else {
                    cout << "Nomor kereta tidak tersedia";
                }
                getch();
            }

        } else if (pil_searchno == 2) {
            for (int i = 0; i < n - 1; i++) {
                int idx_min = i;
                for (int j = i + 1; j < n; j++) {
                    if ((arr + j)->no_kereta < (arr + idx_min)->no_kereta) {
                        idx_min = j;
                    }
                }
                swap((arr + idx_min), (arr + i));
            }
            cout << "Nomor kereta berhasil diurutkan";
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

int main() {
    int pil;
    do {
        system("cls");
        cout << "==========================================================" << endl;
        cout << "|             SISTEM MANAJEMEN KERETA API                |" << endl;
        cout << "==========================================================" << endl;
        cout << "| 1. | Lihat Jadwal Kereta                               |" << endl;
        cout << "| 2. | Tambah Jadwal Kereta                              |" << endl;
        cout << "| 3. | Cari Rute                                         |" << endl;
        cout << "| 4. | Cari No kereta                                    |" << endl;
        cout << "| 5. | Urutkan Nama kereta A-Z                           |" << endl;
        cout << "| 6. | Urutkan Harga Termurah                            |" << endl;
        cout << "| 0. | Keluar                                            |" << endl;
        cout << "==========================================================" << endl;
        cout << "Pilihan: ";
        cin >> pil;

        switch (pil) {
            case 1: 
            jadwal(daftar_kereta, jml_kereta, "DAFTAR JADWAL");
            getch();
            break;

            case 2: {
                kereta* p = daftar_kereta + jml_kereta;
                system("cls");
                cout << "No kereta   : ";
                cin >> p->no_kereta;
                cin.ignore();
                cout << "Nama kereta : ";
                getline(cin, p->nama_kereta);
                cout << "Asal        : ";
                getline(cin, p->asal);
                cout << "Tujuan      : ";
                getline(cin, p->tujuan);
                cout << "Harga       : ";
                cin >> p->harga;
                jml_kereta++;
                break;
            }

            case 3: 
            linear_rute(daftar_kereta, jml_kereta);
            break;

            case 4: 
            jump_search(daftar_kereta, jml_kereta);
            break;


            