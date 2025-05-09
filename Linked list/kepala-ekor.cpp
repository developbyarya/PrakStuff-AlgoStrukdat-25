#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int val){
        data = val;
        next = NULL;
    }
};

Node *kepala = new Node(-9999); 
Node *ekor = new Node(9999);

void sisipDepan(int data, Node* head, Node* tail){
    Node *baru = new Node(data);
    // hanya jika data kosong 
    if (head->next == tail){
        tail->next = baru;
    } else {
        baru->next = head->next;
    }
    head->next = baru;
}


void sisipBelakang(int data, Node* head, Node* tail){
    Node *baru = new Node(data);
    tail->next->next = baru;
    // hanya jika data kosong 
    if (head->next == tail){
        head->next = baru;
    }
    tail->next = baru;
}

void printList(Node* head, Node* tail){
    Node *bantu = head->next;
    while (bantu != nullptr){
        cout << bantu->data << "->";
        bantu = bantu->next;
    }
    cout << "|" << endl;
}

int main(){
    kepala->next = ekor;
    ekor->next = kepala;
    sisipDepan(20, kepala, ekor);
    printList(kepala, ekor);
    sisipBelakang(10, kepala, ekor);
    printList(kepala, ekor);
    sisipDepan(30, kepala, ekor);
    printList(kepala, ekor);
    sisipDepan(50, kepala, ekor);
    printList(kepala, ekor);
    sisipBelakang(40, kepala, ekor);
    printList(kepala, ekor);
    
    return 0;
}