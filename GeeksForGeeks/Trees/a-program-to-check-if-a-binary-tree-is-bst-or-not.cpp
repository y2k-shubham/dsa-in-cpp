// http://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/

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
Not BST

50 1
25 2	75 3
20 4	37 5	100 7
30 10	87 14	150 15
29 20	34 21	81 28
28 40	78 56	84 57
-1 -1
BST

50 1
25 2	75 3
20 4	37 5	100 7
30 10	87 14	150 15
29 20	34 21	81 28
29 40	78 56	84 57
-1 -1
Not BST

50 1
25 2	75 3
20 4	37 5	100 7
30 10	87 14	150 15
29 20	34 21	81 28
30 40	78 56	84 57
-1 -1
Not BST

-1 -1
BST

1 1
-1 -1
BST

2 1
1 2		3 3
-1 -1
BST

1 1
2 2		3 3
-1 -1
Not BST

*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>

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
node * insert(node *, node *, node *);
bool checkBST_1(node *, int &, int &);
bool checkBST_2(node *, int, int);
bool checkBST_3(node *, int &);

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

	int p;
	if (checkBST_1(root, p, p)) {
		cout << "\nIt is BST\n";
	} else {
		cout << "\nIt is not BST\n";
	}

	if (checkBST_2(root, INT_MIN, INT_MAX)) {
		cout << "It is BST\n";
	} else {
		cout << "It is not BST\n";
	}

	p = INT_MIN;
	if (checkBST_3(root, p)) {
		cout << "It is BST\n";
	} else {
		cout << "It is not BST\n";
	}

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

bool checkBST_1(node * root, int &maxV, int &minV) {
	if (root == NULL) {
		// this would never happen (unless tree is empty)
		return true;
	} else {
		int lMax, lMin;
		int rMax, rMin;

		bool lRes, rRes;
		if (root -> lC != NULL) {
			lRes = checkBST_1(root -> lC, lMax, lMin);
		} else {
			lRes = true;
			lMax = INT_MIN;
		}

		if (lRes) {
			if (root -> lC != NULL) {
				rRes = checkBST_1(root -> rC, rMax, rMin);
			} else {
				rRes = true;
				rMin = INT_MAX;
			}

			if (rRes && lMax < root -> val && root -> val < rMin) {
//				printf("at node %d\tlMin = %d\tlMax = %d\trMin = %d\trMax = %d\treturned true\n", root -> val, lMin, lMax, rMin, rMax);
				maxV = (root -> rC == NULL) ? root -> val : rMax;
				minV = (root -> lC == NULL) ? root -> val : lMin;
				return true;
			} else {
//				printf("at node %d\tlMin = %d\tlMax = %d\trMin = %d\trMax = %d\treturned false\n", root -> val, lMin, lMax, rMin, rMax);
				return false;
			}
		} else {
//			printf("at node %d\treturned false as left subtree isn't BST\n", root -> val);
			return false;
		}
	}
}

bool checkBST_2(node * root, int minV, int maxV) {
	if (root == NULL) {
		return true;
	} else if (minV < root -> val && root -> val < maxV) {
		return (checkBST_2(root -> lC, minV, root -> val) &&checkBST_2(root -> rC, root -> val, maxV));
	} else {
		return false;
	}
}

bool checkBST_3(node * root, int &prev) {
	if (root == NULL) {
		return true;
	} else {
		bool res = checkBST_3(root -> lC, prev);

		if (res == true && root -> val > prev) {
			prev = root -> val;
			return checkBST_3(root -> rC, prev);
		} else {
			return false;
		}
	}
}

