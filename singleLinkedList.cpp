#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SINGLE LINK LIST

struct Node
{
    int angka;
    char nama[100];
    Node *next;
} *head, *tail;

Node *createNode(int angka, const char *nama){
    Node *newNode = (Node*)malloc(sizeof(Node));
    
    newNode->angka = angka;
    strcpy(newNode->nama, nama);
    newNode->next = NULL;
    
    return newNode;
}

// Function untuk masukin
// Push Head
void pushHead(int angka, const char *nama){
	Node *temp = createNode(angka, nama);
	
	if(!head){
		head = tail = temp;
	}else {
		// menghubungkan temp dengan head
		temp->next = head;
		head = temp;
	}
}

// Push Tail
void pushTail(int angka, const char *nama){
	Node *temp = createNode(angka, nama);
	
	if(!head){
		head = tail = temp;
	}else {
		// menghubungkan tail dengan temp
		tail->next = temp;
		tail = temp;
	}
}

// Push Mid
void pushMid(int angka, const char *nama) {
    Node *temp = createNode(angka, nama);
    if(!head) head = tail = temp;
    else if(head->angka > angka) pushHead(angka, nama);
    else if(tail->angka < angka) pushTail(angka, nama);
    else {
        Node *curr = head;
        Node *back;
        while(curr->angka < angka) {
            back = curr;
            curr = curr->next;
        }
        back->next = temp;
        temp->next = curr;
    }
}

// Function untuk buang / angkat dia keluar dari barisan
// Pop Head
void popHead(){
	if(!head){
		return;
	}
	else if(head == tail) {
		free(head);
		head = tail = NULL;
	}
	else {
		Node *temp = head->next;
		head->next = NULL;
		free(head);
		head = temp;
	}
}

// Pop Tail
void popTail(){
	if(!head){
		return;
	}
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	else {
		Node *curr = head;
		// cek satu satu dari depan
		while(curr->next != tail){
			curr = curr->next;
		}
		curr->next = NULL;
		free(tail);
		tail = curr;
	}
}

void popMid(int angka) {
    if(!head) return;
    if(head -> angka == angka) popHead();
    else if(tail -> angka == angka) popTail();
    else {
        Node *curr = head, *back;
        while(curr != NULL && curr -> angka < angka) {
            back = curr;
            curr = curr -> next;
        }
        back -> next = curr -> next;
        curr -> next = NULL;
        free(curr);
    }
}

// HEAD -> TEMP -> TAIL

void print(){
	Node *curr = head;
	while(curr != NULL){
		printf("%s %d -> ", curr->nama, curr->angka);
		curr = curr->next;
	}
}

int main(){

	pushHead(10, "aaaa");
	pushTail(11, "bbbb");
	pushHead(12, "cccc");
	pushTail(13, "dddd");
	popTail();
	popHead();
	print();

    return 0;
}
