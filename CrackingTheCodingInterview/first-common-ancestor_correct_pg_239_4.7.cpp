#include <cstdio>
#include <iostream>
#include <cstdlib>

// 50 25 75 15 35 60 90 10 20 30 40 70 80 29 32 28 33 -1
// Microsoft Interview Question: given a BST, print all nodes at a distance k from a given node

struct node {
	int val;
	struct node * lChild;
	struct node * rChild;
};

typedef struct node link;
using namespace std;

link * createNode(int);
link * createTree();
link * insertNode(link *, link *);
void inOrder(link *);
bool findLowestCommonAncestor(link *, int, int);
int nodeCount(link *, int, int, int);

int main() {
	link * root;
	int val_1;
	int val_2;

	root = createTree();

	printf("\nEnter 1st node:\t");
	scanf("%d", &val_1);

	printf("Enter 2nd node:\t");
	scanf("%d", &val_2);

	printf("(n1, n2) = (%d, %d)\tlCount = %d\trCount = %d\n\n", 60, 30, nodeCount(root -> lChild, 60, 30, 0), nodeCount(root -> rChild, 60, 30, 0));
	printf("(n1, n2) = (%d, %d)\tlCount = %d\trCount = %d\n\n", 28, 32, nodeCount(root -> lChild, 28, 32, 0), nodeCount(root -> rChild, 28, 32, 0));
	printf("(n1, n2) = (%d, %d)\tlCount = %d\trCount = %d\n\n", 10, 40, nodeCount(root -> lChild, 10, 40, 0), nodeCount(root -> rChild, 10, 40, 0));

	//findLowestCommonAncestor(root, val_1, val_2);

	return 0;
}

link * createNode(int val) {
	link * newNode;

	newNode = (link *) malloc(sizeof(link));
	newNode -> val = val;
	newNode -> lChild = NULL;
	newNode -> rChild = NULL;

	return newNode;
}

link * createTree() {
	link * root;
	link * newNode;
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

link * insertNode(link * root, link * newNode) {
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

void inOrder(link * root) {
	if (root != NULL) {
		inOrder(root -> lChild);
		cout << root -> val << "\t";
		inOrder(root -> rChild);
	}
}

int nodeCount(link * root, int val_1, int val_2, int ctr) {
	if (root == NULL) {
		return 0;
	} else {
		ctr += nodeCount(root -> lChild, val_1, val_2, ctr);
		ctr += nodeCount(root -> rChild, val_1, val_2, ctr);
		if (root -> val == val_1 || root -> val == val_2) {
			ctr += 1;
			printf("at node = %d\tctr incremented to %d\n", root -> val, ctr);
		}

		return ctr;
	}
}

bool findLowestCommonAncestor(link * root, int val_1, int val_2) {
	if (root -> val == val_1 || root -> val == val_2) {
		printf("At node = %d\tone of the nodes itself is ancestor\n", root -> val);
		cout << "Lowest common ancestor is " << root -> val << endl;
		return true;
	} else {
		int lNodeCount;
		int rNodeCount;
		if ((lNodeCount = nodeCount(root -> lChild, val_1, val_2, 0)) != 1) {
			printf("At node = %d\tleft nodeCount = 2\tboth nodes in left\n", root -> val);
			return findLowestCommonAncestor(root -> lChild, val_1, val_2);
		} else if ((rNodeCount = nodeCount(root -> rChild, val_1, val_2, 0)) != 1) {
			printf("At node = %d\right nodeCount = 2\tboth nodes in right\n", root -> val);
			return findLowestCommonAncestor(root -> rChild, val_1, val_2);
		} else {
			printf("At node = %d\tleft nodeCount = %d\tright node count = %d\tboth nodes on different sides\n", lNodeCount, rNodeCount, root -> val);
			cout << "Lowest common ancestor is " << root -> val << endl;
			return true;
		}
	}
}
