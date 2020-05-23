// http://www.geeksforgeeks.org/function-to-check-if-a-singly-linked-list-is-palindrome/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

struct node {
	int val;
	struct node * next;
};

using namespace std;
typedef struct node link;

node * createNode(int);
node * createList();
void showList(node *);
bool isPalin(node **, node *);

int main() {
	node * head;

	srand(time(NULL));
	head = createList();
	showList(head);

	if (head == NULL || isPalin(&head, head)) {
		printf("\nIt is palindrome\n");
	} else {
		printf("\nIt is not palindrome\n");
	}

	return 0;
}

node * createNode(int val) {
	node * newNode;
	newNode = (node *) malloc(sizeof(node));

	newNode -> next = NULL;
	newNode -> val = val;

	return newNode;
}

node * createList() {
	int len;
	node * head;
	node * list;
	node * newNode;
	int ele;

	printf("Enter length of list:\t");
	scanf("%d", &len);

	head = NULL;
	printf("Enter elements of linked-list:-\n");
	for (int i = 1; i <= len; i++) {
		cin >> ele;
		if (head == NULL) {
//			head = list = createNode(rand() % 1000);
			head = list = createNode(ele);
		} else {
//			newNode = createNode(rand() % 1000);
			newNode = createNode(ele);
			list -> next = newNode;
			list = newNode;
		}
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

bool isPalin(node ** left, node * curr) {
	if (curr == NULL) {
		return true;
	} else if (isPalin(left, curr -> next) == true) {
		if ((* left) -> val == curr -> val) {
			* left = (* left) -> next;
			return true;
		} else {
			return false;
		}
	}
}

