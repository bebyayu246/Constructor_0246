#include <iostream>
#include <string>
using namespace std;

//membuat class buku
class Buku {
private:
    string judul;
    string penulis;
    bool dipinjam; // Status peminjaman, privat

public:
    Buku(string j, string p) : judul(j), penulis(p), dipinjam(false) {}

    // Fungsi untuk melihat status peminjaman
    bool getDipinjam() const {
        return dipinjam;
    }

    // membuat Petugas agar bisa mengubah status peminjaman
    friend class Petugas;
    // membuat Admin agar bisa melihat data buku
    friend class Admin;
};

// membuat Class Peminjaman 
class Peminjaman {
private:
    string nama;
    int id;
    int jumlahBukuDipinjam;
    int totalPinjaman;

public:
    Peminjaman(string n, int i) : nama(n), id(i), jumlahBukuDipinjam(0), totalPinjaman(0) {}


    friend class Petugas;
    friend class Admin;

    // Fungsi untuk menambah jumlah buku yang dipinjam
    void tambahBuku(int jumlah) {
        jumlahBukuDipinjam += jumlah;
        totalPinjaman += jumlah;
    }

    // Fungsi untuk mendapatkan jumlah buku yang dipinjam
    int getJumlahBuku() const {
        return jumlahBukuDipinjam;
    }

    // Fungsi untuk melihat total pinjaman
    int getTotalPinjaman() const {
        return totalPinjaman;
    }

    // Fungsi untuk melihat nama peminjam
    string getNama() const {
        return nama;
    }
};

// membuat Class Petugas 
class Petugas {
private:
    string nama;
    int id;
    string levelAkses;

public:
    Petugas(string n, int i, string l) : nama(n), id(i), levelAkses(l) {}

    // Fungsi untuk memproses peminjaman buku
    void prosesPinjam(Buku* b, Peminjaman* p) {
        if (!b->dipinjam) {
            b->dipinjam = true;
            p->tambahBuku(1); // Tambah jumlah buku yang dipinjam
            cout << "Buku '" << b->judul << "' telah dipinjam oleh " << p->getNama() << endl;
        } else {
            cout << "Buku '" << b->judul << "' sudah dipinjam." << endl;
        }
    }

    // Fungsi untuk memproses pengembalian buku
    void prosesKembali(Buku* b, Peminjaman* p) {
        if (b->dipinjam) {
            b->dipinjam = false;
            p->tambahBuku(-1); // Kurangi jumlah buku yang dipinjam
            cout << "Buku '" << b->judul << "' telah dikembalikan oleh " << p->getNama() << endl;
        } else {
            cout << "Buku '" << b->judul << "' belum dipinjam." << endl;
        }
    }

    
    friend class Admin;
};

// Membuat Class Admin 
class Admin {
private:
    string nama;
    int id;

public:
    Admin(string n, int i) : nama(n), id(i) {}

    // Fungsi untuk mengubah level akses petugas
    void ubahLevelAkses(Petugas* p, string level) {
        p->levelAkses = level;
        cout << "Level akses petugas " << p->nama << " telah diubah menjadi " << level << endl;
    }

    // Fungsi untuk melihat jumlah buku yang dipinjam oleh peminjam
    void lihatJumlahBuku(Peminjaman* p) {
        cout << "Jumlah buku yang dipinjam oleh " << p->getNama() << ": " << p->getJumlahBuku() << endl;
    }

    // Fungsi untuk melihat total pinjaman
    void lihatTotalPinjaman(Peminjaman* p) {
        cout << "Total pinjaman oleh " << p->getNama() << ": " << p->getTotalPinjaman() << endl;
    }

    // Fungsi untuk melihat buku yang sedang diproses
    void lihatBukuSedangDiproses(Buku* b) {
        if (b->dipinjam) {
            cout << "Buku '" << b->judul << "' sedang dipinjam." << endl;
        } else {
            cout << "Buku '" << b->judul << "' belum dipinjam." << endl;
        }
    }

    friend class Petugas;
};

int main() {
    // Membuat objek buku
    Buku buku1("Pemrogaman Dasar", "Mas indra");
    Buku buku2("Algoritma", "Mas gilang");

    // Membuat objek peminjam
    Peminjaman peminjam1("Abun", 103);
    Peminjaman peminjam2("Boby", 104);

    // Membuat objek petugas
    Petugas petugas1("Joko", 1, "Member");

    // Membuat objek admin & mengubah akses petugas
    Admin admin1("Admin", 0);
    admin1.ubahLevelAkses(&petugas1, "Supervisor");

    // Petugas memproses peminjaman
    petugas1.prosesPinjam(&buku1, &peminjam1);
    petugas1.prosesPinjam(&buku2, &peminjam1);

    // Admin melihat jumlah pinjaman
    admin1.lihatJumlahBuku(&peminjam1);

    // Petugas memproses pengembalian
    petugas1.prosesKembali(&buku1, &peminjam1);

    // Admin melihat status peminjaman buku
    admin1.lihatBukuSedangDiproses(&buku1);
    admin1.lihatBukuSedangDiproses(&buku2);

    return 0;
}
