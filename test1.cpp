#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data
{
    char nama[100];
    int nim;
    Data *next;
    Data *prev;
} *head, *tail;

Data *createData(const char *nama, int nim){
    Data *newData = (Data*)malloc(sizeof(Data));

    strcpy(newData->nama, nama);
    newData->nim = nim;
    newData->next = NULL;
    newData->prev = NULL;

    return newData;
}

void pushHead(const char *nama, int nim){
    Data *temp = createData(nama, nim);
    
    if(!head){
        head = tail = temp;
    }
    else {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
}

void pushTail(const char *nama, int nim){
    Data *temp = createData(nama, nim);

    if(!head){
        head = tail = temp;
    }
    else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void pushMid(const char *nama, int nim){
    Data *temp = createData(nama, nim);

    if(!head){
        head = tail = temp;
    }
    else if(nim < head->nim){
        pushHead(nama, nim);
    }
    else if (nim > tail->nim){
        pushTail(nama, nim);
    }
    else {
        Data *curr = head;
        while(curr->nim < nim){
            curr = curr->next;
        }
        // 5 - 6 - 8
        // curr->prev = 5
        // temp = 6
        // curr = 8
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
    else {
        Data *temp = head->next;
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
    else if (head == tail){
        free(head);
        head = tail = NULL;
    }
    else {
        Data *temp = tail->prev;
        tail->prev = NULL;
        temp->next = NULL;
        free(tail);
        tail = temp;
    }
}

void popMid(int nim){
    if(!head){
        return;
    }
    else if(head->nim == nim){
        popHead();
    }
    else if(tail->nim == nim){
        popTail();
    }
    else {
        Data *curr = head->next;
        while(curr->nim != nim){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->next = NULL;
        curr->prev = NULL;
        free(curr);
    }
}

void printData(){
    if (!head){
        printf("NO DATA!\n");
    }
    else {
        Data *curr = head;
        while(curr != NULL){
            printf("%s %d -> ", curr->nama, curr->nim);
            curr = curr->next;
        }
    }
}

void popAll(){
    while(head){
        popHead();
    }
}

int main(){

    pushTail("AAA", 2);
    pushTail("BBB", 5);
    pushTail("DDD", 8);
    pushMid("CCC", 6);

    // popAll();

    printData();

    return 0;
}