/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */

/*어려웠던 부분 
/////////////////////////////////////////////
 insertNode함수에서 key값을 비교하여 삽입하는 부분에서 조건문을 current !=NULL조건을 생각하지 못했습니다.
결국 위에의해 무한루프에 빠지는 경우가 있었습니다.
current !=NULL && node->key > current->key로 설정하여 해결하였습니다.

//////////////////////////////////////////////////////
 invertList함수에서 lead, middle, trail을 사용하여 역순으로 재배치하는 부분에서 어려움을 겪었습니다.
 직접 구글링과 함께 리스트의 그림을 그려가며 이해하고 구현하였습니다.

//////////////////////////////////////////////////////
*/

#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node { //노드 구조체 선언
	int key;
	struct Node* link;
} listNode;

typedef struct Head { //헤드 구조체 선언
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); //초기화 함수
int freeList(headNode* h); //리스트 해제 함수

int insertFirst(headNode* h, int key); //첫번째 노드로 삽입하는 함수
int insertNode(headNode* h, int key); //노드를 삽입하는 함수
int insertLast(headNode* h, int key); //마지막 노드로 삽입하는 함수

int deleteFirst(headNode* h); //첫번째 노드를 삭제하는 함수
int deleteNode(headNode* h, int key); //입력받은 key값을 가진 노드를 삭제하는 함수
int deleteLast(headNode* h); //마지막 노드를 삭제하는 함수
int invertList(headNode* h); //리스트를 역순으로 재배치하는 함수

void printList(headNode* h); //리스트를 출력하는 함수

int main()
{
    printf("[----- [백승헌] [2023041017] -----]");
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': //z나 Z를 입력받으면 headnode를 초기화함.
			headnode = initialize(headnode); 
			break;
		case 'p': case 'P': //p나 P를 입력받으면 리스트를 출력함.
			printList(headnode);
			break;
		case 'i': case 'I': //i나 I를 입력받으면 key값을 입력받아 노드를 삽입함.
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //d나 D를 입력받으면 key값을 입력받아 노드를 삭제함.
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': //n나 N를 입력받으면 key값을 입력받아 마지막 노드로 삽입함.
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': //e나 E를 입력받으면 마지막 노드를 삭제함.
			deleteLast(headnode);
			break;
		case 'f': case 'F': //f나 F를 입력받으면 key값을 입력받아 첫번째 노드로 삽입함.
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //t나 T를 입력받으면 첫번째 노드를 삭제함.
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //r나 R을 입력받으면 리스트를 역순으로 재배치함.
			invertList(headnode);
			break;
		case 'q': case 'Q': //q나 Q를 입력받으면 프로그램을 종료함.
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q를 입력받으면 프로그램 종료

	return 1;
}

headNode* initialize(headNode* h) { //headNode 초기화 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL; //temp의 first를 NULL로 초기화
	return temp;
}

int freeList(headNode* h){ 
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //p에 head의 first값을 넣음
    
	listNode* prev = NULL; //prev를 NULL로 초기화
	while(p != NULL) {
		prev = p; //prev에 p값을 넣음
		p = p->link; //p에 p의 link값을 넣음
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //새로운 노드의 key에 key값을 넣음.

	node->link = h->first; //새로운 노드의 link에 head의 first값을 넣음.
	h->first = node; //head의 first에 새로운 노드를 넣음.

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //새로운 노드의 key에 key값을 넣음.
	node->link = NULL; //새로운 노드의 link를 NULL로 초기화.

	listNode* current = h->first; //current에 head의 first값을 넣음.
	listNode* trace = NULL; //trace를 NULL로 초기화.
	while(current !=NULL && node->key > current->key){ //current가 NULL이 아니고, node의 key값이 current의 key값보다 클때까지 반복
			trace = current;
			current = current->link;
			
	}
	if(trace == NULL) { //trace가 NULL인 경우
		node->link = h->first; //node의 link에 h->first에 해당하는 주소를 할당
		h->first = node; //head가 node를 가리키도록 함
		}

	else{
		trace->link = node; //trace의 link에 node의 주소를 넣음. 
		node->link = current; //node의 link에 기존의 리스트에서 바로 뒤의 current를 넣음.
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node-> key = key; //새로운 node의 key에 key값을 집어넣음.
	node->link = NULL; //새로운 node의 link를 NULL로 설정함.(마지막 노드)


	if(h->first == NULL){
		h->first = node; //먄약 리스트가 비어있다면 head가 바로 위의 노드를 가리키게 함.
	}
	else{
		listNode* current = h->first; //current에 h의 first값을 넣음.
		while(current->link != NULL){ //current가 가리키는 link가 NULL아닐때까지 반복.
			current = current->link;
		}
		current->link = node; //노드를 마지막에 추가함.
	}


	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* ptr = h->first; //포인터변수 ptr의 head의 first를 저장함.
	if(h->first == NULL){
		printf("이미 비어 있음.\n");
		return -1;
	}
	else{
		h->first = ptr->link; //head의 first에 ptr의 link를 저장함.
		ptr->link = NULL; // ptr의 링크, 즉 첫번째 노드의 link를 NULL로 초기화.
		free(ptr); //첫번째 노드의 메모리 링크를 해제함
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if(h->first == NULL){ 
		printf("리스트가 비어 있음.\n");
		return -1;
	}

	listNode* current = h->first;
	listNode* prev = NULL;

	if(current -> key ==  key){ //첫번째 노드가 key값과 같을때 첫번째 노드를 삭제하는 기능
		h->first = current -> link; 
		current->link = NULL;
		free(current);
		return 0;
	}
	//첫번째 노드가 key값과 같지 않을때
	while(current->link != NULL && current-> key != key){ //current의 link가 NULL이 아니고, current의 key값이 key값과 같지 않을때까지 반복
		prev = current;
		current = current -> link;
	}
	

	prev->link = current->link;
	current->link = NULL;
	free(current);

	
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h->first == NULL){
		printf("리스트가 비어 있음.\n");
		return -1;
	}

	listNode* current = h->first;
	listNode* prev = NULL;

	while(current->link != NULL){ //current의 link가 NULL이 아닐때까지 반복하며 마지막 노드를 탐색
		prev = current;
		current = current->link;
	} 
		
    if (prev == NULL) { //리스트에 노드가 하나만 있는 경우
        h->first = NULL;  
    } else {
        prev->link = NULL; //마지막 노드를 삭제하는 기능
    }
	free(current);

	
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode *middle, *trail,*lead;
	lead = h->first; //lead에 head의 first값을 넣음
	middle = NULL; //middle을 NULL로 초기화

	while(lead !=NULL){
		trail = middle; //trail에 middle값을 넣음
		middle = lead; //middle에 lead값을 넣음
		lead = lead-> link; //lead에 lead의 link값을 넣음
		middle->link = trail; //middle의 link에 trail값을 넣음
	}
	h->first = middle; //head의 first를 NULL값에서 middle이 가리키는 값으로 변경
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p; 

	printf("\n---PRINT\n");

	if(h == NULL) { //head가 NULL인 경우 아무것도 출력하지 않음.
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p에 head의 first값을 넣음.

	while(p != NULL) { //p가 NULL이 아닐때까지 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

