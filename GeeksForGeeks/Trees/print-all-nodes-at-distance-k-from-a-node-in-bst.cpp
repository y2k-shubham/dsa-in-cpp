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
int findDepthOfTarget(link *, int);
void print_k_distance_nodes(link *, int, bool, int, int);
void showNodeIfNeeded(link *, int, int);

int main() {
	link * root;
	int targetNode;
	int targetDepth;
	int k;

	root = createTree();

	cout << "\nThe inOrder Traversal is:-\n";
	inOrder(root);

	cout << "\n\nEnter target node:\t\t";
	cin >> targetNode;

	cout << "Enter required distance k:\t";
	cin >> k;

	targetDepth = findDepthOfTarget(root, targetNode);
	printf("\nDepth of target %d is %d\n", targetNode, targetDepth);

	cout << "\nNodes at distance k = " << k << " from targetNode = " << targetNode << " are:-\n";
	print_k_distance_nodes(root, targetNode, true, targetDepth, k);
	printf("\n\n");

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

int findDepthOfTarget(link * root, int target) {
	if (root -> val == target) {
		return 0;
	} else if (target < root -> val) {
		return 1 + findDepthOfTarget(root -> lChild, target);
	} else {
		return 1 + findDepthOfTarget(root -> rChild, target);
	}
}

void showNodeIfNeeded(link * root, int crrDist, int reqDist) {
	if (crrDist == reqDist) {
		cout << root -> val << "\t";
	}
}

void print_k_distance_nodes(link * root, int target, bool onPath, int crrDist, int reqDist) {
	if (root == NULL) {
		return;
	}

	if (onPath) {
		if (root -> val == target) {
			print_k_distance_nodes(root -> lChild, target, false, 1, reqDist);
			showNodeIfNeeded(root, crrDist, reqDist);
			print_k_distance_nodes(root -> rChild, target, false, 1, reqDist);
		} else {
			if (target < root -> val) {
				print_k_distance_nodes(root -> lChild, target, true, crrDist - 1, reqDist);
				showNodeIfNeeded(root, crrDist, reqDist);
				print_k_distance_nodes(root -> rChild, target, false, crrDist + 1, reqDist);
			} else {
				print_k_distance_nodes(root -> lChild, target, false, crrDist + 1, reqDist);
				showNodeIfNeeded(root, crrDist, reqDist);
				print_k_distance_nodes(root -> rChild, target, true, crrDist - 1, reqDist);
			}
		}
	} else {
		if (crrDist < reqDist) {
			print_k_distance_nodes(root -> lChild, target, false, crrDist + 1, reqDist);
			print_k_distance_nodes(root -> rChild, target, false, crrDist + 1, reqDist);
		} else if (crrDist == reqDist) {
			showNodeIfNeeded(root, crrDist, reqDist);
		}
	}
}
