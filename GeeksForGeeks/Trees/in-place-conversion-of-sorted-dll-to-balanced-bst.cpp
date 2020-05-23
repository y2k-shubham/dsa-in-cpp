// http://www.geeksforgeeks.org/in-place-conversion-of-sorted-dll-to-balanced-bst/
// http://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/

/*
1 2 3 4 5 6 7 8 9 10 -1

1 2 3 -1

-1

1 -1

1 2 -1

1 2 3 4 5 6 7 -1

1 2 3 4 -1

1 2 3 4 5 6 -1
*/

#include <cstdio>
#include <iostream>
#include <cstdlib>

struct node {
	struct node * prev;
	int val;
	struct node * next;
};

using namespace std;

void showList(node *, const char *);
void showListRev(node *, const char *);
node * createNode(int);
node * insert(node *, node *);
node * convert1(node *);
void inOrder(node *);
void preOrder(node *);
node * convert2(node **, int);
int findLen(node *);

int main() {
	node * head, * tail;
	int ele;

	cout << "Enter elements to create sorted DLL:-\n";
	cin >> ele;

	head = tail = NULL;
	while (ele != -1) {
		if (head == NULL) {
			head = tail = createNode(ele);
		} else {
			tail = insert(tail, createNode(ele));
		}
		cin >> ele;
	}

	showList(head, "forward linked list");
	showListRev(tail, "reverse linked list");

//	node * root = convert1(head);
	node * root = convert2(&head, findLen(head));

	cout << "\nBST inOrder is:-\n";
	inOrder(root);
	cout << endl;

	cout << "\nBST preOrder is:-\n";
	preOrder(root);
	cout << endl;

	return 0;
}

node * createNode(int val) {
	node * newNode = (node *) malloc(sizeof(node));

	newNode -> val = val;
	newNode -> prev = NULL;
	newNode -> next = NULL;

	return newNode;
}

node * insert(node * tail, node * newNode) {
	if (tail != NULL) {
		tail -> next = newNode;
		newNode -> prev = tail;
	}
	return newNode;
}

void showList(node * head, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (node * list = head; list != NULL; list = list -> next) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n");
}

void showListRev(node * head, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (node * list = head; list != NULL; list = list -> prev) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n");
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> prev);
		printf("%d ", root -> val);
		inOrder(root -> next);
	}
}

void preOrder(node * root) {
	if (root != NULL) {
		printf("%d ", root -> val);
		preOrder(root -> prev);
		preOrder(root -> next);
	}
}

node * convert1(node * head) {
	if (head == NULL) {
		return NULL;
	} else {
		node * l1, * l2;

		for (l1 = l2 = head; l2 != NULL && l2 -> next != NULL; ) {
			l1 = l1 -> next;
			l2 = l2 -> next -> next;
		}

		node * root = l1;
		node * rHead = root -> next;

		if (root -> prev != NULL) {
			root -> prev -> next = NULL;
			root -> prev = NULL;
			root -> prev = convert1(head);
		}

		if (root -> next != NULL) {
			rHead -> prev = NULL;
			root -> next = NULL;
			root -> next = convert1(rHead);
		}

		return root;
	}
}

node * convert2(node ** head, int count) {
	if (count == 0) {
		return NULL;
	} else {
		node * prev = convert2(head, count / 2);
		node * root = * head;

		root -> prev = prev;
		(* head) = (* head) -> next;
		root -> next = convert2(head, count - count / 2 - 1);

		return root;
	}
}

int findLen(node * head) {
	int len = 0;
	for (node * list = head; list != NULL; list = list -> next) {
		len++;
	}

	return len;
}

