#include <cstdio>
#include <iostream>
#include <cstdlib>

// 50 25 75 15 35 60 90 10 20 30 40 70 80 29 32 28 33 -1

struct node_1 {
	int val;
	struct node_1 * lChild;
	struct node_1 * rChild;
};

struct node_2 {
	char val;
	struct node_2 * next;
};

typedef struct node_1 tree;
typedef struct node_2 l_list;
using namespace std;

tree * createNode(int);
tree * createTree();
tree * insertNode(tree *, tree *);
void inOrder(tree *);
void showList(l_list *, tree *, int);
bool findPath(tree*, int, l_list *);
int matchCount(tree *, int, int);
void findAncestor(tree *, int, int);

l_list * createListNode(char direction) {
	l_list * newNode;

	newNode = (l_list *) malloc(sizeof(l_list));
	newNode -> next = NULL;
	newNode -> val = direction;

	return newNode;
}

tree * createNode(int val) {
	tree * newNode;

	newNode = (tree *) malloc(sizeof(tree));
	newNode -> val = val;
	newNode -> lChild = NULL;
	newNode -> rChild = NULL;

	return newNode;
}

tree * createTree() {
	tree * root;
	tree * newNode;
	int val;

	root = NULL;
	newNode = NULL;

	cout << "Enter elements to be inserted:-\n";
	cout << "(Enter -1 to stop entering more elements)\n";
	cin >> val;

	root = createNode(val);
	while (true) {
		cin >> val;

		if (val >= 0) {
			//printf("\nTrying to insert %d\n", val);
			newNode = createNode(val);
			root = insertNode(root, newNode);
		} else {
			break;
		}
	}

	return root;
}

tree * insertNode(tree * root, tree * newNode) {
	//printf("compared %d with root = %d\n", newNode -> val, root -> val);
	if (newNode -> val < root -> val) {
		if (root -> lChild != NULL) {
			//printf("making recursive call to left child %d\n");
			root -> lChild  = insertNode(root -> lChild, newNode);
		} else {
			//printf("inserting as left child\n");
			root -> lChild = newNode;
		}
	} else if (newNode -> val > root -> val) {
		if (root -> rChild != NULL) {
			//printf("making recursive call to right child %d\n");
			root -> rChild = insertNode(root -> rChild, newNode);
		} else {
			//printf("inserting as right child\n");
			root -> rChild = newNode;
		}
	} else {
		printf("\nCan't insert duplicates\n");
	}
	return root;
}

void inOrder(tree * root) {
	if (root != NULL) {
		inOrder(root -> lChild);
		cout << root -> val << "\t";
		inOrder(root -> rChild);
	}
}

int main() {
	tree * root;
	int val_1;
	int val_2;
	l_list * head_1;
	l_list * head_2;

	root = createTree();

	printf("\nThe tree in inOrder is:-\n");
	inOrder(root);

	printf("\n\nEnter the nodes who's common ancestor is to be searched for:-\n");
	printf("(n1, n2) = ");
	scanf("%d%d", &val_1, &val_2);

	printf("root -> left  count = %d\n", matchCount(root -> lChild, val_1, val_2));
	printf("root -> right count = %d\n", matchCount(root -> rChild, val_1, val_2));

	findAncestor(root, val_1, val_2);

	head_1 = createListNode('\0');
	head_2 = createListNode('\0');

	printf("\n");
	findPath(root, val_1, head_1);
	findPath(root, val_2, head_2);

	printf("\n1st path is:-\n");
	showList(head_1, root, val_1);

	printf("\n2nd path is:-\n");
	showList(head_2, root, val_2);

	return 0;
}

void showList(l_list * head, tree * root, int targetVal) {
	l_list * linkedList;
	char lastMove;

	cout << "Root -> ";
	linkedList = head -> next;
	for (head = head -> next; head != NULL; head = head -> next) {
		printf("%c -> ", head -> val);
	}
	printf("Destination\n");

	for (lastMove = '\0'; linkedList != NULL; linkedList = linkedList -> next) {
		cout << root -> val << " -> ";

		if (linkedList -> val == 'l') {
			root = root -> lChild;
			lastMove = 'l';
		} else if (linkedList -> val == 'r') {
			root = root -> rChild;
			lastMove = 'r';
		} else {
			printf("null encountered\n");
			break;
		}
	}
	printf("%d -> ", root -> val);
	printf("%d\n", targetVal);

	if (lastMove == 'l') {
		//printf("%d\n", root -> lChild -> val);
	} else if (lastMove == 'r') {
		//printf("%d\n", root -> rChild -> val);
	}
}

bool findPath(tree * root, int targetVal, l_list * node) {
	if (root != NULL) {
		printf("At node = %d\t", root -> val);
		if (root -> val == targetVal) {
			node -> val = '\0';
			printf("root = %d = target\tpath found\ttrue returned!\n\n", targetVal);
			return true;
		} else if (root -> lChild != NULL && root -> lChild -> val == targetVal) {
			node -> val = 'l';
			printf("lChild = %d = target\tpath found\ttrue returned!\n\n", targetVal);
			return true;
		} else if (root -> rChild != NULL && root -> rChild -> val == targetVal) {
			node -> val = 'r';
			printf("rChild = %d = target\tpath found\ttrue returned!\n\n", targetVal);
			return true;
		} else {
			printf("making recursive call\n");
			node -> next = createListNode('\0');

			node -> next -> val = 'l';
			if (findPath(root -> lChild, targetVal, node -> next)) {
				return true;
			}

			node -> next -> val = 'r';
			if (findPath(root -> rChild, targetVal, node -> next)) {
				return true;
			}

			printf("at node = %d\tno path found\t\tfalse returned\tnode -> next deleted\n", root -> val);
			free(node -> next);
			node -> next = NULL;

			return false;

		}
	} else {
		printf("NULL node reached\tfalse returned\n");
		return false;
	}
}

int matchCount(tree * root, int val_1, int val_2) {
	if (root == NULL) {
		return 0;
	} else {
		int ctr;

		ctr = 0;
		if (root -> val == val_1 || root -> val == val_2) {
			ctr = 1;
		}

		ctr += matchCount(root -> lChild, val_1, val_2);
		ctr += matchCount(root -> rChild, val_1, val_2);

		return ctr;
	}
}

void findAncestor(tree * root, int val_1, int val_2) {
	if (root == NULL) {
		return;
	} else if (root -> val == val_1 || root -> val == val_2) {
		printf("\nCommon Ancestor:\t%d\n", root -> val);
		return;
	} else {
		int lCount;

		lCount = matchCount(root -> lChild, val_1, val_2);
		if (lCount == 1) {
			printf("\nCommon Ancestor:\t%d\n", root -> val);
			return;
		} else if (lCount == 2) {
			findAncestor(root -> lChild, val_1, val_2);
		} else {
			findAncestor(root -> rChild, val_1, val_2);
		}
	}
}
