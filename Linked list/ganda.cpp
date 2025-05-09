#include <iostream> 
using namespace std;

struct Node{
    int data;
    Node* next;
    Node* prev;
};

void sisipDepan(int data, Node*& head){
    Node* newNode = new Node{data, nullptr, nullptr};
    newNode->next = head;

    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
}

void sisipBelakang(int data, Node* head){
    Node* newNode = new Node{data, nullptr, nullptr};
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void sisipTengah(int data, Node* head){
    Node* newNode = new Node{data, nullptr, nullptr};
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp != nullptr && temp->data < data) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        sisipBelakang(data, head);
        return;
    }
    newNode->next = temp;
    newNode->prev = temp->prev;
    if (temp->prev != nullptr) {
        temp->prev->next = newNode;
    } else {
        head = newNode;
    }
    temp->prev = newNode;

}

void hapusDepan(Node*& head){
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
}

void hapusBelakang(Node*& head){
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    if (temp->prev != nullptr) {
        temp->prev->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
}

void hapusSpesifik(Node*& head, int kunci){
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    while (temp != nullptr && temp->data != kunci) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        return; // Kunci tidak ditemukan
    }
    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next; // Hapus node pertama
    }
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    delete temp;
}

void printDepan(Node* head){
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " <-> ";
        temp = temp->next;
    }
    cout << "|>" << endl;
}

void printBelakang(Node* head){
    Node* temp = head;
    while(temp->next != nullptr) {
        temp = temp->next;
    }

    while (temp != nullptr) {
        cout << temp->data << " <-> ";
        temp = temp->prev;
    }
    cout << "|>" << endl;
}

int main(){
    Node* kepala = nullptr;
    sisipDepan(20, kepala);
    printDepan(kepala);
    sisipBelakang(40, kepala);
    printDepan(kepala);
    sisipTengah(30, kepala);
    printDepan(kepala);
    sisipDepan(0, kepala);
    printBelakang(kepala);



}