#include <iostream>
#include <iomanip>
using namespace std;

struct Pegawai {
    int id_pegawai;
    char nama[100];
    float gaji;
};

int total_pegawai = 0;

void swap(Pegawai &a, Pegawai &b) {
    Pegawai temp = a;
    a = b;
    b = temp;
}
// Fungsi partition untuk Quick Sort
int partition(Pegawai arr[], int low, int high) {
    int pivot = arr[high].id_pegawai; // Pivot berdasarkan id_pegawai
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].id_pegawai < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}


// Implementasi Quick Sort
void quickSort(Pegawai arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int binary_search(Pegawai arr[], int n, int cari){
    quickSort(arr,0, n-1);
    int start = 0, end = n-1;

    while(start <= end){
        int mid = (start + end) / 2;
        if (arr[mid].id_pegawai == cari){
            return mid;
        } else if (cari < arr[mid].id_pegawai){
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    return -1;

}


void save_to_file(Pegawai daftar_pegawai[], int n){
    char filename[] = "pegawai.dat";
    FILE* filePtr = fopen(filename, "ab");

    fwrite(daftar_pegawai, sizeof(*daftar_pegawai), n, filePtr);

    fclose(filePtr);

}
void overwrite(Pegawai daftar_pegawai[], int n){
    char filename[] = "pegawai.dat";
    FILE* filePtr = fopen(filename, "wb");

    fwrite(daftar_pegawai, sizeof(*daftar_pegawai), n, filePtr);

    fclose(filePtr);

}

void read_from_file() {
    char filename[] = "pegawai.dat";
    FILE* filePtr = fopen(filename, "rb");

    if (!filePtr) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    // 1. Hitung jumlah data dalam file
    int jumlah = 0;
    Pegawai temp;
    while (fread(&temp, sizeof(Pegawai), 1, filePtr) == 1) {
        jumlah++;
    }

    // Jika tidak ada data, tutup file dan keluar
    if (jumlah == 0) {
        cout << "File kosong!" << endl;
        fclose(filePtr);
        return;
    }

    // 2. Buat array sepanjang jumlah data
    Pegawai daftar_pegawai[jumlah];

    // 3. Baca ulang file dan masukkan ke array
    rewind(filePtr);  // Kembalikan pointer file ke awal
    fread(daftar_pegawai, sizeof(Pegawai), jumlah, filePtr);
    fclose(filePtr);

    // 4. Urutkan array menggunakan Quick Sort
    quickSort(daftar_pegawai, 0, jumlah - 1);

    // 5. Tampilkan data sesuai format
    cout << "Data Pegawai yang telah diurutkan:\n";
    cout << "----------------------------------\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "ID: " << daftar_pegawai[i].id_pegawai << endl;
        cout << "Nama: " << daftar_pegawai[i].nama << endl;
        cout << "Gaji: Rp. " << fixed << setprecision(0) << daftar_pegawai[i].gaji << endl;
        cout << "------------------------------" << endl;
    }

}

void update_file(int id_cari) {
    char filename[] = "pegawai.dat";
    FILE* filePtr = fopen(filename, "rb");

    if (!filePtr) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    // 1. Hitung jumlah data dalam file
    int jumlah = 0;
    Pegawai temp;
    while (fread(&temp, sizeof(Pegawai), 1, filePtr) == 1) {
        jumlah++;
    }

    // Jika tidak ada data, tutup file dan keluar
    if (jumlah == 0) {
        cout << "File kosong!" << endl;
        fclose(filePtr);
        return;
    }

    // 2. Buat array sepanjang jumlah data
    Pegawai daftar_pegawai[jumlah];

    // 3. Baca ulang file dan masukkan ke array
    rewind(filePtr);  // Kembalikan pointer file ke awal
    fread(daftar_pegawai, sizeof(Pegawai), jumlah, filePtr);
    fclose(filePtr);

    // 4. Urutkan array menggunakan Quick Sort
    quickSort(daftar_pegawai, 0, jumlah - 1);

    // 5. Cari data
    int index_hasil = binary_search(daftar_pegawai, jumlah, id_cari);
    float gaji_baru;
    if (index_hasil != -1) {
        cout << "Pegawai di Temukan\n";
        cout << "----------------------------------\n";
        cout << "ID: " << daftar_pegawai[index_hasil].id_pegawai << endl;
        cout << "Nama: " << daftar_pegawai[index_hasil].nama << endl;
        cout << "Masukan gaji Baru: "; cin >> gaji_baru;
        daftar_pegawai[index_hasil].gaji = gaji_baru;
        cout << "------------------------------" << endl;
        overwrite(daftar_pegawai, jumlah);
    } else {
        cout << "Data tidak ditemukan!" << endl;
    }

}




void view_tambah_data();
void view_lihat_data();
void view_cari_data();
void view_perbarui();

int main()
{
    int pilih;
    do {
        cout << "===SI Kepegawaian===" << endl;
        cout << "1. Tambah data pegawai" << endl
            << "2. Lihat data pegawai" << endl
            << "3. Cari data pegawai" << endl
            << "4. Perbarui gaji" << endl
            << "0. Keluar" << endl;
        cout << "Pilih: "; cin >> pilih;
        switch (pilih)
        {
        case 1:
            view_tambah_data();
            break;
        case 2:
            view_lihat_data();
            break;
        case 3:
            view_cari_data();
            break;
        case 4:
            view_perbarui();
            break;
        
        
        default:
            break;
        }
    }while (pilih != 0);
    return 0;
}
void view_tambah_data(){
    cout << "===Tambah data===" << endl;
    int jumlah;
    cout << "Masukan jumlah data: "; cin >> jumlah;
    Pegawai daftar_pegawai[jumlah];


    for (int i=0; i < jumlah; i++){
        cout << "Masukan id: "; cin >> daftar_pegawai[i].id_pegawai;
        cin.ignore();
        cout << "Masukan nama: "; cin.getline(daftar_pegawai[i].nama, 100);  
        cout << "Masukan gaji: "; cin >> daftar_pegawai[i].gaji;
        cout << "---------------------------------------" << endl;
    }

    save_to_file(daftar_pegawai, jumlah);
    total_pegawai += jumlah;

    cout << jumlah << " data berhasil ditambahkan" << endl;
}

void view_lihat_data(){
    cout << "===Daftar Pegawai===" << endl;
    Pegawai daftar_pegawai[total_pegawai];

    read_from_file();

}

void view_cari_data(){
    int id_cari;
    
    Pegawai pegawai;


    cout << "===Cari data===" << endl;
    cout << "Masukan id untuk dicari: ";
    cin >> id_cari;

    char filename[] = "pegawai.dat";
    FILE* filePtr = fopen(filename, "rb");


    while (fread(&pegawai, sizeof(Pegawai), 1, filePtr) == 1 ){
        if (pegawai.id_pegawai == id_cari){
            cout << "ID: " << pegawai.id_pegawai << endl;
            cout << "Nama: " << pegawai.nama << endl;
            cout << "Gaji: Rp. " << fixed << setprecision(0) << pegawai.gaji << endl;
            cout << "------------------------------" << endl;
            break;
        }
    }

    fclose(filePtr);


}

void view_perbarui(){
    cout << "===Perbarui Gaji===" << endl;
    Pegawai daftar_pegawai[total_pegawai];
    int id_cari;
    cout << "Masukan id untuk dicari: "; cin >> id_cari;
    
    update_file(id_cari);


}
