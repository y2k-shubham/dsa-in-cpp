// http://www.geeksforgeeks.org/diameter-of-a-binary-tree/
// diameter is defined as length of longest path between any two leaves of the tree
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct node {
	int val;
	struct node * lC;
	struct node * rC;
};

struct node * newNode(int);
int findHeight(struct node *);
int findDim(struct node *, int &);

int main() {
	struct node *root = newNode(1);
	root->lC        = newNode(2);
	root->rC       = newNode(3);
	root->lC->lC  = newNode(4);
	root->lC->rC = newNode(5);

	root->lC->lC->rC = newNode(6);
	root->lC->rC->rC = newNode(7);
	root->rC->lC = newNode(8);
	root->rC->lC->lC = newNode(9);
	root->rC->lC->lC->lC = newNode(10);

	printf("height(1) = %d\n", findHeight(root));
	printf("height(2) = %d\n", findHeight(root -> lC));
	printf("height(3) = %d\n", findHeight(root -> rC));
	printf("height(4) = %d\n", findHeight(root -> lC -> lC));
	printf("height(5) = %d\n", findHeight(root -> lC -> rC));
	printf("height(NULL) = %d\n", findHeight(root -> rC -> rC));

	int dim = 0;
	printf("\nheight(1) = %d\n", findDim(root, dim));
	printf("dim(1) = %d\n", dim);

	dim = 0;
	printf("\nheight(2) = %d\n", findDim(root -> lC, dim));
	printf("dim(2) = %d\n", dim);

	dim = 0;
	printf("\nheight(3) = %d\n", findDim(root -> rC, dim));
	printf("dim(3) = %d\n", dim);

	dim = 0;
	printf("\nheight(4) = %d\n", findDim(root -> lC -> lC, dim));
	printf("dim(4) = %d\n", dim);

	dim = 0;
	printf("\nheight(5) = %d\n", findDim(root -> lC -> rC, dim));
	printf("dim(5) = %d\n", dim);

	dim = 0;
	printf("\nheight(6) = %d\n", findDim(root -> lC -> lC -> rC, dim));
	printf("dim(6) = %d\n", dim);

	dim = 0;
	printf("\nheight(7) = %d\n", findDim(root -> lC -> rC -> rC, dim));
	printf("dim(7) = %d\n", dim);

	dim = 0;
	printf("\nheight(8) = %d\n", findDim(root -> rC -> lC, dim));
	printf("dim(8) = %d\n", dim);

	dim = 0;
	printf("\nheight(9) = %d\n", findDim(root -> rC -> lC -> lC, dim));
	printf("dim(9) = %d\n", dim);

	dim = 0;
	printf("\nheight(10) = %d\n", findDim(root -> rC -> lC -> lC -> lC, dim));
	printf("dim(10) = %d\n", dim);

	return 0;
}

struct node * newNode(int val) {
	struct node * newNode = (struct node *) malloc(sizeof(struct node));

	newNode -> val = val;
	newNode -> lC = NULL;
	newNode -> rC = NULL;

	return newNode;
};

int findHeight(struct node * root) {
	if (root == NULL) {
		return 0;
	} else {
		return 1 + max(findHeight(root -> lC), findHeight(root -> rC));
	}
}

int findDim(struct node * root, int &dim) {
	if (root == NULL) {
		return 0;
	} else {
		int lH = findDim(root -> lC, dim);
		int rH = findDim(root -> rC, dim);

		dim = max(dim, (1 + lH + rH));

		return 1 + max(lH, rH);
	}
}
