// TusharRoy: https://www.youtube.com/watch?v=13m9ZCB8gjw
#include <cstdio>
#include <vector>
#include <cmath>

/*
>> check the input format, it's given in comments on top of the program.
>> it says keep entering values to be inserted into tree along with their position in the tree, till -1 is entered for position.
>> here position is 1-indexed, so root has position 1, root -> left has position 2, root -> right has position 3, root -> left -> left has position 4 and so on.
>> the tree need not be complete binary tree but all successive insertion positions should be legal
>> in the input given below, all nodes (along-with their positions) written in a single line actually lie in same level, so each line of input denotes a level
*/

/*
5 1
36 2	14 3
47 4	21 5	-8 6	19 7
61 8	75 9	-7 13	27 15
54 16	19 17	50 18	100 19	-5 27
90 38	120 39	-6 54	-4 55
110 78	0 111
-1 222
-2 444
-1 -1

1 1
2 2
4 4
-1 -1
*/

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
node * findLCA(node *, int, int, int &);

int main() {
	node * root;
	int val, pos;
	int ele_1, ele_2;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (pos != -1) {
		node * path = getPath(pos);
		root = insert(root, path -> right, createNode(val));

		scanf("%d%d", &val, &pos);
	}

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	printf("\nEnter elements to find LCA:\t");
	scanf("%d%d", &ele_1, &ele_2);

	int matchCount = 0;
	node * lca = findLCA(root, ele_1, ele_2, matchCount);
	if (matchCount == 2) {
		printf("\nLowest common ancestor is %d\n", lca -> val);
	} else {
		printf("\nEither %d or %d (or both) are not present in binary tree\n", ele_1, ele_2);
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

// Wrong method, doesn't work in case when one node is root of another
//node * findLCA(node * root, int ele_1, int ele_2, int &matchCount) {
//	if (root == NULL) {
//		return NULL;
//	} else if (root -> val == ele_1 || root -> val == ele_2) {
//		matchCount++;
//		return root;
//	} else {
//		node * lResult = findLCA(root -> left, ele_1, ele_2, matchCount);
//		node * rResult = findLCA(root -> right, ele_1, ele_2, matchCount);
//
//		if (lResult != NULL && rResult != NULL) {
//			return root;
//		} else if (lResult != NULL) {
//			return lResult;
//		} else {
//			return rResult;
//		}
//	}
//}

// Correct method
node * findLCA(node * root, int ele_1, int ele_2, int &matchCount) {
	if (root == NULL) {
		return NULL;
	} else {
		node * lRes = findLCA(root -> left, ele_1, ele_2, matchCount);
		if (matchCount == 2) {
			return lRes;
		} else if (matchCount == 1 && (root -> val == ele_1 || root -> val == ele_2)) {
			matchCount++;
			return root;
		} else if (root -> val == ele_1 || root -> val == ele_2) {
			findLCA(root -> right, ele_1, ele_2, matchCount);
			matchCount++;	// don't put this statement before above recursive call
			return root;	// at this point, one node is root and whether we've found other in right subtree or not, either ways, we have to return root only
		} else {
			return findLCA(root -> right, ele_1, ele_2, matchCount);
		}
	}
}

