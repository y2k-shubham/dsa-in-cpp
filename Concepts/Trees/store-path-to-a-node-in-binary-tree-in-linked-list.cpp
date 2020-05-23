#include <cstdio>
#include <vector>
#include <cmath>

/*
>> check the input format, it's given in comments on top of the program.
>> it says keep entering values to be inserted into tree along with their position in the tree, till -1 is entered for position.
>> here position is 1-indexed, so root has position 1, root -> left has position 2, root -> right has position 3, root -> left -> left has position 4 and so on.
>> the tree need not be complete binary tree but all successive insertion positions should be legal
>> in the input given below, all nodes (along-with their positions) written in a single line actually lie in same level, so each line of input denotes a level
*/

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

int main() {
	node * root;
	pathNode * head, * tail;
	int val, pos;
	int ele;

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

	printf("\nEnter element to print path:\t");
	scanf("%d", &ele);

	head = tail = createNode('\0');
	if (findPath(root, tail, ele)) {
		printf("\nPath to target node is:-\n");
		showPath(head -> next);
		showPath(root, head -> next);
	} else {
		printf("\nElement doesn't exist in binary tree\n");
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
		printf("%d\t->\t", root -> val);
		showPath(root -> left, head -> next);
	} else {
		printf("%d\t->\t", root -> val);
		showPath(root -> right, head -> next);
	}
}

void showPath(pathNode * head) {
	if (head == NULL) {
		printf("target\n");
	} else if (head -> move == 'L') {
		printf("L\t->\t");
		showPath(head -> next);
	} else {
		printf("R\t->\t");
		showPath(head -> next);
	}
}

