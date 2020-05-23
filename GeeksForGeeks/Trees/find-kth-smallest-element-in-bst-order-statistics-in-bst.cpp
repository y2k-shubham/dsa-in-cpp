// http://www.geeksforgeeks.org/find-k-th-smallest-element-in-bst-order-statistics-in-bst/

/*
50
25 75
10 37 100
30 87 150
34 81
78 84
-1
*/

#include <cstdio>
#include <iostream>
#include <climits>

struct node {
	int val;
	struct node * left;
	struct node * right;
};

node * insert(node *, node *);
void inOrder(node *);
node * createNode(int);
int findKthSmallEle(node *, int, int &);

int main() {
	node * root;
	int k;
	int ele;

	printf("\nEnter nodes to create BST:-\n(-1 to terminate)\n");
	scanf("%d", &ele);

	root = NULL;
	while (ele != -1) {
		root = insert(root, createNode(ele));
		scanf("%d", &ele);
	}

	printf("\nThe BST in inOrder is:-\n");
	inOrder(root);
	printf("\n");

	printf("\nEnter k for finding kth smallest element:\t");
	scanf("%d", &k);

	int smallOrder = 0;
	int kthSmall = findKthSmallEle(root, k, smallOrder);

	if (smallOrder == k) {
		printf("kth smallest element is %d\n", kthSmall);
	} else {
		printf("BST has less than k elements\n");
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

node * insert(node * root, node * newNode) {
	if (root == NULL) {
		return newNode;
	} else {
		if (newNode -> val < root -> val) {
			root -> left = insert(root -> left, newNode);
		} else if (newNode -> val > root -> val) {
			root -> right = insert(root -> right, newNode);
		} else {
			printf("\nDuplicate element not allowed:\t%d", newNode -> val);
		}
		return root;
	}
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> left);
		printf("%d ", root -> val);
		inOrder(root -> right);
	}
}

int findKthSmallEle(node * root, int k, int &ctr) {
	if (root != NULL) {
		int ele = findKthSmallEle(root -> left, k, ctr);
		if (ctr == k) {
			return ele;
		} else {
			++ctr;
			if (ctr == k) {
				return root -> val;
			} else {
				return findKthSmallEle(root -> right, k, ctr);
			}
		}
	}
}
