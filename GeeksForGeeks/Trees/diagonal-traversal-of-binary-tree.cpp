// http://www.geeksforgeeks.org/diagonal-traversal-of-binary-tree/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=700193

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
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <list>

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
void showListRev(node *, const char *);
node * insert(node *, node *, node *);
void createDiagMap(node *, int, map <int, list <int> > &);
void diagOrder(map <int, list <int> >);

int main() {
	node * root;
	map <int, list <int> > diagMap;
	int val, pos;

	printf("\nEnter (val, pos) to insert into tree:-\n(pos starts from 1)\n");
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

	createDiagMap(root, 0, diagMap);
	diagOrder(diagMap);

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

void createDiagMap(node * root, int diagNo, map <int, list <int> > &diagMap) {
	if (root != NULL) {
		if (diagMap.find(diagNo) == diagMap.end()) {
			list <int> tmpList;
			tmpList.push_back(root -> val);
			diagMap.insert(make_pair(diagNo, tmpList));
		} else {
			diagMap[diagNo].push_back(root -> val);
		}

		createDiagMap(root -> left, diagNo + 1, diagMap);
		createDiagMap(root -> right, diagNo, diagMap);
	}
}

void diagOrder(map <int, list <int> > diagMap) {
	if (diagMap.empty()) {
		cout << "\nTree is empty\n";
	} else {
		cout << "\nDiagonal order traversal of tree is:-\n";
		for (map <int, list <int> >::iterator i = diagMap.begin(); i != diagMap.end(); i++) {
			for (list <int>::iterator j = (* i).second.begin(); j != (* i).second.end(); j++) {
				printf("%d ", *j);
			}
			cout << endl;
		}
		cout << endl;
	}
}

