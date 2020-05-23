// WRONG PROGRAM
// http://www.geeksforgeeks.org/boundary-traversal-of-binary-tree/

/*
Explanation of used methodology
Observation:	Boundary comprises set of first and last elements of each level
Technique:		Based on above observation, we can carry-out a Pre-Order traversal of the tree
				Every time we encounter a new level (where we haven't been previously), we display
				the node (because it is guaranteed to be a node belonging to boundary).

				We also
				store the status of last visited node for each level in a vector. Each vector
				element holds two values, the last node seen on that level during pre-order
				traversal and whether that node has already been displayed or not.

				So if we end up	at a level where we've already been previously, we know that
				we've already displayed the first node that was encountered on this level;
				therefore we won't display this node, only store it in the particular level's index
				in the array and mark the visited status as false.

				Finally after the preorder traversal has been completed, we would have displayed all
				elements of left boundary (some of them may also be the elements of right boundary) and
				would have stored all elements of right boundary
*/

/*
>> check the input format, it's given in comments on top of the program.
>> it says keep entering values to be inserted into tree along with their position in the tree, till -1 is entered for position.
>> here position is 1-indexed, so root has position 1, root -> left has position 2, root -> right has position 3, root -> left -> left has position 4 and so on.
>> the tree need not be complete binary tree but all successive insertion positions should be legal
*/

/*
			1
	   2          3
	4    5   6      7
   8 9 10  11 13  14
	  20  22   27
				 55


1 1
2 2		3 3
4 4		5 5		6 6		7 7
8 8		9 9		10 10	11 11	13 13	14 14
20 20	22 22	27 27
55 55
-1 -1

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
#include <vector>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

struct lvl {
	bool printed;
	node * lstNode;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
node * insert(node *, node *, node *);
void inOrderIter(node *);
void buildLvlVec(node *, vector <lvl> &, int);
void showLvlVec(vector <lvl>);
void showLvlVecProper(vector <lvl>);

int main() {
	node * root;
	node * head, * tail;
	vector <lvl> lvlVec;
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

	cout << "\nThe boundary traversal is:-\n";
	buildLvlVec(root, lvlVec, 0);
	showLvlVecProper(lvlVec);
//	showLvlVec(lvlVec);

	return 0;
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> left = NULL;
	newNode -> right = NULL;

	return newNode;
}

lvl createLvlNode(node * lstNode) {
	lvl newNode;
	newNode.printed = true;
	newNode.lstNode = lstNode;
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

void buildLvlVec(node * root, vector <lvl> &lvlVec, int lvl) {
	if (root != NULL) {
		if (lvlVec.size() <= lvl) {
			// if you've come to this level for first time, print the node and extend the vector
			lvlVec.push_back(createLvlNode(root));
			printf("arr[%d] = %d\tprinted Y\n", lvl, root -> val);
//			cout << root -> val << " ";
		} else {
			// otherwise, just add node to vector
			printf("arr[%d] = %d\t", lvl, root -> val);
			lvlVec[lvl].lstNode = root;
			lvlVec[lvl].printed = false;

			if (root -> left == NULL && root -> right == NULL) {
				// if it's a leaf node (that hasn't been printed), print it
//				cout << root -> val << " ";
				lvlVec[lvl].printed = true;
				printf("printed Y\n");
				return;
			} else {
				printf("printed N\n");
			}
		}

		// continue pre-order traversal
		buildLvlVec(root -> left, lvlVec, lvl + 1);
		buildLvlVec(root -> right, lvlVec, lvl + 1);
	}
}

void showLvlVec(vector <lvl> lvlVec) {
	cout << "\nLvlVec is:-\n";
	for (int i = 0; i < lvlVec.size(); i++) {
		printf("Lvl %d\tLstNod %d\tPrinted ", i, (lvlVec[i].lstNode) -> val);
		if (lvlVec[i].printed == true) {
			cout << "Y\n";
		} else {
			cout << "N\n";
		}
	}
}

void showLvlVecProper(vector <lvl> lvlVec) {
	for (int i = lvlVec.size() - 1; i > 0; i--) {
		if (lvlVec[i].printed == false) {
			printf("%d ", (lvlVec[i].lstNode) -> val);
		}
	}
	cout << endl;
}
