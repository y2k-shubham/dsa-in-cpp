#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <stdbool.h>
#include <climits>
#include <ctime>

struct node {
	int val;
	struct node * next;
};

using namespace std;
typedef struct node link;

link * createNode(int);
link * createList(int);
void showList(link *, const char *);
link * partitionList(link *, int, int);

int main() {
	link * head;
	int n;
	int k;

	printf("Enter n:\t");
	scanf("%d", &n);

	printf("Enter k:\t");
	scanf("%d", &k);

    srand(time(NULL));
	head = createList(n);
	showList(head, "\nThe original list is:-\n");

	head = partitionList(head, n, k);
	showList(head, "\nThe partitioned list is:-\n");

	return 0;
}

link * createNode(int val) {
	link * newNode;

	newNode = (link *) malloc(sizeof(link));
	newNode -> next = NULL;
	newNode -> val = val;

	return newNode;
}

link * createList(int n) {
	link * head;
	link * listCrr;
	link * newNode;
	int i;

	head = listCrr = createNode(rand() % n);
	for (i = 2; i <= n; i++) {
		newNode = createNode(rand() % n);

		listCrr -> next = newNode;
		listCrr = newNode;
	}

	return head;
}

void showList(link * head, const char * msg) {
	link * listCrr;

	printf("%s", msg);
	for (listCrr = head; listCrr != NULL; listCrr = listCrr -> next) {
		printf("%d -> ", listCrr -> val);
	}
	printf("NULL\n");
}

link * partitionList(link * head, int n, int k) {
	link * newHead;
	link * newTail;
	link * listCrr;
	link * tempPtr;
	bool deleteHead;
	int ctr;

    //printf("\nPartition Function\n");
	if (head -> val >= k) {
		deleteHead = true;
		newHead = newTail = createNode(INT_MIN);
		newHead -> next = head;
		//printf("New head created\n");
	} else {
		deleteHead = false;
		for (tempPtr = head; tempPtr -> next -> val <= k; tempPtr = tempPtr -> next) {
		}
		newHead = head;
		head = tempPtr;
		newTail = tempPtr;
		//printf("New head not created\n");
	}

	for (listCrr = head, ctr = 1; ctr <= (n * n) && listCrr != NULL && listCrr -> next != NULL; ctr++) {
        //printf("Reading %d\t", listCrr -> next -> val);
		if (listCrr -> next -> val < k) {
			tempPtr = newTail -> next;
			newTail -> next = listCrr -> next;
			listCrr -> next = listCrr -> next -> next;
			newTail -> next -> next = tempPtr;
            //printf("appended after %d\n", newTail -> val);
            newTail = newTail -> next;
		} else {
			listCrr = listCrr -> next;
			//printf("skipped\n");
		}
	}

	if (deleteHead) {
        //printf("\nnewHead deleted before return\tnow newHead = %d\n", newHead -> next -> val);
		return newHead -> next;
	} else {
	    //printf("\nnewHead retained\tnewHead = %d\n", newHead -> val);
		return newHead;
	}
}
