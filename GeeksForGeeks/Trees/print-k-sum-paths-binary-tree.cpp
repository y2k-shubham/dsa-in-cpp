// http://www.geeksforgeeks.org/print-k-sum-paths-binary-tree/
// parent map not really needed here, can be done via a simple list of nodes on current path

#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <list>

/*
1 1
3 2		-1 3
2 4		1 5		4 6		5 7
1 10	1 12	2 13	6 15
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
node * insert(node *, node *, node *);
void findKSumPaths(int, int, node *, node *, map <node *, node *>&, map <int, set <node *> >&);
void showPath(map <node *, node *>, node *, node *);

int main() {
	node * root;
	int val, pos;
	int k;
	map <node *, node *> parMap;
	map <int, set <node *> > sumMap;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (pos != -1) {
		node * path = getPath(pos);
		root = insert(root, path -> right, createNode(val));

		scanf("%d%d", &val, &pos);
	}

	printf("\nInOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	printf("\nEnter required sum k:\t");
	scanf("%d", &k);

	set <node *> dummySet;
	node * dummyNode = createNode(INT_MIN);
	dummySet.insert(dummyNode);
	sumMap[0] = dummySet;

	printf("\nPaths having sum = %d are:-\n", k);
	findKSumPaths(k, 0, root, dummyNode, parMap, sumMap);

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

void findKSumPaths(int k, int crrSum, node * crr, node * par, map <node *, node *>& parMap, map <int, set <node *> >& sumMap) {
	if (crr != NULL) {
		parMap[crr] = par;
		crrSum += crr -> val;

//		printf("\nat node %d\tcrrSum = %d\n", crr -> val, crrSum);

		if (sumMap.find(crrSum) == sumMap.end()) {
			set <node *> newSet;
			newSet.insert(crr);
			sumMap[crrSum] = newSet;
		} else {
			sumMap[crrSum].insert(crr);
		}

		int diffSum = crrSum - k;
		if (sumMap.find(diffSum) != sumMap.end()) {
			for (set <node *>::iterator i = sumMap[diffSum].begin(); i != sumMap[diffSum].end(); i++) {
				//				printf("printing path from %d to here\n", (*i) -> val);
				showPath(parMap, crr, *i);
			}
		}

		findKSumPaths(k, crrSum, crr -> left, crr, parMap, sumMap);
		findKSumPaths(k, crrSum, crr -> right, crr, parMap, sumMap);

		sumMap[crrSum].erase(crr);
	}
}

void showPath(map <node *, node *> parMap, node * src, node * tar) {
	list <int> path;

	for (node * crrNode = src; crrNode != tar; crrNode = parMap[crrNode]) {
		path.push_front(crrNode -> val);
	}

	for (list <int>::iterator i = path.begin(); i != path.end(); i++) {
		printf("%d\t", *i);
	}
	cout << endl;
}

