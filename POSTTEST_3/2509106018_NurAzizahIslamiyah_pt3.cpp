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

void swapPointer(kereta* a, kereta* b) {
    kereta temp = *a;
    *a = *b;
    *b = temp;
}

const int MAX_KAPASITAS = 100;

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
            ketemu = true;
            break;
        }
        cout << "Belum ketemu" << endl;
    }
    if (!ketemu) {
        cout << "Rute tidak ditemukan" << endl;
        }
        cout << "--- Pencarian Selesai ---";
        getch();
    }

void jump_search(kereta* &arrRef, int n) { 
    system("cls");
    //autosort
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) if (arrRef[j].no_kereta < arrRef[m].no_kereta) m = j;
        swapPointer(&arrRef[m], &arrRef[i]);
    }
    
    int target;
    cout << "Masukkan Nomor Kereta yang dicari: ";
    if (!(cin >> target)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    int step = sqrt(n);
    int prev = 0;
    while (arrRef[min(step, n) - 1].no_kereta < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
        break;
    }

    bool ketemu = false;
    for (int i = prev; i < min(step, n); i++) {
        if (arrRef[i].no_kereta == target) {
            cout << "\nKereta Ditemukan: " << arrRef[i].nama_kereta << " [" << arrRef[i].no_kereta << "]";
            ketemu = true;
            break;
        }
    }
    if (!ketemu)
    cout << "Data tidak ditemukan.";
    getch();
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
    kereta daftar_kereta[MAX_KAPASITAS] = {
        {102, "Thomas Rail", "Jakarta", "Surabaya", 500000},
        {112, "Emily Emerald", "Malang", "Solo", 600000},
        {110, "Titipo Little", "Yogyakarta", "Jakarta", 450000},
        {104, "Gordon Big", "Bandung", "Solo", 480000},
        {106, "Percy GreenLoco", "Surabaya", "Bogor", 250000}
    };
    int jml = 5;
    int pil;
    kereta* ptrData = daftar_kereta; 
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

                cout << endl;
                cout << "-- Jadwal ditambahkan --" << endl;
                getch();
                break;
            }

            case 3: 
            linear_rute(daftar_kereta, jml_kereta);
            break;

            case 4: 
            jump_search(ptrData, jml_kereta);
            break;


            case 5: 
                merge_nama(daftar_kereta, 0, jml_kereta - 1); 
                jadwal(daftar_kereta, jml_kereta, "HASIL MERGE SORT NAMA");
                getch(); 
                break;

            case 6: 
            selectionsort_harga(daftar_kereta, jml_kereta); 
            jadwal(daftar_kereta, jml_kereta, "HASIL SORT HARGA");
            getch(); 
            break;
        }

    } while (pil != 0);
    return 0;
}

//perbaikan
// 1. Jump search tidak auto sorting dapat menyebabkan data salah (-5)
// 2. Swap ke index-0 saat search merusak data (-5)
// 3. Tidak ada validasi kapasitas array (-2)
// 4. Tidak ada validasi input (-2)

// Saran:
// 1. Linear search nya jangan case sensitive soalnya rawan gagal
// 2. Global variable terlalu banyak
// 3. Selection sort tidak efisien
// 4. Merge sort pakai array lokal yang boros memori