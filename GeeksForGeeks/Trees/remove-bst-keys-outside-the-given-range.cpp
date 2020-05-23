// http://www.geeksforgeeks.org/remove-bst-keys-outside-the-given-range/

/*
50
25 75
10 37 100
30 87 150
34 81
78 84
-1

6
-13 14
-8 13 15
7
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
node * deleteNode(node *, int);
node * findInOrderSucc(node *);
void swap(node *, node *);
node * postOrderDel(node *, int, int);
node * postOrderSmartDel(node *, int, int);
node * postOrderLazyDel(node *, int, int);

int main() {
	node * root;
	int rMin, rMax;
	int ele;

	cout << "Enter nodes to be inserted into BST\n(-1 to terminate)\n";
	cin >> ele;
	root = NULL;

	while (ele != -1) {
		root = insertNode(root, createNode(ele));
		cin >> ele;
	}

	cout << "\nOriginal InOrder tree is:-\n";
	inOrder(root);
	cout << endl;

	cout << "\nEnter range outside which values have to be deleted:\t";
	cin >> rMin >> rMax;

//	root = postOrderDel(root, rMin, rMax);				// brute force delete
//	root = postOrderSmartDel(root, rMin, rMax);			// smart delete
	root = postOrderLazyDel(root, rMin, rMax);			// Lazy delete, doesn't recurse when all nodes in a subtree lie outside the range

	cout << "\nAfter deletion, InOrder tree is:-\n";
	inOrder(root);
	cout << endl;

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
		printf("node %d not present in bst\n", ele);
	} else if (ele < root -> val) {
		root -> lC = deleteNode(root -> lC, ele);
	} else if (ele > root -> val) {
		root -> rC = deleteNode(root -> rC, ele);
	} else {
		if (root -> lC == NULL && root -> rC == NULL) {
			delete(root);
			return NULL;
		} else if (root -> lC != NULL && root -> rC != NULL) {
			node * succ = findInOrderSucc(root -> rC);
			swap(root, succ);
			root -> rC = deleteNode(root -> rC, ele);
			return root;
		} else if (root -> lC != NULL) {
			node * tmp = root -> lC;
			delete(root);
			return tmp;
		} else {
			node * tmp = root -> rC;
			delete(root);
			return tmp;
		}
	}
}

node * findInOrderSucc(node * tmp) {
	if (tmp -> lC == NULL) {
		return tmp;
	} else {
		return findInOrderSucc(tmp -> lC);
	}
}

void swap(node * n1, node * n2) {
	int val = n1 -> val;
	n1 -> val = n2 -> val;
	n2 -> val = val;
}

node * postOrderDel(node * root, int rMin, int rMax) {
	if (root != NULL) {
//		printf("at node %d\n", root -> val);

		root -> lC = postOrderDel(root -> lC, rMin, rMax);
		root -> rC = postOrderDel(root -> rC, rMin, rMax);

		if (root -> val < rMin || root -> val > rMax) {
//			printf("deleting node = %d\t", root -> val);
			root = deleteNode(root, root -> val);
//			if (root != NULL) {
//				printf("new current root = %d\n", root -> val);
//			} else {
//				printf("new current root = NULL\n");
//			}
		}

		return root;
	} else {
		return NULL;
	}
}

node * postOrderSmartDel(node * root, int rMin, int rMax) {
	if (root == NULL) {
		return NULL;
	} else {
		root -> lC = postOrderDel(root -> lC, rMin, rMax);
		root -> rC = postOrderDel(root -> rC, rMin, rMax);

		/*
		Realize that after we've recursed over left and right subtrees, if the current node has
		to be deleted, then either it would've become a leaf node or it would've single child but
		never both child. This is so because if current node lies outside given range, then
		definitely either left subtree or right subtree will also lie entirely out-of-range.

		We can take advantage of this fact and go ahead with deletion in this method only, without
		requirement of any additional methods
		*/

		if (root -> val < rMin) {
			// left subtree would already have been deleted, right subtree may or may not have been deleted
			node * tmp = root -> rC;
			delete(root);
			return tmp;
		} else if (root -> val > rMax) {
			// right subtree would already have been deleted, left subtree may or may not have been deleted
			node * tmp = root -> lC;
			delete(root);
			return tmp;
		} else {
			return root;
		}
	}
}

node * postOrderLazyDel(node * root, int rMin, int rMax) {
	if (root == NULL) {
		return NULL;
	} else {
		if (root -> val < rMin) {
			return postOrderDel(root -> rC, rMin, rMax);
		} else if (root -> val > rMax) {
			return postOrderDel(root -> lC, rMin, rMax);
		} else {
			root -> lC = postOrderDel(root -> lC, rMin, rMax);
			root -> rC = postOrderDel(root -> rC, rMin, rMax);
			return root;
		}
	}
}

