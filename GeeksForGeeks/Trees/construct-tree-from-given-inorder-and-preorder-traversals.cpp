// http://www.geeksforgeeks.org/construct-tree-from-given-inorder-and-preorder-traversal/

/*
17
8 4 9 2 20 10 5 22 11 1 6 13 27 55 3 14 7
1 2 4 8 9 5 10 20 11 22 3 6 13 27 55 7 14
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

struct node {
	int val;
	struct node * left;
	struct node * right;
};

void inOrderTrav(node *);
node * createNode(int);
node * createTree(int [MAX], int [MAX], int, int);
int linSearch(int [MAX], int, int, int);
void input(int [MAX], int, const char *);

int main() {
	int inOrder[MAX], preOrder[MAX];
	int len;

	cout << "Enter no of nodes in tree:\t";
	cin >> len;

	input(inOrder, len, "in-order");
	input(preOrder, len, "pre-order");

	node * root = createTree(preOrder, inOrder, 0, len - 1);

	printf("\nThe inOrder traversal is:-\n");
	inOrderTrav(root);
	printf("\n");

	return 0;
}

void input(int arr[MAX], int len, const char * msg) {
	printf("\nEnter %s traversal:-\n", msg);
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void inOrderTrav(node * root) {
	if (root != NULL) {
		inOrderTrav(root -> left);
		printf("%d ", root -> val);
		inOrderTrav(root -> right);
	}
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> left = NULL;
	newNode -> right = NULL;

	return newNode;
}

node * createTree(int preOrder[MAX], int inOrder[MAX], int iLo, int iHi) {
	static int preInd = 0;
	if (iLo > iHi) {
		return NULL;
	} else {
		node * root = createNode(preOrder[preInd++]);
		int ind = linSearch(inOrder, iLo, iHi, root -> val);

		root -> left = createTree(preOrder, inOrder, iLo, ind - 1);
		root -> right = createTree(preOrder, inOrder, ind + 1, iHi);

		return root;
	}
}

int linSearch(int arr[MAX], int lo, int hi, int ele) {
	for (int i = lo; i <= hi; i++) {
		if (arr[i] == ele) {
			return i;
		}
	}

	return -1;
}

