// http://www.practice.geeksforgeeks.org/problem-page.php?pid=700174

/*
	  50
   25    75
10   40     76
   32  49     77
28   45      http://www.practice.geeksforgeeks.org/problem-page.php?pid=700174   78
   42 			  79
					80

lView: 50 25 10 32 28 42 80
*/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
#define MAX 100

struct node {
	int val;
	struct node * lC;
	struct node * rC;
};

node * createNode(int);
node * insert(node *, node *);
void inOrder(node *);
void leftView(bool [MAX], node *, int);

int main() {
	node * root;
	bool done[MAX];
	int ele;

	printf("Enter elements of BST\n(-1 to terminate)\n");
	scanf("%d", &ele);

	root = NULL;
	memset(done, false, sizeof(done));

	while (ele != -1) {
		root = insert(root, createNode(ele));
		scanf("%d", &ele);
	}

	printf("\nThe BST in inOrder is:-\n");
	inOrder(root);
	printf("\n");

	printf("\nThe BST's left view is:-\n");
	leftView(done, root, 0);

	return 0;
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> lC = NULL;
	newNode -> rC = NULL;

	return newNode;
}

node * insert(node * root, node * newNode) {
	if (root == NULL) {
		return newNode;
	} else if (newNode -> val < root -> val) {
		root -> lC = insert(root -> lC, newNode);
		return root;
	} else {
		root -> rC = insert(root -> rC, newNode);
		return root;
	}
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> lC);
		printf("%d ", root -> val);
		inOrder(root -> rC);
	}
}

void leftView(bool done[MAX], node * root, int level) {
	if (root != NULL) {
		if (!done[level]) {
			printf("%d\n", root -> val);
			done[level] = true;
		}

		leftView(done, root -> lC, level + 1);
		leftView(done, root -> rC, level + 1);
	}
}
