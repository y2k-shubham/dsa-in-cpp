// RunTime: O(n)

/*
Strategy:	Traverse the list to form two separate linked list of even and odd nodes respectively
			Then append head of odd list at end of even list
*/

#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

struct node {
	int val;
	struct node * next;
};

node * createNode(int);
node * input();
void showList(node *, const char *);
node * rearrange(node *);

int main() {
	node * head;

	head = input();
	showList(head, "original");

	rearrange(head);
	showList(head, "rearranged");

	return 0;
}

node * createNode(int val) {
	node * newNode;

	newNode = (node *) malloc(sizeof(node));
	newNode -> val = val;
	newNode -> next = NULL;

	return newNode;
}

node * input() {
	node * head, * list, * newNode;
	int ele;

	cout << "Enter elements of linked list:-\n";
	cin >> ele;

	head = list = createNode(ele);
	cin >> ele;

	while (ele > 0) {
		newNode = createNode(ele);
		list -> next = newNode;
		list = newNode;
		cin >> ele;
	}

	return head;
}

void showList(node * head, const char * msg) {
	printf("\n%s linked list is:-\n", msg);

	for (node * list = head; list != NULL; list = list -> next) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n\n");
}

node * rearrange(node * head) {
	node * heven, * hodd;
	node * teven, * todd;
	node * list, * tail;
	int reqRem;

	heven = hodd = teven = todd = NULL;
	if (head -> val % 2 == 0) {
		heven = teven = head;
		reqRem = 0;
	} else {
		hodd = todd = head;
		reqRem = 1;
	}

	tail = head;
	for (list = head -> next; list != NULL; list = list -> next) {
		if (list -> val % 2 == reqRem) {
			tail = list;
		} else if (reqRem == 0) {
			if (hodd == NULL) {
				hodd = todd = list;
			} else {
				todd -> next = list;
			}

			reqRem = 1;
			teven = tail;
		} else {
			if (heven == NULL) {
				heven = teven = tail;
			} else {
				teven -> next = list;
			}

			reqRem = 0;
			todd = tail;
		}
	}

	// link tail of even list to head of odd list
	// also handle the cases when even list is empty or odd list is empty
	if (hodd == NULL) {
		return heven;
	} else if (heven == NULL) {
		return hodd;
	} else {
		teven -> next = hodd;
		return heven;
	}
}

