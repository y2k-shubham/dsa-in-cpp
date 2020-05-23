#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

struct node {
	int val;
	struct node * next;
};

void showList(node *, const char *);
node * input(const char *);
node * createNode(int);
node * merge(node *, node *);

int main() {
	node * head_1, * head_2, * head_3;
	head_1 = head_2 = head_3 = NULL;

	head_1 = input("first");
	head_2 = input("second");

	showList(head_1, "first");
	showList(head_2, "second");

	head_3 = merge(head_1, head_2);
	showList(head_3, "merged");

	return 0;
}

void showList(node * head, const char * msg) {
	printf("\nThe %s linked list is:-\n", msg);
	for (node * list = head; list != NULL; list = list -> next) {
		printf("%d\t", list -> val);
	}
	cout << endl;
}

node * input(const char * msg) {
	node * head, * list, * newNode;
	int n, ele;

	printf("\nEnter length of %s linked-list:\t", msg);
	cin >> n;

	if (n <= 0) {
		return NULL;
	}

	printf("Enter elements of %s linked-list:-\n", msg);
	cin >> ele;

	list = head = createNode(ele);
	for (int i = 2; i <= n; i++) {
		cin >> ele;
		newNode = createNode(ele);

		list -> next = newNode;
		list = newNode;
	}

	return head;
}

node * createNode(int val) {
	node * newNode = (node *) malloc(sizeof(node));
	newNode -> next = NULL;
	newNode -> val = val;

	return newNode;
}

node * merge(node * head_1, node * head_2) {
	// cases when one list is empty
	if (head_1 == NULL) {
		return head_2;
	} else if (head_2 == NULL) {
		return head_1;
	}

	node * head, * list, * newNode;

	if (head_1 -> val < head_2 -> val) {
		list = head = head_1;
		head_1 = head_1 -> next;
	} else {
		list = head = head_2;
		head_2 = head_2 -> next;
	}

	while (head_1 != NULL && head_2 != NULL) {
		if (head_1 -> val < head_2 -> val) {
			newNode = head_1;
			head_1 = head_1 -> next;
		} else {
			newNode = head_2;
			head_2 = head_2 -> next;
		}

		list -> next = newNode;
		newNode -> next = NULL;		// for safety although list will finally terminate at null
		list = newNode;
	}

	if (head_1 != NULL) {
		list -> next = head_1;
	} else if (head_2 != NULL) {
		list -> next = head_2;
	}

	return head;
}

