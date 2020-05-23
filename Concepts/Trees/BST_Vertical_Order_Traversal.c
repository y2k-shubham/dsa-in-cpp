#include <stdio.h>
#include <stdlib.h>

struct node {
	int val;
	struct node * left;
	struct node * right;
};

typedef struct node link;
#define Min(a, b) ((a < b) ? a : b)
#define Max(a, b) ((a > b) ? a : b)

link * createNode(int);
link * insertNode(link *, link *);
link * deleteNode(link *, int);
link * findInOrderSuccessor(link *);
void swapNodes(link *, link *);
void findDistances(link *, int *, int *, int);
void verticalOrder(link *, int, int);

int main() {
	link * root;
	int choice;
	int val;
	int leftDist;
	int rightDist;

	choice = -1;
	root = NULL;

	while (choice != 4) {
		printf("\n===\nChoose an action:-\n");
		printf("1. Insert\n");
		printf("2. Delete\n");
		printf("3. Vertical Order\n");
		printf("4. Exit\n");

		printf("Enter your choice:\t");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("\nEnter the element to be inserted:\t");
				scanf("%d", &val);
				root = insertNode(root, createNode(val));
				break;

			case 2:
				printf("\nEnter the element to be deleted:\t");
				scanf("%d", &val);
				root = deleteNode(root, val);
				break;

			case 3:
				leftDist = rightDist = 0;
				findDistances(root, &leftDist, &rightDist, 0);
				printf("\nThe vertical order traversal is:-\n");
				for (val = leftDist; val <= rightDist; val++) {
                    printf("Line %d:\t", val);
                    verticalOrder(root, val, 0);
                    printf("\n");
				}
				break;

			case 4:
				continue;

			default:
				printf("\nInvalid Choice\n");
		}
	}

	return 0;
}

link * createNode(int val) {
	link * newNode;

	newNode = (link *) malloc(sizeof(link));
	newNode -> val = val;
	newNode -> left = NULL;
	newNode -> right = NULL;

	return newNode;
}

link * insertNode(link * root, link * newNode) {
	if (root == NULL) {
		return newNode;
	} else {
		if (newNode -> val < root -> val) {
			root -> left = insertNode(root -> left, newNode);
		} else if (newNode -> val > root -> val) {
			root -> right = insertNode(root -> right, newNode);
		} else {
			printf("Error! : Repeated Element:\t%d\n", newNode -> val);
		}

		return root;
	}
}

link * deleteNode(link * root, int val) {
	if (root == NULL) {
		printf("\nError : Element not found\n");
		return NULL;
	} else if (val < root -> val) {
		root -> left = deleteNode(root -> left, val);
	} else if (val > root -> val) {
		root -> right = deleteNode(root -> right, val);
	} else if (root -> left == NULL && root -> right == NULL) {
		free(root);
		return NULL;
	} else if (root -> left == NULL) {
		link * temp;
		temp = root -> right;
		free(root);
		return temp;
	} else if (root -> right == NULL) {
		link * temp;
		temp = root -> left;
		free(root);
		return temp;
	} else {
		link * inOrderSuccessor;
		inOrderSuccessor = findInOrderSuccessor(root -> right);
		swapNodes(root, inOrderSuccessor);
		root -> right = deleteNode(root -> right, inOrderSuccessor -> val);
	}
	return root;
}

link * findInOrderSuccessor(link * root) {
	if (root -> left == NULL) {
		return root;
	} else {
		return findInOrderSuccessor(root -> left);
	}
}

void swapNodes(link * node_1, link * node_2) {
	int temp;

	temp = node_1 -> val;
	node_1 -> val = node_2 -> val;
	node_2 -> val = temp;
}

void findDistances(link * root, int * min, int * max, int crrDist) {
	if (root != NULL) {
		* min = Min(* min, crrDist);
		* max = Max(* max, crrDist);
		findDistances(root -> left, min, max, (crrDist - 1));
		findDistances(root -> right, min, max, (crrDist + 1));
	}
}

void verticalOrder(link * root, int targetLine, int crrLine) {
	if (root != NULL) {
		if (crrLine == targetLine) {
			printf("%d\t", root -> val);
		}

		verticalOrder(root -> left, targetLine, (crrLine - 1));
		verticalOrder(root -> right, targetLine, (crrLine + 1));
	}
}
