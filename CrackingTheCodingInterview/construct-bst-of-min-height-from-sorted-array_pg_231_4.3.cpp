#include <cstdio>
#include <iostream>
#include <cstdlib>

struct node {
	int val;
	struct node * lChild;
	struct node * rChild;
};

typedef struct node link;
using namespace std;
#define maxVal(a, b) ((a > b) ? a : b)

link * createNode(int);
link * createTree();
link * insertNode(link *, link *);
link * insertNode(int *, int, int);
void inOrder(link *);
void fillArray(int *, int);
int findHeight(link *);

link * createNode(int val) {
	link * newNode;

	newNode = (link *) malloc(sizeof(link));
	newNode -> val = val;
	newNode -> lChild = NULL;
	newNode -> rChild = NULL;

	return newNode;
}

void fillArray(int * arr, int n) {
	int i;

	for (i = 0; i < n; i++) {
		arr[i] = i + 1;
	}
}

link * createTree() {
	link * root;
	link * newNode;
	int val;
	int n;

	root = NULL;
	newNode = NULL;

	cout << "Enter no of elements to be inserted:\t";
	cin >> n;

	int arr[n];

	fillArray(&arr[0], n);
	root = insertNode(&arr[0], 0, n - 1);

	return root;
}

link * insertNode(int * arr, int lo, int hi) {
	if (lo > hi) {
		return NULL;
	} else {
		int mid;
		link * newNode;

		mid = (lo + hi) / 2;
		newNode = createNode(arr[mid]);

		newNode -> lChild = insertNode(arr, lo, mid - 1);
		newNode -> rChild = insertNode(arr, mid + 1, hi);

		return newNode;
	}
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

int main() {
	link * root;

	root = createTree();

	cout << "\nThe tree in InOrder is:-\n";
	inOrder(root);

	cout << "\n\nThe height of tree is:\t" << findHeight(root) << "\n" << endl;

	return 0;
}

int findHeight(link * root) {
	if (root == NULL) {
		return 0;
	} else {
		return maxVal(1 + findHeight(root -> lChild), 1 + findHeight(root -> rChild));
	}
}
