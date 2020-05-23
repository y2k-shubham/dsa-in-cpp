#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>

struct node {
	int val;
	struct node * l_child;
	struct node * r_child;
};

typedef struct node link;
using namespace std;

link * insertNode(link *, link *);
void in_order(link *);
link * createNode(int);
void spiral_order(link *);

int main() {
	link * root;
	link * newNode;
	int element;

	cout << "\nEnter elements into the Binary-Search-Tree (-1 to terminate):-\n";
	cin >> element;

	root = NULL;
	while (element != -1) {
		newNode = createNode(element);
		root = insertNode(root, newNode);
		cin >> element;
	}

	cout << "\nThe BST in In-Order is:-\n";
	in_order(root);

	cout << "\n\nThe BST in Spiral-Level-Order is:-\n";
	spiral_order(root);

	return 0;
}

link * createNode(int element) {
	link * newNode;

	newNode = (link *) malloc(sizeof(link));
	newNode -> l_child = NULL;
	newNode -> r_child = NULL;
	newNode -> val = element;

	return newNode;
}

void in_order(link * root) {
	if (root != NULL) {
		in_order(root -> l_child);
		cout << root -> val << "\t";
		in_order(root -> r_child);
	}
}

link * insertNode(link * root, link * newNode) {
	if (root == NULL) {
		return newNode;
	} else {
		if (newNode -> val < root -> val) {
			root -> l_child = insertNode(root -> l_child, newNode);
		} else if (newNode -> val > root -> val) {
			root -> r_child = insertNode(root -> r_child, newNode);
		} else {
			cout << "\nError! : Repeated Elements not allowed\n";
		}
		return root;
	}
}

void spiral_order(link * root) {
	stack <link *> s1, s2;

	s2.push(root);
	while (!s1.empty() || !s2.empty()) {
		while (!s1.empty()) {
			link * tmp = s1.top();
			s1.pop();

			if (tmp -> r_child != NULL) {
				s2.push(tmp -> r_child);
			}
			if (tmp -> l_child != NULL) {
				s2.push(tmp -> l_child);
			}

			printf("%d\t", tmp -> val);
		}
		printf("\n");

		while (!s2.empty()) {
			link * tmp = s2.top();
			s2.pop();

			if (tmp -> l_child != NULL) {
				s1.push(tmp -> l_child);
			}
			if (tmp -> r_child != NULL) {
				s1.push(tmp -> r_child);
			}

			printf("%d\t", tmp -> val);
		}
		printf("\n");
	}
	printf("\n");
}
