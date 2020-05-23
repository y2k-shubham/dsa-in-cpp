#include <stdio.h>
#include <stdlib.h>

struct node {
	int val;
	struct node * prev;
	struct node * next;
};

typedef struct node link;

link * tail;

link * createNode(int);
link * createList();
void showList(link *);
link * reverseListRecursive(link *, link *, link *);
link * reverseListIterative(link *);
void showListRev(link *);
void nullify(link *);

int main() {
	link * head;

    head = createNode(0);
    nullify(head);

    if (head == NULL) {
        printf("Head is null\n\n");
    } else {
        printf("head -> val = %d\n\n", head -> val);
    }

    printf("Original List:-\n");
	head = createList();
	showList(head);
	showListRev(tail);

    printf("\nAfter Recursive Reverse:-\n");
	head = reverseListRecursive(NULL, head, head -> next);
	showList(head);
	showListRev(tail);

    printf("\nAfter Iterative Reverse:-\n");
	head = reverseListIterative(head);
	showList(head);
	showListRev(tail);

	return 0;
}

void nullify(link * head) {
    head = NULL;
}

link * createNode(int val) {
	link * newNode;
	newNode = (link *) malloc(sizeof(link));

	newNode -> prev = NULL;
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
		newNode -> prev = list;
		list = newNode;
	}

    tail = list;
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

void showListRev(link * list) {
    if (list == NULL) {
		printf("NULL\n");
	} else {
		printf("%d -> ", list -> val);
		showListRev(list -> prev);
	}
}

link * reverseListRecursive(link * listPrev, link * listCurr, link * listNext) {
    link * head;

    if (listPrev == NULL) {
        tail = listCurr;
    }

    if (listCurr -> next != NULL) {
		head = reverseListRecursive(listCurr, listCurr -> next, listNext -> next);
	} else {
	    head = listCurr;
	}
	listCurr -> next = listPrev;
	listCurr -> prev = listNext;
	return head;
}

link * reverseListIterative(link * listCurr) {
    link * listPrev;
    link * listNext;

    listPrev = NULL;
    listNext = listCurr -> next;
    tail = listCurr;

    while (listNext != NULL) {
        listCurr -> next = listPrev;
        listCurr -> prev = listNext;

        listPrev = listCurr;
        listCurr = listNext;
        listNext = listNext -> next;
    }

    listCurr -> next = listPrev;
    listCurr -> prev= listNext;

    return listCurr;
}

