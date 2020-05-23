#include <stdio.h>
#include <stdlib.h>

struct node {
	int val;
	struct node * next;
};

typedef struct node link;

link * createNode(int);
link * createList();
void showList(link *);
link * reverseListRecursive(link *, link *);
link * reverseListIterative(link *);

int main() {
	link * head;

	head = createList();
	showList(head);
	head = reverseListRecursive(head, NULL);
	showList(head);
	head = reverseListIterative(head);
	showList(head);

	return 0;
}

link * createNode(int val) {
	link * newNode;

	newNode = (link *) malloc(sizeof(link));
	newNode -> next = NULL;
	newNode -> val = val;

	return newNode;
}

link * createList() {
	link * head;
	link * list;
	link * newNode;
	int i;

	head = createNode(1);
	list = head;

	for (i = 2; i <= 10; i++) {
		newNode = createNode(i);
		list -> next = newNode;
		list = newNode;
	}

	return head;
}

void showList(link * list) {
	if (list == NULL) {
		printf("NULL\n");
	} else {
		printf("%d -> ", list -> val);
		showList(list -> next);
	}
}

link * reverseListRecursive(link * listCrr, link * listPrev) {
    link * head;
	if (listCrr -> next != NULL) {
		head = reverseListRecursive(listCrr -> next, listCrr);
	} else {
	    head = listCrr;
	}
	listCrr -> next = listPrev;
	return head;
}

link * reverseListIterative(link * listCrr) {
    link * listPrev;
    link * listNext;

    listPrev = NULL;
    listNext = listCrr -> next;

    while (listNext != NULL) {
        listCrr -> next = listPrev;
        listPrev = listCrr;
        listCrr = listNext;
        listNext = listNext -> next;
    }

    listCrr -> next = listPrev;

    return listCrr;
}
