#include <iostream>
using namespace std;

struct Buku {
    int no_ref;
    string title;
    string publisher;
};

struct PTBNode {
    Buku buku;
    PTBNode* left;
    PTBNode* right;
};

PTBNode* ptb_root = nullptr;

void save_file(string filename, string content)
{
    FILE* file = fopen(filename.c_str(), "w");
    // WRite files
    fwrite((content + "\n").c_str(), sizeof(char), content.length()+1, file); 
    fclose(file);

}

string buku_to_str(Buku buku){
    return buku.title + "-" + buku.publisher + "-" + to_string(buku.no_ref);
}

PTBNode* PTB_insert(PTBNode* root, Buku buku){
    if (!root){
        PTBNode* newNode = new PTBNode;
        newNode->buku = buku;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return root;
    };
    if (buku.no_ref < root->buku.no_ref) root->left = PTB_insert(root->left, buku);
    else root->right = PTB_insert(root->right, buku);
    return root;

}


void tambah_buku(Buku buku) {
    if (ptb_root == nullptr) {
       ptb_root = new PTBNode; 
       ptb_root->buku = buku;
       ptb_root->left = nullptr;
       ptb_root->right = nullptr;

       save_file("rak-utama.txt", buku_to_str(buku));

    } else {

    }

}


int main(){
    cout << "==============================" << endl;
    cout << "           Library            " << endl;
    cout << "==============================" << endl;
    cout << "1. Tambah buku" << endl;
    cout << "2. Cari lokasi buku" << endl;
    cout << "3. Daftar isi rak " << endl;
    Buku t_buku;
    t_buku.no_ref = 123;
    t_buku.title = "Hary";
    t_buku.publisher = "JK Rowling";
    tambah_buku(t_buku);



    return 0;
}