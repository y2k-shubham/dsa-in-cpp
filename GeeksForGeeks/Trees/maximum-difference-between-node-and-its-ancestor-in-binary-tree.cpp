// http://www.geeksforgeeks.org/maximum-difference-between-node-and-its-ancestor-in-binary-tree/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=700227

/*
			1
	   2          3
	 4   5   6      7
   8 9 10  11 13  14
	  20  22   27
				 55


1 1
2 2		3 3
4 4		5 5		6 6		7 7
8 8		9 9		10 10	11 11	13 13	14 14
20 20	22 22	27 27
55 55
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
void showListRev(node *, const char *);
node * insert(node *, node *, node *);
node * findHead(node *);
node * findTail(node *);
node * convert(node *);

int main() {
	node * root;
	node * head, * tail;
	int val, pos;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (val != -1 && pos != -1) {
		node * path = getPath(pos);
		root = insert(root, path -> right, createNode(val));

		scanf("%d%d", &val, &pos);
	}

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	int maxDiff = INT_MIN;
	findMaxDiff(root, maxDiff);
	cout << "\nMax diff between ancestor and node values is " << maxDiff << endl;

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

void showList(node * head, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (node * list = head; list != NULL; list = list -> right) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n");
}

void showListRev(node * head, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (node * list = head; list != NULL; list = list -> left) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n");
}

node * insert(node * root, node * path, node * newNode) {
	if (path == NULL) {
		return newNode;
	} else {
		if (path -> val % 2 == 1) {
			root -> right = insert(root -> right, path -> right, newNode);
		} else {
			root -> left = insert(root -> left, path -> right, newNode);
		}

		return root;
	}
}

int findMaxDiff(Node * root, int &maxDiff) {
	if (root == NULL) {
		return 0;
	} else {
		int lMin, rMin, totMin;

		lMin = (root -> left == NULL) ? INT_MAX : findMaxDiff(root -> left, maxDiff);
		rMin = (root -> right == NULL) ? INT_MAX : findMaxDiff(root -> right, maxDiff);

		totMin = min(lMin, rMin);
		maxDiff = max(maxDiff, root -> data - totMin);

		return min(root -> data, totMin);
	}
}


