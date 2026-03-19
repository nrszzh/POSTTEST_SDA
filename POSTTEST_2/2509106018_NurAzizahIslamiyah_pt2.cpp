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
using namespace std;

struct Kereta {
    int noKereta;
    string namaKereta;
    string asal;
    string tujuan;
    int harga;
};

void swap(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}
