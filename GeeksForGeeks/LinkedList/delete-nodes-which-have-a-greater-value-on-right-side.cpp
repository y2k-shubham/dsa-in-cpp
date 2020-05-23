// http://www.geeksforgeeks.org/delete-nodes-which-have-a-greater-value-on-right-side/
#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

struct node {
	int val;
	struct node * next;
};

node * newNode(int);
node * insert(node *, node *);
void showList(node *);
node * removeSmall(node *, int &);

int main() {
	node * head, * tail;
	head = tail = NULL;

	head = tail = insert(tail, newNode(8));
	tail = insert(tail, newNode(9));
	tail = insert(tail, newNode(8));
	tail = insert(tail, newNode(7));
	tail = insert(tail, newNode(3));
	tail = insert(tail, newNode(2));
	tail = insert(tail, newNode(4));

	showList(head);

	int nxtGr8 = -99999999;
	head = removeSmall(head, nxtGr8);

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

node * removeSmall(node * crrNode, int &nxtGr8) {
	if (crrNode != NULL) {
		crrNode -> next = removeSmall(crrNode -> next, nxtGr8);

		if (crrNode -> val < nxtGr8) {
			return crrNode -> next;
		} else {
			nxtGr8 = max(nxtGr8, crrNode -> val);
		}
	}
	return crrNode;
}

void showList(node * head) {
	printf("\nThe list is:-\n");
	for (node * list = head; list != NULL; list = list -> next) {
		printf("%d\t", list -> val);
	}
	printf("\n");
}
