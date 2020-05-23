// http://www.geeksforgeeks.org/sort-linked-list-already-sorted-absolute-values/
#include <cstdio>
#include <iostream>

using namespace std;

struct node {
	int val;
	struct node * next;
};

node * newNode(int);
node * insert(node *, node *);
void showList(node *);
void sort(node **, node *, node *);

int main() {
	node * head, * tail;

	head = tail = NULL;
	head = tail = insert(tail, newNode(1));
	tail = insert(tail, newNode(-2));
	tail = insert(tail, newNode(-3));
	tail = insert(tail, newNode(4));
	tail = insert(tail, newNode(-5));
	tail = insert(tail, newNode(8));
	tail = insert(tail, newNode(-7));

//	head = tail = NULL;
//	head = tail = insert(tail, newNode(-5));
//	tail = insert(tail, newNode(-10));

//	head = tail = NULL;
//	head = tail = insert(tail, newNode(5));
//	tail = insert(tail, newNode(10));

//	head = tail = NULL;
//	head = tail = insert(tail, newNode(1));
//	tail = insert(tail, newNode(-2));

	showList(head);

	node ** headPtr = &head;
	sort(headPtr, head, NULL);

	head = *headPtr;
	showList(head);

	return 0;
}

node * newNode(int val) {
	node * tmp = new node;
	tmp -> val = val;
	tmp -> next = NULL;
	return tmp;
}

node * insert(node * tail, node * newNode) {
	if (tail != NULL) {
		tail -> next = newNode;
	}
	return newNode;
}

void showList(node * head) {
	printf("\nThe list is:-\n");
	for (node * list = head; list != NULL; list = list -> next) {
		printf("%d\t", list -> val);
	}
	printf("\n");
}

void sort(node ** head, node * crr, node * prev) {
	if (crr == NULL) {
		return ;
	} else {
//		showList(*head);
//		if (prev != NULL) {
//			printf("\nat node crr = %d, prev = %d\t*head = %d\n", crr -> val, prev -> val, (*head) -> val);
//		} else {
//			printf("\nat node crr = %d, prev = NULL\t*head = %d\n", crr -> val, (*head) -> val);
//		}

		if (crr -> val < 0 && prev != NULL) {
			node * crrNext = crr -> next;

//			printf("crr(%d)->next made to point to head(%d)\n", crr -> val, (* head) -> val);
			crr -> next = * head;

			//			printf("*head made to point to crr(%d)\n", crr -> val);
			* head = crr;

//			if (crrNext != NULL) {
//				printf("prev(%d)->next made to point to crrNext(%d)\n", prev -> val, crrNext -> val);
//			} else {
//				printf("prev(%d)->next made to point to NULL\n", prev -> val);
//			}
			prev -> next = crrNext;

			sort(head, crrNext, prev);
		} else {
			sort(head, crr -> next, crr);
		}
	}
}
