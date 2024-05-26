/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
void freeNode(Node* ptr);
/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("[----- [백승헌] [2023041017] -----]");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}


void inorderTraversal(Node* ptr) {
    if(ptr) {
        inorderTraversal(ptr->left);
        printf("%d ", ptr->key);
        inorderTraversal(ptr->right);
    }
}

void preorderTraversal(Node* ptr) {
    if(ptr) {
        printf("%d ", ptr->key);
        preorderTraversal(ptr->left);
        preorderTraversal(ptr->right);
    }
}

void postorderTraversal(Node* ptr) {
    if(ptr) {
        postorderTraversal(ptr->left);
        postorderTraversal(ptr->right);
        printf("%d ", ptr->key);
    }
}



int insert(Node* head, int key)
{
	
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode ->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if(head->left == NULL){
		head->left = newNode;
		return 1;
	}

	Node* p = head->left;
	Node* parent = NULL;

	while(p !=NULL){
		parent = p;
		if(p->key == key){
			printf("해당 키가 이미 존재합니다.");
			free(newNode);
			return 0;
		}
		else if(p->key < key){
			p = p->right;
		}
		else{
			p= p->left;
		}
	}
	if(parent->key < key) {
		parent->right = newNode;
	} else {
		parent->left = newNode;
	}
	return 1;
}

int deleteLeafNode(Node* head, int key) {
	Node* parent = NULL;
	Node* ptr = head->left;

	while(ptr != NULL) {
		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) { // Leaf node
				if(parent == NULL) { // Root node is the leaf
					head->left = NULL;
				} else {
					if(parent->left == ptr) {
						parent->left = NULL;
					} else {
						parent->right = NULL;
					}
				}
				free(ptr);
				return 1;
			} else {
				printf("Node [%d] is not a leaf node\n", key);
				return 0;
			}
		}
		parent = ptr;
		if(ptr->key < key) {
			ptr = ptr->right;
		} else {
			ptr = ptr->left;
		}
	}

	printf("Cannot find the node [%d]\n", key);
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr) return NULL;
	if(key == ptr->key) return ptr;
	if(key < ptr->key){
		return searchRecursive(ptr->left, key);
	}
	return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;

	while(ptr){
		if(ptr->key == key)
			return ptr;
		if(ptr->key < key){
			ptr= ptr->right;
		}
		else if(ptr->key > key){
			ptr = ptr->left;
		}
	}
	return NULL;
}


int freeBST(Node* head) {
    if(head->left == head) {
        free(head);
        return 1;
    }

    freeNode(head->left);
    free(head);
    return 1;
}

void freeNode(Node* ptr) {
    if(ptr) {
        freeNode(ptr->left);
        freeNode(ptr->right);
        free(ptr);
    }
}

