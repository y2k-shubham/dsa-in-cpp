// paths need not start at root and end at leaf

/*
1 1
20 2	3 3
4 6		15 7
6 12	7 13	8 14	9 15
-1 -1
8
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <map>
#include <list>
#include <utility>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

struct pathNode {
	char move;
	struct pathNode * next;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
node * inputTree();
void showList(node *, const char *);
void showAllPaths(node *, node *, node *, int, map <node *, node *>&, map <int, list <pair <node *, char> > >&, int);
void showPath(map <node *, node *>, map <int, list <pair <node *, char> > >, node *, node *);
node * insert(node *, node *, node *);
pathNode * createNode(char);

int main() {
	int reqSum;
	node * root;
	map <node *, node *> par;
	map <int, list <pair <node *, char> > > pathSums;

	root = inputTree();

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	cout << "\nEnter required sum:\t";
	cin >> reqSum;

	cout << endl;
	showAllPaths(root, NULL, root, reqSum, par, pathSums, 0);

	return 0;
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> left = NULL;
	newNode -> right = NULL;

	return newNode;
}

pathNode * createNode(char move) {
	pathNode * newNode = new pathNode;
	newNode -> move = move;
	newNode -> next = NULL;
	return newNode;
}

node * inputTree() {
	node * root;
	pathNode * head, * tail;
	int ele, k, pathLength;
	int val, pos;

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

void showAllPaths(node * crrNode, node * crrPar, node * root, int reqSum, map <node *, node *>& par, map <int, list <pair <node *, char> > >& pathSums, int crrSumOld) {
	if (crrNode != NULL) {
		int crrSumNew = crrSumOld + crrNode -> val;
		par[crrNode] = crrPar;

		printf("at node %d\toldSum = %d\tnewSum = %d\n", crrNode -> val, crrSumOld, crrSumNew);

		// print possible path starting at root at this stage
		if (crrSumNew == reqSum) {
			printf("Found path from root %d to node %d\n", root -> val, crrNode -> val);
			showPath(par, pathSums, root, crrNode);
		}

		// print all possible other paths at this stage
		int diff = abs(reqSum - crrSumNew);
		if (pathSums.find(diff) != pathSums.end()) {
			list <pair <node *, char> > startNodes = pathSums[diff];

			for (list <pair <node *, char> >::iterator i = startNodes.begin(); i != startNodes.end(); i++) {
				pair <node *, char> p = *i;
				if (crrSumNew > reqSum && p.second != 'u') {
					if (p.second == 'l') {
						printf("lFound path from node %d to node %d\n", p.first -> left -> val, crrNode -> val);
						showPath(par, pathSums, crrNode, p.first -> left);
					} else {
						printf("rFound path from node %d to node %d\n", p.first -> right -> val, crrNode -> val);
						showPath(par, pathSums, crrNode, p.first -> right);
					}
				} else if (crrSumNew < reqSum && p.second == 'u') {
					printf("eFound path from node %d to node %d\n", p.first -> val, crrNode -> val);
					showPath(par, pathSums, crrNode, p.first);
				}
			}
		}

		// insert current node in pathSums
		pair <node *, char> p = make_pair(crrNode, '\0');
		if (pathSums.find(crrSumNew) == pathSums.end()) {
			list <pair <node *, char> > l;
			l.push_back(p);
			pathSums[crrSumNew] = l;
		} else {
			pathSums[crrSumNew].push_back(p);
		}

		list <pair <node *, char> >::iterator i;

		// traverse left
		for (i = pathSums[crrSumNew].begin(); i != pathSums[crrSumNew].end(); i++) {
			if ((*i).first == crrNode) {
				break;
			}
		}
		(*i).second = 'l';
		showAllPaths(crrNode -> left, crrNode, root, reqSum, par, pathSums, crrSumNew);

		// traverse right
		for (i = pathSums[crrSumNew].begin(); i != pathSums[crrSumNew].end(); i++) {
			if ((*i).first == crrNode) {
				break;
			}
		}
		(*i).second = 'r';
		showAllPaths(crrNode -> right, crrNode, root, reqSum, par, pathSums, crrSumNew);

		// backtrack
		for (i = pathSums[crrSumNew].begin(); i != pathSums[crrSumNew].end(); i++) {
			if ((*i).first == crrNode) {
				break;
			}
		}
		(*i).second = 'u';
	}
}

void showPath(map <node *, node *> par, map <int, list <pair <node *, char> > > pathSums, node * tarNode, node * crrNode) {

}

