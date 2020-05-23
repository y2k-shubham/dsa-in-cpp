/*
 * To compile it, C++11 support is needed.
 * Enable support in CodeBlocks from Settings > Compiler > check 'Have g++ follow the C++11 ISO C++ language standard'
 */

/*
0 1
0 2		15 3
-10 4	10 5	0 6		10 7
-5 9	-10 12	10 13	20 15
-5 25	20 27	15 30	25 31
15 54	25 55
-1 -1

0 1
0 2		15 3
-10 4	10 5	10 6		10 7
-5 9	-10 12	10 13	20 15
-5 25	20 27	15 30	25 31
15 54	25 55
-1 -1

0 1
0 2		15 3
-10 4	10 5	10 6		10 7
-5 9	-10 12	10 13	20 15
-5 25	20 27	15 30	25 31
15 54	19 55
-1 -1

0 1
0 2		15 3
-10 4	10 5	10 6	16 7
-5 9	-10 12	10 13	20 15
-5 25	20 27	15 30	25 31
15 54	19 55
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <tuple>
#include <cmath>
#include <utility>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

void inOrder(node *);
node * inputTree();
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
node * insert(node *, node *, node *);
bool isLeaf(node *);
tuple <int, int, pair <int, node *> > maxBST(node *);

int main() {
	node * root;

	root = inputTree();

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	pair <int, node *> resPair = get <2> (maxBST(root));
	if (resPair.first > 1) {
		printf("\nLargest BST rooted at %d contains %d nodes\n", (resPair.second) -> val, resPair.first);
	} else {
		printf("\nGiven binary tree doesn't contain any BST\n");
	}

	return 0;
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> left = NULL;
	newNode -> right = NULL;

	return newNode;
}

node * inputTree() {
	node * root;
	int val, pos;
	int ele;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (pos != -1) {
		node * path = getPath(pos);
		root = insert(root, path -> right, createNode(val));

		scanf("%d%d", &val, &pos);
	}

	return root;
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

node * insert(node * root, node * path, node * newNode) {
	if (path == NULL) {
//		printf("at node %d\tpath = NULL\n", root -> val);
		return newNode;
	} else {
//		printf("at node %d\tpath = %d\n", root -> val, path -> val);
		if (path -> val % 2 == 1) {
			root -> right = insert(root -> right, path -> right, newNode);
		} else {
			root -> left = insert(root -> left, path -> right, newNode);
		}

		return root;
	}
}

tuple <int, int, pair <int, node *> > maxBST(node * root) {
	if (root == NULL) {
		node * tmpNode;
		return make_tuple(INT_MAX, INT_MIN, make_pair(0, tmpNode));
	} else if (isLeaf(root)) {
		return make_tuple(root -> val, root -> val, make_pair(1, root));
	} else {
		pair <int, node *> lPair, rPair;
		int lMin, lMax, lCount;
		int rMin, rMax, rCount;

		tie(lMin, lMax, lPair) = maxBST(root -> left);
		lCount = lPair.first;
		tie(rMin, rMax, rPair) = maxBST(root -> right);
		rCount = rPair.first;

//		printf("at node %d, subtree is ", root -> val);
		if (lMax < root -> val && root -> val < rMin) {
			tuple <int, int, pair <int, node *> > newTup = make_tuple(min(lMin, root -> val), max(root -> val, rMax), make_pair(lCount + rCount + 1, root));
//			printf("BST\t, returned (%d, %d, [%d, %d])\n", (get <0> (newTup)), (get <1> (newTup)), (get <2> (newTup)).first, (get <2> (newTup)).second -> val);
			return (newTup);
		} else {
			tuple <int, int, pair <int, node *> > newTup = make_tuple(INT_MIN, INT_MAX, make_pair(max(lCount, rCount), ((lCount > rCount) ? lPair.second : rPair.second)));
//			printf("not BST\t, returned (%d, %d, [%d, %d])\n", get <0> (newTup), get <1> (newTup), (get <2> (newTup)).first, (get <2> (newTup)).second -> val);
			return (newTup);
		}
	}
}

bool isLeaf(node * root) {
	if (root -> left == NULL && root -> right == NULL) {
		return true;
	} else {
		return false;
	}
}

