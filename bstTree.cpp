#include<stdio.h>
#include<stdlib.h>

struct Node{
	int key;
	Node *left;
	Node *right;
};

Node *createNode(int key){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

Node *insertNode(Node *temp, int key){
	Node *masuk = createNode(key);
	
	if(temp == NULL){
		return masuk;
	}
	
	else if(temp->key > key){
		temp->left = insertNode(temp->left, key);
	}
	
	else if(temp -> key < key){
		temp->right = insertNode(temp->right, key);
	}
	
	return temp;
}

void printInOrder(Node *curr){
	if(curr != NULL){
		printInOrder(curr->left);
		printf("%d -> ", curr->key);
		printInOrder(curr->right);
	}
}

void printPreOrder(Node *curr){
	if(curr != NULL){
		printf("%d -> ", curr->key);
		printPreOrder(curr->left);
		printPreOrder(curr->right);
	}
}

void printPostOrder(Node *curr){
	if(curr != NULL){
		printPostOrder(curr->left);
		printPostOrder(curr->right);
		printf("%d -> ", curr->key);
	}
}

void searchNode(Node *curr, int key){
	if(curr == NULL){
		printf("Ga Ketemu\n");
		return;
	}
	
	else{
		if(curr -> key == key){
			printf("Ketemu\n");
		}
		
		else if(curr -> key > key){
			searchNode(curr->left, key);
		}
		
		else if(curr -> key < key){
			searchNode(curr->right, key);
		}
	}
}

Node *removeNode(Node *root, int key){
	if(root == NULL){
		return NULL;
	}
	
	else if(root->key > key){
		root->left = removeNode(root->left, key);
	}
	
	else if(root->key < key){
		root->right = removeNode(root->right, key);
	}
	
	else if(key == root->key){
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
		}
		
		else if(root->left == NULL || root->right == NULL){
			Node *temp;
			
			if(root->left == NULL){
				temp = root->right;
			}
			
			else if(root->right == NULL){
				temp = root->left;
			}
			
			*root = *temp;
			free(temp);
			temp = NULL;
		}
		
		//predecessor = nilai terbesar di kiri 
		//sucessor = nilai terkecil di kanan
		else{  // predecessor
			Node *temp = root->left;
			
			while(temp->right){
				temp = temp->right;
			}
			
			root->key = temp->key;
			
			root->left = removeNode(root->left, temp->key);    // menghapus nilai yang kita ambil tadi
			
		}
		
		return root;
		
//		else{  // sucessor
//			Node *temp = curr -> right
//			
//			while(temp -> left){
//				temp = temp -> left
//			}
//			
//			curr -> key = temp -> key;
//			
//			curr -> right = removeNode(curr -> right, temp -> key)    // menghapus nilai yang kita ambil tadi
//			
//		}
	}
}


int main(){
	Node *root = NULL;
	root = insertNode(root, 20);
	insertNode(root, 15);
	insertNode(root, 21);
	insertNode(root, 25);
	insertNode(root, 13);
//	printPostOrder(root);
//	searchNode(root, 21);
	removeNode(root, 21);
	printInOrder(root);
	
	return 0;
}