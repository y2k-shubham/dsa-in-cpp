// http://www.geeksforgeeks.org/inorder-predecessor-successor-given-key-bst/

/*
50
25 75
10 37 100
30 87 150
34 81
78 84
-1
*/

#include <cstdio>
#include <iostream>

struct node {
	int val;
	struct node * lC;
	struct node * rC;
};

using namespace std;

node * createNode(int);
node * insertNode(node *, node *);
void inOrder(node *);
bool inOrder(node *, int, node **, node **);

int main() {
	node * root;
	int ele;

	cout << "Enter nodes to be inserted into BST\n(-1 to terminate)\n";
	cin >> ele;
	root = NULL;

	while (ele != -1) {
		root = insertNode(root, createNode(ele));
		cin >> ele;
	}

	cout << "\nInOrder tree is:-\n";
	inOrder(root);
	cout << endl;

	cout << "\nEnter node for finding successor and predecessor:\t";
	cin >> ele;

	node ** suc, ** pre;
	node * tmp1 = createNode(-1);
	suc = &tmp1;
	node * tmp2 = createNode(-1);
	pre = &tmp2;

	if (inOrder(root, ele, pre, suc)) {
		cout << "\nInOrder Predecessor = " << (*pre) -> val;
		cout << "\nInOrder Successor   = " << (*suc) -> val << endl;
	} else {
		cout << "\nNode not found in BST\n";
	}

	return 0;
}

node * createNode(int val) {
	node * newNode = new node;
	newNode -> val = val;
	newNode -> lC = NULL;
	newNode -> rC = NULL;
	return newNode;
}

node * insertNode(node * root, node * newNode) {
	if (root == NULL) {
		return newNode;
	} else {
		if (newNode -> val < root -> val) {
			root -> lC = insertNode(root -> lC, newNode);
		} else if (newNode -> val > root -> val) {
			root -> rC = insertNode(root -> rC, newNode);
		} else {
			cout << "Can't insert duplicate element\n";
		}
		return root;
	}
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> lC);
		cout << root -> val << " ";
		inOrder(root -> rC);
	}
}

bool inOrder(node * root, int ele, node ** pre, node ** suc) {
	if (root != NULL) {
		if (ele < root -> val) {
			*suc = root;
			return inOrder(root -> lC, ele, pre, suc);
		} else if (ele > root -> val) {
			*pre = root;
			return inOrder(root -> rC, ele, pre, suc);
		} else {
			if (root -> lC != NULL) {
				node * tmp = root -> lC;
				while (tmp -> rC != NULL) {
					tmp = tmp -> rC;
				}
				*pre = tmp;
			}
			if (root -> rC != NULL) {
				node * tmp = root -> rC;
				while (tmp -> lC != NULL) {
					tmp = tmp -> lC;
				}
				*pre = tmp;
			}
			return true;
		}
	} else {
		return false;
	}
}


