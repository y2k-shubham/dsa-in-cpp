// A simple and tail recursive C++ program to reverse
// a linked list
#include<bits/stdc++.h>
using namespace std;

struct node {
	int data;
	struct node *next;
};

node * checkPallin(node *, node *, bool &);

// A utility function to create a new node
node *newNode(int key) {
	node *temp = new node;
	temp->data = key;
	temp->next = NULL;
	return temp;
}

// A utility function to print a linked list
void printlist(node *head) {
	while(head != NULL) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

// Driver program to test above functions
int main() {
//	node *head1 = newNode(1);
//	head1->next = newNode(2);
//	head1->next->next = newNode(2);
//	head1->next->next->next = newNode(4);
//	head1->next->next->next->next = newNode(5);
//	head1->next->next->next->next->next = newNode(6);
//	head1->next->next->next->next->next->next = newNode(7);
//	head1->next->next->next->next->next->next->next = newNode(8);

//	node *head1 = newNode(1);
//	head1->next = newNode(2);
//	head1->next->next = newNode(4);
//	head1->next->next->next = newNode(5);
//	head1->next->next->next->next = newNode(5);
//	head1->next->next->next->next->next = newNode(4);
//	head1->next->next->next->next->next->next = newNode(2);
//	head1->next->next->next->next->next->next->next = newNode(1);

//	node *head1 = newNode(1);
//	head1->next = newNode(2);
//	head1->next->next = newNode(4);
//	head1->next->next->next = newNode(5);
//	head1->next->next->next->next = newNode(4);
//	head1->next->next->next->next->next = newNode(2);
//	head1->next->next->next->next->next->next = newNode(1);

//	node *head1 = newNode(1);
//	head1->next = newNode(2);
//	head1->next->next = newNode(4);
//	head1->next->next->next = newNode(5);
//	head1->next->next->next->next = newNode(3);
//	head1->next->next->next->next->next = newNode(2);
//	head1->next->next->next->next->next->next = newNode(1);

	node *head1 = newNode(1);

	cout << "Given linked list\n";
	printlist(head1);

	bool isPallin = true;
	checkPallin(head1, head1, isPallin);

	if (isPallin) {
		printf("\nLinked list is pallindrome\n");
	} else {
		printf("\nLinked list is not pallindrome\n");
	}

	return 0;
}

node * checkPallin(node * curr, node * head, bool &isPallin) {
	if (curr -> next == NULL) {
		if (curr -> data != head -> data) {
			isPallin = false;
		}

		return head -> next;
	} else {
		node * tmp = checkPallin(curr -> next, head, isPallin);

		if (isPallin && (curr -> data != tmp -> data)) {
			isPallin = false;
		}

		return tmp -> next;
	}
}
