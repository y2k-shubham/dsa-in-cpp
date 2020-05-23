#include <cstdio>
#include <vector>
#include <cmath>

/*
5 1
36 2	14 3
47 4	21 5	-8 6	19 7
61 8	75 9	-7 13	27 15
54 16	19 17	50 18	100 19	-5 27
90 38	120 39	-6 54	-4 55
110 78	0 111
-1 222
-2 444
-1 -1

5 1
36 2	42 3
47 4	21 5	-8 6	19 7
61 8	75 9	7 13	27 15
54 16	19 17	50 18	100 19	-5 27
90 38	120 39	-6 54	-4 55
110 78	0 111
-1 222
-2 444
-1 -1
*/

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

struct pathNode {
	char move;
	struct pathNode * next;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
node * insert(node *, node *, node *);
pathNode * createNode(char);
bool findPath(node *, pathNode *, int);
void showPath(node *, pathNode *);
void showPath(pathNode *);
void showLCA(node *, pathNode *, pathNode *, bool);

int main() {
	node * root;
	pathNode * head_1, * head_2;
	int val, pos;
	int ele_1, ele_2;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (pos != -1) {
		node * path = getPath(pos);
		root = insert(root, path -> right, createNode(val));

		scanf("%d%d", &val, &pos);
	}

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	printf("\nEnter elements for finding LCA:\t");
	scanf("%d%d", &ele_1, &ele_2);

	head_1 = createNode('\0');
	head_2 = createNode('\0');
	if (findPath(root, head_1, ele_1) && findPath(root, head_2, ele_2)) {
		head_1 = head_1 -> next;
		head_2 = head_2 -> next;

		printf("\nPath to node %d is:-\n", ele_1);
		showPath(head_1);
		showPath(root, head_1);

		printf("\nPath to node %d is:-\n", ele_2);
		showPath(head_2);
		showPath(root, head_2);

		printf("\nPath to LCA is:-\n");
		showLCA(root, head_1, head_2, false);
		showLCA(root, head_1, head_2, true);
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

pathNode * createNode(char move) {
	pathNode * newNode = new pathNode;
	newNode -> move = move;
	newNode -> next = NULL;
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

bool findPath(node * root, pathNode * tail, int ele) {
	if (root == NULL) {
		return false;
	} else if (root -> val == ele) {
		return true;
	} else {
		pathNode * newNode = createNode('\0');
		tail -> next = newNode;

		newNode -> move = 'L';
		if (findPath(root -> left, newNode, ele)) {
			return true;
		}

		newNode -> move = 'R';
		if (findPath(root -> right, newNode, ele)) {
			return true;
		}

		delete(newNode);
		tail -> next = NULL;

		return false;
	}
}

void showPath(node * root, pathNode * head) {
	if (head == NULL) {
		// reached target node
		printf("%d\n", root -> val);
	} else if (head -> move == 'L') {
		printf("%d -> ", root -> val);
		showPath(root -> left, head -> next);
	} else {
		printf("%d -> ", root -> val);
		showPath(root -> right, head -> next);
	}
}

void showPath(pathNode * head) {
	if (head == NULL) {
		printf("target\n");
	} else if (head -> move == 'L') {
		printf("L -> ");
		showPath(head -> next);
	} else {
		printf("R -> ");
		showPath(head -> next);
	}
}

void showLCA(node * root, pathNode * path_1, pathNode * path_2, bool showNode) {
	if (path_1 == NULL || path_2 == NULL) {
		if (showNode) {
			printf("%d -> target\n", root -> val);
			printf("\nLCA is %d\n", root -> val);
		} else if (path_1 != NULL) {
			printf("%c\n", path_1 -> move);
		} else {
			printf("%c\n", path_2 -> move);
		}
	} else if (path_1 -> move != path_2 -> move) {
		if (showNode) {
			printf("%d -> target\n", root -> val);
			printf("LCA is %d\n", root -> val);
		} else {
			printf("LCA\n");
		}
	} else {
		if (showNode) {
			printf("%d -> ", root -> val);
		} else {
			printf("%c -> ", path_1 -> move);
		}

		if (path_1 -> move == 'L') {
			showLCA(root -> left, path_1 -> next, path_2 -> next, showNode);
		} else {
			showLCA(root -> right, path_1 -> next, path_2 -> next, showNode);
		}
	}
}

