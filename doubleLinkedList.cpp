#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Double Link List

struct Node
{
    int angka;
    char nama[100];
    Node *next;
    Node *prev; 
} *head, *tail;

Node *createNode(int angka, const char *nama){
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->angka = angka;
    strcpy(newNode->nama, nama);
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void pushHead(int angka, const char *nama){
    Node *temp = createNode(angka, nama);

    if(!head){
        head = tail = temp;
    }else {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
}

void pushTail(int angka, const char *nama){
    Node *temp = createNode(angka, nama);

    if(!head){
        head = tail = temp;
    }else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void pushMid(int angka, const char *nama){
    Node *temp = createNode(angka, nama);

    if(!head){
        head = tail = temp;
    }else if(angka < head->angka){
        pushHead(angka, nama);
    }else if (angka > tail->angka){
        pushTail(angka, nama);
    }else{
        Node *curr = head;
        // Bandingkan sama angka yang mau kita masukin
        while (curr->angka < angka){
            curr = curr->next;
        }
        curr->prev->next = temp;
        temp->prev = curr->prev;
        curr->prev = temp;
        temp->next = curr;
    }
}

void popHead(){
    if(!head){
        return;
    }
    else if(head == tail){
        free(head);
        head = tail = NULL;
    }
    else{
        Node *temp = head->next;
        head->next = NULL;
        temp->prev = NULL;
        free(head);
        head = temp;
    }
}

void popTail(){
    if(!head){
        return;
    }
    else if(head == tail){
        free(head);
        head = tail = NULL;
    }
    else{
        Node *temp = tail->prev;
        tail->prev = NULL;
        temp->next = NULL;
        free(tail);
        tail = temp;
    }
}

void popMid(int angka){
    if(!head){
        head = tail = NULL;
    }
    else if(head->angka == angka){
        popHead();
    }
    else if(tail->angka == angka){
        popTail();
    }
    else{
        Node *curr = head->next;
        while (curr->angka != angka){
            curr = curr->next;
        }
        
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = NULL;
        curr->next = NULL;
        free(curr);
    }
}

void print(){
    Node *curr = head;
    while (curr != NULL)
    {
        printf("%d %s -> ", curr->angka, curr->nama);
        curr = curr->next;
    }
    
}

int main(){
    // pushHead(10);
    // pushHead(5);
    // pushTail(15);
    // popHead();
    // popTail();

    pushMid(7, "Budi");
    pushMid(9, "Udin");
    pushMid(8, "Kepin");
    pushMid(10, "Asep");

    popMid(9);

    print();

    return 0;
}