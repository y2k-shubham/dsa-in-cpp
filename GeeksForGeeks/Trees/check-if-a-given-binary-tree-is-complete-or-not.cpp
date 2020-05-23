// http://www.geeksforgeeks.org/check-if-a-given-binary-tree-is-complete-tree-or-not/

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

1 1
2 2		3 3
-1 -1

-1 -1

1 1
-1 -1

1 1
2 2
-1 -1

1 1
2 2		3 3
4 4
-1 -1

1 1
2 2		3 3
6 6
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>
#include <queue>

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
bool isCompleteIter(node *);

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

	if (isCompleteIter(root)) {
		cout << "\nIt is complete binary tree\n";
	} else {
		cout << "\nIt is not complete binary tree\n";
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

bool isCompleteIter(node * root) {
	if (root == NULL) {
		return true;
	}

	queue <node *> que;
	bool mustBeLeaf = false;

	que.push(root);
	while (!que.empty()) {
		root = que.front();
		que.pop();

		if (!mustBeLeaf) {
			if (root -> left != NULL && root -> right != NULL) {
				// found a normal full node
				que.push(root -> left);
				que.push(root -> right);
			} else if (root -> left == NULL && root -> right == NULL) {
				// found first leaf node, all subsequent nodes should be leaf nodes
				mustBeLeaf = true;
			} else if (root -> right == NULL) {
				// found the only single-child node, all subsequent nodes should be leaf nodes
				que.push(root -> left);
				mustBeLeaf = true;
			} else {
				// found a node where left is null and right isn't null
				return false;
			}
		} else {
			if (root -> left != NULL || root -> right != NULL) {
				return false;
			}
		}
	}

	return true;
}
