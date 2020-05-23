// http://www.geeksforgeeks.org/bottom-view-binary-tree/

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
#include <map>

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
void findBottomView(node *, map <int, pair <int, int> > &, int, int);
void showBottomView(map <int, pair <int, int> >);

int main() {
	node * root;
	node * head, * tail;
	int val, pos;
	map <int, pair <int, int> > bottomView;

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

	findBottomView(root, bottomView, 0, 0);
	showBottomView(bottomView);

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

void findBottomView(node * root, map <int, pair <int, int> > &bottomView, int horDist, int depth) {
	if (root != NULL) {
		findBottomView(root -> right, bottomView, horDist + 1, depth + 1);
		findBottomView(root -> left , bottomView, horDist - 1, depth + 1);

		map <int, pair <int, int> >::iterator it = bottomView.find(horDist);

		if (it == bottomView.end()) {
//			printf("added\thorDist = %d\tdepth = %d\troot = %d\n", horDist, depth, root -> val);
			bottomView.insert(make_pair(horDist, make_pair(depth, root -> val)));
		} else if ((it -> second).first < depth) {
//			printf("updat\thorDist = %d\tdepth = %d\troot = %d\n", horDist, depth, root -> val);
			(it -> second).first = depth;
			(it -> second).second = root -> val;
		}
	}
}

void showBottomView(map <int, pair <int, int> > bottomView) {
	printf("\nBottom view of tree is:-\n");
	for (map <int, pair <int, int> >::iterator it = bottomView.begin(); it != bottomView.end(); it++) {
		printf("%d\t", (it -> second).second);
	}
	printf("\n");
}
