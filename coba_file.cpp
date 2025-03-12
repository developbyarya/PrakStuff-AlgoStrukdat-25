#include <iostream>
using namespace std;

struct Mahasiswa {
    char nama[50];
    float ipk;
};

int main(){
    FILE *hiu;

    hiu = fopen("mahasiswa.dat", "wb");

    if (hiu == NULL){
        cout << "Gagal membuka file!" << endl;
        return 1;
    }
    
    
    Mahasiswa mhs[] = {{"Gradiva", 4}, {"Arya", 4}};
    fwrite(&mhs, sizeof(Mahasiswa), 2, hiu);
    fclose(hiu);

    hiu = fopen("mahasiswa.dat", "rb");
    Mahasiswa mhs1[2];
    fread(&mhs1, sizeof(Mahasiswa), 2, hiu);
    cout << mhs1[1].nama << endl;

    fclose(hiu);


    return 0;
}