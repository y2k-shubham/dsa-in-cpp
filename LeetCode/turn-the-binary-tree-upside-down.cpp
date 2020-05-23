// INCORRECT SOLUTION: different formulations in different places
// http://qa.geeksforgeeks.org/5011/turn-the-binary-tree-upside-down
// http://teisei.github.io/algorithm/interview/2016/06/05/Leetcode-Locked-Problems/
// https://discuss.leetcode.com/category/165/binary-tree-upside-down

#include <cstdio>
#include <iostream>

/*
1 1
2 2		3 3
4 4		5 5
-1 -1

*/

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
node * insert(node *, node *, node *);
node * turnUpsideDown(node *, node *);;

int main() {
	node * root;
	int val, pos;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (pos != -1) {
		node * path = getPath(pos);
		root = insert(root, path -> right, createNode(val));

		scanf("%d%d", &val, &pos);
	}

	printf("\nBefore flipping, inOrder traversal is:-\n");
	inOrder(root);
	printf("\n\n");

	root = turnUpsideDown(root, NULL);

	printf("\nAfter flipping, inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	return 0;
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> left = NULL;
	newNode -> right = NULL;

	return newNode;
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> left);
		printf("%d ", root -> val);
		inOrder(root -> right);
	}
}

node * getPath(int val) {
	node * head;

	head = createNode(val);
	val /= 2;

	while (val >= 1) {
		node * newNode = createNode(val);
		newNode -> right = head;
		head = newNode;

		val /= 2;
	}

	return head;
}

node * insert(node * root, node * path, node * newNode) {
	if (path == NULL) {
//		printf("at node %d\tpath = NULL\n", root -> val);
		return newNode;
	} else {
//		printf("at node %d\tpath = %d\n", root -> val, path -> val);
		if (path -> val % 2 == 1) {
			root -> right = insert(root -> right, path -> right, newNode);
		} else {
			root -> left = insert(root -> left, path -> right, newNode);
		}

		return root;
	}
}

node * turnUpsideDown(node * crr, node * par) {
	if (crr == NULL) {
		return NULL;
	} else {
		node * root = turnUpsideDown(crr -> left, crr);
		crr -> left = (par != NULL) ? (par -> right) : NULL;
		crr -> right = (par != NULL) ? par : NULL;

		if (root == NULL) {
			return crr;
		} else {
			return root;
		}
	}
}


