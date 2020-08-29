// http://www.geeksforgeeks.org/connect-nodes-at-same-level-with-o1-extra-space/
// Difficult problem, extension of:
// http://www.geeksforgeeks.org/connect-nodes-at-same-level/
// LeetCode 116: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/

/*
Possible Solutions
1.  Soln is based on property of tree being perfect binary tree
(all leaf nodes are at same level)
.
We exploit the recursive property: performing pre-order traversal,
 - When standing at a node, we set next ptrs of it's children
 - by recursive property, the current nodes next ptrs were already set when we were at it's parent
.
Here's the logic
 - left child's next ptr will be right child itself
 - right child's next ptr will be the left child of current node's own next ptr
   - here, of course, in case current node has to next ptr (is the rightmost node)
	   then it's child (also being rightmost node) will have it's next ptr empty
::
2. (Implemented here) Here we again leverage the recursive property.
But this time we ensure that the soln works for imperfect binary trees as well
 - before setting nextRight for left or right children, we first traverse to nextRight of
   current node itself and set it's nextRight
 - then nextRight of current node's right can be set by finding the first node to it's right in it's own
   level (simple iteration)
 - and similary the nextRight of current node's left can be set by either equating it to it's right
   sibling (if it exists), or else similarly finding the first node to it's right in the same level as we
	 would've done above
*/

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


1 1
2 2		3 3
4 4		5 5		6 6		7 7
8 8		9 9		10 14	11 15
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
	struct node * nextRight;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
void showListRev(node *, const char *);
node * insert(node *, node *, node *);
node * getNextRight(node *);
void connect(node *);

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

	printf("\nThe inOrder traversal before connection is:-\n");
	inOrder(root);
	printf("\n");

	connect(root);

	printf("\nThe inOrder traversal after connection is:-\n(number shown in bracket is nextRight node)\n");
	inOrder(root);
	printf("\n");

	return 0;
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> left = NULL;
	newNode -> right = NULL;
	newNode -> nextRight = NULL;

	return newNode;
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> left);

		if (root -> nextRight == NULL) {
			printf("%d ", root -> val);
		} else {
			printf("%d(%d) ", root -> val, root -> nextRight -> val);
		}


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

node * getNextRight(node * root) {
	if (root == NULL) {
		return NULL;
	} else {
		root = root -> nextRight;

		while (root != NULL) {
			if (root -> left != NULL) {
				return root -> left;
			} else if (root -> right != NULL) {
				return root -> right;
			} else {
				root = root -> nextRight;
			}
		}

		return NULL;
	}
}

void connect(node * root) {
	if (root != NULL) {
		connect(root -> nextRight);

		if (root -> left != NULL) {
			if (root -> right != NULL) {
				// ...and also not here
				root -> left -> nextRight = root -> right;
			} else {
				// if it comes here... (up and down)
				root -> left -> nextRight = getNextRight(root);
			}
		}

		if (root -> right != NULL) {
			// ...then it wouldn't come here
			root -> right -> nextRight = getNextRight(root);
		}

		connect(root -> left);
		connect(root -> right);
	}
}

