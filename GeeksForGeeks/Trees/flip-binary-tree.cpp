// http://www.geeksforgeeks.org/flip-binary-tree/

/*
>> check the input format, it's given in comments on top of the program.
>> it says keep entering values to be inserted into tree along with their position in the tree, till -1 is entered for position.
>> here position is 1-indexed, so root has position 1, root -> left has position 2, root -> right has position 3, root -> left -> left has position 4 and so on.
>> the tree need not be complete binary tree but all successive insertion positions should be legal
*/

/*
			     1
        2                3
	4      5         6       7
   8 9   10 11        13      14
	    20   22         27
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
4 4		5 5		6 6		7 7
-1 -1

1 1
2 2		3 3
4 6		5 7
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

void inOrder(node *);
void levelOrder(node *);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
void showListRev(node *, const char *);
node * insert(node *, node *, node *);
node * flip(node *);

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

	printf("\nBefore flipping, the inOrder traversal is:-\n");
	inOrder(root);
	cout << endl;

	printf("\nBefore flipping, the level-Order traversal is:-\n");
	levelOrder(root);

	root = flip(root);

	printf("\nAfter flipping, the inOrder traversal is:-\n");
	inOrder(root);
	cout << endl;

	printf("\nAfter flipping, the level-Order traversal is:-\n");
	levelOrder(root);

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

void levelOrder(node * root) {
	queue <node *> que;

	que.push(root);
	while (!que.empty()) {
		int nodeCount = que.size();

		while (nodeCount > 0) {
			node * crrNode = que.front();
			que.pop();

			printf("%d ", crrNode -> val);

			if (crrNode -> left != NULL) {
				que.push(crrNode -> left);
			}
			if (crrNode -> right != NULL) {
				que.push(crrNode -> right);
			}

			nodeCount--;
		}
		cout << endl;
	}
	cout << endl;
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

node * flip(node * root) {
	if (root == NULL) {
		return NULL;
	} else if (root -> left == NULL && root -> right == NULL) {
		return root;
	} else {
		node * flippedRoot = flip(root -> left);

		root -> left -> left = root -> right;
		root -> left -> right = root;
		root -> left = root -> right = NULL;

		return flippedRoot;
	}
}

