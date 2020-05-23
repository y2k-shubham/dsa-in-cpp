// http://www.geeksforgeeks.org/maximum-sum-nodes-binary-tree-no-two-adjacent/
// http://code.geeksforgeeks.org/1Rt0d3

/*
>> check the input format, it's given in comments on top of the program.
>> it says keep entering values to be inserted into tree along with their position in the tree, till -1 is entered for position.
>> here position is 1-indexed, so root has position 1, root -> left has position 2, root -> right has position 3, root -> left -> left has position 4 and so on.
>> the tree need not be complete binary tree but all successive insertion positions should be legal
*/

/*
			     1
        2                 3
	4       5         6       7
   8 9   10  11        13   14
	    20  22          27
				         55


Copy and paste one of the following inputs to run the program:

Input 1
1 1
2 2	    3 3
4 4     5 5     6 6     7 7
8 8     9 9     10 10   11 11   13 13   14 14
20 20   22 22   27 27
55 55
-1 -1
Output 1
149

Input 2
1 1
2 2     3 3
1 4     4 6     5 7
-1 -1
Output 2
11
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>
#include <cstdlib>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

struct nodeSum {
	int inc;
	int exc;

	struct nodeSum * left;
	struct nodeSum * right;
};

void inOrder(node *);
void inOrderInc(nodeSum *);
void inOrderExc(nodeSum *);
node * createNode(int);
nodeSum * createSumNode();
node * getPath(int);
void showList(node *, const char *);
node * insert(node *, node *, node *);
nodeSum * createSumTree(node *);

int main() {
	node * root;
	int val, pos;

	printf("\nEnter (val, pos) to insert into tree:-\n(pos starts from 1)\n");
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

	nodeSum * sumRoot = createSumTree(root);

	printf("\nExc inOrder traversal of sumTree is:-\n");
	inOrderExc(sumRoot);
	cout << endl;

	printf("\nInc inOrder traversal of sumTree is:-\n");
	inOrderInc(sumRoot);
	cout << endl;

	printf("\nMaximum possible sum is %d\n", sumRoot -> inc);

	return 0;
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> left = NULL;
	newNode -> right = NULL;

	return newNode;
}

nodeSum * createSumNode() {
	nodeSum * newNode = (nodeSum *) malloc(sizeof(nodeSum));

	newNode -> left = newNode -> right = NULL;
	newNode -> inc = newNode -> exc = 0;

	return newNode;
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> left);
		printf("%d ", root -> val);
		inOrder(root -> right);
	}
}

void inOrderInc(nodeSum * root) {
	if (root != NULL) {
		inOrderInc(root -> left);
		printf("%d ", root -> inc);
		inOrderInc(root -> right);
	}
}

void inOrderExc(nodeSum * root) {
	if (root != NULL) {
		inOrderExc(root -> left);
		printf("%d ", root -> exc);
		inOrderExc(root -> right);
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

nodeSum * createSumTree(node * root) {
	if (root == NULL) {
		return NULL;
	} else {
		nodeSum * newNode = createSumNode();

		newNode -> left = createSumTree(root -> left);
		newNode -> right = createSumTree(root -> right);

		// maximum possible sum of left subtree if left child (root of left subtree) is included
		int lIncSum = (newNode -> left != NULL) ? (newNode -> left -> inc) : 0;
		// maximum possible sum of right subtree if right child (root of right subtree) is included
		int rIncSum = (newNode -> right != NULL) ? (newNode -> right -> inc) : 0;

		// maximum possible sum of left subtree if left child (root of left subtree) is excluded
		int lExcSum = (newNode -> left != NULL) ? (newNode -> left -> exc) : 0;
		// maximum possible sum of right subtree if right child (root of right subtree) is excluded
		int rExcSum = (newNode -> right != NULL) ? (newNode -> right -> exc) : 0;

		// if we exclude this node, maximum possible sum is what we'll obtain by including
		// sums of left and right subtrees (possibly) along with their roots (left child and right child)
		newNode -> exc = lIncSum + rIncSum;

		// if we are allowed to include this node, maximum possible sum would be max of above value and
		// the sum of current node with exc values of it's left and right childs
		newNode -> inc = max(newNode -> exc, (lExcSum + rExcSum + root -> val));

		// This means that while exc stores maximum possible sum of current subtree, necessarily
		// excluding root node, inc only stores the maximum possible sum of current subtree,
		// where we are allowed to include root node but it's not mandatory to include the root node

		return newNode;
	}
}

