#include<stdio.h>
#include<stdlib.h>

struct Node{
	int key;
	Node *left;
	Node *right;
	int height;
};

Node *createNode(int key){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
	
	
	return newNode;
}

int max(int a, int b){
	if(a > b){
		return a;
	}
	
	else{
		return b;
	}
}

int getHeight(Node *node){
	if(node == NULL){
		return 0;
	}
	
	return node->height;
}

int getBalance(Node *node){
	if(node == NULL){
		return 0;
	}
	
	return getHeight(node->left) - getHeight(node->right);
}

Node *rightRotate(Node *node){
	Node *a = node->left;
	Node *b = a->right;
	
	//rotatenya
	a->right = node;
	node->left = b;
	
	//update tinggi
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	a->height =  1 + max(getHeight(node->left), getHeight(node->right));
}

Node *leftRotate(Node *node){
	Node *a = node->right;
	Node *b = a->left;
	
	//rotatenya
	a->left = node;
	node->right = b;
	
	//update tinggi
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	a->height =  1 + max(getHeight(node->left), getHeight(node->right));
}

Node *insertNode(Node *node, int key){
	Node *temp = createNode(key);
	
	if(node == NULL){
		return temp;
	}
	
	else if(key < node->key){
		node->left = insertNode(node->left, key);
	}
	
	else if(key > node->key){
		node->right = insertNode(node->right, key);
	}
	
//	updateHeight
	node->height =  1 + max(getHeight(node->left), getHeight(node->right));
	
	//cek balance
	int balance = getBalance(node);
	
	// kalo ga balance
	// left left
	if(balance > 1 && key < node ->left->key){
		return rightRotate(node);
	}
	
	// left right
	else if(balance > 1 && key > node->left->key){
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	
	// right right
	if(balance < -1 && key > node ->right->key){
		return leftRotate(node);
	}
	
	// right left
	else if(balance < -1 && key < node->right-> key){
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	
	
	return node;
}

void inOrder(Node *node){
	if(node != NULL){
		inOrder(node->left);
		printf("%d -> ", node->key);
		inOrder(node->right);
	}
}

Node *removeNode(Node *node, int key){
	if(node == NULL){
		return node;
	}
	
	else if(key > node->key){
		node->right = removeNode(node->right, key);
	}
	
	else if(key < node->key){
		node->left = removeNode(node->left, key);
	}
	
	else{
		if(!node->left && !node->right){
			free(node);
			node = NULL;
		}
		
		else if(!node->left || !node->right){
			Node *temp;
			
			if(node->left != NULL){
				temp = node->left;
			}
			
			else if(node->right != NULL){
				temp = node->right;
			}
			
			*node = *temp;
			free(temp);
			temp = NULL;
		}
		
		else{
			Node *temp = node->left;
			while(temp->right){
				temp = temp->right;
			}
			
			node->key = temp->key;
			node-> left = removeNode(node->left, temp->key);
		}
	}
	
	return node;
	
}

int main(){
	Node *root = NULL;
	root = insertNode(root, 10);
	root = insertNode(root, 15);
	root = insertNode(root, 11);
	root = insertNode(root, 9);
	root = insertNode(root, 8);
	root = insertNode(root, 4);
	root = insertNode(root, 2);
	
	inOrder(root);
	printf("\n");
	root = removeNode(root, 9);
	inOrder(root);
	return 0;
}