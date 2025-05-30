#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct PtbNode
{
    string judul;
    string durasi;
    string status;
    PtbNode *left;
    PtbNode *right;

    // inisialisasi PtbNode baru
    PtbNode(string val, string val1, string val2)
    {
        judul = val;
        durasi = val1;
        status = val2;
        left = right = nullptr;
    }
};

struct undoAction
{
    string aksi;
    string judul;
    string durasi;
    string status;
} undoLast;

PtbNode *top, *depan, *belakang;
PtbNode *root = nullptr;
PtbNode *undoTop = nullptr; // stack undo
int menu;
char pilihan;

// beranda
void beranda()
{
    cout << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    cout << setfill(' ') << setw(15) << "" << "IDLIX Tube" << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    cout << "Menu" << endl;
    cout << "1. Tambah Video" << endl;
    cout << "2. Tampilkan Daftar Video" << endl;
    cout << "3. Tambahkan ke Playlist" << endl;
    cout << "4. Tonton Video" << endl;
    cout << "5. Riwayat Tontonan" << endl;
    cout << "6. Hapus Video" << endl;
    cout << "7. Undo tindakan terakhir" << endl;
    cout << "Pilih menu: ";
    cin >> menu;
}

// buat queue
void buatQueue()
{
    depan = nullptr;
    belakang = nullptr;
}

// cek apa queue kosong
int queueKosong()
{
    return (depan == nullptr);
}

// buat stack
void buatStack()
{
    top = nullptr;
}

// cek apa stack kosong
bool stackKosong()
{
    return top == nullptr;
}

// untuk normalisasi input
string to_lowercase(string str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 'a' - 'A';
        }
    }
    return str;
}

// menambahkan video
void tambahVideo(PtbNode *&root, string val, string val1, string val2)
{

    if (root == nullptr)
    {
        root = new PtbNode(val, val1, val2);
        return;
    }

    if (val < root->judul)
    {
        tambahVideo(root->left, val, val1, val2);
    }
    else if (val > root->judul)
    {
        tambahVideo(root->right, val, val1, val2);
    }
    else
    {
        cout << "Judul " << val << " sudah ada di dalam list. Silakan masukan judul lain." << endl;
    }
}

void searchBST(PtbNode *root, string target)
{
    target = to_lowercase(target);
    PtbNode *curr = root;

    while (curr)
    {
        string curr_judul = to_lowercase(curr->judul);
        if (curr_judul == target)
        {
            cout << curr->judul << " ditemukan" << endl;
            return;
        }
        curr = (target < curr_judul) ? curr->left : curr->right;
    }
    cout << target << " tidak ditemukan." << endl;
}

PtbNode *search(PtbNode *root, string target)
{
    target = to_lowercase(target);
    PtbNode *curr = root;
    while (curr)
    {
        string curr_judul_lc = to_lowercase(curr->judul);
        if (curr_judul_lc == target)
        {
            // cout << curr->judul << " ditemukan." << endl;
            return curr;
        }
        curr = (target < curr_judul_lc) ? curr->left : curr->right;
    }
    cout << target << " tidak ditemukan." << endl;
    return nullptr;
}

// queue
void tambah_playlist(string val, string val1, string val2)
{
    // buat node baru untuk menyalin BST
    PtbNode *baru = new PtbNode(val, val1, val2);
    baru->right = nullptr;
    baru->left = nullptr;

    if (depan == nullptr)
    {
        depan = baru;
    }
    else
    {
        belakang->right = baru;
    }
    belakang = baru;
}

// untuk menampilkan playlist
void tampilkanPlaylist()
{
    cout << "Lihat playlist? (Y/N) ";
    cin >> pilihan;

    if (pilihan == 'Y' || pilihan == 'y')
    {
        if (queueKosong())
        {
            cout << "Playlist Kosong." << endl;
        }

        PtbNode *bantu = depan;
        cout << "Isi playlist: " << endl;
        while (bantu != nullptr)
        {
            cout << "Judul: " << bantu->judul << endl;
            cout << "Durasi: " << bantu->durasi << endl;
            cout << "Status: " << bantu->status << endl;
            cout << setfill('-') << setw(10) << endl;
            bantu = bantu->right;
        }
    }
    else
    {
        return;
    }
}

// hapus dari playlist untuk undo
void hapusdariPlaylist(string judul)
{
    if (queueKosong())
        return;

    PtbNode *curr = depan;
    PtbNode *prev = nullptr;

    while (curr != nullptr && curr->judul != judul)
    {
        prev = curr;
        curr = curr->right;
    }

    if (curr == nullptr)
        return; // tidak ditemukan

    if (prev == nullptr)
    {
        // hapus node paling depan
        depan = curr->right;
    }
    else
    {
        prev->right = curr->right;
    }

    if (curr == belakang)
    {
        belakang = prev;
    }
    delete curr;
}

void riwayatTontonan(string val, string val1, string val2)
{

    PtbNode *curr = new PtbNode(val, val1, val2);
    curr->right = top;
    top = curr;
}

// untuk video yang sedang diputar
void tontonVideo()
{
    if (queueKosong())
    {
        cout << "Tidak ada video dalam playlist untuk diputar." << endl;
        return;
    }

    PtbNode *video = depan;
    // ambil data dari antrean paling depan playlist
    cout << "Sedang memutar video: " << endl;
    cout << "Judul: " << video->judul << endl;
    cout << "Durasi: " << video->durasi << endl;

    // kembalikan status video ke 'tersedia'
    PtbNode *balik = search(root, video->judul);
    if (balik != nullptr)
    {
        balik->status = "Tersedia";
    }

    // masukkan riwayat
    riwayatTontonan(video->judul, video->durasi, "Tersedia");

    depan = depan->right;

    // undo
    undoLast = {"tontonVideo", video->judul, video->durasi, "Tersedia"};
    // hapus dari playlist
    delete video;
}

// tampilkan riwayat
void tampilkanRiwayat()
{
    if (stackKosong())
    {
        cout << "Belum ada video yang ditonton." << endl;
        return;
    }

    cout << "Riwayat Tontonan: " << endl;
    PtbNode *bantu = top;

    while (bantu != nullptr)
    {
        cout << "Judul: " << bantu->judul << endl;
        cout << "Durasi: " << bantu->durasi << endl;
        cout << "Status: " << bantu->status << endl;
        bantu = bantu->right;
    }
    cout << endl;
}

// hapus
void hapus(PtbNode *&root, string target)
{
    if (root == nullptr)
    {
        cout << "Video tidak ditemukan." << endl;
        return;
    }

    if (target < root->judul)
    {
        hapus(root->left, target);
    }
    else if (target > root->judul)
    {
        hapus(root->right, target);
    }
    else
    {
        if (root->left == nullptr)
        {
            root = root->right;
        }
        else if (root->right == nullptr)
        {
            root = root->left;
        }
        else
        {
            // yang ingin dihapus ketemu
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                root = nullptr;
            }
            else if (root->left == nullptr)
            {
                PtbNode *temp = root;
                root = root->right;
                delete temp;
            }
            else if (root->right == nullptr)
            {
                PtbNode *temp = root;
                root = root->left;
                delete temp;
            }
            else
            {
                // cari inorder dari dua anak
                PtbNode *successor = root->right;
                while (successor->left != nullptr)
                {
                    successor = successor->left;
                }
                // salin data ke successor root
                root->judul = successor->judul;
                root->durasi = successor->durasi;
                root->status = successor->status;

                // hapus successor
                hapus(root->right, successor->judul);
            }
        }
    }
}

// untuk undo yang terakhir dilakukan
void undo()
{
    if (undoLast.aksi == "")
    {
        cout << "Tidak ada aksi yang bisa di-undo." << endl;
        return;
    }

    if (undoLast.aksi == "tambah")
    {
        hapus(root, undoLast.judul);
        cout << "Undo berhasil. Video yang ditambahkan sudah dihapus." << endl;
    }
    else if (undoLast.aksi == "hapus")
    {
        tambahVideo(root, undoLast.judul, undoLast.durasi, undoLast.status);
        cout << "Undo berhasil. Hapus dibatalkan." << endl;
    }
    else if (undoLast.aksi == "tambah_playlist")
    {
        hapusdariPlaylist(undoLast.judul);
        PtbNode *vid = search(root, undoLast.judul);
        if (vid != nullptr)
        {
            vid->status = "Tersedia";
            cout << "Undo berhasil. Video dihapus dari playlist." << endl;
        }
    }
    else if (root, undoLast.aksi == "tontonVideo")
    {
        hapus(root, undoLast.judul);
        cout << "Undo berhasil." << endl;
    }
    else
    {
        cout << "Undo tidak bisa dilakukan." << endl;
    }

    // agar undo tidak dilakukan berulang-ulang
    undoLast = {"", "", "", ""};
}

void contohVideo()
{
    tambahVideo(root, "Film 1", "72 menit", "Tersedia");
    tambahVideo(root, "Film DEF", "120 menit", "Tersedia");
    tambahVideo(root, "Film Abc", "75 menit", "Tersedia");
    tambahVideo(root, "Film 2", "100 menit", "Tersedia");
    tambahVideo(root, "Film dSa", "20 menit", "Tersedia");
}

// tampilkan daftar video secara inorder
void inorder(PtbNode *root)
{
    int maxJudullength = 10;
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << left << setfill(' ') << setw(maxJudullength) << "Judul video: " << root->judul
         << "\tDurasi: " << root->durasi
         << "\tStatus: " << root->status << endl;
    inorder(root->right);
}

// pencarian di menu 2
void cari(PtbNode *root)
{
    string target;
    cout << "Apakah Anda ingin mencari video? (Y/N): ";
    cin >> pilihan;
    if (pilihan == 'Y' || pilihan == 'y')
    {
        cout << "Masukkan judul video: ";
        cin.ignore();
        getline(cin, target);

        searchBST(root, target);
    }
    else
    {
        return;
    }
}

int main()
{
    contohVideo();
    do
    {
        system("CLS");
        beranda();
        switch (menu)
        {
        case 1:
        {
            string input_judul, input_durasi;

            cout << "Masukkan judul: ";
            cin.ignore();
            getline(cin, input_judul);
            cout << "Masukkan durasi: ";
            getline(cin, input_durasi);
            tambahVideo(root, input_judul, input_durasi, "Tersedia");

            // undo
            undoLast = {"tambah", input_judul, input_durasi, "Tersedia"};
            break;
        }
        case 2:
            inorder(root);
            cari(root);
            break;
        case 3:
        {
            // simpan variabel lokal untuk judul sementara
            string input_pl_judul;

            // tampilkan video yang tersedia
            inorder(root);
            // input ke playlist
            cout << "Masukkan judul video untuk dimasukkan ke playlist: ";
            cin.ignore();
            getline(cin, input_pl_judul);

            // normalisasi input ke huruf kecil
            string input_pl_judul_lc = to_lowercase(input_pl_judul);
            PtbNode *vid = search(root, input_pl_judul_lc);

            if (vid && vid->status == "Tersedia")
            {
                vid->status = "Dalam antrian";
                tambah_playlist(vid->judul, vid->durasi, vid->status);
                cout << "Video berhasil ditambahkan ke playlist." << endl;
            }
            else
            {
                cout << "Video tidak bisa ditambahkan ke playlist." << endl;
            }
            tampilkanPlaylist();

            // undo
            undoLast = {"tambah_playlist", vid->judul, vid->durasi, vid->status};
            break;
        }
        case 4:
            tontonVideo();
            break;
        case 5:
            tampilkanRiwayat();
            break;
        case 6:
        {
            string hapus_judul;
            cout << "Masukkan judul video yang ingin dihapus: ";
            cin.ignore();
            getline(cin, hapus_judul);

            // undo
            PtbNode *hapusVid = search(root, hapus_judul);
            if (hapusVid)
            {
                undoLast = {"hapus", hapusVid->judul, hapusVid->durasi, hapusVid->status};
                hapus(root, hapus_judul);
            }
            else
            {
                cout << "Video tidak ditemukan." << endl;
            }

            hapus(root, hapus_judul);
            break;
        }
        case 7:
            undo();
            break;
        default:
            cout << "Menu yang dipilih tidak tersedia. Silakan pilih menu antara 1-7.";
            break;
        }
        cout << "Ulangi program? (Y/N)? ";
        cin >> pilihan;
    } while (pilihan == 'Y' || pilihan == 'y');
    return 0;
}
