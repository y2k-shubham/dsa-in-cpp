// http://quiz.geeksforgeeks.org/threaded-binary-tree/

/*
			     1
        2                 3
	4       5         6       7
   8 9   10  11        13   14
	    20  22          27
				         55


1 1
2 2		3 3
4 4		5 5		6 6		7 7
8 8		9 9		10 10	11 11	13 13	14 14
20 20	22 22	27 27
55 55
-1 -1
*/

#include <cstdio>
#include <iostream>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
	bool rThread;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
void showListRev(node *, const char *);
node * insert(node *, node *, node *);
//node * insertAndLink(node *, node **, node *, node *);
void makeLinks(node *, node **);
void inOrderThread_1(node *);
void inOrderThread_2(node *);
node * leftMost(node *);

int main() {
	node * root;
	int val, pos;

	printf("\nEnter (val, pos) to insert into tree:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (val != -1 && pos != -1) {
//		node * tmp = createNode(INT_MIN);
//		node ** prev = &tmp;
		node * path = getPath(pos);

//		root = insertAndLink(root, prev, path -> right, createNode(val));
		root = insert(root, path -> right, createNode(val));

		scanf("%d%d", &val, &pos);
	}

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	node * tmp = createNode(INT_MIN);
	node ** prev = &tmp;
	makeLinks(root, prev);

	printf("\nThe threaded inOrder traversal 1 is:-\n");
	inOrderThread_1(root);
	printf("\n");

	printf("\nThe threaded inOrder traversal 2 is:-\n");
	inOrderThread_2(root);
	printf("\n");


	return 0;
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> left = NULL;
	newNode -> right = NULL;
	newNode -> rThread = false;

	return newNode;
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> left);

		if (root -> rThread) {
			printf("%d(%d) ", root -> val, root -> right -> val);
		} else {
			printf("%d ", root -> val);
			inOrder(root -> right);
		}
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

void showListRev(node * head, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (node * list = head; list != NULL; list = list -> left) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n");
}

node * insert(node * root, node * path, node * newNode) {
	if (path == NULL) {
		return newNode;
	} else {
		if (path -> val % 2 == 1) {
			root -> right = insert(root -> right, path -> right, newNode);
		} else {
			root -> left = insert(root -> left, path -> right, newNode);
		}

		return root;
	}
}

void makeLinks(node * root, node ** prev) {
	if (root != NULL) {
		makeLinks(root -> left, prev);

		if ((* prev) -> val != INT_MIN) {
			(* prev) -> right = root;
			(* prev) -> rThread = true;
		}
		(* prev) = root;

		makeLinks(root -> right, prev);
	}
}

void inOrderThread_1(node * root) {
	bool goLeft = true;
	while (root != NULL) {
		if (root -> left != NULL && goLeft) {
			root = root -> left;
		} else {
			if (root -> rThread) {
				goLeft = false;
			} else {
				goLeft = true;
			}

			printf("%d ", root -> val);
			root = root -> right;
		}
	}
}

void inOrderThread_2(node * root) {
	root = leftMost(root);
	while (root != NULL) {
		printf("%d ", root -> val);

		if (root -> rThread == true) {
			root = root -> right;
		} else {
			root = leftMost(root -> right);
		}
	}
}

node * leftMost(node * root) {
	if (root == NULL) {
		return NULL;
	} else if (root -> left == NULL) {
		return root;
	} else {
		return leftMost(root -> left);
	}
}

//node * insertAndLink(node * root, node ** prev, node * path, node * newNode) {
//	if (path == NULL) {
//		if ((* prev) -> val != INT_MIN) {
//			newNode -> right = * prev;
//			newNode -> rThread = true;
//			printf("inserting %d, %d -> rThread made to point to %d\n", newNode -> val, newNode -> val, (* prev) -> val);
//		}
//		return newNode;
//	} else {
//		if (path -> val % 2 == 1) {
//			root -> right = insertAndLink(root -> right, prev, path -> right, newNode);
//		} else {
//			printf("inserting %d, *prev updated to %d\n", newNode -> val, root -> val);
//			(* prev) = root;
//			root -> left = insertAndLink(root -> left, prev, path -> right, newNode);
//		}
//
//		return root;
//	}
//}

