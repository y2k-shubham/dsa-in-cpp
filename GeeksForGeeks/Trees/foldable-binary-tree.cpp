// http://www.geeksforgeeks.org/foldable-binary-trees/

/*
			     1
        2                 3
	4       5         6       7
   8 9   10  11        13   14
	    20  22          27
				         55


1 1
2 2		3 3
4 4		5 5		6 6		7 7
8 8		9 9		10 10	11 11	13 13	14 14
20 20	22 22	27 27
55 55
-1 -1

		10
	7		15
	  9   11

10 1
7 2		15 3
9 5		11 6
-1 -1

		10
	7		15
9				11

10 1
7 2		15 3
9 4		11 7
-1 -1


		10
	7		15
  5       11

10 1
7 2		15 3
5 4		11 6
-1 -1

		10
	7		 15
  9   10   12

10 1
7 2		15 3
9 4		10 5	12 6
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
bool isFoldable(node *, node *);

int main() {
	node * root;
	int val, pos;

	printf("\nEnter (val, pos) to insert into tree:-\n(pos starts from 1)\n");
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

	if (root == NULL || isFoldable(root -> left, root -> right)) {
		printf("\nIt is Foldable Binary Tree\n");
	} else {
		printf("\nIt is not Foldable Binary Tree\n");
	}

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

bool isFoldable(node * lRoot, node * rRoot) {
	if (lRoot == NULL && rRoot == NULL) {
		return true;
	} else if (lRoot != NULL && rRoot != NULL) {
		return isFoldable(lRoot -> left, rRoot -> right) && isFoldable(lRoot -> right, rRoot -> left);
	} else {
		return false;
	}
}

