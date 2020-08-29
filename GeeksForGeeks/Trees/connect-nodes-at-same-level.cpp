// http://www.geeksforgeeks.org/connect-nodes-at-same-level/
// LeetCode 116: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/

/*
Possible Solutions
1. (Brute force) Do inorder traversal one level at a time and use a *prev pointer for last visited
	node at the same level for making links. so at a time, only nodes of a particular level will
	be connected and this will require the method to be called O(h) times (once for each level)
	Time: O(nh)		Space: O(h)

2. Store all nodes of a particular level in map of level to list of nodes (map <int, list <node *> >
	and then traverse each list separately for establishing links
	Time: O(n)		Space: O(n)

3. Use level order traversal and connect each node's nextRight pointer to to node on front of que
	(to account for level changes, use the technique for printing level order traversal in multiple
	lines)
	Time: O(n)		Space: O(no of nodes in widest level of tree)

4. Use map for storing last visited node (*prev) for each level and then set up links while
	traversing (this has been used in the following program)
	Time: O(n)		Space: O(h)
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
#include <map>
#include <utility>

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
void connect(map <int, node *> &, node *, int);

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

	map <int, node *> lvlPrevMap;
	connect(lvlPrevMap, root, 0);

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

void connect(map <int, node *> &lvlPrevMap, node * root, int lvl) {
	if (root != NULL) {
		if (lvlPrevMap.find(lvl) != lvlPrevMap.end()) {
			node * prev = lvlPrevMap[lvl];
			prev -> nextRight = root;
		}
		lvlPrevMap[lvl] = root;

		connect(lvlPrevMap, root -> left, lvl + 1);
		connect(lvlPrevMap, root -> right, lvl + 1);
	}
}


