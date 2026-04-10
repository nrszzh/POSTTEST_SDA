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

struct transaksi {
    string nama_penumpang;
    string detail_tiket;
};

const int MAX_KAPASITAS = 100;
const int MAX_SISTEM = 10;

transaksi antrean[MAX_SISTEM];
int front = -1, rear = -1;

transaksi riwayat[MAX_SISTEM];
int top = -1;


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
            kereta *p = (arr + i);
            cout << "| " << setw(5) << left << p->no_kereta 
                << "| " << setw(18) << left << p->nama_kereta 
                << "| " << setw(15) << left << p->asal 
                << "| " << setw(15) << left << p->tujuan 
                << "| Rp" << setw(13) << left << p->harga << " |" << endl;
        }
        cout << "================================================================================" << endl;
    }
}

void swap(kereta* a, kereta* b) {
    kereta temp = *a;
    *a = *b;
    *b = temp;
}

bool case_sensitif(string a, string b) {
    if (a.length() != b.length()) return false;
    for (int i = 0; i < (int)a.length(); i++) {
        if (tolower(a[i]) != tolower(b[i])) return false;
    } return true;
}

void linear_rute(kereta* arr, int n) {
    system("cls");
    if (n == 0) {
        cout << "Data kosong";
        getch();
        return;
    }
    jadwal(arr, n, "CARI RUTE KEBEERANGKATAN");
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
        if (case_sensitif((arr + i)->asal, asal) && case_sensitif((arr + i)->tujuan, tujuan)) {
            cout << (arr+i)->nama_kereta << " (" << (arr+i)->no_kereta << ")" << endl;
            cout << "   -- Rute ditemukan --" << endl;
            ketemu = true;
            break;
        }
        cout << (arr+i)->nama_kereta << " (" << (arr+i)->no_kereta << ")" << endl;
        cout << "   -- Belum ketemu -- " << endl;
    }
    if (!ketemu)
        cout << "\n >> Rute tidak ditemukan" << endl;
        getch();
    }

void jump_search(kereta* &arrRef, int n) { 
    system("cls");
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) if (arrRef[j].no_kereta < arrRef[m].no_kereta) m = j;
        swap(&arrRef[m], &arrRef[i]);
    }
    
    int target;
    cout << "Masukkan Nomor Kereta:";
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

    for (int i = prev; i < min(step, n); i++) {
        if (arrRef[i].no_kereta == target) {
            cout << "\nKereta Ditemukan: " << arrRef[i].nama_kereta << " [" << arrRef[i].no_kereta << "]";
            getch();
            return;
        }
    }
    cout << "Data tidak ditemukan.";
    getch();
}

void merge(kereta arr[], int kiri, int mid, int kanan) {
    int n1 = mid - kiri + 1;
    int n2 = kanan - mid;
    kereta *left = new kereta[n1];
    kereta *right = new kereta[n2];
    for (int i = 0; i < n1; i++) left[i] = arr[kiri + i];
    for (int j = 0; j < n2; j++) right[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = kiri;
    while (i < n1 && j < n2) {
        if (left[i].nama_kereta <= right[j].nama_kereta) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
    delete[] left;
    delete[] right;
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
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + min_idx)->harga)
            min_idx = j;
        }
        if (min_idx != i)
        swap((arr + min_idx), (arr + i));
    }
}

void enqueue(string nama, string info) {
    if (rear == MAX_SISTEM - 1)
    cout << "Antrian Penuh" << endl;
    else {
        if (front == -1) front = 0;
        rear++;
        transaksi* p = (antrean + rear);
        p->nama_penumpang = nama;
        p->detail_tiket = info;
        cout << "Penumpang berhasil di tambahkan ke antrian." << endl;
    }
}

void dequeue() {
    if (front == -1 || front > rear)
    cout << "Antrian kosong" << endl;
    else {
        transaksi proses = *(antrean + front);
        if (top < MAX_SISTEM - 1) {
            top++;
            *(riwayat + top) = proses;
            cout << "\n Berhasil, Tiket: " << proses.nama_penumpang << endl;
        }
        front++;
        if (front > rear) {
            front = -1; rear = -1; }
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
    int jml_kereta = 5;
    int pil;
    kereta* ptrData = daftar_kereta; 

    do {
        system("cls");
        cout << "==========================================================" << endl;
        cout << "|             SISTEM MANAJEMEN KERETA API                |" << endl;
        cout << "==========================================================" << endl;
        cout << "| 1. | Lihat Jadwal Kereta                               |" << endl;
        cout << "| 2. | Tambah Jadwal Kereta                              |" << endl;
        cout << "| 3. | Cari Rute Kereta                                  |" << endl;
        cout << "| 4. | Cari Nomor Kereta                                 |" << endl;
        cout << "| 5. | Urutkan Nama kereta A-Z                           |" << endl;
        cout << "| 6. | Urutkan Harga Termurah                            |" << endl;
        cout << "| 0. | Keluar                                            |" << endl;
        cout << "==========================================================" << endl;
        cout << "Pilihan: ";
        if (!(cin >> pil)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (pil) {
            case 1: 
            jadwal(ptrData, jml_kereta, "JADWAL KEBERANGKATAN KERETA");
            getch();
            break;

            case 2: 
            if (jml_kereta < MAX_KAPASITAS) {
                kereta* p = (ptrData + jml_kereta);
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
            } else {
                cout << "-- Kapasitas penuh --" << endl;
                getch();
            }
                break;

            case 3: 
            linear_rute(ptrData, jml_kereta);
            break;

            case 4: 
            jump_search(ptrData, jml_kereta);
            break;


            case 5: 
                merge_nama(ptrData, 0, jml_kereta - 1); 
                jadwal(ptrData, jml_kereta, "HASIL SORT NAMA");
                getch(); 
                break;

            case 6: 
            selectionsort_harga(ptrData, jml_kereta); 
            jadwal(ptrData, jml_kereta, "HASIL SORT HARGA");
            getch(); 
            break;
        }

    } while (pil != 0);
    return 0;
}
