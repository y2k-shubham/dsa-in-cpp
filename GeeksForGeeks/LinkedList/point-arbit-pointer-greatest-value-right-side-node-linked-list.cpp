// http://www.geeksforgeeks.org/point-arbit-pointer-greatest-value-right-side-node-linked-list/
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

struct node {
	int val;
	struct node * next;
	struct node * arbit;
};

using namespace std;
typedef struct node link;

node * createList();
void showList(node *);
node * revList(node *, node *);
void linkArbit(node *);
void showArbit(node *);

int main() {
	node * head;

	srand(time(NULL));
	head = createList();
	showList(head);

	head = revList(head, NULL);
	showList(head);

	linkArbit(head);

	head = revList(head, NULL);
	showList(head);
	showArbit(head);

	return 0;
}

node * createNode(int val) {
	node * newNode;
	newNode = (node *) malloc(sizeof(node));

	newNode -> next = NULL;
	newNode -> arbit = NULL;
	newNode -> val = val;

	return newNode;
}

node * createList() {
	int len;
	node * head;
	node * list;
	node * newNode;

	printf("Enter length of list:\t");
	scanf("%d", &len);

	head = list = createNode(rand() % 1000);
	for (int i = 2; i <= len; i++) {
		newNode = createNode(rand() % 1000);
		list -> next = newNode;
		list = newNode;
	}

	return head;
}

void showList(node * head) {
	printf("\nThe linked list is:-\n");
	for (node * list = head; list != NULL; list = list -> next) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n");
}

void showArbit(node * head) {
	printf("\nThe arbit values are:-\n");
	for (node * list = head; list -> next != NULL; list = list -> next) {
		printf("%d -> ", list -> arbit -> val);
	}
	printf("NULL\n");
}

node * revList(node * head, node * prev) {
	if (head -> next != NULL) {
		node * tmp;

		tmp = head -> next;
		head -> next = prev;

		return revList(tmp, head);
	} else {
		head -> next = prev;
		return head;
	}
}

void linkArbit(node * head) {
	node * maxNode;

	head -> arbit = NULL;
	maxNode = head;

	for (node * list = head -> next; list != NULL; list = list -> next) {
		list -> arbit = maxNode;

		if (list -> val > maxNode -> val) {
			maxNode = list;
		}
	}
}
