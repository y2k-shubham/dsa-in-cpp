/*
7
0 35
164 29789
32188745 65479
3 1
7894 3215
0 0
4 325
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
void showList(node *, const char *);
node * createList(int, node *);
node * clone(node *);
int addUnequal(node *, node *, node *, node *, node *);
int addEqual(node *, node *, node *);

int main() {
	int t;

	cout << "Enter no of test cases:\t";
	cin >> t;

	while (t-- > 0) {
		node * head1, * head2, * head3;
		int n1, n2;

		cout << endl << "================================" << endl;
		cout << "Enter two positive integers:\t";
		cin >> n1 >> n2;

		head1 = createList(n1, NULL);
		head2 = createList(n2, NULL);
		head3 = createNode(0);

		showList(head1, "first");
		showList(head2, "second");

		if (head1 == NULL) {
			head3 = clone(head2);
		} else if (head2 == NULL) {
			head3 = clone(head1);
		} else {
			node * list1, * list2, * list3;
			node * newNode;
			for (list1 = head1, list2 = head2, list3 = head3; list1 != NULL && list2 != NULL; ) {
				newNode = createNode(0);
				list3 -> next = newNode;
				list3 = newNode;

				list1 = list1 -> next;
				list2 = list2 -> next;
			}

			node * longer, * shorter, * rem;
			if (list1 == NULL) {
				shorter = head1;
				longer = head2;
				rem = list2;
			} else {
				shorter = head2;
				longer = head1;
				rem = list1;
			}

			head3 = (head3 -> next != NULL) ? (head3 -> next) : head3;
			int carry = addUnequal(longer, shorter, head3, list3, rem);

			while (carry > 0) {
				newNode = createNode(carry % 10);
				carry /= 10;

				newNode -> next = head3;
				head3 = newNode;
			}
		}

		showList(head3, "sum");
	}

	return 0;
}

node * createNode(int val) {
	node * newNode;

	newNode = (node *) malloc(sizeof(node));
	newNode -> val = val;
	newNode -> next = NULL;

	return newNode;
}

void showList(node * head, const char * msg) {
	printf("\n%s linked list is:-\n", msg);

	for (node * list = head; list != NULL; list = list -> next) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n\n");
}

node * clone(node * head) {
	if (head == NULL) {
		return NULL;
	} else {
		node * newNode = createNode(head -> val);
		newNode -> next = clone(head -> next);
		return newNode;
	}
}

node * createList(int n, node * head) {
	if (n == 0) {
		return head;
	} else {
		node * newNode = createNode(n % 10);

		newNode -> next = head;
		head = newNode;

		return createList(n / 10, head);
	}
}

int addUnequal(node * longer, node * shorter, node * result, node * resTail, node * rem) {
	if (rem == NULL) {
		printf("longer = %d\tshorter = %d\trem = NULL\n", longer -> val, shorter -> val);
		return addEqual(longer, shorter, result);
	} else {
		printf("longer = %d\tshorter = %d\trem = %d\n", longer -> val, shorter -> val, rem -> val);
		node * newNode = createNode(0);
		resTail -> next = newNode;

		int carry = addUnequal(longer -> next, shorter, result -> next, newNode, rem -> next);
		int sum = longer -> val + carry;

		result -> val = sum % 10;
		return sum / 10;
	}
}

int addEqual(node * list1, node * list2, node * list3) {
	int sum;

	if (list1 -> next == NULL) {
		sum = list1 -> val + list2 -> val;
	} else {
		int carry = addEqual(list1 -> next, list2 -> next, list3 -> next);
		sum = list1 -> val + list2 -> val + carry;
	}

	list3 -> val = sum % 10;
	return sum / 10;
}

