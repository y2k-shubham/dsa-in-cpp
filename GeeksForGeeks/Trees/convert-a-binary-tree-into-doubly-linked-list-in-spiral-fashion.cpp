// http://www.geeksforgeeks.org/convert-a-binary-tree-into-doubly-linked-list-in-spiral-fashion/

/*
			1
	   2          3
	4     5   6      7
   8 9  10 11  13  14
       20 22    27
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
#include <cstdlib>
#include <stack>

using namespace std;

struct node {
	int val;
	struct node * lC;
	struct node * rC;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
void showListRev(node *, const char *);
node * insert(node *, node *, node *);
node * makeSpiralLL(node *);
node * pop(stack <node *> &);

int main() {
	node * root;
	int val, pos;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (val != -1 && pos != -1) {
		node * path = getPath(pos);
//		showList(path);
		root = insert(root, path -> rC, createNode(val));

//		printf("\n");
		scanf("%d%d", &val, &pos);
	}

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	node * tail = makeSpiralLL(root);
	showList(root, "spiral linked list (normal)");
	showListRev(tail, "spiral linked list (reverse)");

	return 0;
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> lC);
		printf("%d ", root -> val);
		inOrder(root -> rC);
	}
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> lC = NULL;
	newNode -> rC = NULL;

	return newNode;
}

node * getPath(int val) {
	node * head;

	head = createNode(val);
	val /= 2;

	while (val >= 1) {
		node * newNode = createNode(val);
		newNode -> rC = head;
		head = newNode;

		val /= 2;
	}

	return head;
}

void showList(node * head, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (node * list = head; list != NULL; list = list -> rC) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n");
}

void showListRev(node * head, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (node * list = head; list != NULL; list = list -> lC) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n");
}

node * insert(node * root, node * path, node * newNode) {
	if (path == NULL) {
		return newNode;
	} else {
		if (path -> val % 2 == 1) {
			root -> rC = insert(root -> rC, path -> rC, newNode);
		} else {
			root -> lC = insert(root -> lC, path -> rC, newNode);
		}

		return root;
	}
}

node * makeSpiralLL(node * root) {
	stack <node *> s1;
	stack <node *> s2;
	node * last;

	s1.push(root);
	last = NULL;
	while (!s1.empty() || !s2.empty()) {
		if (last != NULL) {
			last -> rC = s1.top();
		}

		while (!s1.empty()) {
			node * tmp = pop(s1);

			if (tmp -> rC != NULL) {
				s2.push(tmp -> rC);
			}
			if (tmp -> lC != NULL) {
				s2.push(tmp -> lC);
			}

			tmp -> lC = last;
			if (!s1.empty()) {
				tmp -> rC = s1.top();
			}

			last = tmp;
		}

		if (!s2.empty()) {
			last -> rC = s2.top();
		} else {
			last -> rC = NULL;
		}

		while (!s2.empty()) {
			node * tmp = pop(s2);

			if (tmp -> lC != NULL) {
				s1.push(tmp -> lC);
			}
			if (tmp -> rC != NULL) {
				s1.push(tmp -> rC);
			}

			tmp -> lC = last;
			if (!s2.empty()) {
				tmp -> rC = s2.top();
			}

			last = tmp;
		}

		if (s1.empty()) {
			last -> rC = NULL;
		}
	}

	return last;
}

node * pop(stack <node *> &stk) {
	node * tmp = stk.top();
	stk.pop();
	return tmp;
}

