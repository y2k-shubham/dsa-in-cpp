#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

node * newNode(int);

int main() {
	node * root;
	stack <node *> stk;

	root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->right->left = newNode(6);
	root->right->right = newNode(7);
	root->left->left->left = newNode(8);
	root->left->right->right = newNode(9);
	root->right->right->left = newNode(10);

	node * rootCopy = root;
	for (int target = 1; target <= 10; target++) {
		root = rootCopy;

		while (true) {
			while (root != NULL && root -> val != target) {
				stk.push(root);
				root = root -> left;
			}

			if (root != NULL && root -> val == target) {
				break;
			} else {
				if (stk.top() -> right == NULL) {
					root = stk.top();
					stk.pop();

					while (!stk.empty() && root == stk.top() -> right) {
						root = stk.top();
						stk.pop();
					}
				}
				root = (stk.empty()) ? NULL : stk.top() -> right;
			}
		}

		printf("\nAncestors of %d are:-\n", target);
		while (!stk.empty()) {
			printf("%d ", stk.top() -> val);
			stk.pop();
		}
	}

	return 0;
}

node * newNode(int val) {
	node * tmp = new node;
	tmp -> val = val;
	tmp -> left = NULL;
	tmp -> right = NULL;
	return tmp;
}
