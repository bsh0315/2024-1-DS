/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

/*****************************
 * 2023041017 백승헌
 * 기존 코드에서 추가한 함수
 * freeNode(Node* ptr)
 * freeBST함수의 편리성을 위해서 재귀적으로 노드를 해제하는 함수를 추가적으로 구현했다.
 * 
 *************************/

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
		printf("[----- [백승헌] [2023041017] -----]\n");
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
			//z를 입력받을 경우 이진탐색트리를 초기화하는 initializeBST함수 호출
			break;
		case 'q': case 'Q':
			freeBST(head);
			//q를 입력받을 경우 이진탐색트리를 해제하는 freeBST함수 호출
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			//n을 입력받을 경우 insert함수 호출
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			//d를 입력받을 경우 deleteLeafNode함수 호출, 입력받은 키값을 가진 리프노드를 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
				//f를 입력받을 경우 searchIterative함수 호출
				//입력받은 키값을 가진 노드를 찾으면 해당 노드의 주소 출력, 찾지 못하면 찾지 못했다는 메세지 출력
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
				//s를 입력받을 경우 searchRecursive함수 호출
				//입력받은 키값을 가진 노드를 찾으면 해당 노드의 주소 출력, 찾지 못하면 찾지 못했다는 메세지 출력
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			//i를 입력받을 경우 inorderTraversal함수 호출
			//중위순회로 노드의 키값들을 출력
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			//p를 입력받을 경우 preorderTraversal함수 호출
			//전위순회로 노드의 키값들을 출력
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			//t를 입력받을 경우 postorderTraversal함수 호출
			//후위순회로 노드의 키값들을 출력
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
	//이진탐색트리가 비어있지 않을 경우 freeBST함수 호출
	//이진탐색트리를 해제한다.

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	//헤드노드 생성
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	//헤드노드의 왼쪽 자식노드를 NULL(루트노드)로 설정, 오른쪽 자식노드는 헤드노드 자신으로 설정
	return 1;
}


void inorderTraversal(Node* ptr) {
    if(ptr) {
        inorderTraversal(ptr->left);
        printf("%d ", ptr->key);
        inorderTraversal(ptr->right);
    }
	//중위순회를 재귀적인 방법으로 구현했다.
}

void preorderTraversal(Node* ptr) {
    if(ptr) {
        printf("%d ", ptr->key);
        preorderTraversal(ptr->left);
        preorderTraversal(ptr->right);
    }
	//전위순회를 재귀적인 방법으로 구현했다.
}

void postorderTraversal(Node* ptr) {
    if(ptr) {
        postorderTraversal(ptr->left);
        postorderTraversal(ptr->right);
        printf("%d ", ptr->key);
    }
	//후위순회를 재귀적인 방법으로 구현했다.
}



int insert(Node* head, int key)
{
	
	Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 노드 생성
	newNode ->key = key; //새로운 노드의 키값을 입력받은 키값으로 설정
	newNode->left = NULL; //새로운 노드의 왼쪽 자식노드를 NULL로 설정
	newNode->right = NULL; //새로운 노드의 오른쪽 자식노드를 NULL로 설정

	if(head->left == NULL){ 
		head->left = newNode;
		return 1;
	}
	// 루트노드가 비어있을 경우 새로운 노드를 루트노드로 설정
	
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
	//p가 NULL이 될때까지 반복하며 새로운 노드의 위치를 찾는다.

	if(parent->key < key) {
		parent->right = newNode; //부모노드의 키값이 입력받은 키값보다 작을 경우 오른쪽 자식노드로 설정
	} else {
		parent->left = newNode; //부모노드의 키값이 입력받은 키값보다 클 경우 왼쪽 자식노드로 설정
	}
	return 1;
}

int deleteLeafNode(Node* head, int key) {
	Node* parent = NULL;
	Node* ptr = head->left; 

	while(ptr != NULL) { 
		if(ptr->key == key) { //ptr의 키값이 입력받은 키값과 같을 경우
			if(ptr->left == NULL && ptr->right == NULL) { //ptr이 리프노드일 경우
				if(parent == NULL) {  
					head->left = NULL;
					//ptr이 루트노드일 경우 루트노드를 NULL로 설정
				} else {
					if(parent->left == ptr) {
						parent->left = NULL;
						//부모노드의 왼쪽 자식노드가 ptr일 경우 왼쪽 자식노드를 NULL로 설정
					} else {
						parent->right = NULL;
						//부모노드의 오른쪽 자식노드가 ptr일 경우 오른쪽 자식노드를 NULL로 설정
					}
				}
				free(ptr); //ptr 해제
				return 1;
			} else {
				printf("Node [%d] is not a leaf node\n", key);
				//ptr이 리프노드가 아닐 경우 해당 노드가 리프노드가 아니라는 메세지 출력
				return 0;
			}
		}
		parent = ptr; //부모노드를 현재 노드로 설정
		if(ptr->key < key) {
			ptr = ptr->right;
			//ptr의 키값이 입력받은 키값보다 작을 경우 오른쪽 자식노드로 이동
		} else {
			ptr = ptr->left;
			//ptr의 키값이 입력받은 키값보다 클 경우 왼쪽 자식노드로 이동
		}
	}

	printf("Cannot find the node [%d]\n", key);
	//ptr이 NULL이 될때까지 입력받은 키값을 찾지 못할 경우 찾지 못했다는 메세지 출력
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr) return NULL; //ptr이 NULL일 경우 NULL 반환
	if(key == ptr->key) return ptr; //ptr의 키값이 입력받은 키값과 같을 경우 ptr 반환(루트노드일 경우)
	if(key < ptr->key){ 
		return searchRecursive(ptr->left, key);
	}
	return searchRecursive(ptr->right, key);
	//key값이 ptr의 키값보다 작을 경우 왼쪽 자식노드로 이동, 클 경우 오른쪽 자식노드로 이동
}

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left; //루트노드부터 시작

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
	//ptr이 NULL이 될때까지 반복하며 키값을 찾는다.
	return NULL;
	//ptr이 NULL이 되면 NULL 반환
}


int freeBST(Node* head) {
    if(head->left == head) {
        free(head);
		//루트노드가 헤드노드일 경우 헤드노드만 해제
        return 1;
    }

    freeNode(head->left);
	//루트노드가 헤드노드가 아닐 경우 루트노드부터 해제
    free(head);
	//헤드노드 해제
    return 1;
}

void freeNode(Node* ptr) {
    if(ptr) {
        freeNode(ptr->left);
        freeNode(ptr->right);
        free(ptr);
    }
	//재귀적으로 노드를 해제하는 함수
}

