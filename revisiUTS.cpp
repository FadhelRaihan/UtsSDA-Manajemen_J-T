#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <cstdio>
#include <vector>
#include <conio.h>
#include <iomanip>

using namespace std;

struct dataAdmin
{
    string username = "admin", password = "admin123";
};

struct laporanKaryawan
{
    string tanggal;
    int gaji = 0, barang = 0;
};

struct dataKaryawan
{
    string nama, alamat;
    int usia;
    vector<laporanKaryawan> laporan; // Menggunakan vektor untuk laporan karyawan
    dataKaryawan *prevData;
    dataKaryawan *nextData;
};

dataKaryawan *headData = NULL;

bool isEmptyData()
{
    if (headData == NULL)
        return true;
    return false;
}

bool kembali()
{
    string kembali;
    while (true)
    {
        cout << "\nKembali ke menu awal[Y/N]: ";
        cin >> kembali;

        if (kembali == "Y" || kembali == "y")
        {
            return true;
        }
        else if (kembali == "N" || kembali == "n")
        {
            return false;
        }
        else
        {
            cout << "Input tidak valid. Harap masukkan Y atau N." << endl;
        }
    }
}

bool cekHuruf(const string &str)
{
    for (char karakter : str)
    {
        if (!isalpha(karakter) && karakter != ' ')
        {
            return false;
        }
    }
    return true;
}

void login()
{
    dataAdmin data;
    while (true)
    {
        string user, pass;
        system("cls");
        cout << "=====|LOGIN SISTEM MANAJEMEN KARYAWAN J&T|=====" << endl;

        cout << "\nUsername : ";
        cin >> user;
        cin.ignore();

        cout << "Password : ";
        char ch;
        while ((ch = _getch()) != '\r')
        {
            if (ch == '\b')
            {
                if (pass.length() > 0)
                {
                    pass.pop_back();
                    cout << "\b \b";
                }
            }
            else
            {
                pass += ch;
                cout << '*';
            }
        }
        cout << endl;

        if (user == data.username && pass == data.password)
        {
            cout << "Login berhasil. Enter untuk lanjut...";
            cin.clear();
            getchar();
            break;
        }
        else
        {
            cout << "Username atau password salah. Enter untuk mengulang...";
            cin.clear();
            getchar();
        }
    }
}

void createData()
{
    while (true)
    {
        system("cls");
        cout << "=====|BUAT/TAMBAH DATA KARYAWAN|=====\n";

        dataKaryawan *newData = new dataKaryawan;

        cout << "\nNama     : ";
        getline(cin >> ws, newData->nama);
        while (!cekHuruf(newData->nama))
        {
            cout << "\nInput bukan berupa huruf. Tekan enter untuk mengulang...";
            cin.clear();
            getchar();
            cout << "\nNama     : ";
            getline(cin >> ws, newData->nama);
        }

        cout << "Usia     : ";
        while (!(cin >> newData->usia))
        {
            cout << "\nInput bukan berupa angka. Tekan enter untuk mengulang...";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            cout << "Usia     : ";
        }

        cout << "Alamat   : ";
        getline(cin >> ws, newData->alamat);

        cout << "\nData sudah ditambahkan" << endl;

        if (isEmptyData())
        {
            newData->prevData = NULL;
            newData->nextData = NULL;
            headData = newData;
        }
        else
        {
            dataKaryawan *current = headData;
            while (current->nextData != NULL)
            {
                current = current->nextData;
            }
            current->nextData = newData;
            newData->prevData = current;
            newData->nextData = NULL;
        }

        if (kembali())
        {
            break;
        }
    }
}

void tambahGaji()
{
    string namaKaryawan;

    while (true)
    {
        system("cls");
        dataKaryawan *current = headData;
        cout << "=====|TAMBAH GAJI KARYAWAN|=====" << endl;
        cout << "\nNama karyawan: ";
        getline(cin >> ws, namaKaryawan);

        if (isEmptyData())
        {
            cout << "\nLinked list kosong" << endl;
            if (kembali())
            {
                break;
            }
            else
            {
                break;
            }
        }

        bool ditemukan = false;
        while (current != NULL)
        {
            if (current->nama == namaKaryawan)
            {
                ditemukan = true;
                break;
            }
            current = current->nextData;
        }

        if (!ditemukan)
        {
            cout << "\nData dengan nama " << namaKaryawan << " tidak ditemukan" << endl;
            if (kembali())
            {
                break;
            }
        }
        else
        {
            laporanKaryawan laporan;
            cout << "Tanggal laporan (dd/mm/yy): ";
            getline(cin >> ws, laporan.tanggal);

            cout << "Jumlah barang: ";
            cin >> laporan.barang;

            int totalGaji = laporan.barang * 1700;
            laporan.gaji = totalGaji;

            current->laporan.push_back(laporan);
            cout << "\nLaporan gaji berhasil ditambahkan" << endl;
            if (kembali())
            {
                break;
            }
        }
    }
}

void ambilGaji()
{
    string namaKaryawan;

    while (true)
    {
        system("cls");
        dataKaryawan *current = headData;
        cout << "=====|AMBIL GAJI KARYAWAN|=====" << endl;
        cout << "\nNama karyawan: ";
        getline(cin >> ws, namaKaryawan);

        if (isEmptyData())
        {
            cout << "\nLinked list kosong" << endl;
            if (kembali())
            {
                break;
            }
            else
            {
                break;
            }
        }

        bool ditemukan = false;
        while (current != NULL)
        {
            if (current->nama == namaKaryawan)
            {
                ditemukan = true;
                break;
            }
            current = current->nextData;
        }

        if (!ditemukan)
        {
            cout << "\nData dengan nama " << namaKaryawan << " tidak ditemukan" << endl;
            if (kembali())
            {
                break;
            }
        }
        else
        {
            current->laporan.clear();
            cout << "\nSemua laporan karyawan " << namaKaryawan << " berhasil dihapus" << endl;
            cout << "Enter untuk lanjut...";
            cin.clear();
            getchar();
            return;
        }
    }
}

void kelolaGaji()
{
    int pilihFitur;

    while (true)
    {
        system("cls");
        cout << "=====|KELOLA GAJI KARYAWAN|=====" << endl;
        cout << "\n |1. Tambah gaji karyawan   |" << endl;
        cout << " |2. Ambil gaji karyawan    |" << endl;
        cout << " |3. Keluar                 |" << endl;
        cout << "\nPilih fitur: ";
        if (cin >> pilihFitur)
        {
            if (pilihFitur == 1)
            {
                tambahGaji();
            }
            else if (pilihFitur == 2)
            {
                ambilGaji();
            }
            else if (pilihFitur == 3)
            {
                break;
            }
            else
            {
                cout << "Pilihan tidak valid, tekan enter untuk mengulang...";
                cin.ignore();
                getchar();
                break;
            }
        }
        else
        {
            cout << "\nInput bukan berupa angka. Tekan enter untuk mengulang..." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
        }
    }
}

void cetakDataTable()
{
    while (true)
    {
        dataKaryawan *current = headData;
        int urutan = 1;
        system("cls");
        cout << "=====|DATA KARYAWAN|=====\n";
        cout << "\n"
             << endl;
        // Menentukan lebar kolom
        const int colWidth = 15;

        // Mencetak header tabel
        cout << setw(colWidth) << left << "No" << setw(colWidth) << left << "Nama" << setw(colWidth) << left << "Usia" << setw(colWidth) << left << "Alamat" << endl;

        // Mencetak baris pembatas
        cout << setw(colWidth * 4) << setfill('-') << "" << setfill(' ') << endl;

        // Mencetak data
        while (current != NULL)
        {
            cout << setw(colWidth) << left << urutan++
                 << setw(colWidth) << left << current->nama
                 << setw(colWidth) << left << current->usia
                 << setw(colWidth) << left << current->alamat << endl;

            current = current->nextData;
        }

        if (kembali())
        {
            break;
        }
    }
}

void cetakLaporanTable()
{
    string namaKaryawan;
    int totalGaji = 0;
    int urutan = 1;
    string status;

    while (true)
    {
        system("cls");
        dataKaryawan *current = headData;
        cout << "=====|DATA KARYAWAN|=====" << endl;
        cout << "\nNama karyawan : ";
        getline(cin >> ws, namaKaryawan);

        if (isEmptyData())
        {
            cout << "\nLinked list kosong" << endl;
            if (kembali())
            {
                break;
            }
            else
            {
                break;
            }
        }

        bool ditemukan = false;
        while (current != NULL)
        {
            if (current->nama == namaKaryawan)
            {
                ditemukan = true;
                break;
            }
            current = current->nextData;
        }

        if (!ditemukan)
        {
            cout << "\nData dengan nama " << namaKaryawan << " tidak ditemukan" << endl;
            if (kembali())
            {
                break;
            }
        }
        else
        {
            system("cls");
            cout << "=====|LAPORAN GAJI KARYAWAN|=====" << endl;
            cout << "\n" << endl;
           
            // Menentukan lebar kolom
            const int colWidth = 15;

            // Mencetak header tabel
            cout << setw(colWidth) << left << "No" << setw(colWidth) << left << "Tanggal" << setw(colWidth) << left << "Jumlah Barang" << setw(colWidth) << left << "Gaji" << endl;

            // Mencetak baris pembatas
            cout << setw(colWidth * 4) << setfill('-') << "" << setfill(' ') << endl;

            // Mencetak data
            for (int i = 0; i < current->laporan.size(); ++i)
            {
                cout << setw(colWidth) << left << urutan++
                     << setw(colWidth) << left << current->laporan[i].tanggal
                     << setw(colWidth) << left << current->laporan[i].barang
                     << setw(colWidth) << left << current->laporan[i].gaji << endl;

                totalGaji += current->laporan[i].gaji;
            }

            if (current->laporan.empty())
            {
                status = "Sudah diambil";
            }
            else
            {
                status = "Belum diambil";
            }
            
            cout << "\nTotal gaji: " << totalGaji << endl;
            cout << "Status gaji: " << status << endl;

            if (kembali())
            {
                break;
            }
        }
    }
}

void hapusData()
{
    while (true)
    {
        system("cls");
        dataKaryawan *current = headData;
        dataKaryawan *prev = NULL;
        string namaKaryawan;

        cout << "=====|HAPUS DATA KARYAWAN|=====" << endl;
        cout << "\nNama karyawan yang ingin dihapus: ";
        getline(cin >> ws, namaKaryawan);

        // kondisi ketika list kosong
        if (isEmptyData())
        {
            cout << "\nLinked list kosong" << endl;
            if (kembali())
            {
                break;
            }
            else
            {
                break;
            }
        }

        // mencari list dengan nama yang sama dengan yang di inputkan
        while (current != NULL && current->nama != namaKaryawan)
        {
            prev = current;
            current = current->nextData;
        }

        // kondisi ketika list ditemukan
        if (current != NULL)
        {
            // jika list yang akan dihapus adalah head
            if (prev == NULL)
            {
                headData = headData->nextData;
            }
            else
            {
                prev->nextData = current->nextData;
                if (current->nextData != NULL)
                {
                    current->nextData->prevData = prev;
                }
            }
            delete current;
            cout << "\nData dengan nama " << namaKaryawan << " telah dihapus" << endl;
            if (kembali())
            {
                break;
            }
        }
        else
        {
            cout << "\nData dengan nama " << namaKaryawan << " tidak ditemukan" << endl;
            if (kembali())
            {
                break;
            }
        }
    }
}

int main()
{
    while (true)
    {
        int pilihFitur;

        while (true)
        {
            system("cls");
            cout << "=====|MANAJEMEN KARYAWAN J&T|=====" << endl;
            cout << "\n        |1. Login       |" << endl;
            cout << "        |2. Keluar      |" << endl;
            cout << "\nPilih fitur: ";
            if (cin >> pilihFitur)
            {
                if (pilihFitur == 1)
                {
                    login();
                    break;
                }
                else if (pilihFitur == 2)
                {
                    system("cls");
                    return false;
                }
            }
        }

        while (true)
        {
            system("cls");
            cout << "=====|MANAJEMEN KARYAWAN J&T|=====" << endl;
            cout << "\n |1. Tambah data karyawan       |" << endl;
            cout << " |2. Kelola gaji karyawan       |" << endl;
            cout << " |3. Hapus data karyawan        |" << endl;
            cout << " |4. Tampilkan data karyawan    |" << endl;
            cout << " |5. Tampilkan laporan karyawan |" << endl;
            cout << " |6. Keluar                     |" << endl;
            cout << "\nPilih fitur: ";
            if (cin >> pilihFitur)
            {
                if (pilihFitur == 1)
                {
                    createData();
                }
                else if (pilihFitur == 2)
                {
                    kelolaGaji();
                }
                else if (pilihFitur == 3)
                {
                    hapusData();
                }
                else if (pilihFitur == 4)
                {
                    cetakDataTable();
                }
                else if (pilihFitur == 5)
                {
                    cetakLaporanTable();
                }
                else if (pilihFitur == 6)
                {
                    break;
                }
                else
                {
                    cout << "Pilihan tidak valid, tekan enter untuk mengulang...";
                    cin.ignore();
                    getchar();
                    break;
                }
            }
            else
            {
                cout << "\nInput bukan berupa angka. Tekan enter untuk mengulang..." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getchar();
            }
        }
    }
    return 0;
}