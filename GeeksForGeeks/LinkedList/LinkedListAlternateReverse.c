#include <stdio.h>
#include <stdlib.h>

struct node {
	int val;
	struct node * next;
};

typedef struct node link;

link * createNode(int);
link * createList(int);
void showList(link *, const char *);
link * split(link *, int);
link * merge(link *, link *);

int main() {
	int n;
	link * head_1;
	link * head_2;

	printf("\nEnter length of list:\t");
	scanf("%d", &n);

	head_1 = NULL;
	head_1 = createList(n);

	showList(head_1, "\nThe Original list was:-\n");

	head_2 = split(head_1, n);

	showList(head_1, "\nAfter splitting,\n1st half:-\n");
	showList(head_2, "2nd half:-\n");

	merge(head_1, head_2);

	showList(head_1, "\nAfter merging, the list became:-\n");

	return 0;
}

link * createList(int n) {
	int i;
	link * head;
	link * list;
	link * newNode;

	newNode = createNode(1);
	head = newNode;

	for (list = newNode, i = 2; i <= n; i++) {
		newNode = createNode(i);
		list -> next = newNode;
		list = newNode;
	}

	return head;
}

link * createNode(int val) {
	link * newNode;
	newNode = (link *) malloc(sizeof(link));

	newNode -> val = val;
	newNode -> next = NULL;

	return newNode;
}

void showList(link * head, const char * message) {
	link * list;

	printf("%s", message);
	for (list = head; list != NULL; list = list -> next) {
		printf("%d\t", list -> val);
	}
	printf("\n");
}

// not used
link * splitAlternate(link * head_1, int n) {
	link * head_2;
	link * list_1;
	link * list_2;
	link * list_2_copy;

	head_2 = head_1 -> next;
	list_1 = head_1;
	list_2 = head_2;
	list_2_copy = list_2;

	while (list_2 != NULL && list_2 -> next != NULL) {
		list_2_copy = list_2;
		list_1 -> next = list_2 -> next;
		list_1 = list_1 -> next;

		if (list_1 -> next != NULL) {
			list_2 -> next = list_1 -> next;
		}
		list_2 = list_2 -> next;
	}

	list_1 -> next = NULL;
	if (list_2_copy != NULL) {
		list_2_copy -> next = !(n % 2) ? (list_2_copy -> next) : NULL;
	}

	return head_2;
}

link * split(link * head, int n) {
	link * listFrwrd;
	link * listBkwrd;
	int i;
	int lim;

	lim = (n + 1) / 2;
	for (i = 1, listFrwrd = head; i <= lim; i++) {
		listBkwrd = listFrwrd;
		listFrwrd = listFrwrd -> next;
	}

	listBkwrd -> next = NULL;
	return listFrwrd;
}

link * merge(link * front, link * rear) {
	if (rear != NULL && rear -> next != NULL) {
		front = merge(front, rear -> next);
	}

	if (rear != NULL) {
		rear -> next = front -> next;
		front -> next = rear;

		return rear -> next;
	} else {
		return NULL;
	}
}
