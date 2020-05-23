// http://www.geeksforgeeks.org/transform-bst-sum-tree/

/*
Input
50
25 75
10 37 100
30 87 150
34 81
78 84
-1

Input
11
2 29
1 7 15 40
35
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
void convert_1(node *, int &);
int convert_2(node *, int);

int main() {
	node * root;
	int ele;

	cout << "Enter elements to create BST:\t";

	cin >> ele;
	root = NULL;

	while (ele != -1) {
		root = insertNode(root, createNode(ele));
		cin >> ele;
	}

	cout << "\nInOrder traversal of BST is:-\n";
	inOrder(root);
	cout << endl;

	// Method_1
//	int gsum = 0;
//	convert_1(root, gsum);

	// Method_2
	convert_2(root, 0);

	cout << "\nInOrder traversal of after conversion BST is:-\n";
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

void convert_1(node * root, int &gsum) {
	if (root != NULL) {
		convert_1(root -> rC, gsum);

		gsum += root -> val;
		root -> val = gsum - (root -> val);

		convert_1(root -> lC, gsum);
	}
}

int convert_2(node * root, int gsum) {
	if (root == NULL) {
		return 0;
	} else {
		int lsum, rsum;
		lsum = rsum = 0;

		rsum = convert_2(root -> rC, gsum);
		lsum = convert_2(root -> lC, gsum + rsum + root -> val);

		int tmp = root -> val;
		root -> val = gsum + rsum;

		return lsum + rsum + tmp;
	}
}

