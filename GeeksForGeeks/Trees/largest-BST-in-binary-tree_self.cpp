#include <cstdio>
#include <vector>
#include <cmath>

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

5 1
36 2	42 3
47 4	21 5	-8 6	19 7
61 8	75 9	7 13	27 15
54 16	19 17	50 18	100 19	-5 27
90 38	120 39	-6 54	-4 55
110 78	0 111
-1 222
-2 444
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
vector <int> findMaxBST(node *, int &, node * &);
vector <int> createVector(int, int, int);

int main() {
	node * root;
	node * head, * tail;
	int val, pos;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (pos != -1) {
		node * path = getPath(pos);
		root = insert(root, path -> right, createNode(val));

//		showList(path, "path");
//		printf("\nInOrder tree is:-\n");
//		inOrder(root);
//		printf("\n");

		scanf("%d%d", &val, &pos);
	}

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	int maxSize = 0;
	node * maxRoot;
	findMaxBST(root, maxSize, maxRoot);

	printf("\nSize of max BST is %d\n", maxSize);
	printf("The max BST in inOrder is:-\n");
	inOrder(maxRoot);
	printf("\n");

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

vector <int> findMaxBST(node * root, int &maxSize, node * &maxRoot) {
	vector <int> lVec, rVec;

//	printf("here1");
	if (root -> left != NULL) {
		lVec = findMaxBST(root -> left, maxSize, maxRoot);
	} else {
		lVec = createVector(root -> val, root -> val, 0);
	}

//	printf("here2");
	if (root -> right != NULL) {
		rVec = findMaxBST(root -> right, maxSize, maxRoot);
	} else {
		rVec = createVector(root -> val, root -> val, 0);
	}

//	printf("here3");
	if (lVec[1] < root -> val && rVec[0] > root -> val) {
		if (lVec[2] + rVec[2] + 1 > maxSize) {
			maxSize = lVec[2] + rVec[2] + 1;
			maxRoot = root;
		}
	}

//	printf("here4");
	int tmpArr[] = {min(lVec[0], root -> val), max(rVec[1], root -> val), (lVec[2] + rVec[2] + 1)};
	vector <int> tmpVec (tmpArr, tmpArr + 3);

//	printf("here5");
	return tmpVec;
}

vector <int> createVector(int a, int b, int c) {
	vector <int> tmp;
	tmp.push_back(a);
	tmp.push_back(b);
	tmp.push_back(c);
	return tmp;
}
