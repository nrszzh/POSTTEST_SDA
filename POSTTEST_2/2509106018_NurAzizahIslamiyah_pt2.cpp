// Sistem manajemen keberangkatan Kereta Api
// Program mengelola jadwal dan informasi tiket kereta api (struct, pointer, array of struct, searching, dan sorting)
// Tampil jadwal semua kereta (menggunakan pointer)
// Tambah data kereta baru
// Linear Search cari berdasarkan rute (asal & tujuan)
// jump Search cari berdasarkan nomor kereta
// Merge sort urutkan berdasarkan nama kereta (A-Z)
// Selection Sort urutkan berdasarkan harga tiket (termurah)
// Setiap searching dan pointer menerapkan swap dengan pointer

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
        << "| " << setw(15) << left << "Harga" << " |\n";
    cout << "================================================================================\n";
}