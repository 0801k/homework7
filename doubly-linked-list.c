//Doubly Linked List
#include<stdio.h>
#include<stdlib.h>

typedef struct Node { // (typedef�� ����Ͽ�) Node ����ü ����
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head { // (typedef�� ����Ͽ�) Head ����ü ����
	struct Node* first;
}headNode;

// �Լ� ����Ʈ
// note: initialize�� ���������͸� �Ű������� ����
//       lab3�� initialize�� �������� ���� �Ұ�
int initialize(headNode** h);

// note: freeList�� �̱������͸� �Ű������� ����
//       - initialize�� �� �ٸ��� ���� �Ұ�
//       - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� ��
int freeList(headNode* h);

int insertNode(headNode* h, int key); // list �˻� ��� ����
int insertLast(headNode* h, int key); // list�� key ��� �߰�
int insertFirst(headNode* h, int key); // list ó���� key ��� �߰�
int deleteNode(headNode* h, int key); // list�� key ��� ����
int deleteLast(headNode* h); // list ������ ����
int deleteFirst(headNode* h); // list ù��° ����

int invertList(headNode* h); // link �������� ���ġ

void printList(headNode* h); // ���

int main()
{
	char command; // ���� command
	int key; // ���� key
	headNode* headnode=NULL;

	do{
        printf("[----- [�����]  [2020039102] -----]\n");

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
		scanf(" %c", &command); // command �ޱ�

		switch(command) {
		case 'z': case 'Z': // z �Ǵ� Z �� ���
			initialize(&headnode);
			break;
		case 'p': case 'P': // p �Ǵ� P �� ���
			printList(headnode);
			break;
		case 'i': case 'I': // i �Ǵ� I �� ���
			printf("Your Key = ");
			scanf("%d", &key); // key �ޱ�
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // d �Ǵ� D �� ���
			printf("Your Key = ");
			scanf("%d", &key); // key �ޱ�
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // n �Ǵ� N �� ���
			printf("Your Key = ");
			scanf("%d", &key); // key �ޱ�
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // e �Ǵ� E �� ���
			deleteLast(headnode);
			break;
		case 'f': case 'F': // f �Ǵ� F �� ���
			printf("Your Key = ");
			scanf("%d", &key); // key �ޱ�
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // t �Ǵ� T �� ���
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // r �Ǵ� R �� ���
			invertList(headnode);
			break;
		case 'q': case 'Q': // q �Ǵ� Q �� ���
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // ��� ���
			break;
		}

	}while(command != 'q' && command != 'Q'); // command �� q �Ǵ� Q �� �ƴϸ� ��� ����

	return 1;
}

int initialize(headNode** h) {

	// headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ����
	if(*h != NULL) // headNode �� NULL �ƴ�
		freeList(*h); // ����

	// headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ����
	*h = (headNode*)malloc(sizeof(headNode)); // �ּ� �ޱ�
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	// h�� ����� listNode �޸� ����
	// headNode�� �����Ǿ�� ��
	listNode* p = h->first;
	listNode* prev = NULL;

	while(p != NULL) { // p�� NULL �� �ƴϸ�
		prev = p;
		p = p->rlink;
		free(prev); // listNode ����
	}
	free(h); // headNode ����
	return 0;
}

void printList(headNode* h) {
	int i = 0; // i = 0
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // headNode �� NULL �̸�
		printf("Nothing to print....\n"); // ��� ���
		return;
	}

	p = h->first;

	while(p != NULL) { // listNode �� NULL �� �ƴϸ�
		printf("[ [%d]=%d ] ", i, p->key); // p ����Ű�� key ���
		p = p->rlink; // p ���� p�� ����Ű�� rlink ���� �ּ� ����
		i++; // i 1�� ����
	}

	printf("  items = %d\n", i);
}

// list�� key�� ���� ����ϳ��� �߰�
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node�� 'listNode' Ÿ������ �ּ� �ޱ�
	node->key = key; // node ����Ű�� key �� key �ּ� ����
	node->rlink = NULL; // node ����Ű�� rlink �� n �ּ� ����
	node->llink = NULL; // node ����Ű�� llink �� n �ּ� ����

	if (h->first == NULL) // headNode�� NULL�� ���
	{
		h->first = node; // ��� �߰�
		return 0;
	}

	listNode* n = h->first;
	while(n->rlink != NULL) { // rlink �� NULL �� �ƴϸ�
		n = n->rlink; // n ���� n �� ����Ű�� rlink ���� �ּ� ����
	}
	n->rlink = node; // n �� ����Ű�� rlink �� node �ּ� ����
	node->llink = n; // node �� ����Ű�� llink �� n �ּ� ����
	return 0;
}

// list�� ������ ��� ����
int deleteLast(headNode* h) {

	if (h->first == NULL) // first �� NULL �̸�
	{
		printf("nothing to delete.\n"); // ��� ���
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	// ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� 
	if(n->rlink == NULL) { // rlink �� NULL �̸�
		h->first = NULL;
		free(n); // ����
		return 0;
	}

	// ������ ������ �̵� 
	while(n->rlink != NULL) { // rlink�� NULL�� �ƴ� ���
		trail = n;
		n = n->rlink; //  n ���� n �� ����Ű�� rlink ���� �ּ� ����
	}

	trail->rlink = NULL; // n ����, ���� ��� ��ũ NULL
	free(n); // ����

	return 0;
}

// list ó���� key�� ���� ����ϳ��� �߰�
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node �� listNode Ÿ�� �ּҹޱ�
	node->key = key; //  node ����Ű�� key �� key �ּ� ����
	node->rlink = node->llink = NULL; // node ����Ű�� rlink llink �� NULL ����

	if(h->first == NULL) // first �� NULL �̸�
	{
		h->first = node; // �߰�
		return 1;
	}

	node->rlink = h->first; // node ����Ű�� rlink �� h ����Ű�� first �� �ּ� ����
	node->llink = NULL; // node ����Ű�� llink �� NULL ����


	listNode *p = h->first;
	p->llink = node; // �߰�
	h->first = node; // �߰�

	return 0;
}

// list ù��° ��� ����
int deleteFirst(headNode* h) {

	if (h->first == NULL) // first �� NULL �̸�
	{
		printf("nothing to delete.\n"); // ��� ���
		return 0;
	}
	listNode* n = h->first; // stack �� n �����, h ����Ű�� first �� �ּ� n �� ����
	h->first = n->rlink; // h ����Ű�� first �� �ּ� n �� ����

	free(n); // ����

	return 0;
}

// ����Ʈ�� ��ũ�� �������� �� ��ġ
int invertList(headNode* h) {


	if(h->first == NULL) { // first �� NULL �̸�
		printf("nothing to invert...\n"); // ��� ���
		return 0;
	}

	listNode *n = h->first; // stack �� n �����, h ����Ű�� first �� �ּ� n �� ����
	listNode *trail = NULL; // stack �� trail �����, NULL ����
	listNode *middle = NULL; // stack �� middle �����, NULL ����

	while(n != NULL){ // first �� NULL �ƴϸ�
		trail = middle; // trail �� middle �� �ּ� ����
		middle = n; // middle �� n �� �ּ� ����
		n = n->rlink; // n �� n ����Ű�� rlink �� �ּ� ����
		middle->rlink = trail; // middle ����Ű��  rlink �� trail �� �ּ� ����
		middle->llink = n; // middle ����Ű�� link �� n �� �ּ� ����
	}

	h->first = middle; // ���ġ

	return 0;
}

// ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node �� listNode Ÿ�� �ּҹޱ�
	node->key = key; // node ����Ű�� key �� key ����
	node->llink = node->rlink = NULL; // node ����Ű�� llink rlink �� NULL ����

	if (h->first == NULL) // first �� NULL �̸�
	{
		h->first = node; // �߰�
		return 0;
	}

	listNode* n = h->first;

	// key ���� ������ ��ġ�� ã�´� 
	while(n != NULL) { // n �� NULL �� �ƴϸ�
		if(n->key >= key) {
			// n ����Ű�� key �� �Է¹��� key ���� ũ��
			if(n == h->first) {
				insertFirst(h, key);
			} else { // n ����Ű�� h ����Ű�� first ����Ű�� ���� ���ٸ� , insertFirst �Լ� ȣ��
				node->rlink = n; // node ����Ű�� rlink �� n �� �ּ� ����
				node->llink = n->llink; // node ����Ű�� llink �� n ����Ű�� llink �ּ� ����
				n->llink->rlink = node; // n ����Ű�� llink ����Ű�� rlink �� node �ּ� ����
			}
			return 0;
		}
		n = n->rlink; // n ����Ű�� rlink �� �ּ� n �� ����
	}

	// ������ ������ ã�� ���� ���, �������� ���� 
	insertLast(h, key); // �������� �߰�
	return 0;
}

// list ���� key ��� ����
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // first �� NULL �̸�
	{
		printf("nothing to delete.\n"); // ��� ���
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) { // n �� NULL �� �ƴϸ�
		if(n->key == key) {
			if(n == h->first) { 
				deleteFirst(h); // n ����Ű�� h ����Ű�� first ����Ű�� �� ������, deleteFirst ȣ��
			} else if (n->rlink == NULL){ // �������� ��
				deleteLast(h); // ������ ����
			} else { // �߰��� ��
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n); // ����
			}
			return 1;
		}
		n = n->rlink;
	}


	printf("cannot find the node for key = %d\n", key);
	return 1;
}