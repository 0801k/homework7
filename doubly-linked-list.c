//Doubly Linked List
#include<stdio.h>
#include<stdlib.h>

typedef struct Node { // (typedef를 사용하여) Node 구조체 생성
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head { // (typedef를 사용하여) Head 구조체 생성
	struct Node* first;
}headNode;

// 함수 리스트
// note: initialize는 이중포인터를 매개변수로 받음
//       lab3의 initialize와 차이점을 이해 할것
int initialize(headNode** h);

// note: freeList는 싱글포인터를 매개변수로 받음
//       - initialize와 왜 다른지 이해 할것
//       - 이중포인터를 매개변수로 받아도 해제할 수 있을 것
int freeList(headNode* h);

int insertNode(headNode* h, int key); // list 검색 노드 삽입
int insertLast(headNode* h, int key); // list에 key 노드 추가
int insertFirst(headNode* h, int key); // list 처음에 key 노드 추가
int deleteNode(headNode* h, int key); // list에 key 노드 삭제
int deleteLast(headNode* h); // list 마지막 삭제
int deleteFirst(headNode* h); // list 첫번째 삭제

int invertList(headNode* h); // link 역순으로 재배치

void printList(headNode* h); // 출력

int main()
{
	char command; // 변수 command
	int key; // 변수 key
	headNode* headnode=NULL;

	do{
        printf("[----- [노관범]  [2020039102] -----]\n");

		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 받기

		switch(command) {
		case 'z': case 'Z': // z 또는 Z 일 경우
			initialize(&headnode);
			break;
		case 'p': case 'P': // p 또는 P 일 경우
			printList(headnode);
			break;
		case 'i': case 'I': // i 또는 I 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 받기
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // d 또는 D 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 받기
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // n 또는 N 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 받기
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // e 또는 E 일 경우
			deleteLast(headnode);
			break;
		case 'f': case 'F': // f 또는 F 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 받기
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // t 또는 T 일 경우
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // r 또는 R 일 경우
			invertList(headnode);
			break;
		case 'q': case 'Q': // q 또는 Q 일 경우
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 경고문 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); // command 가 q 또는 Q 가 아니면 계속 진행

	return 1;
}

int initialize(headNode** h) {

	// headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if(*h != NULL) // headNode 가 NULL 아님
		freeList(*h); // 해제

	// headNode에 대한 메모리를 할당하여 리턴
	*h = (headNode*)malloc(sizeof(headNode)); // 주소 받기
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	// h와 연결된 listNode 메모리 해제
	// headNode도 해제되어야 함
	listNode* p = h->first;
	listNode* prev = NULL;

	while(p != NULL) { // p가 NULL 이 아니면
		prev = p;
		p = p->rlink;
		free(prev); // listNode 해제
	}
	free(h); // headNode 해제
	return 0;
}

void printList(headNode* h) {
	int i = 0; // i = 0
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // headNode 가 NULL 이면
		printf("Nothing to print....\n"); // 경고문 출력
		return;
	}

	p = h->first;

	while(p != NULL) { // listNode 가 NULL 이 아니면
		printf("[ [%d]=%d ] ", i, p->key); // p 가리키는 key 출력
		p = p->rlink; // p 안의 p가 가리키는 rlink 안의 주소 삽입
		i++; // i 1씩 증가
	}

	printf("  items = %d\n", i);
}

// list에 key에 대한 노드하나를 추가
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node에 'listNode' 타입으로 주소 받기
	node->key = key; // node 가리키는 key 에 key 주소 삽입
	node->rlink = NULL; // node 가리키는 rlink 에 n 주소 삽입
	node->llink = NULL; // node 가리키는 llink 에 n 주소 삽입

	if (h->first == NULL) // headNode가 NULL일 경우
	{
		h->first = node; // 노드 추가
		return 0;
	}

	listNode* n = h->first;
	while(n->rlink != NULL) { // rlink 가 NULL 이 아니면
		n = n->rlink; // n 안의 n 이 가리키는 rlink 안의 주소 삽입
	}
	n->rlink = node; // n 이 가리키는 rlink 에 node 주소 삽입
	node->llink = n; // node 가 가리키는 llink 에 n 주소 삽입
	return 0;
}

// list의 마지막 노드 삭제
int deleteLast(headNode* h) {

	if (h->first == NULL) // first 가 NULL 이면
	{
		printf("nothing to delete.\n"); // 경고문 출력
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	// 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 
	if(n->rlink == NULL) { // rlink 가 NULL 이면
		h->first = NULL;
		free(n); // 삭제
		return 0;
	}

	// 마지막 노드까지 이동 
	while(n->rlink != NULL) { // rlink가 NULL이 아닐 경우
		trail = n;
		n = n->rlink; //  n 안의 n 이 가리키는 rlink 안의 주소 삽입
	}

	trail->rlink = NULL; // n 삭제, 이전 노드 링크 NULL
	free(n); // 삭제

	return 0;
}

// list 처음에 key에 대한 노드하나를 추가
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 에 listNode 타입 주소받기
	node->key = key; //  node 가리키는 key 에 key 주소 삽입
	node->rlink = node->llink = NULL; // node 가리키는 rlink llink 에 NULL 삽입

	if(h->first == NULL) // first 가 NULL 이면
	{
		h->first = node; // 추가
		return 1;
	}

	node->rlink = h->first; // node 가리키는 rlink 에 h 가리키는 first 에 주소 삽입
	node->llink = NULL; // node 가리키는 llink 에 NULL 삽입


	listNode *p = h->first;
	p->llink = node; // 추가
	h->first = node; // 추가

	return 0;
}

// list 첫번째 노드 삭제
int deleteFirst(headNode* h) {

	if (h->first == NULL) // first 가 NULL 이면
	{
		printf("nothing to delete.\n"); // 경고문 출력
		return 0;
	}
	listNode* n = h->first; // stack 에 n 만들고, h 가리키는 first 안 주소 n 에 삽입
	h->first = n->rlink; // h 가리키는 first 안 주소 n 에 삽입

	free(n); // 삭제

	return 0;
}

// 리스트의 링크를 역순으로 재 배치
int invertList(headNode* h) {


	if(h->first == NULL) { // first 가 NULL 이면
		printf("nothing to invert...\n"); // 경고문 출력
		return 0;
	}

	listNode *n = h->first; // stack 에 n 만들고, h 가리키는 first 안 주소 n 에 삽입
	listNode *trail = NULL; // stack 에 trail 만들고, NULL 삽입
	listNode *middle = NULL; // stack 에 middle 만들고, NULL 삽입

	while(n != NULL){ // first 가 NULL 아니면
		trail = middle; // trail 에 middle 안 주소 삽입
		middle = n; // middle 에 n 안 주소 삽입
		n = n->rlink; // n 에 n 가리키는 rlink 안 주소 삽입
		middle->rlink = trail; // middle 가리키는  rlink 에 trail 안 주소 삽입
		middle->llink = n; // middle 가리키는 link 에 n 안 주소 삽입
	}

	h->first = middle; // 재배치

	return 0;
}

// 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 에 listNode 타입 주소받기
	node->key = key; // node 가리키는 key 에 key 삽입
	node->llink = node->rlink = NULL; // node 가리키는 llink rlink 에 NULL 삽입

	if (h->first == NULL) // first 가 NULL 이면
	{
		h->first = node; // 추가
		return 0;
	}

	listNode* n = h->first;

	// key 기준 삽입할 위치를 찾는다 
	while(n != NULL) { // n 이 NULL 이 아니면
		if(n->key >= key) {
			// n 가리키는 key 가 입력받은 key 보다 크면
			if(n == h->first) {
				insertFirst(h, key);
			} else { // n 가리키는 h 가리키는 first 가리키는 곳과 같다면 , insertFirst 함수 호출
				node->rlink = n; // node 가리키는 rlink 에 n 안 주소 삽입
				node->llink = n->llink; // node 가리키는 llink 에 n 가리키는 llink 주소 삽입
				n->llink->rlink = node; // n 가리키는 llink 가리키는 rlink 에 node 주소 삽입
			}
			return 0;
		}
		n = n->rlink; // n 가리키는 rlink 안 주소 n 에 삽입
	}

	// 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 
	insertLast(h, key); // 마지막에 추가
	return 0;
}

// list 에서 key 노드 삭제
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // first 가 NULL 이면
	{
		printf("nothing to delete.\n"); // 경고문 출력
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) { // n 이 NULL 이 아니면
		if(n->key == key) {
			if(n == h->first) { 
				deleteFirst(h); // n 가리키는 h 가리키는 first 가리키는 곳 같으면, deleteFirst 호출
			} else if (n->rlink == NULL){ // 마지막일 때
				deleteLast(h); // 마지막 삭제
			} else { // 중간일 때
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n); // 삭제
			}
			return 1;
		}
		n = n->rlink;
	}


	printf("cannot find the node for key = %d\n", key);
	return 1;
}