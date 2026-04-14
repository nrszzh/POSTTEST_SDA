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
    transaksi* next;
};

transaksi* front = nullptr;
transaksi* rear = nullptr;
transaksi* top = nullptr;

const int MAX_KAPASITAS = 100;
const int MAX_SISTEM = 10;

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
    transaksi* baru = new transaksi;
    baru->nama_penumpang = nama;
    baru->detail_tiket = info;
    baru->next = nullptr;

    if (front == nullptr) {
        front = rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }
    cout << "Penumpang berhasil ditambahkan." << endl;
}

void dequeue() {
    if (front == nullptr) {
        cout << "\n Antrean Kosong." << endl;
        return;
    }
    transaksi *temp = front;
    cout << "\n Penumpang    : " << temp->nama_penumpang << endl;
    cout << " Detail Tiket : " << temp->detail_tiket << endl;
    cout << "\n >> Berhasil diproses, Tiket: " << temp->nama_penumpang << " [SELESAI]" << endl;

    transaksi* riwayat_baru = new transaksi;
    riwayat_baru->nama_penumpang = temp->nama_penumpang;
    riwayat_baru->detail_tiket = temp->detail_tiket;
    riwayat_baru->next = top;
    top = riwayat_baru; //push riwayat setelh proses antrean

    front = front->next;
    if (front == nullptr) rear = nullptr;
    delete temp;
}

void ehr_input() {
    cin.clear(); 
    cin.ignore(1000, '\n');
    cout << "\n >> Input harus berupa angka (Enter)" << endl;
    getch();
}

int main() {
    kereta daftar_kereta[MAX_KAPASITAS] = {
        {102, "Thomas Rail", "Jakarta", "Surabaya", 500000},
        {112, "Emily Emerald", "Malang", "Solo", 600000},
        {110, "Titipo Little", "Yogyakarta", "Jakarta", 450000},
        {104, "Gordon Big", "Bandung", "Solo", 480000},
        {106, "Percy GreenLoco", "Surabaya", "Bogor", 250000}
    };
    transaksi antrean[MAX_SISTEM];
    int front = -1, rear = -1;
    transaksi riwayat[MAX_SISTEM];
    int top = -1;
    int jml_kereta = 5;
    int pilihan = -1;
    int sub = -1;
    kereta* ptrData = daftar_kereta; 

    do {
        system("cls");
        cout << "==========================================================" << endl;
        cout << "|             SISTEM MANAJEMEN KERETA API                |" << endl;
        cout << "==========================================================" << endl;
        cout << "| 1. | Database Kereta Api                               |" << endl;
        cout << "| 2. | Transaksi Tiket                                   |" << endl;
        cout << "| 0. | Keluar                                            |" << endl;
        cout << "==========================================================" << endl;
        cout << "Pilihan: ";
        if (!(cin >> pilihan)) {
            ehr_input();
            pilihan = -1;
            continue;
        }

        if (pilihan == 1) {
            do {
                system("cls");
                cout << "==========================================================" << endl;
                cout << "|                    DATABASE KERETA API                 |" << endl;
                cout << "==========================================================" << endl;
                cout << "| 1. | Lihat Jadwal Kereta                               |" << endl;
                cout << "| 2. | Tambah Jadwal Kereta                              |" << endl;
                cout << "| 3. | Cari Rute Kereta                                  |" << endl;
                cout << "| 4. | Cari Nomor Kereta                                 |" << endl;
                cout << "| 5. | Urutkan Nama Kereta A-Z                           |" << endl;
                cout << "| 6. | Urutkan Harga Termurah                            |" << endl;
                cout << "| 0. | Kembali                                           |" << endl;
                cout << "==========================================================" << endl;
                cout << "Pilihan: ";

                if (!(cin >> sub)) {
                    ehr_input();
                    sub = -1;
                    continue;
                }

                switch (sub) {
                    case 1:
                        jadwal(ptrData, jml_kereta, "JADWAL KEBERANGKATAN KERETA");
                        getch();
                        break;

                    case 2: 
                        if (jml_kereta < MAX_KAPASITAS) {
                            kereta* p = (ptrData + jml_kereta);
                            system("cls");
                            jadwal(ptrData, jml_kereta, "TAMBAH JADWAL KERETA");
                            cout << " No kereta   : ";
                            if (!(cin >> p->no_kereta)) { 
                                ehr_input(); 
                                break; 
                            }
                            cin.ignore();
                            cout << " Nama kereta : ";
                            getline(cin, p->nama_kereta);
                            cout << " Asal        : ";
                            getline(cin, p->asal);
                            cout << " Tujuan      : ";
                            getline(cin, p->tujuan);
                            cout << " Harga       : ";
                            if (!(cin >> p->harga)) { 
                                ehr_input();
                                break; 
                            }
                            
                            jml_kereta++;
                            cout << "\n -- Jadwal Berhasil Ditambahkan --" << endl;
                        } else {
                            cout << "\n JadwalPenuh" << endl;
                        }
                        getch();
                        break;

                    case 3: 
                        linear_rute(ptrData, jml_kereta);
                        break;

                    case 4: 
                        jump_search(ptrData, jml_kereta);
                        break;

                    case 5: 
                        if (jml_kereta > 0) {
                            merge_nama(ptrData, 0, jml_kereta - 1); 
                            jadwal(ptrData, jml_kereta, "HASIL URUT NAMA KERETA");
                        } else {
                            cout << "\nData kosong." << endl;
                        }
                        getch(); 
                        break;

                    case 6: 
                        if (jml_kereta > 0) {
                            selectionsort_harga(ptrData, jml_kereta); 
                            jadwal(ptrData, jml_kereta, "HASIL SORT HARGA");
                            getch(); 
                        } else {
                            cout << "\nData kosong." << endl;
                        }
                        getch();
                        break;
                    }
                } while (sub != 0);
            } 

        else if (pilihan == 2) {   
            do {
                sub = -1;
                system("cls");
                cout << "==========================================================" << endl;
                cout << "|                     TRANSAKSI TIKET                    |" << endl;
                cout << "==========================================================" << endl;
                cout << "| 1. | Ambil Antrean                                     |" << endl;
                cout << "| 2. | Proses Tiket                                      |" << endl;
                cout << "| 3. | Lihat Semua Antrean                               |" << endl;
                cout << "| 4. | Riwayat Transaksi                                 |" << endl;
                cout << "| 5. | Hapus Transaksi Terakhir                          |" << endl;
                cout << "| 6. | Info Antrean dan Riwayat                          |" << endl;
                cout << "| 0. | Kembali                                           |" << endl;
                cout << "==========================================================" << endl;
                cout << "Pilihan: ";

                if (!(cin >> sub)) {
                    ehr_input();
                    sub = -1;
                    continue; 
                }

                switch (sub) {
                    case 1: {
                        system("cls");
                        string n; 
                        cout << ">>> AMBIL ANTREAN <<<" << endl;
                        cout << " Nama Penumpang : "; 
                        cin.ignore(1000, '\n');
                        getline(cin, n);
                        cout << " IDX Kereta (0-" << jml_kereta << ") : ";
                        int id;
                        if (!(cin >> id)) {
                            ehr_input();
                            sub = -1;
                        } else {
                            int idx = id - 1;
                            if (idx >= 0 && idx < jml_kereta) {
                                kereta* k = (ptrData + idx);
                                string info = k->nama_kereta + " [" + k->asal + " - " + k->tujuan + "]";
                                enqueue(n, info);
                            } else {
                                cout << "\n indeks kereta tidak valid (Pilih 0-" << jml_kereta << ")" << endl;
                            }
                        }
                        getch(); 
                        break;
                    }

                    case 2:
                        system("cls");
                        cout << ">>> PROSES ANTREAN TIKET <<<" << endl;
                        dequeue(); 
                        getch();
                        break;

                    case 3:
                        system("cls");
                        cout << ">>> ANTREAN TIKET <<<" << endl;
                        cout << "----------------------------------------------------------------------------" << endl;
                        cout << "| NO | NAMA PENUMPANG          | DETAIL TIKET                              |" << endl;
                        cout << "----------------------------------------------------------------------------" << endl;
                        
                        if (front == -1 || front > rear) {
                            cout << "|              ( Antrian kosonng )                                         |" << endl;
                        } else {
                            int no = 1;
                            for (int i = front; i <= rear; i++) {
                                transaksi* p = (antrean + i);
                                cout << "| " << left << setw(3) << no++ 
                                    << "| " << setw(24) << p->nama_penumpang 
                                    << "| " << setw(42) << p->detail_tiket << "|" << endl;
                            }
                        }
                        cout << "----------------------------------------------------------------------------" << endl;
                        getch();
                        break;

                    case 4:
                        system("cls");
                        cout << ">>> RIWAYAT TRANSAKSI <<<" << endl;
                        cout << "---------------------------------------------------------------------------------------" << endl;
                        cout << "| NO | NAMA PENUMPANG          | DETAIL TIKET                           | STATUS      |" << endl;
                        cout << "---------------------------------------------------------------------------------------" << endl;
                        
                        if (top == -1) {
                            cout << "|      ( Belum ada riwayat transaksi )                                                |" << endl;
                        } else {
                            int no = 1;
                            for (int i = top; i >= 0; i--) {
                                transaksi* p = (riwayat + i);
                                cout << "| " << left << setw(3) << no++ 
                                    << "| " << setw(24) << p->nama_penumpang 
                                    << "| " << setw(40) << p->detail_tiket 
                                    << "| " << setw(12) << "SUKSES" << "|" << endl;
                            }
                        }
                        cout << "---------------------------------------------------------------------------------------" << endl;
                        getch();
                        break;

                    case 5:
                        system("cls");
                        cout << ">>> HAPUS RIWAYAT TERAKHIR <<<" << endl;
                        if (top == -1) {
                            cout << " Riwayat transaksi kosong." << endl;
                        } else {
                            transaksi* pHapus = (riwayat + top);
                            cout << " Menghapus riwayat transaksi: " << pHapus->nama_penumpang << endl;
                            cout << "\n >> Riwayat berhasi dihapus" << endl;
                        }
                        getch();
                        break;

                    case 6:
                        system("cls");
                        cout << "==========================================================" << endl;
                        cout << "|                INFO ANTREAN DAN RIWAYAT                |" << endl;
                        cout << "==========================================================" << endl;
                        cout << " [ ANTREAN TERDEPAN ]" << endl;
                        if (front == -1 || front > rear) {
                            cout << " > Tidak ada antrean." << endl;
                        } else {
                            cout << " > Nama   : " << (antrean + front)->nama_penumpang << endl;
                            cout << " > Detail : " << (antrean + front)->detail_tiket << endl;
                        }
                        cout << "\n----------------------------------------------------------\n" << endl;

                        cout << " [ TRANSAKSI TERAKHIR ]" << endl;
                        if (top == -1) {
                            cout << " > Belum ada riwayat transaksi." << endl;
                        } else {
                            cout << " > Nama   : " << (riwayat + top)->nama_penumpang << endl;
                            cout << " > Detail : " << (riwayat + top)->detail_tiket << endl;
                            cout << " > Status : SUKSES" << endl;
                        }
                        
                        cout << "==========================================================" << endl;
                        getch();
                        break;
                    }
            } while (sub != 0);
        }
    } while (pilihan != 0);
    return 0;
}