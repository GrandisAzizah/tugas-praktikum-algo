#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct node
{
    string namaPelanggan;
    string jenisRoti;
    int hargaRoti;
    node *next;
};

node *depan = nullptr, *belakang = nullptr;
node *top = nullptr;

// buat queue
void buatqueue()
{
    depan = nullptr;
    belakang = nullptr;
}

// cek apakah queue kosong
int queuekosong()
{
    return (depan == nullptr);
}

// buat stack
void buatStack()
{
    depan = belakang = nullptr;
}

// cek apakah stack kosong
bool stackKosong()
{
    return depan == nullptr;
}

// pakai queue untuk tambah antrean pesanan
void tambahPesanan(string namaPelanggan, string jenisRoti, int hargaRoti)
{
    node *NB = new node;
    NB->namaPelanggan = namaPelanggan;
    NB->jenisRoti = jenisRoti;
    NB->hargaRoti = hargaRoti;
    NB->next = nullptr;

    if (depan == nullptr)
    {
        depan = NB;
    }
    else
    {
        belakang->next = NB;
    }
    belakang = NB;
}

void contohPesanan()
{
    // tambah pesanan di sini
    cout << "DAFTAR PESANAN DALAM ANTRIAN:" << endl;
    cout << setfill('-') << setw(20) << "" << endl;
    buatqueue();
    tambahPesanan("Pelanggan B", "Roti Cokelat", 12000);
    tambahPesanan("Pelanggan A", "Roti Tawar Gandum", 10500);
    tambahPesanan("Pelanggan M", "Roti Keju", 13000);
    tambahPesanan("Pelanggan X", "Roti Pisang", 11000);
    tambahPesanan("Pelanggan Y", "Roti Kismis", 12500);

    // Pelanggan B adalah cutomer pertama
    // Pelanggan Y adalah customer terakhir
}

// batalkan pesanan terakhir (Pelanggan Y)
void batalkanPesanan()
{
    if (stackKosong())
    {
        cout << "Tidak ada pesanan." << endl;
        return;
    }

    node *bantu, *hapus;
    bantu = depan;

    while (bantu->next != belakang)
    {
        bantu = bantu->next;
    }
    bantu->next = nullptr;
    hapus = belakang;
    belakang = bantu;
    delete hapus;
}

// queue
void tampilkanPesanan()
{
    node *bantu = depan;

    if (bantu == nullptr)
    {
        cout << "Tidak ada pesanan." << endl;
    }

    while (bantu != nullptr)
    {
        cout << "Nama Pelanggan: " << bantu->namaPelanggan << " " << endl;
        cout << "Jenis Roti: " << bantu->jenisRoti << " " << endl;
        cout << "Harga Roti: " << bantu->hargaRoti << " " << endl;
        cout << setfill('-') << setw(20) << "" << endl;
        bantu = bantu->next;
    }
    cout << endl;
}

// pakai stack
void riwayatPesanan(string namaPelanggan, string jenisRoti, int hargaRoti)
{
    node *newNode = new node;
    newNode->namaPelanggan = namaPelanggan;
    newNode->jenisRoti = jenisRoti;
    newNode->hargaRoti = hargaRoti;
    newNode->next = top;
    top = newNode;
}

void layaniPesanan()
{
    if (queuekosong())
    {
        cout << "Tidak ada pesanan untuk dilayani." << endl;
        return;
    }

    // string nama = bantu->namaPelanggan juga bisa
    node *bantu = depan;
    string namaPelanggan = bantu->namaPelanggan;
    string jenisRoti = bantu->jenisRoti;
    int hargaRoti = bantu->hargaRoti;

    // pindahkan ke riwayat
    riwayatPesanan(namaPelanggan, jenisRoti, hargaRoti);

    // hapus dari queue
    depan = depan->next;
    delete bantu;
}

void tampilkanRiwayat()
{
    node *bantu = top;
    while (bantu != nullptr)
    {
        cout << "Nama Pelanggan: " << bantu->namaPelanggan << " " << endl;
        cout << "Jenis Roti: " << bantu->jenisRoti << " " << endl;
        cout << "Harga Roti: " << bantu->hargaRoti << " " << endl;
        cout << setfill('-') << setw(20) << "" << endl;
        bantu = bantu->next;
    }
    cout << endl;
}

int main()
{
    cout << setfill('=') << setw(50) << "" << endl;
    cout << setfill(' ') << setw(18) << "" << "TOKO MANIS LEZAT" << endl;
    cout << setfill('=') << setw(50) << "" << endl
         << endl;

    // TAMBAH PESANAN KE ANTRIAN
    buatqueue();
    contohPesanan();

    // TAMPILKAN PESANAN
    tampilkanPesanan();
    cout << endl
         << endl;

    // MEMBATALKAN PESANAN DARI ANTRIAN
    batalkanPesanan();
    cout << "DAFTAR PESANAN SETELAH PESANAN TERAKHIR DIBATALKAN:" << endl;
    cout << setfill('-') << setw(20) << "" << endl;
    tampilkanPesanan();
    cout << endl
         << endl;

    //  LAYANI PESANAN
    while (!queuekosong())
    {
        layaniPesanan();
    }

    // SEMUA PESANAN YANG SUDAH DILAYANI
    cout << "RIWAYAT PESANAN: " << endl;
    cout << setfill('-') << setw(20) << "" << endl;
    tampilkanRiwayat();
    cout << endl
         << endl;

    return 0;
}
