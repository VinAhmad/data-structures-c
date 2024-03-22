#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const int size = 26;

struct Table{
	char nama[100];
	Table *next;
	Table *prev;
}*table[size], *tHead[size], *tTail[size];

Table *createTable(const char *nama){
	Table *newData = (Table*)malloc(sizeof(Table));
	strcpy(newData -> nama, nama);
	newData -> next = NULL;
	newData -> prev = NULL;
	
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
	
	if(tHead[index] == NULL){
		tHead[index] = tTail[index] = temp;
	}
	
	else{
		if(strcmp(tHead[index] -> nama, nama) >= 0){
			temp -> next = tHead[index];
			tHead[index] -> prev = temp;
			tHead[index] = temp;
		}
		
		else if(strcmp(tTail[index] -> nama, nama) <= 0){
			tTail[index] -> next = temp;
			temp -> prev = tTail[index];
			tTail[index] = temp;
		}
		
		else{
			Table *curr = tHead[index] -> next;
		
			while(strcmp(curr -> nama, nama) <= 0){
				curr = curr -> next;
			}
				
			// ab -> next = temp
			curr -> prev -> next = temp;
			temp -> prev = curr -> prev;
			temp -> next = curr;
			curr -> prev = temp;
		}
	}
}

void print(){
	for(int i=0; i<size;i++){
		printf("Index %d: ", i);
		if(tHead[i] == NULL){
			printf("-\n");
		}
		
		else{
			Table *curr = tHead[i];
			while(curr != NULL){
				printf("%s ", curr -> nama);
				curr = curr -> next;
				
				if(curr != NULL){
					printf("-> ");
				}
			}
			printf("\n");
		}
	}
}

void del(const char *nama){
	int index = hash(nama);
	
	if(!tHead[index]){
		return;
	}
	
	else if(strcmp(tHead[index] -> nama, nama) == 0){
		if(strcmp(tHead[index] -> nama, tTail[index]-> nama) == 0){
			free(tHead[index]);
			tHead[index] = tTail[index] = NULL;
		}
		
		else{
			Table *temp = tHead[index] -> next;
			temp -> prev = NULL;
			tHead[index] -> next = NULL;
			free(tHead[index]);
			tHead[index] = temp;
		}
	}
	
	else if(strcmp(tTail[index] -> nama, nama) == 0){
		Table *temp = tTail[index] -> prev;
		temp -> next = NULL;
		tTail[index] -> prev = NULL;
		free(tTail[index]);
		tTail[index] = temp;	
	}
	
	else{
		Table *curr = tHead[index] -> next;
		while(strcmp(curr -> nama, nama) != 0){
			curr = curr -> next;
		}
		
		curr -> prev -> next = curr -> next;
		curr -> next -> prev = curr -> prev;
		curr -> prev = NULL;
		curr -> next = NULL;
		free(curr);
	}
	
	
}

int main(){
	insert("Abi");
	insert("Babi");
	insert("Aan");
	insert("Ad");
	del("Abi");
	print();
	
	return 0;
	
}