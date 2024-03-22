#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hash Table - Single

const int size = 5;

struct Table
{
    char nama[100];
} *table[size];

Table *createTable(const char *nama){
    Table *newData = (Table*)malloc(sizeof(Table));
    strcpy(newData->nama, nama);

    return newData;
}

int hash(const char *nama){
    if(nama[0] >= 'A' && nama[0] <= 'Z'){
        return (nama[0] - 'A') % size;
    }
    else if(nama[0] >= 'a' && nama[0] <= 'z'){
        return (nama[0] - 'a') % size;
    }
}

void insert(const char *nama){
    Table *temp = createTable(nama);
    int index = hash(nama);

    if(table[index] == NULL){
        table[index] = temp;
    }
    else {
        int point = index + 1;
        while (table[point] != NULL){
            point = (point + 1) % size;

            if(point == index){
                printf("Table Full\n");
                return;
            }
        }
        
        table[point] = temp;
    }
}

void del(const char *nama){
    int index = hash(nama);

    if(strcmp(table[index]->nama, nama) == 0){
        free(table[index]);
        table[index] = NULL;
    }
    else {
        int point = index + 1;
        while (table[point] == NULL || strcmp(table[point]->nama, nama) != 0){
            point = (point + 1) % size;

            if(point == index){
                printf("Ga ketemu\n");
                return;
            }
        }
        
        free(table[point]);
        table[point] = NULL;
    }
}

void print(){
    for(int i = 0; i < size; i++){
        printf("index %d: ", i);

        if(table[i] == NULL){
            printf("NULL\n");
        }
        else {
            printf("%s\n", table[i]->nama);
        }
    }
}

int main(){
    insert("Anto");
    insert("Caca");
    insert("Cari");
    insert("Coco");
    insert("Can");
    del("Anto");
    del("Coco");
    print();


    return 0;
}