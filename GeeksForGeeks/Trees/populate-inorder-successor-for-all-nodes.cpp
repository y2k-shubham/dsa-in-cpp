// http://www.geeksforgeeks.org/populate-inorder-successor-for-all-nodes/

/*
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
#include <cstdlib>

using namespace std;

struct node {
	int val;
	struct node * lC;
	struct node * rC;
	struct node * next;
};

void inOrder(node *, bool);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
node * insert(node *, node *, node *);
void link(node *, node **);

int main() {
	node * root;
	int val, pos;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (val != -1 && pos != -1) {
		node * path = getPath(pos);
		root = insert(root, path -> rC, createNode(val));

		scanf("%d%d", &val, &pos);
	}

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root, false);
	printf("\n\n");

	node * tmp = createNode(-1);
	link(root, &tmp);
	tmp -> next = NULL;

	printf("\nThe inOrder traversal with inOrder successor is:-\n");
	inOrder(root, true);
	printf("\n");

	return 0;
}

void inOrder(node * root, bool showNext) {
	if (root != NULL) {
		inOrder(root -> lC, showNext);

		if (showNext && root -> next != NULL) {
			printf("[%d %d] ", root->val, root -> next -> val);
		} else {
			printf("%d ", root -> val);
		}

		inOrder(root -> rC, showNext);
	}
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;

	newNode -> lC = NULL;
	newNode -> rC = NULL;
	newNode -> next = NULL;

	return newNode;
}

node * getPath(int val) {
	node * head;

	head = createNode(val);
	val /= 2;

	while (val >= 1) {
		node * newNode = createNode(val);
		newNode -> rC = head;
		head = newNode;

		val /= 2;
	}

	return head;
}

void showList(node * head, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (node * list = head; list != NULL; list = list -> rC) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n");
}

node * insert(node * root, node * path, node * newNode) {
	if (path == NULL) {
		return newNode;
	} else {
		if (path -> val % 2 == 1) {
			root -> rC = insert(root -> rC, path -> rC, newNode);
		} else {
			root -> lC = insert(root -> lC, path -> rC, newNode);
		}

		return root;
	}
}

void link(node * root, node ** prev) {
	if (root != NULL) {
		link(root -> lC, prev);

		if ((*prev) -> val !=  -1) {
			printf("%d -> next\tmade to point to %d\n", (*prev) -> val, root -> val);
			(*prev) -> next = root;
		}
		*prev = root;

		link(root -> rC, prev);
	}
}
