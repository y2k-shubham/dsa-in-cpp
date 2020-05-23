/*
	Perform a single traversal of binary tree and then answer queries for distance between
	any pair of nodes. Assume that nodes are unique.
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
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <list>
#include <utility>

using namespace std;

struct node {
	int val;
	struct node * left;
	struct node * right;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
node * inputTree();
node * insert(node *, node *, node *);
void showList(node *, const char *);

void createMaps(node *, node *, map <node *, node *>&, map <int, node *>&);
void doQueries(node *, map <node *, node *>, map <int, node *>);
list <node *> getPath(map <node *, node *>, node *);
int getCommonPathLen(list <node *>, list <node *>);

int main() {
	node * root;
	map <node *, node *> parent;
	map <int, node *> nodes;

	root = inputTree();

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	createMaps(root, NULL, parent, nodes);
	doQueries(root, parent, nodes);

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

void createMaps(node * crrNode, node * parNode, map <node *, node *>& parent, map <int, node *>& nodes) {
	if (crrNode != NULL) {
		parent.insert(make_pair(crrNode, parNode));
		nodes.insert(make_pair(crrNode -> val, crrNode));

		createMaps(crrNode -> left, crrNode, parent, nodes);
		createMaps(crrNode -> right, crrNode, parent, nodes);
	}
}

void doQueries(node * root, map <node *, node *> parent, map <int, node *> nodes) {
	int ele_1, ele_2;

	printf("\nEnter queries:-\n");
	cin >> ele_1 >> ele_2;

	while (ele_1 != -1 || ele_2 != -1) {
		if (nodes.find(ele_1) == nodes.end() || nodes.find(ele_2) == nodes.end()) {
			printf("Incorrect Query!\n\n");
		} else {
			list <node *> path_1 = getPath(parent, nodes[ele_1]);
			list <node *> path_2 = getPath(parent, nodes[ele_2]);
			int pLen;

			if (path_1.empty() || path_2.empty()) {
				pLen = path_1.size() + path_2.size();
			} else {
				pLen = path_1.size() + path_2.size() - 2 * getCommonPathLen(path_1, path_2);
			}

			printf("Length of path between nodes %d and %d is %d\n\n", ele_1, ele_2, pLen);
		}

		cin >> ele_1 >> ele_2;
	}
}

list <node *> getPath(map <node *, node *> parent, node * crrNode) {
	list <node *> path;

	while (parent[crrNode] != NULL) {
		path.push_front(crrNode);
		crrNode = parent[crrNode];
	}

	return path;
}

int getCommonPathLen(list <node *> path_1, list <node *> path_2) {
	int comPLen = 0;
	list <node *>::iterator i1 = path_1.begin();
	list <node *>::iterator i2 = path_2.begin();

	while ((i1 != path_1.end() && i2 != path_2.end()) && (*i1 == *i2)) {
		i1++;
		i2++;
		comPLen++;
	}

	return comPLen;
}

