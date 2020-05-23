/*
1 50
1 25 1 75
1 10 1 37 1 100
1 30 1 87 1 150
1 34 1 81
1 78 1 84
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
node * deleteNode(node *, int);
node * findInOrdSucc(node *);
void swap(node *, node *);

int main() {
	node * root;
	int choice;
	int ele;

	root = NULL;
	choice = -1;

	while (choice != 4) {
		cout << "\n1. Insert";
		cout << "\n2. Delete";
		cout << "\n3. InOrder";
		cout << "\n4. Exit";
		cout << "\nEnter your choice:\t";
		cin >> choice;

		switch (choice) {
			case 1:
				cout << "\nEnter element:\t";
				cin >> ele;
				root = insertNode(root, createNode(ele));
				break;

			case 2:
				cout << "\nEnter element:\t";
				cin >> ele;
				root = deleteNode(root, ele);
				break;

			case 3:
				cout << "\nInOrder traversal is:-\n";
				inOrder(root);
				cout << endl;

			case 4:
				continue;

			default:
				cout << "\nError! : invalid input\n";
		}
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

node * deleteNode(node * root, int ele) {
	if (root == NULL) {
		cout << "Element not found in BST\n";
		return NULL;
	} else if (ele < root -> val) {
		root -> lC = deleteNode(root -> lC, ele);
		return root;
	} else if (ele > root -> val) {
		root -> rC = deleteNode(root -> rC, ele);
		return root;
	} else {
		if (root -> lC != NULL && root -> rC != NULL) {
			node * inOrdSucc = findInOrdSucc(root -> rC);
//			printf("Double child node %d swapped with inOrdSuc %d\nDeletion called on %d -> rC = %d\n", root -> val, inOrdSucc -> val, ele, root -> rC -> val);
			swap(root, inOrdSucc);
			root -> rC = deleteNode(root -> rC, ele);
			return root;
		} else if (root -> lC != NULL) {
//			printf("Single child node deleted, %d -> lC = %d returned\n", root -> val, root -> lC -> val);
			node * tmp = root -> lC;
			delete(root);
			return tmp;
		} else if (root -> rC != NULL) {
//			printf("Single child node deleted, %d -> rC = %d returned\n", root -> val, root -> rC -> val);
			node * tmp = root -> rC;
			delete(root);
			return tmp;
		} else {
//			printf("Leaf node %d deleted, NULL returned\n", root -> val);
			delete(root);
			return NULL;
		}
	}
}

node * findInOrdSucc(node * root) {
	if (root -> lC == NULL) {
		return root;
	} else {
		return findInOrdSucc(root -> lC);
	}
}

void swap(node * n1, node * n2) {
	int tmp = n1 -> val;
	n1 -> val = n2 -> val;
	n2 -> val = tmp;
}

