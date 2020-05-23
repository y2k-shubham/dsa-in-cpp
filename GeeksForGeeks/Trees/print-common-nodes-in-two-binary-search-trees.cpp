// http://www.geeksforgeeks.org/print-common-nodes-in-two-binary-search-trees/
// O(m + n) solution using simultaneous iterative inorder traversal of both BSTs

/*
5
1 10
0 4 7
9
-1

10
7 20
4 9
-1

*/

#include <cstdio>
#include <iostream>
#include <stack>

struct node {
	int val;
	struct node * lC;
	struct node * rC;
};

using namespace std;

node * createNode(int);
node * insertNode(node *, node *);
void inOrder(node *);
node * inputTree(const char *);
void showTree(node *, const char *);
void printCommonNodes(node *, node *);

int main() {
	node * root1, * root2;

	root1 = inputTree("first");
	root2 = inputTree("second");

	showTree(root1, "first");
	showTree(root2, "second");

	printCommonNodes(root1, root2);

	return 0;
}

node * inputTree(const char * msg) {
	int ele;
	node * root;

	printf("Enter nodes of %s BST:\t", msg);
	cin >> ele;
	root = NULL;

	while (ele != -1) {
		root = insertNode(root, createNode(ele));
		cin >> ele;
	}

	return root;
}

void showTree(node * root, const char * msg) {
	printf("\nInOrder traversal of %s tree is:-\n", msg);
	inOrder(root);
	cout << endl;
}

node * createNode(int val) {
	node * newNode = new node;
	newNode -> val = val;
	newNode -> lC = NULL;
	newNode -> rC = NULL;
	return newNode;
}

node * insertNode(node * root, node * newNode) {
	if (root == NULL) {
		return newNode;
	} else {
		if (newNode -> val < root -> val) {
			root -> lC = insertNode(root -> lC, newNode);
		} else if (newNode -> val > root -> val) {
			root -> rC = insertNode(root -> rC, newNode);
		} else {
			cout << "Can't insert duplicate element\n";
		}
		return root;
	}
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> lC);
		cout << root -> val << " ";
		inOrder(root -> rC);
	}
}

void printCommonNodes(node * root1, node * root2) {
	stack <node *> stk1;
	stack <node *> stk2;

	printf("\nCommon nodes of both trees are:-\n");
	while (true) {
		if (root1 != NULL) {
			stk1.push(root1);
			root1 = root1 -> lC;
		} else if (root2 != NULL) {
			stk2.push(root2);
			root2 = root2 -> lC;
		} else {
			if (stk1.empty() || stk2.empty()) {
				break;
			} else {
				root1 = stk1.top();
				root2 = stk2.top();

				if (root1 -> val < root2 -> val) {
					// means inorder successor of root1 could possibly match with root2
					stk1.pop();				// but we definitely won't need root1 anymore, so pop
					root1 = root1 -> rC;	// move rightwards in tree1 (towards inorder successor)
					root2 = NULL;			// make root2 NULL so that in next iteration, we surely enter the else clause
				} else if (root1 -> val > root2 -> val) {
					stk2.pop();
					root2 = root2 -> rC;
					root1 = NULL;
				} else {
					// we've found matching nodes in both trees
					printf("%d\t", root1 -> val);
					stk1.pop();
					stk2.pop();
					root1 = root2 = NULL;
				}
			}
		}
	}
	cout << endl;
}

