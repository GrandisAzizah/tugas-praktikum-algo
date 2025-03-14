#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct data_penduduk
{
    int nik;
    string nama;
    string alamat;
    string jenis_kelamin;
};

data_penduduk dp[100];
data_penduduk *ptr = dp;
string nama_file;
int i;
char pilihan;       // untuk looping do while, akan direct user ke beranda lagi jika memilih 'y' atau 'Y'
int menu;           // pilih menu di beranda
int jml_data_input; // jumlah data yang diinputkan
int cari_nik;

// halaman awal dan menu
void beranda()
{
    cout << endl;
    cout << setfill('=') << setw(50) << "" << endl;
    cout << setfill(' ') << setw(5) << "" << "PROGRAM DATA KEPENDUDUKAN KECAMATAN DEPOK" << endl;
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "1. Input Data" << endl;
    cout << "2. Tampilkan Data" << endl;
    cout << "3. Cari Data Berdasarkan NIK" << endl;
    cout << "4. Edit Data" << endl;
    cout << "5. Hapus Data" << endl;
    cout << "6. Keluar Dari Program" << endl;
    cout << "Pilih menu : ";
    cin >> menu;
}

// input data
void input_data()
{
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "Input Data Kependudukan" << endl;
    // pengguna bisa membuat file baru dengan nama yang diputuskan oleh pengguna
    cout << endl;
    cout << "Masukkan nama file: ";
    cin >> nama_file;

    // open file jika sudah ada, create jika belum ada
    FILE *file = fopen(nama_file.c_str(), "a");
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    // pengguna memasukkan jumlah input yang diinginkan
    cout << "Masukkan jumlah data yang ingin diinputkan: ";
    cin >> jml_data_input;

    cin.ignore();

    // input data sebanyak jml_data_input
    for (int i = 0; i < jml_data_input; i++)
    {
        cout << "Masukkan data ke-" << i + 1 << endl;
        cout << "Masukkan NIK" << ": ";
        cin >> (ptr + i)->nik;

        cout << "Masukkan nama" << ": ";
        cin.ignore();
        getline(cin, (ptr + i)->nama);

        cout << "Masukkan alamat" << ": ";
        getline(cin, (ptr + i)->alamat);

        cout << "Masukkan jenis kelamin" << ": ";
        cin >> (ptr + i)->jenis_kelamin;

        // menampilkan input yang sudah dilakukan ke file yang dibuat oleh pengguna
        fprintf(file, "nik: %d\n", (ptr + i)->nik);
        fprintf(file, "nama: %s\n", (ptr + i)->nama.c_str());
        fprintf(file, "alamat: %s\n", (ptr + i)->alamat.c_str());
        fprintf(file, "jenis kelamin: %s\n", (ptr + i)->jenis_kelamin.c_str());
        fprintf(file, "\n");

        cout << endl;
    }
    fclose(file);
}

// output data
void output_data()
{
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "Tampilkan Data Kependudukan" << endl;

    // pengguna menginput nama file yang ingin dibuka
    cout << "Nama file yang ingin dibuka: ";
    cin >> nama_file;
    cin.ignore();

    FILE *file = fopen(nama_file.c_str(), "r"); // membuka file dalam mode baca
    if (!file)
    {
        cout << "File tidak dapat dibuka" << endl;
        return;
    }

    // membaca dan menampilkan data dari file
    data_penduduk *ptr_data_pdd = dp;
    int count = 0; // untuk menghitung jumlah data yang dibaca
    while (fscanf(file, "nik: %d\n", &ptr_data_pdd[count].nik) != EOF)
    {
        char buffer[256]; // buffer untuk membaca string
        fscanf(file, "nama: %[^\n]\n", buffer);
        ptr_data_pdd[count].nama = buffer;

        fscanf(file, "alamat: %[^\n]\n", buffer);
        ptr_data_pdd[count].alamat = buffer;

        fscanf(file, "jenis kelamin: %[^\n]\n", buffer);
        ptr_data_pdd[count].jenis_kelamin = buffer;

        count++; // increment untuk data berikutnya
    }

    fclose(file);

    // update jml_data_input
    jml_data_input = count;

    // mengurutkan data menggunakan pointer dengan bubble sort
    // p1: iterasi
    // p2 itu membandingkan data ke-n dan data selanjutnya untuk swap atau tidak
    for (data_penduduk *p1 = ptr_data_pdd; p1 < ptr_data_pdd + jml_data_input; p1++)
    {
        for (data_penduduk *p2 = ptr_data_pdd; p2 < ptr_data_pdd + jml_data_input - (p1 - ptr_data_pdd) - 1; p2++)
        {
            if (p2->nik > (p2 + 1)->nik)
            {
                data_penduduk temp = *p2;
                *p2 = *(p2 + 1);
                *(p2 + 1) = temp;
            }
        }
    }

    // Menampilkan data yang sudah diurutkan
    cout << "Data yang ada pada file (setelah diurutkan berdasarkan NIK): " << endl;
    cout << setfill('-') << setw(50) << "" << endl;
    for (data_penduduk *p = ptr_data_pdd; p < ptr_data_pdd + jml_data_input; p++)

    {
        cout << "NIK: " << p->nik << endl;
        cout << "Nama: " << p->nama << endl;
        cout << "Alamat: " << p->alamat << endl;
        cout << "Jenis Kelamin: " << p->jenis_kelamin << endl;
        cout << setfill('-') << setw(50) << "" << endl;
    }
}

// membaca file sebelum melakukan pencarian
void baca_sebelum_program()
{
    cout << "Nama file: ";
    cin >> nama_file;
    cin.ignore();

    FILE *file = fopen(nama_file.c_str(), "r"); // membuka file dalam mode baca
    if (!file)
    {
        cout << "File tidak dapat dibuka" << endl;
        return;
    }

    // membaca data dari file
    jml_data_input = 0;
    while (fscanf(file, "nik: %d\n", &dp[jml_data_input].nik) != EOF)
    {
        char buffer[256]; // buffer untuk membaca string
        fscanf(file, "nama: %[^\n]\n", buffer);
        dp[jml_data_input].nama = buffer;

        fscanf(file, "alamat: %[^\n]\n", buffer);
        dp[jml_data_input].alamat = buffer;

        fscanf(file, "jenis kelamin: %[^\n]\n", buffer);
        dp[jml_data_input].jenis_kelamin = buffer;

        jml_data_input++; // increment untuk data berikutnya
    }

    fclose(file);
}

// cari data di dalam file berdasarkan NIK
void cari_data()
{
    int i;
    i = 0;
    bool found;
    found = false;
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "Cari Data Penduduk Berdasarkan NIK" << endl;

    // void untuk membaca file sebelum searching
    baca_sebelum_program();

    // pengguna input NIK yang ingin dicari
    cout << "Masukkan NIK yang ingin dicari: ";
    cin >> cari_nik;

    // searching menggunakan linear search
    while (i < jml_data_input && !found)
    {
        if ((ptr + i)->nik == cari_nik)
        {
            found = true;
        }
        else
        {
            i++;
        }
    }

    if (!found)
    {
        cout << "Data " << cari_nik << " tidak ditemukan" << endl;
    }
    else
    {
        cout << "Data " << cari_nik << " ditemukan di index ke-" << i << endl;
        cout << "NIK: " << cari_nik << endl;
        cout << "Nama: " << (ptr + i)->nama << endl;
        cout << "Alamat: " << (ptr + i)->alamat << endl;
        cout << "Jenis Kelamin: " << (ptr + i)->jenis_kelamin << endl;
    }
}

void edit_data()
{
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "Edit Data Penduduk" << endl;
    cout << endl;

    // baca file sebelum edit
    baca_sebelum_program();
    // pengguna memasukkan NIK dari data yang ingin diedit
    cout << "Masukkan NIK dari data yang ingin diedit alamatnya: ";
    cin >> cari_nik;

    bool found = false;
    int index = -1;
    for (int i = 0; i < jml_data_input; i++)
    {
        if ((ptr + i)->nik == cari_nik)
        {
            found = true;
            index = i;
            cout << "Data ditemukan!" << endl;
            cout << "NIK: " << (ptr + i)->nik << endl;
            cout << "Nama: " << (ptr + i)->nama << endl;
            cout << "Alamat: " << (ptr + i)->alamat << endl;
            cout << "Jenis Kelamin: " << (ptr + i)->jenis_kelamin << endl;

            // pengisian alamat baru
            cout << "Masukkan alamat baru: ";
            cin.ignore();
            getline(cin, (ptr + i)->alamat);
            break;
        }
    }

    // jika file tidak ditemukan
    if (!found)
    {
        cout << "Data dengan NIK " << cari_nik << " tidak ditemukan" << endl;
    }

    // buka file untuk menulis
    FILE *file = fopen(nama_file.c_str(), "w");

    // file tidak dapat dibuka
    if (!file)
    {
        cout << "File tidak dapat dibuka." << endl;
        return;
    }

    // menulis kembali semua file setelah edit
    for (int i = 0; i < jml_data_input; i++)
    {
        fprintf(file, "nik: %d\n", (ptr + i)->nik);
        fprintf(file, "nama: %s\n", (ptr + i)->nama.c_str());
        fprintf(file, "alamat: %s\n", (ptr + i)->alamat.c_str());
        fprintf(file, "jenis kelamin: %s\n", (ptr + i)->jenis_kelamin.c_str());
        fprintf(file, "\n");
    }

    fclose(file);
    cout << "Data berhasil diperbarui." << endl;
}

void hapus_data()
{
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "Hapus Data" << endl;
    cout << endl;

    // baca file
    baca_sebelum_program();

    // cari NIK yang datanya akan dihapus
    cout << "Masukkan NIK yang datanya ingin dihapus: ";
    cin >> cari_nik;

    bool found = false;
    int index = -1;

    // cari data berdasarkan NIK
    for (int i = 0; i < jml_data_input; i++)
    {
        if ((ptr + i)->nik == cari_nik)
        {
            found = true;
            index = i;
            break;
        }
    }

    // cek data ditemukan atau tidak
    if (!found)
    {
        cout << "Data dengan NIK " << cari_nik << " tidak ditemukan." << endl;
        return;
    }

    // hapus data
    for (int i = index; i < jml_data_input - 1; i++)
    {
        (ptr + i)->nik = (ptr + i + 1)->nik;
    }

    jml_data_input--; // kurangi jumlah data

    // buka file untuk menulis
    FILE *file = fopen(nama_file.c_str(), "w");

    // file tidak dapat dibuka
    if (!file)
    {
        cout << "File tidak dapat dibuka." << endl;
        return;
    }

    // menulis kembali semua file setelah dihapus
    for (int i = 0; i < jml_data_input; i++)
    {
        fprintf(file, "nik: %d\n", (ptr + i)->nik);
        fprintf(file, "nama: %s\n", (ptr + i)->nama.c_str());
        fprintf(file, "alamat: %s\n", (ptr + i)->alamat.c_str());
        fprintf(file, "jenis kelamin: %s\n", (ptr + i)->jenis_kelamin.c_str());
        fprintf(file, "\n");
    }

    fclose(file);
    cout << "Data dengan NIK " << cari_nik << " telah dihapus." << endl;
}

void keluar()
{
    cout << "Terima kasih telah menggunakan program ini." << endl;
    exit(0);
}

int main()
{
    do
    {
        system("CLS");
        beranda();
        cout << endl;
        switch (menu)
        {
        case 1:
            input_data();
            break;
        case 2:
            output_data();

            break;
        case 3:
            cari_data();
            break;
        case 4:
            edit_data();
            break;
        case 5:
            hapus_data();
            break;
        case 6:
            keluar();
            break;
        default:
            cout << "Pilihan tidak tersedia. Silakan pilih menu yang valid." << endl;
        }
        cout << "Ulangi program? (y/n): ";
        cin >> pilihan;
    } while (pilihan == 'Y' || pilihan == 'y');
}
