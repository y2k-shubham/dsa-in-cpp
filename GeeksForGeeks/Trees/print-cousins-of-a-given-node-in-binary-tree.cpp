// http://www.geeksforgeeks.org/print-cousins-of-a-given-node-in-binary-tree/
// This program only prints closest (immediate) cousins, actual question asks us to print all cousins
// (i.e. all nodes at the same level as target node, except node itself and it's siblings)

/*
>> check the input format, it's given in comments on top of the program.
>> it says keep entering values to be inserted into tree along with their position in the tree, till -1 is entered for position.
>> here position is 1-indexed, so root has position 1, root -> left has position 2, root -> right has position 3, root -> left -> left has position 4 and so on.
>> the tree need not be complete binary tree but all successive insertion positions should be legal
*/

/*
			    1
	   2                3
   4       5     	6        7
 8   9  10   11       13   14
	   20  22           27
				         55


1 1
2 2		3 3
4 4		5 5		6 6		7 7
8 8		9 9		10 10	11 11	13 13	14 14
20 20	22 22	27 27
55 55
-1 -1

			   20
	 8			    	22
4         12		   		25
	   10    14

20 1
8 2		22 3
4 4		12 5		25 7
10 10	14 11
-1 -1



20 1
8 2
4 4		12 5
10 10		14 11
-1 -1


						  50
		    20							 90
	  10							80		  100
  5         15				     60    85
 4 6     12   18
            17  19

50 1
20 2	90 3
10 4	80 6	100 7
5 8		15 9	60 12	85 13
4 16	6 17	12 18	18 19
17 38	19 39
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <cstdlib>

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
node * insert(node *, node *, node *);
int dispCousins(node *, int);
void printChildren(node *, int);

int main() {
	node * root;
	node * head, * tail;
	int val, pos;
	int target;

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

	cout << "\nEnter target node for displaying cousins:\t";
	cin >> target;

	if (dispCousins(root, target) == -1) {
		printf("Node %d not found in tree\n", target);
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

int dispCousins(node * root, int target) {
	if (root == NULL) {
		return -1;
	} else if (root -> val == target) {
		return 1;
	} else {
		int lDist = dispCousins(root -> left, target);
		if (lDist > 0) {
			if (lDist == 2) {
				printChildren(root -> right, target);
			}
			return lDist + 1;
		} else {
			int rDist = dispCousins(root -> right, target);
			if (rDist > 0) {
				if (rDist == 2) {
					printChildren(root -> left, target);
				}
				return rDist + 1;
			} else {
				return -1;
			}
		}
	}
}

void printChildren(node * root, int target) {
	if (root == NULL || (root -> left == NULL && root -> right == NULL)) {
		printf("%d has no cousins", target);
	} else {
		printf("Cousins of %d are:-\n", target);
		if (root -> left != NULL) {
			printf("%d\t", root -> left -> val);
		}
		if (root -> right != NULL) {
			printf("%d\t", root -> right -> val);
		}
	}
	cout << endl;
}
