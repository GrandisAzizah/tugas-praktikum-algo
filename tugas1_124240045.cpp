#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int menu;
char pilihan;
struct roti
{
    string nama_roti;
    string kode;
    float harga;
};

roti r[5] = {
    {"Roti Tawar", "001", 15000.00},
    {"Roti Coklat", "002", 18000.00},
    {"Roti Keju", "003", 20000.00},
    {"Roti Gandum", "004", 22000.00},
    {"Roti Pisang", "005", 17000.00}};

roti *ptr = r;

void beranda()
{
    cout << endl;
    cout << setfill('=') << setw(50) << "" << endl;
    cout << setfill(' ') << setw(20) << "" << "TOKO ROTI AK" << endl;
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "1. Tampilkan daftar Roti" << endl;
    cout << "2. Cari Berdasarkan Kode" << endl;
    cout << "3. Cari berdasarkan Nama" << endl;
    cout << "4. Sort Harga Roti (asc)" << endl;
    cout << "5. Sort Harga Roti (desc)" << endl;
    cout << "6. Exit" << endl;
    cout << "Pilih menu : ";
    cin >> menu;
}

void daftar_roti()
{
    const int maxNamaRotiLength = 20;
    // HEADER
    cout << setfill('=') << setw(50) << "" << endl;
    cout << left << setfill(' ') << setw(20) << "Nama Roti"
         << setfill(' ') << setw(8) << " "
         << "Kode" << right << setfill(' ') << setw(7) << " "
         << "Harga" << endl;
    cout << setfill('=') << setw(50) << "" << endl;

    // PENGULANGAN UNTUK ISI TABEL
    for (int i = 0; i < 5; i++)
    {
        cout << left << setfill(' ') << setw(20) << (ptr + i)->nama_roti
             << left << setfill(' ') << setw(8) << "  " << (ptr + i)->kode
             << left << fixed << setprecision(2) << setfill(' ')
             << setw(8) << "" << (ptr + i)->harga
             << endl;
    }
    cout << setfill('=') << setw(50) << "" << endl;
}

void cari_kode()
{
    bool found;
    found = false;
    int i;
    i = 0;
    string search_code;
    cout << endl;
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "Masukkan kode yang ingin dicari: ";
    cin.ignore();
    getline(cin, search_code);

    while (i < 5 && !found)
    {
        if ((ptr + i)->kode == search_code)
        {
            found = true;
        }
        else
        {
            i++;
        }
    }

    if (found)
    {
        cout << "Nama: " << (ptr + i)->nama_roti << ", "
             << "Kode " << search_code << ", "
             << "Harga: " << fixed << setprecision(2) << (ptr + i)->harga
             << endl;
    }
    else
    {
        cout << "Data dengan kode " << search_code << " tidak ditemukan" << endl;
    }
}

void cari_nama()
{
    int awal, akhir, k; // awal+akhir/2
    bool found;
    found = false;
    awal = 0;
    akhir = 4;
    string search_name;

    cout << endl;
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "Masukkan nama roti yang ingin dicari: ";
    cin.ignore();
    getline(cin, search_name);

    for (int i = 0; i < 5 - 1; i++) // iterasi jumlah elemen
    {
        for (int j = 0; j < 5 - i - 1; j++) // iterasi melakukan perbandingan
        {
            if ((ptr + j)->nama_roti > (ptr + j + 1)->nama_roti) // bandingkan harga, jika harga lebih besar, maka tukar posisi
            {
                roti temp = *(ptr + j);
                *(ptr + j) = *(ptr + j + 1);
                *(ptr + j + 1) = temp;
            }
        }
    }

    while ((!found) && (awal <= akhir))
    {
        k = (awal + akhir) / 2;
        if (search_name == (ptr + k)->nama_roti)
        {
            found = true;
        }
        else
        {
            if (search_name < (ptr + k)->nama_roti)
            {
                akhir = k - 1; // awal tetap
            }
            else
            {
                awal = k + 1; // akhir tetap
            }
        }
    }

    if (found)
    {
        cout << "Nama: " << search_name << ", "
             << "Kode " << (ptr + k)->kode << ", "
             << "Harga: " << fixed << setprecision(2) << (ptr + k)->harga
             << endl;
    }
    else
    {
        cout << "Data dengan nama " << search_name << " tidak ditemukan" << endl;
    }
}

int partition(roti arr[], int low, int high)
{
    float pivot = arr[high].harga;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].harga <= pivot)
        {
            i++;
            roti temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    roti temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quicksort(roti arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

void sort_asc()
{
    cout << "Daftar roti dalam urutan ascending:" << endl;
    quicksort(r, 0, 4);

    const int maxNamaRotiLength = 20;
    // HEADER
    cout << setfill('=') << setw(50) << "" << endl;
    cout << left << setfill(' ') << setw(20) << "Nama Roti"
         << setfill(' ') << setw(8) << " "
         << "Kode" << right << setfill(' ') << setw(7) << " "
         << "Harga" << endl;
    cout << setfill('=') << setw(50) << "" << endl;

    // PENGULANGAN UNTUK ISI TABEL
    for (int i = 0; i < 5; i++)
    {
        cout << left << setfill(' ') << setw(20) << (ptr + i)->nama_roti
             << left << setfill(' ') << setw(8) << "  " << (ptr + i)->kode
             << left << fixed << setprecision(2) << setfill(' ')
             << setw(8) << "" << (ptr + i)->harga
             << endl;
    }
    cout << setfill('=') << setw(50) << "" << endl;
}

void sort_dsc()
{
    cout << "Daftar roti dalam urutan descending:" << endl;
    for (int i = 0; i < 5 - 1; i++)
    {
        for (int j = 0; j < 5 - i - 1; j++)
        {
            if ((ptr + j)->harga < (ptr + j + 1)->harga)
            {
                roti temp = *(ptr + j);
                *(ptr + j) = *(ptr + j + 1);
                *(ptr + j + 1) = temp;
            }
        }
    }

    const int maxNamaRotiLength = 20;
    // HEADER
    cout << setfill('=') << setw(50) << "" << endl;
    cout << left << setfill(' ') << setw(20) << "Nama Roti"
         << setfill(' ') << setw(8) << " "
         << "Kode" << right << setfill(' ') << setw(7) << " "
         << "Harga" << endl;
    cout << setfill('=') << setw(50) << "" << endl;

    // PENGULANGAN UNTUK ISI TABEL
    for (int i = 0; i < 5; i++)
    {
        cout << left << setfill(' ') << setw(20) << (ptr + i)->nama_roti
             << left << setfill(' ') << setw(8) << "  " << (ptr + i)->kode
             << left << fixed << setprecision(2) << setfill(' ')
             << setw(8) << "" << (ptr + i)->harga
             << endl;
    }
    cout << setfill('=') << setw(50) << "" << endl;
}

void exit()
{
    exit(0);
}

int main()
{
    do
    {
        system("CLS");
        beranda();

        switch (menu)
        {
        case 1:
            daftar_roti();
            break;
        case 2:
            cari_kode();

            break;
        case 3:
            cari_nama();
            break;
        case 4:
            sort_asc();
            break;
        case 5:
            sort_dsc();
            break;
        case 6:
            exit();
            break;
        }
        cout << "Ulangi program? (y/n): ";
        cin >> pilihan;
    } while (pilihan == 'Y' || pilihan == 'y');
}