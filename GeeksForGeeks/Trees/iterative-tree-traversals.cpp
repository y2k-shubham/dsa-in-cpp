// InOrder: http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
// PreOrder: http://www.geeksforgeeks.org/iterative-preorder-traversal/
// PostOrder1: http://www.geeksforgeeks.org/iterative-postorder-traversal/
// PostOrder2: http://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/

/*
>> check the input format, it's given in comments on top of the program.
>> it says keep entering values to be inserted into tree along with their position in the tree, till -1 is entered for position.
>> here position is 1-indexed, so root has position 1, root -> left has position 2, root -> right has position 3, root -> left -> left has position 4 and so on.
>> the tree need not be complete binary tree but all successive insertion positions should be legal
*/

/*
			     1
        2                3
	4      5         6       7
   8 9   10 11        13      14
	    20   22         27
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
#include <stack>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
void showListRev(node *, const char *);
node * insert(node *, node *, node *);
void inOrderIter(node *);
void preOrderIter1(node *);
void preOrderIter2(node *);
void postOrderIter1(node *);
void postOrderIter2(node *);
void postOrderIter3(node *);
void revStack(stack <node *> &);
void insertAtBottom(stack <node *> &, node *);
void output(stack <node *>, const char *);

int main() {
	node * root;
	node * head, * tail;
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

	printf("\n\nIterative inOrder traversal:-\n");
	inOrderIter(root);

	printf("\nIterative preOrder traversal 1:-\n");
	preOrderIter1(root);

	printf("\nIterative preOrder traversal 2:-\n");
	preOrderIter2(root);

	postOrderIter1(root);
	postOrderIter2(root);

	printf("\nIterative postOrder traversal 3:-\n");
	postOrderIter3(root);

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

void inOrderIter(node * root) {
	node * crrNode;
	stack <node *> stk;

	crrNode = root;
	while (true) {
		if (crrNode != NULL) {
			stk.push(crrNode);
			crrNode = crrNode -> left;
		} else if (!stk.empty()) {
			crrNode = stk.top();
			stk.pop();
			printf("%d ", crrNode -> val);

			crrNode = crrNode -> right;
		} else {
			break;
		}
	}
	printf("\n");
}

void preOrderIter1(node * root) {
	stack <node *> stk;

	while (true) {
		if (root != NULL) {
			printf("%d ", root -> val);
			stk.push(root);
			root = root -> left;
		} else if (!stk.empty()) {
			root = stk.top();
			stk.pop();
			root = root -> right;
		} else {
			break;
		}
	}
	printf("\n");
}

void preOrderIter2(node * root) {
	stack <node *> stk;
	stk.push(root);

	while (!stk.empty()) {
		root = stk.top();
		stk.pop();

		cout << root -> val << " ";

		if (root -> right != NULL) {
			stk.push(root -> right);
		}

		if (root -> left != NULL) {
			stk.push(root -> left);
		}
	}
	cout << endl;
}

void postOrderIter1(node * root) {
	stack <node *> stkRec;
	stack <node *> stkOut;

	while (true) {
		if (root != NULL) {
			stkOut.push(root);
			stkRec.push(root);
			root = root -> right;
		} else if (stkRec.empty()) {
			break;
		} else {
			root = stkRec.top();
			stkRec.pop();

			root = root -> left;
		}
	}

	revStack(stkOut);

	output(stkOut, "iterative post-order traversal 1");
	cout << endl;
}

void postOrderIter2(node * root) {
	stack <node *> stkRec;
	stack <node *> stkOut;

	stkRec.push(root);
	while (!stkRec.empty()) {
		root = stkRec.top();
		stkOut.push(root);
		stkRec.pop();

		if (root -> left != NULL) {
			stkRec.push(root -> left);
		}

		if (root -> right != NULL) {
			stkRec.push(root -> right);
		}
	}

	revStack(stkOut);

	output(stkOut, "iterative post-order traversal 2");
	cout << endl;
}

void postOrderIter3(node * root) {
	stack <node *> stk;

	while (true) {
		if (root != NULL) {
			if (root -> right != NULL) {
				stk.push(root -> right);
			}
			stk.push(root);

			root = root -> left;
		} else if (stk.empty()) {
			break;
		} else {
			root = stk.top();
			stk.pop();

			if (root -> right != NULL && !stk.empty() && stk.top() == root -> right) {
				stk.pop();
				stk.push(root);
				root = root -> right;
			} else {
				printf("%d ", root -> val);
				root = NULL;
			}
		}
	}
	cout << endl;
}

void revStack(stack <node *> &stk) {
	if (!stk.empty()) {
		node * ele = stk.top();
		stk.pop();

		revStack(stk);
		insertAtBottom(stk, ele);
	}
}

void insertAtBottom(stack <node *> &stk, node * ele) {
	if (stk.empty()) {
		stk.push(ele);
	} else {
		node * tmp = stk.top();
		stk.pop();

		insertAtBottom(stk, ele);
		stk.push(tmp);
	}
}

void output(stack <node *> stk, const char * msg) {
	if (stk.empty()) {
		printf("\nThe %s is:-\n", msg);
	} else {
		node * ele = stk.top();
		stk.pop();

		output(stk, msg);

		cout << (ele -> val) << " ";
	}
}

