// TusharRoy
// http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/

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

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

void inOrder(node *);
void preOrder(node *);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
void showListRev(node *, const char *);
node * insert(node *, node *, node *);
node * findInOrderPred(node *);
void morrisInOrder(node *);
void morrisPreOrder(node *);

int main() {
	node * root;
	int val, pos;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (val != -1 && pos != -1) {
		node * path = getPath(pos);
		root = insert(root, path -> right, createNode(val));

		scanf("%d%d", &val, &pos);
	}

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	printf("\nThe Morris inOrder traversal is:-\n");
	morrisInOrder(root);
	printf("\n");

	printf("\nThe preOrder traversal is:-\n");
	preOrder(root);
	printf("\n");

	printf("\nThe Morris preOrder traversal is:-\n");
	morrisPreOrder(root);
	printf("\n");

	return 0;
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> left = NULL;
	newNode -> right = NULL;

	return newNode;
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> left);
		printf("%d ", root -> val);
		inOrder(root -> right);
	}
}

void preOrder(node * root) {
	if (root != NULL) {
		printf("%d ", root -> val);
		preOrder(root -> left);
		preOrder(root -> right);
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

void morrisInOrder(node * root) {
	while (root != NULL) {
		if (root -> left == NULL) {
			printf("%d ", root -> val);
			root = root -> right;
		} else {
			node * pred = findInOrderPred(root);
			if (pred != NULL) {
				pred -> right = root;
				root = root -> left;
			} else {
				printf("%d ", root -> val);
				root = root -> right;
			}
		}
	}
}

void morrisPreOrder(node * root) {
	while (root != NULL) {
		if (root -> left == NULL) {
			printf("%d ", root -> val);
			root = root -> right;
		} else {
			node * pred = findInOrderPred(root);
			if (pred != NULL) {
				printf("%d ", root -> val);
				pred -> right = root;
				root = root -> left;
			} else {
				root = root -> right;
			}
		}
	}
}

node * findInOrderPred(node * root) {
	node * tmp = root -> left;
	while (tmp -> right != NULL && tmp -> right != root) {
		tmp = tmp -> right;
	}

	if (tmp -> right == NULL) {
		return tmp;
	} else {
		tmp -> right = NULL;
		return NULL;
	}
}

